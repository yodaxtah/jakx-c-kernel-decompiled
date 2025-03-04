#include "kdgo.h"

#include <cstring>

#include "common/log/log.h"

#include "game/common/dgo_rpc_types.h"
#include "game/common/loader_rpc_types.h"
#include "game/common/play_rpc_types.h"
#include "game/common/player_rpc_types.h"
#include "game/common/ramdisk_rpc_types.h"
#include "game/common/str_rpc_types.h"
#include "game/kernel/common/Ptr.h"
#include "game/kernel/common/kprint.h"
#include "game/sce/sif_ee.h"

ee::sceSifClientData cd[6];  //! client data for each IOP Remove Procedure Call.
u32 sShowStallMsg;           //! setting to show a "stalled on iop" message
u16 x[8];                    //! stupid temporary for storing a message
u32 sMsgNum;                 //! Toggle for double buffered message sending.
s32 numberOfRpcChannels = 7;

void kdgo_init_globals() {
  memset(x, 0, sizeof(x));
  memset(cd, 0, sizeof(cd));
  sShowStallMsg = 1;
}

int RpcCallEndFunction_W(long param_1) {
  if (param_1 != 0) {
    int* args = (int*)param_1;
    if ((code *)args[1] != nullptr) {
      (*(code *)args[1])(args[2], args[3]);
    }
    return iSignalSema(*args);
  } else {
    int in_v0_lo;
    return in_v0_lo;
  }
}

/*!
 * Function overload for the RpcCall with a null callback.
 * TODO: Is this Goal_Wrapper? It is called in C-functions though.
 */
s32 RpcCall(s32 rpcChannel, u32 fno, bool async, void* sendBuff, s32 sendSize, void* recvBuff, s32 recvSize) {
  return RpcCall(rpcChannel, fno, async, sendBuff, sendSize, recvBuff, recvSize, nullptr);
}

/*!
 * Call the given RPC with the given function number and buffers.
 * In Jak X, errors are written out. The conditions have been negated.
 * DONE, EXACT.
 */
s32 RpcCall(s32 rpcChannel,
            u32 fno,
            bool async,
            void* sendBuff,
            s32 sendSize,
            void* recvBuff,
            s32 recvSize,
            void* callback) {
  if (rpcChannel >= numberOfRpcChannels) {
    MsgErr("dkernel: RpcCall() error; invalid port id %d\n", rpcChannel);
  } else if (sendSize >= 0xffff1) {
    MsgErr("dkernel: RpcCall() error; invalid send/receive sizes (ssize=%d rsize=%d)\n", (s32)sendSize, recvSize);
  } else if (!((((uint)sendSize < 0xffff1) && (-1 < recvSize)) && (recvSize < 0xffff1))) {
    MsgErr("dkernel: RpcCall() error; NULL send buffer (secv=0x%08x ssize=%d)\n", (s32)nullptr, sendSize);
  } else if (!(recvSize < 1) || (recvBuff != nullptr)) {
    MsgErr("dkernel: RpcCall() error; NULL receive buffer (recv=0x%08x rsize=%d)\n", (s32)nullptr, recvSize);
  } else if ((uint)sendBuff & 0xf) {
    MsgErr("dkernel: RpcCall() error; misaligned send buffer (send=0x%08x ssize=%d)\n", sendBuff, sendSize); // added missing parenthesis
  } else if ((uint)recvBuff & 0xf) {
    MsgErr("dkernel: RpcCall() error; misaligned receive buffer (recv=0x%08x rsize=%d\n", recvBuff, recvSize);
  } else {
    WaitSema(RpcCallEndFunctionArgs_W[rpcChannel].sema_id);
    RpcCallEndFunctionArgs_W[rpcChannel].callback = callback;
    RpcCallEndFunctionArgs_W[rpcChannel].fourth = 0; // in_stack_00000008;
    RpcCallEndFunctionArgs_W[rpcChannel].third = 0; // in_stack_00000000;
    return SifCallRpc(&cd_G_rpc[rpcChannel], fno, (int)async, sendBuff, sendSize, recvBuff, recvSize, RpcCallEndFunction_W, &RpcCallEndFunctionArgs_W[rpcChannel]);
  }
  return -1;
}

namespace {
struct GoalStackArgs {
  u64 args[8];
  template <typename T>
  T get_as(int i) {
    static_assert(sizeof(T) <= 8, "arg size");
    T result;
    memcpy(&result, args + i, sizeof(T));
    return result;
  }
};
}  // namespace

/*!
 * GOAL Wrapper for RpcCall.
 */
// u64 RpcCall_wrapper(void* _args) {
//   GoalStackArgs* args = (GoalStackArgs*)_args;
//   auto rpcChannel = args->get_as<s32>(0);
//   auto fno = args->get_as<u32>(1);
//   auto async = args->get_as<u32>(2);
//   auto send_buff = args->get_as<u64>(3);
//   auto send_size = args->get_as<s32>(4);
//   auto recv_buff = args->get_as<u64>(5);
//   auto recv_size = args->get_as<s32>(6);
//   return RpcCallProxy(&cd[rpcChannel], fno, async, Ptr<u8>(send_buff).c(), send_size,
//                        Ptr<u8>(recv_buff).c(), recv_size, nullptr, nullptr);
// }

/*!
 * Check if the given RPC is busy, by channel.
 */
u32 RpcBusy(s32 channel) {
  if (channel < numberOfRpcChannels) {
    return sceSifCheckStatRpc(&cd_G_rpc[channel]);
  } else {
    return 1;
  }
}

/*!
 * Wait for an RPC to not be busy. Prints a stall message if sShowStallMsg is true and we have
 * to wait on the IOP.  Stalling here is bad because it means the rest of the game can't run.
 */
void RpcSync(s32 channel) {
  if (6 < (uint)channel) {
    MsgErr("dkernel: RpcSync() error; invalid port id %d\n", channel);
  }
  if (RpcBusy(channel)) {
    if (sShowStallMsg) {
      Msg(6, "dkernel: RpcSync() warning; port #%d stalled; waiting...\n", channel);
    }
    WaitSema(RpcCallEndFunctionArgs_W[channel].sema_id);
    SignalSema(RpcCallEndFunctionArgs_W[channel].sema_id);
    while (RpcBusy(channel)) {
      // an attempt to avoid spamming SIF?
      sceKernelDelayThread_G(10000);
    }
    if (sShowStallMsg) {
      Msg(6, "dkernel: RpcSync(); port #%d acquired\n", channel);
    }
  }
}

/*!
 * Setup an RPC.
 */
s32 RpcBind(s32 channel, s32 id) {
  if (channel < numberOfRpcChannels) {
    bool displayedWarning = false;
    while (true) {
      if (SifBindRpc(&cd_G_rpc[channel], id, 0) < 0) {
        MsgErr("dkernel: RpcBind() error; bind failed on port #%d id 0x%08x\n", channel, id);
        return -1;
      } else if (cd_G_rpc[channel].server != nullptr) {
        MsgErr("dkernel: RpcBind() port #%d id 0x%08x bound\n", channel, id);
        return 0;
      } else if (!displayedWarning) {
        displayedWarning = true;
        MsgErr("dkernel: RpcBind() warning; port #%d id 0x%08x not responding; retrying...\n", channel, id);
      }
      sceKernelDelayThread_G(10000);
    }
  } else {
    MsgErr("dkernel: RpcBind() error; invalid port id %d\n", channel);
    return -1;
  }
}

/*!
 * Setup all RPCs.
 * DONE, EXACT.
 */
s32 InitRPC() {
  s32 sVar1;
  int semaId;
  int iVar3;
  ee_sema_t someSema;
  
  if (RPC_Initialized_G) {
    MsgErr("dkernel: InitRPC() error; multiple initializations attempted");
    return -1;
  } else {
    for (int i = 0; i < numberOfRpcChannels; i++) {
      RpcCallEndFunctionArgs_W[i].fourth = 0;
      RpcCallEndFunctionArgs_W[i].sema_id = -1;
      RpcCallEndFunctionArgs_W[i].callback = nullptr;
      RpcCallEndFunctionArgs_W[i].third = 0;
    }
    for (int i = 0; i < 6; i++) { // FIXME: why is it 6 here? Why is RpcChannels_W of length 6 and RpcCallEndFunctionArgs_W of length 7?
      if (!RpcBind(RpcChannels_W[i].channel, RpcChannels_W[i].id)) {
        return -1;
      }
    }
    for (int i = 0; i < numberOfRpcChannels; i++) {
      memset(&someSema, 0, 0x18); // MACRO
      someSema.init_count = 1;
      someSema.max_count = 1;
      semaId = CreateSema(&someSema);
      RpcCallEndFunctionArgs_W[i].sema_id = semaId;
      if (semaId < 0) {
        for (int j = i; j > 0; --j) {
          DeleteSema(RpcCallEndFunctionArgs_W[j].sema_id);
          RpcCallEndFunctionArgs_W[j].sema_id = -1;
        }
        return -1;
      }
    }
    RPC_Initialized_G = true;
    return 0;
  }
}

/*!
 * Send a message to the IOP to stop it.
 * DONE, EXACT.
 */
int StopIOP_G() {
  if (Is_RPC_Initialized_G() && IOP_RUNNING_W) {
    x[2] = 0x10;
    x[3] = 0;
    // RpcSync(1); // FIXME: PLAYER_RPC_CHANNEL at 1? Previously at 0.
    IOP_RUNNING_W = false;
    return RpcCall(1, 0, false, &x, 0x30, nullptr, 0);
  } else {
    return 0;
  }
}

/*!
 * Load the TEST.DGO file.
 * Presumably used for debugging DGO loads.
 * We don't have the TEST.DGO file, so this isn't very useful.
 *
 * DONE,
 * EXACT,
 * UNUSED
 */
void LoadDGOTest() {
  u32 lastObject = 0;

  // backup show stall message and set it to false
  // EE will be loading DGO in a loop, so it will always be stalling
  // no need to print it.
  bool lastShowStall = setStallMsg_G(false);

  // pick somewhat arbitrary memory to load the DGO into
  BeginLoadingDGO("TEST.DGO", Ptr<u8>(0x4800000), Ptr<u8>(0x4c00000), Ptr<u8>(0x4000000));
  while (true) {
    // keep trying to load.
    Ptr<u8> dest_buffer(0);
    do {
      dest_buffer = GetNextDGO(&lastObject);
    } while (!dest_buffer.offset);

    // print the name of the object we loaded, its destination, and its size.
    Msg(6, "Loaded %s at %8.8X length %d\n", (dest_buffer + 4).cast<char>().c(), dest_buffer.offset,
        *(dest_buffer.cast<u32>()));
    if (lastObject) {
      break;
    }

    // okay to load the next one
    ;
    // so let's be lazy for now...
    ContinueLoadingDGO(Ptr<u8>(0x4800000));
  }

  setStallMsg_G(lastShowStall);
}
