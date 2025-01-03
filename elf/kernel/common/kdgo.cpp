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

void kdgo_init_globals() {
  memset(x, 0, sizeof(x));
  memset(cd, 0, sizeof(cd));
  sShowStallMsg = 1;
}

/*!
 * Call the given RPC with the given function number and buffers.
 */

s32 RpcCallProxy(s32 rpcChannel,u32 fno,bool async,void* sendBuff,s32 sendSize,void* recvBuff,
                s32 recvSize) {
  s32 sVar1;
  
  sVar1 = RpcCall(rpcChannel,fno,async,sendBuff,sendSize,recvBuff,recvSize,(void *)0x0);
  return sVar1;
}

s32 RpcCall(s32 rpcChannel,u32 fno,bool async,void* sendBuff,s32 sendSize,void* recvBuff,
           s32 recvSize,void* callback) {
  int iVar1;
  char* format;
  int in_stack_00000000;
  int in_stack_00000008;
  
  if ((uint)rpcChannel < 7) {
    if ((((uint)sendSize < 0xffff1) && (-1 < recvSize)) && (recvSize < 0xffff1)) {
      if ((sendSize < 1) || (sendBuff != (void *)0x0)) {
        if ((recvSize < 1) || (recvBuff != (void *)0x0)) {
          if (((uint)sendBuff & 0xf) == 0) {
            if (((uint)recvBuff & 0xf) == 0) {
              WaitSema(RpcCallEndFunctionArgs_W[rpcChannel].sema_id);
              RpcCallEndFunctionArgs_W[rpcChannel].callback = callback;
              RpcCallEndFunctionArgs_W[rpcChannel].fourth = in_stack_00000008;
              RpcCallEndFunctionArgs_W[rpcChannel].third = in_stack_00000000;
              iVar1 = SifCallRpc(cd_G_rpc + rpcChannel,fno,(int)async,sendBuff,sendSize,recvBuff,
                                 recvSize,RpcCallEndFunction_W,RpcCallEndFunctionArgs_W + rpcChannel
                                );
              return iVar1;
            }
            format = "dkernel: RpcCall() error; misaligned receive buffer (recv=0x%08x rsize=%d\n";
          }
          else {
            format = "dkernel: RpcCall() error; misaligned send buffer (send=0x%08x ssize=%d\n";
            recvBuff = sendBuff;
            recvSize = sendSize;
          }
        }
        else {
          recvBuff = (void *)0x0;
          format = "dkernel: RpcCall() error; NULL receive buffer (recv=0x%08x rsize=%d)\n";
        }
      }
      else {
        recvBuff = (void *)0x0;
        format = "dkernel: RpcCall() error; NULL send buffer (send=0x%08x ssize=%d)\n";
        recvSize = sendSize;
      }
    }
    else {
      format = "dkernel: RpcCall() error; invalid send/receive sizes (ssize=%d rsize=%d)\n";
      recvBuff = (void *)sendSize;
    }
    MsgErr(format,(s32)recvBuff,recvSize);
  }
  else {
    MsgErr("dkernel: RpcCall() error; invalid port id %d\n",rpcChannel);
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
  int iVar1;
  uint uVar2;
  
  uVar2 = 1;
  if ((uint)channel < 7) {
    iVar1 = SifCheckStatRpc(cd_G_rpc + channel);
    uVar2 = (uint)(iVar1 != 0);
  }
  return uVar2;
}

/*!
 * Wait for an RPC to not be busy. Prints a stall message if sShowStallMsg is true and we have
 * to wait on the IOP.  Stalling here is bad because it means the rest of the game can't run.
 */
void RpcSync(s32 channel) {
  u32 uVar1;
  
  if (6 < (uint)channel) {
    MsgErr("dkernel: RpcSync() error; invalid port id %d\n",channel);
    return;
  }
  uVar1 = RpcBusy(channel);
  if (uVar1 != 0) {
    if (sShowStallMsg != '\0') {
      Msg(6,"dkernel: RpcSync() warning; port #%d stalled; waiting...\n",channel);
    }
    WaitSema(RpcCallEndFunctionArgs_W[channel].sema_id);
    SignalSema(RpcCallEndFunctionArgs_W[channel].sema_id);
    while (uVar1 = RpcBusy(channel), uVar1 != 0) {
      sceKernelDelayThread_G(10000);
    }
    if (sShowStallMsg != '\0') {
      Msg(6,"dkernel: RpcSync(); port #%d acquired\n",channel);
      return;
    }
  }
  return;
}

/*!
 * Setup an RPC.
 */
s32 RpcBind(s32 channel,s32 id) {
  bool bVar1;
  int iVar2;
  
  if ((uint)channel < 7) {
    bVar1 = false;
    while( true ) {
      iVar2 = SifBindRpc(cd_G_rpc + channel,id,0);
      if (iVar2 < 0) break;
      if (cd_G_rpc[channel].server != (SifRpcServerData_t *)0x0) {
        MsgErr("dkernel: RpcBind() port #%d id 0x%08x bound\n",channel,id);
        return 0;
      }
      if (!bVar1) {
        bVar1 = true;
        MsgErr("dkernel: RpcBind() warning; port #%d id 0x%08x not responding; retrying...\n",
               channel,id);
      }
      sceKernelDelayThread_G(10000);
    }
    MsgErr("dkernel: RpcBind() error; bind failed on port #%d id 0x%08x\n",channel,id);
  }
  else {
    MsgErr("dkernel: RpcBind() error; invalid port id %d\n",channel);
  }
  return -1;
}

/*!
 * Setup all RPCs
 */
s32 InitRPC() {
  s32 sVar1;
  int iVar2;
  int iVar3;
  ee_sema_t eStack_40;
  
  if (RPC_Initialized_G == '\0') {
    iVar3 = 0;
    do {
      iVar2 = iVar3 + 1;
      RpcCallEndFunctionArgs_W[iVar3].fourth = 0;
      RpcCallEndFunctionArgs_W[iVar3].sema_id = -1;
      RpcCallEndFunctionArgs_W[iVar3].callback = (void *)0x0;
      RpcCallEndFunctionArgs_W[iVar3].third = 0;
      iVar3 = iVar2;
    } while (iVar2 < 7);
    iVar3 = 0;
    do {
      iVar2 = iVar3 + 1;
      sVar1 = RpcBind(RpcChannels_W[iVar3].channel,RpcChannels_W[iVar3].id);
      if (sVar1 != 0) {
        return -1;
      }
      iVar3 = iVar2;
    } while (iVar2 < 6);
    iVar3 = 0;
    while( true ) {
      memset(&eStack_40,0,0x18);
      eStack_40.init_count = 1;
      eStack_40.max_count = 1;
      iVar2 = CreateSema(&eStack_40);
      RpcCallEndFunctionArgs_W[iVar3].sema_id = iVar2;
      if (iVar2 < 0) break;
      iVar3 = iVar3 + 1;
      if (6 < iVar3) {
        RPC_Initialized_G = 1;
        return 0;
      }
    }
    while (iVar3 = iVar3 + -1, -1 < iVar3) {
      DeleteSema(RpcCallEndFunctionArgs_W[iVar3].sema_id);
      RpcCallEndFunctionArgs_W[iVar3].sema_id = -1;
    }
  }
  else {
    MsgErr("dkernel: InitRPC() error; multiple initializations attempted");
  }
  return -1;
}

/*!
 * Send a message to the IOP to stop it.
 */
int StopIOP_G() {
  int iVar1;
  
  iVar1 = Is_RPC_Initialized_G();
  if ((iVar1 != 0) && (IOP_RUNNING_W != '\0')) {
    DAT_002d2d82 = 0x10;
    RpcSync(1);
    iVar1 = RpcCallProxy(1,0,false,&DAT_002d2d80,0x30,(void *)0x0,0);
    IOP_RUNNING_W = '\0';
  }
  return iVar1;
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
  undefined4 *puVar1;
  undefined8 uVar2;
  u32 local_20 [4];
  
  local_20[0] = 0;
  uVar2 = setStallMsg_G(0);
  BeginLoadingDGO("TEST.DGO",(u8 *)0x4800000,(u8 *)0x4c00000,(u8 *)0x4000000);
  while( true ) {
    do {
      puVar1 = (undefined4 *)GetNextDGO(local_20);
    } while (puVar1 == (undefined4 *)0x0);
    Msg(6,"Loaded %s at %8.8X length %d\n",puVar1 + 1,puVar1,*puVar1);
    if (local_20[0] != 0) break;
    ContinueLoadingDGO((u8 *)0x4800000);
  }
  setStallMsg_G(uVar2,0x4c00000,0x4000000);
  return;
}
