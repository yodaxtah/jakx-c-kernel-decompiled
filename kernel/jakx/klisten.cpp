#include "klisten.h"

#include "common/symbols.h"

#include "game/kernel/common/Ptr.h"
#include "game/kernel/common/Symbol4.h"
#include "game/kernel/common/kdsnetm.h"
#include "game/kernel/common/klink.h"
#include "game/kernel/common/klisten.h"
#include "game/kernel/common/kmalloc.h"
#include "game/kernel/common/kprint.h"
#include "game/kernel/common/kscheme.h"
#include "game/kernel/jak3/klink.h"
#include "game/kernel/jak3/kscheme.h"

namespace jak3 {

using namespace jak3_symbols;

Ptr<Symbol4<u32>> ListenerLinkBlock;
Ptr<Symbol4<u32>> ListenerFunction;
Ptr<Symbol4<u32>> KernelFunction;  // new in jak2
Ptr<Symbol4<u32>> kernel_dispatcher;
Ptr<Symbol4<u32>> kernel_packages;
Ptr<Symbol4<u32>> sync_dispatcher;

void klisten_init_globals() {
  ListenerLinkBlock.offset = 0;
  ListenerFunction.offset = 0;
  KernelFunction.offset = 0;
  kernel_dispatcher.offset = 0;
  kernel_packages.offset = 0;
  sync_dispatcher.offset = 0;
}

/*!
 * Initialize the Listener by setting up symbols shared between GOAL and C for the listener.
 * Also adds "kernel" to the kernel_packages list.
 * There was an "ACK" message sent here, but this is removed because we don't need it.
 */
void InitListener(void)

{
  u32 *puVar1;
  u32 *puVar2;
  String *car;
  u64 uVar3;
  int unaff_s7_lo;
  
  ListenerLinkBlock = intern_from_c(-1,0,"*listener-link-block*");
  ListenerFunction = intern_from_c(-1,0,"*listener-function*");
  KernelFunction = intern_from_c(-1,0,"*kernel-function*");
  kernel_dispatcher = intern_from_c(-1,0,"kernel-dispatcher");
  sync_dispatcher = intern_from_c(-1,0,"sync-dispatcher");
  kernel_packages = intern_from_c(-1,0,"*kernel-packages*");
  print_column = intern_from_c(-1,0,"*print-column*");
  puVar1 = ListenerFunction;
  *(int *)((int)ListenerLinkBlock + -1) = unaff_s7_lo;
  puVar2 = KernelFunction;
  *(int *)((int)puVar1 + -1) = unaff_s7_lo;
  *(int *)((int)puVar2 + -1) = unaff_s7_lo;
  puVar1 = kernel_packages;
  car = make_string_from_c("kernel");
  uVar3 = new_pair(unaff_s7_lo + 0xa0,*(u32 *)(unaff_s7_lo + 0x6f),(u32)car,
                   *(u32 *)((int)kernel_packages + -1));
  *(int *)((int)puVar1 + -1) = (int)uVar3;
  if (MasterDebug != 0) {
    SendFromBufferD(0,0,&AckBufArea,0);
    return;
  }
  return;
}

/*!
 * Handle an incoming listener message
 */
void ProcessListenerMessage(char *msg)

{
  kheapinfo *heap;
  s32 sVar1;
  u32 uVar2;
  u8 *data;
  uint8_t *puVar3;
  undefined in_t1_lo;
  ulong uVar4;
  size_t __n;
  int unaff_s7_lo;
  undefined4 unaff_s7_hi;
  
  sVar1 = MessCount;
  ListenerStatus = 1;
  if (false) {
switchD_00270650_caseD_2:
    MsgErr("dkernel: unknown message error: <%d> of %d bytes\n",protoBlock.field57_0x48,MessCount);
  }
  else {
    switch(protoBlock.field57_0x48) {
    case 1:
      break;
    default:
      goto switchD_00270650_caseD_2;
    case 5:
      uVar2 = atoi(msg);
      inspect_object(uVar2);
      break;
    case 6:
      uVar2 = atoi(msg);
      print_object(uVar2);
      break;
    case 7:
      uVar4 = CONCAT44(unaff_s7_hi,unaff_s7_lo);
      if (CONCAT44(unaff_s7_hi,unaff_s7_lo) < (ulong)(long)LastSymbol) {
        do {
          uVar2 = (u32)uVar4;
          if (*(int *)((uVar2 - unaff_s7_lo) + SymbolString) != 0) {
            inspect_object(uVar2);
          }
          uVar4 = (ulong)(int)(uVar2 + 4);
        } while (uVar4 < (ulong)(long)LastSymbol);
      }
      uVar4 = (ulong)SymbolTable2;
      if (uVar4 < CONCAT44(unaff_s7_hi,unaff_s7_lo)) {
        do {
          uVar2 = (u32)uVar4;
          if (*(int *)((uVar2 - unaff_s7_lo) + SymbolString) != 0) {
            inspect_object(uVar2);
          }
          uVar4 = (ulong)(int)(uVar2 + 4);
        } while (uVar4 < CONCAT44(unaff_s7_hi,unaff_s7_lo));
      }
      break;
    case 8:
      KernelShutdown(1);
      goto LAB_00270664;
    case 9:
      __n = (size_t)MessCount;
      data = kmalloc(kdebugheap,MessCount,0,"listener-link-buf");
      memcpy(data,msg,__n);
      heap = kdebugheap;
      *(u8 **)(ListenerLinkBlock + -1) = data + 4;
      puVar3 = link_and_exec(data,"*listener*",sVar1 - *(int *)(data + 4),heap,0x10,(bool)in_t1_lo);
      *(uint8_t **)(ListenerFunction + -1) = puVar3;
      return;
    }
    ClearPending();
  }
LAB_00270664:
  SendAck();
  return;
}

int sql_query_sync(String *string_in)

{
  int iVar1;
  int unaff_s7_lo;
  undefined4 unaff_s7_hi;
  
  if (MasterDebug == 0) {
    iVar1 = unaff_s7_lo + -7;
  }
  else {
    *(int *)(SqlResult + -1) = unaff_s7_lo;
    output_sql_query(string_in + 1);
    *(int *)(ListenerFunction + -1) = unaff_s7_lo;
    ListenerStatus = 1;
    ClearPending();
    SendAck();
    iVar1 = *(int *)(ListenerFunction + -1);
    kdebugheap->top = kdebugheap->top + -0x4000;
    if ((long)iVar1 == CONCAT44(unaff_s7_hi,unaff_s7_lo)) {
      while ((long)*(int *)(SqlResult + -1) == CONCAT44(unaff_s7_hi,unaff_s7_lo)) {
        KernelDispatch(*(u32 *)(sync_dispatcher + -1));
        SendAck();
        if ((long)*(int *)(SqlResult + -1) == CONCAT44(unaff_s7_hi,unaff_s7_lo)) {
          iVar1 = 0;
          do {
            iVar1 = iVar1 + 1;
          } while (iVar1 < 100000);
        }
      }
    }
    iVar1 = *(int *)(SqlResult + -1);
    kdebugheap->top = kdebugheap->top + 0x4000;
  }
  return iVar1;
}

}  // namespace jak3
