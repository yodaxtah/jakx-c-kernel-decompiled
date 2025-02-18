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
void BeginLoadingDGO(const char* name, u8* buffer1, u8* buffer2, u8* currentHeap) {
  uint msgID = sMsgNum;
  RPC_Dgo_Cmd* mess = sMsg + sMsgNum;
  sMsgNum = sMsgNum ^ 1;
  RpcSync(4);

  sMsg[msgID].result = 0x29a; // why is this result? Swap with status?

  sMsg[msgID].buffer1 = (uint32_t)buffer1;
  sMsg[msgID].buffer2 = (uint32_t)buffer2;

  sMsg[msgID].buffer_heap_top = (uint32_t)currentHeap;

  sMsg[msgID].cgo_id = cgo_id;
  cgo_id++;

  strcpy(sMsg[msgID].name, name);
  RpcCallNoCallback(4, 0, true, mess, 0x40, mess,
          0x40);
  sLastMsg = mess;
}

/*!
 * Get the next object in the DGO.  Will block until something is loaded.
 * @param lastObjectFlag: will get set to 1 if this is the last object.
 *
 * DONE,
 * MODIFIED : added exception if the sLastMessage isn't set (game just returns null as buffer)
 */
u8* GetNextDGO(u32* lastObjectFlag) {
  *lastObjectFlag = 1;
  RpcSync(4);
  u8* buffer = nullptr;
  if (sLastMsg != nullptr) {
    if (sLastMsg->result == 2 || sLastMsg->result == 0) { // Should be status
      buffer =
          (u8 *)sLastMsg->buffer1;
    }

    if (sLastMsg->result == 2) { // Should be status
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
void ContinueLoadingDGO(u8 b1, u8* b2, u8* heapPtr) {
  u32 msgID = sMsgNum;
  RPC_Dgo_Cmd* sendBuff = sMsg + sMsgNum;
  sMsgNum = sMsgNum ^ 1;
  sMsg[msgID].result = 0x29a; // Should be status
  sMsg[msgID].buffer1 = (int)(char)b1;
  sMsg[msgID].buffer2 = (uint32_t)b2;
  sendBuff->buffer_heap_top = (uint32_t)heapPtr;
  RpcCallNoCallback(4, 1, true, sendBuff, 0x40,
          sendBuff, 0x40);
  sLastMsg = sendBuff;
}
/*!
 * Load and link a DGO file.
 * This does not use the mutli-threaded linker and will block until the entire file is done.
 */
void load_and_link_dgo(u64 name_gstr, u64 heap_info, u64 flag, u64 buffer_size) {
  const char* name = (const char*)((int)name_gstr + 4);
  kheapinfo* heap = (kheapinfo*)heap_info;
  load_and_link_dgo_from_c(name, heap, (u32)flag, (s32)buffer_size, false);
}

/*!
 * Load and link a DGO file.
 * This does not use the mutli-threaded linker and will block until the entire file is done.e
 */
void load_and_link_dgo_from_c(const char* name,
                              kheapinfo* heap,
                              u32 linkFlag,
                              s32 bufferSize,
                              bool jump_from_c_to_goal) {
  u8* oldHeapTop = heap->top;

  u8* buffer2 = kmalloc(heap, bufferSize, 0x2040, "dgo-buffer-2");
  u8* buffer1 = kmalloc(heap, bufferSize, 0x2040, "dgo-buffer-2");
  
  undefined fileName_a8; // TBD
  char fileName_b4 [4];
  char fileName_b0 [8];
  kstrcpyup(fileName_b0, name);
  if (fileName_b4[(int)strlen(fileName_b0)] != '.') {
    fileName_a8 = 0;
    strcat(fileName_b0, ".CGO");
  }

  bool oldShowStall = setStallMsg_GW(false);

  if (POWERING_OFF_W == false) {
    BeginLoadingDGO(
      acStack_b0, buffer1, buffer2,
      (u8*)((uint)(heap->current + 0x3f) & 0xffffffc0));

    u32 lastObjectLoaded = 0;
    while (true) { // TBD
      int32_t* dgoObj;
      do {
        if ((lastObjectLoaded != 0) || (POWERING_OFF_W != false)) {
          goto LAB_00270d58; // TBD
        }
        dgoObj = (int32_t *)GetNextDGO(&lastObjectLoaded);
      } while (dgoObj == nullptr);

      if (lastObjectLoaded != 0) {
        heap->top = oldHeapTop;
      }

      FUN_0027cc90_patch(dgoObj, bufferSize);

      uint8_t* obj = (uint8_t*)(dgoObj + 0x10);
      u32 objSize = *dgoObj;

      char objName[64];
      strcpy(objName, (char *)(dgoObj + 1));
      undefined in_t1_lo;
      link_and_exec(obj, objName, objSize, heap, linkFlag, (bool)in_t1_lo);
      if (lastObjectLoaded != 0) {
        break;
      }
      if (POWERING_OFF_W == false) {
        ContinueLoadingDGO((u8)buffer1, buffer2, (u8 *)((uint)(heap->current + 0x3f) & 0xffffffc0));
      }
    }
  }
LAB_00270d58: // TBD
  if (POWERING_OFF_W == false) {
    setStallMsg_GW(oldShowStall);
    return;
  } else {
    KernelShutdown(3);
    ShutdownMachine(3);
    Msg(6, "load_and_link_dgo_from_c: cannot continue; load aborted\n");
    do {
                      /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
}

}  // namespace jak3
