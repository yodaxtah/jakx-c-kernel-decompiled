#include "kdgo.h"

#include "common/global_profiler/GlobalProfiler.h"
#include "common/log/log.h"
#include "common/util/Timer.h"

#include "game/kernel/common/fileio.h"
#include "game/kernel/common/kdgo.h"
#include "game/kernel/common/kmalloc.h"
#include "game/kernel/jak3/klink.h"
#include "game/overlord/jak3/rpc_interface.h"

namespace jak3 {

jak3::RPC_Dgo_Cmd* sLastMsg;  //! Last DGO command sent to IOP
jak3::RPC_Dgo_Cmd sMsg[2];    //! DGO message buffers
uint16_t cgo_id = 10;

void kdgo_init_globals() {
  sLastMsg = nullptr;
  memset(sMsg, 0, sizeof(sMsg));
  cgo_id = 10;
}

/*!
 * Send message to IOP to start loading a new DGO file
 * Uses a double-buffered message buffer
 * @param name: the name of the DGO file
 * @param buffer1 : one of the two file loading buffers
 * @param buffer2 : the other of the two file loading buffers
 * @param currentHeap : the current heap (for loading directly into the heap).
 *
 * DONE,
 * MODIFIED : Added print statement to indicate when DGO load starts.
 */
void BeginLoadingDGO(const char* name, Ptr<u8> buffer1, Ptr<u8> buffer2, Ptr<u8> currentHeap) {
  uint msgID = sMsgNum;
  RPC_Dgo_Cmd* mess = sMsg + sMsgNum;
  sMsgNum = sMsgNum ^ 1;
  RpcSync(DGO_RPC_CHANNEL_PLUS_1);

  sMsg[msgID].status = DGO_RPC_RESULT_INIT;

  sMsg[msgID].buffer1 = (uint32_t)buffer1.offset;
  sMsg[msgID].buffer2 = (uint32_t)buffer2.offset;

  sMsg[msgID].buffer_heap_top = (uint32_t)currentHeap.offset;

  sMsg[msgID].cgo_id = cgo_id;
  cgo_id++;

  strcpy(sMsg[msgID].name, name);
  RpcCallNoCallback(DGO_RPC_CHANNEL_PLUS_1, DGO_RPC_LOAD_FNO, true, mess, sizeof(RPC_Dgo_Cmd), mess,
          sizeof(RPC_Dgo_Cmd));
  sLastMsg = mess;
}

/*!
 * Get the next object in the DGO.  Will block until something is loaded.
 * @param lastObjectFlag: will get set to 1 if this is the last object.
 *
 * DONE,
 * MODIFIED : added exception if the sLastMessage isn't set (game just returns null as buffer)
 */
Ptr<u8> GetNextDGO(u32* lastObjectFlag) {
  *lastObjectFlag = 1;
  RpcSync(DGO_RPC_CHANNEL_PLUS_1);
  Ptr<u8> buffer(0);
  if (sLastMsg) {
    if ((sLastMsg->status == DGO_RPC_RESULT_MORE) || (sLastMsg->status == DGO_RPC_RESULT_DONE)) {
      buffer.offset =
          (u8 *)sLastMsg->buffer1;
    }

    if (sLastMsg->status == DGO_RPC_RESULT_MOR) {
      *lastObjectFlag = 0;
    }

    sLastMsg = nullptr;
  }
  return buffer;
}

/*!
 * Instruct the IOP to continue loading the next object.
 * Only should be called once it is safe to overwrite the previous.
 * @param heapPtr : pointer to heap so the IOP could try to load directly into a heap if it wants.
 * This should be updated after each object file load to make sure the IOP knows the exact location
 * of the end of the GOAL heap data.
 *
 * Unlike jak 1, we update buffer1 and buffer2 here for borrow heap loads.
 */
void ContinueLoadingDGO(Ptr<u8> b1, Ptr<u8> b2, Ptr<u8> heapPtr) {
  u32 msgID = sMsgNum;
  jak3::RPC_Dgo_Cmd* sendBuff = sMsg + sMsgNum;
  sMsgNum = sMsgNum ^ 1;
  sMsg[msgID].status = DGO_RPC_RESULT_INIT;
  sMsg[msgID].buffer1 = b1.offset;
  sMsg[msgID].buffer2 = b2.offset;
  sendBuff->buffer_heap_top = heapPtr.offset;
  RpcCallNoCallback(DGO_RPC_CHANNEL_PLUS_1, DGO_RPC_LOAD_NEXT_FNO, true, sendBuff, sizeof(jak3::RPC_Dgo_Cmd),
          sendBuff, sizeof(jak3::RPC_Dgo_Cmd));
  sLastMsg = sendBuff;
}
/*!
 * Load and link a DGO file.
 * This does not use the mutli-threaded linker and will block until the entire file is done.
 */
void load_and_link_dgo(u64 name_gstr, u64 heap_info, u64 flag, u64 buffer_size) {
  const char* name = Ptr<char>((int)name_gstr + 4).c();
  Ptr<kheapinfo> heap = Ptr<kheapinfo>(heap_info);
  load_and_link_dgo_from_c(name, heap, (u32)flag, (s32)buffer_size, false);
}

/*!
 * Load and link a DGO file.
 * This does not use the mutli-threaded linker and will block until the entire file is done.e
 */
void load_and_link_dgo_from_c(const char* name,
                              Ptr<kheapinfo> heap,
                              u32 linkFlag,
                              s32 bufferSize,
                              bool jump_from_c_to_goal) {
  u8* oldHeapTop = heap->top;

  u8* buffer2 = kmalloc(heap, bufferSize, KMALLOC_TOP | KMALLOC_ALIGN_64, "dgo-buffer-2");
  u8* buffer1 = kmalloc(heap, bufferSize, KMALLOC_TOP | KMALLOC_ALIGN_64, "dgo-buffer-2");

  char fileName[16];
  kstrcpyup(fileName + 4, name); // TODO: This is different because the prefix is DGO_ maybe?
  if ((fileName + 12)[(int)strlen(fileName + 4)] != '.') { // FIXME: How does this match len(name) - 4?
    fileName = '\0';
    strcat(fileName + 4, ".CGO");
  }

  bool oldShowStall = setStallMsg_GW(false);

  if (!POWERING_OFF_W) {
    BeginLoadingDGO(
      acStack_b0, buffer1, buffer2,
      Ptr<u8>((uint)(heap->current + 0x3f).offset & 0xffffffc0));

    u32 lastObjectLoaded = 0;
    while (!lastObjectLoaded && !POWERING_OFF_W) { // TBD
      Ptr<u8> dgoObj = GetNextDGO(&lastObjectLoaded);
      if (!dgoObj.offset) {
        continue;
      }

      if (lastObjectLoaded) {
        heap->top = oldHeapTop;
      }

      FUN_0027cc90_patch(dgoObj, bufferSize);

      Ptr<u8> obj = dgoObj + 0x40;
      u32 objSize = *(dgoObj.cast<u32>());

      char objName[64];
      strcpy(objName, (dgoObj + 4).cast<char>().c());
      ;
      {
        undefined in_t1_lo;
        link_and_exec(obj, objName, objSize, heap, linkFlag, (bool)in_t1_lo);
      }

      if (lastObjectLoaded) {
        break;
      }
      if (POWERING_OFF_W == false) {
        ContinueLoadingDGO((u8)buffer1, buffer2, Ptr<u8>((uint)(heap->current + 0x3f) & 0xffffffc0));
      }
    }
  }

  if (!POWERING_OFF_W) {
    setStallMsg_GW(oldShowStall);
  } else {
    KernelShutdown(3);
    ShutdownMachine(3);
    Msg(6, "load_and_link_dgo_from_c: cannot continue; load aborted\n");
    while (true) {
      ; /* WARNING: Do nothing block with infinite loop */
    }
  }
}

}  // namespace jak3
