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
void BeginLoadingDGO(const_char *name,u8 *buffer1,u8 *buffer2,u8 *currentHeap) {
  int iVar1;
  undefined *sendBuff;
  
  iVar1 = sMsgNum * 0x40;
  sendBuff = &sMsg + iVar1;
  sMsgNum = sMsgNum ^ 1;
  RpcSync(4);
  *(undefined2 *)(&DAT_002d3082 + iVar1) = 0x29a;
  *(int *)(&DAT_002d30a0 + iVar1) = cgo_id;
  *(u8 **)(&DAT_002d3084 + iVar1) = buffer1;
  *(u8 **)(&DAT_002d3088 + iVar1) = buffer2;
  cgo_id = cgo_id + 1;
  *(u8 **)(&DAT_002d308c + iVar1) = currentHeap;
  strcpy((char *)(iVar1 + 0x2d3090),name);
  RpcCallProxy(4,0,true,sendBuff,0x40,sendBuff,0x40);
  sLastMsg = sendBuff;
  return;
}

/*!
 * Get the next object in the DGO.  Will block until something is loaded.
 * @param lastObjectFlag: will get set to 1 if this is the last object.
 *
 * DONE,
 * MODIFIED : added exception if the sLastMessage isn't set (game just returns null as buffer)
 */
u8 * GetNextDGO(u32 *lastObjectFlag) {
  u8 *puVar1;
  
  *lastObjectFlag = 1;
  puVar1 = (u8 *)0x0;
  RpcSync(4);
  if (sLastMsg != 0) {
    if (*(short *)(sLastMsg + 2) == 2) {
      puVar1 = *(u8 **)(sLastMsg + 4);
    }
    else if (*(short *)(sLastMsg + 2) == 0) {
      puVar1 = *(u8 **)(sLastMsg + 4);
    }
    if (*(short *)(sLastMsg + 2) == 2) {
      *lastObjectFlag = 0;
    }
    sLastMsg = 0;
  }
  return puVar1;
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
void ContinueLoadingDGO(u8 *heapPtr) {
  undefined4 in_a1_lo;
  undefined4 in_a2_lo;
  int iVar1;
  undefined *sendBuff;
  
  iVar1 = sMsgNum * 0x40;
  sMsgNum = sMsgNum ^ 1;
  sendBuff = &sMsg + iVar1;
  *(undefined4 *)(&DAT_002d308c + iVar1) = in_a2_lo;
  *(undefined2 *)(&DAT_002d3082 + iVar1) = 0x29a;
  *(u8 **)(&DAT_002d3084 + iVar1) = heapPtr;
  *(undefined4 *)(&DAT_002d3088 + iVar1) = in_a1_lo;
  RpcCallProxy(4,1,true,sendBuff,0x40,sendBuff,0x40);
  sLastMsg = sendBuff;
  return;
}

/*!
 * Load and link a DGO file.
 * This does not use the mutli-threaded linker and will block until the entire file is done.
 */
void load_and_link_dgo(u64 name_gstr,u64 heap_info,u64 flag,u64 buffer_size)
{
  bool in_t0_lo;
  
  load_and_link_dgo_from_c((const_char *)((int)name_gstr + 4),(kheapinfo *)heap_info,(u32)flag,(s32)buffer_size,in_t0_lo);
  return;
}

/*!
 * Load and link a DGO file.
 * This does not use the mutli-threaded linker and will block until the entire file is done.e
 */
void load_and_link_dgo_from_c(const_char *name,kheapinfo *heap,u32 linkFlag,s32 bufferSize, bool jump_from_c_to_goal) {
  u8 *buffer2;
  u8 *buffer1;
  int32_t *piVar1;
  size_t sVar2;
  undefined in_t1_lo;
  char acStack_b4 [4];
  char acStack_b0 [8];
  undefined local_a8;
  char acStack_90 [64];
  u32 local_50;
  u32 local_4c;
  u8 *local_48;
  undefined4 local_44;
  
  local_48 = heap->top;
  local_4c = linkFlag;
  buffer2 = kmalloc(heap,bufferSize,0x2040,"dgo-buffer-2");
  buffer1 = kmalloc(heap,bufferSize,0x2040,"dgo-buffer-2");
  local_50 = 0;
  kstrcpyup(acStack_b0,name);
  sVar2 = strlen(acStack_b0);
  if (acStack_b4[(int)sVar2] != '.') {
    local_a8 = 0;
    strcat(acStack_b0,".CGO");
  }
  local_44 = setStallMsg_G(0);
  if (POWERING_OFF_W == false) {
    BeginLoadingDGO(acStack_b0,buffer1,buffer2,(u8 *)((uint)(heap->current + 0x3f) & 0xffffffc0));
    while( true ) {
      do {
        if ((local_50 != 0) || (POWERING_OFF_W != false)) goto LAB_00270d58;
        piVar1 = (int32_t *)GetNextDGO(&local_50);
      } while (piVar1 == (int32_t *)0x0);
      if (local_50 != 0) {
        heap->top = local_48;
      }
      FUN_0027cc90_patch(piVar1,bufferSize);
      strcpy(acStack_90,(char *)(piVar1 + 1));
      link_and_exec((uint8_t *)(piVar1 + 0x10),acStack_90,*piVar1,heap,local_4c,(bool)in_t1_lo);
      if (local_50 != 0) break;
      if (POWERING_OFF_W == false) {
        ContinueLoadingDGO(buffer1);
      }
    }
  }
LAB_00270d58:
  if (POWERING_OFF_W == false) {
    setStallMsg_G(local_44);
    return;
  }
  KernelShutdown(3);
  ShutdownMachine(3);
  Msg(6,"load_and_link_dgo_from_c: cannot continue; load aborted\n");
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}

}  // namespace jak3
