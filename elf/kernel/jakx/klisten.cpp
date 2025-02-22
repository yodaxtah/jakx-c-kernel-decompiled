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
void InitListener() {
  ListenerLinkBlock = intern_from_c(-1, 0, "*listener-link-block*");
  ListenerFunction = intern_from_c(-1, 0, "*listener-function*");
  KernelFunction = intern_from_c(-1, 0, "*kernel-function*");
  kernel_dispatcher = intern_from_c(-1, 0, "kernel-dispatcher");
  sync_dispatcher = intern_from_c(-1, 0, "sync-dispatcher");
  kernel_packages = intern_from_c(-1, 0, "*kernel-packages*");
  print_column = intern_from_c(-1, 0, "*print-column*");
  int unaff_s7_lo;
  *(int *)((int)ListenerLinkBlock - 1) = unaff_s7_lo;
  *(int *)((int)ListenerFunction - 1) = unaff_s7_lo;
  *(int *)((int)KernelFunction - 1) = unaff_s7_lo;

  *(int *)((int)kernel_packages - 1) =
      new_pair(unaff_s7_lo + 0xa0, *(u32 *)(unaff_s7_lo + 0x6f),
               (u32)make_string_from_c("kernel"), *(u32 *)((int)kernel_packages - 1));
  //  if (MasterDebug != 0) {
  //    SendFromBufferD(0, 0, &AckBufArea, 0);
  //  }
}

/*!
 * Handle an incoming listener message
 */
void ProcessListenerMessage(char* msg) {
  ListenerStatus = 1;
  switch (protoBlock.msg_kind) {
    case 1:
      ClearPending();
      break;
    case 5:
      inspect_object(atoi(msg));
      ClearPending();
      break;
    case 6:
      print_object(atoi(msg));
      ClearPending();
      break;
    case 7:
      // TBD
      undefined4 unaff_s7_hi;
      int unaff_s7_lo;
      ulong uVar4 = CONCAT44(unaff_s7_hi,unaff_s7_lo);
      if (CONCAT44(unaff_s7_hi,unaff_s7_lo) < (ulong)(long)LastSymbol) {
        do {
          u32 uVar2 = (u32)uVar4;
          if (*(int *)((uVar2 - unaff_s7_lo) + SymbolString) != 0) {
            inspect_object(uVar2);
          }
          uVar4 = (ulong)(int)(uVar2 + 4);
        } while (uVar4 < (ulong)(long)LastSymbol);
      }
      uVar4 = (ulong)SymbolTable2;
      if (uVar4 < CONCAT44(unaff_s7_hi,unaff_s7_lo)) {
        do {
          u32 uVar2 = (u32)uVar4;
          if (*(int *)((uVar2 - unaff_s7_lo) + SymbolString) != 0) {
            inspect_object(uVar2);
          }
          uVar4 = (ulong)(int)(uVar2 + 4);
        } while (uVar4 < CONCAT44(unaff_s7_hi,unaff_s7_lo));
      }
      ClearPending();
      break;
    case 8:
      KernelShutdown(1);
    case 9: {
      u8* buffer = kmalloc(kdebugheap, MessCount, 0, "listener-link-buf");
      memcpy(buffer, msg, (size_t)MessCount);
      *(u8 **)(ListenerLinkBlock - 1) = buffer + 4;

      undefined in_t1_lo; // TODO: why would this be true? I expect this to be false...
      *(uint8_t **)(ListenerFunction - 1) = link_and_exec(buffer, "*listener*", MessCount - *(int *)(buffer + 4), kdebugheap,
                                                           0x10, (bool)in_t1_lo);
      return;
    } break;
    default:
      MsgErr("dkernel: unknown message error: <%d> of %d bytes\n", protoBlock.msg_kind, MessCount);
      break;
  }
  SendAck();
}

int sql_query_sync(String* string_in) {
  
  if (MasterDebug == 0) {
    int unaff_s7_lo;
    return unaff_s7_lo + -7;
  }
  else {
    int unaff_s7_lo;
    undefined4 unaff_s7_hi;
    *(int *)(SqlResult - 1) = unaff_s7_lo;
    output_sql_query(string_in + 1);
    *(int *)(ListenerFunction - 1) = unaff_s7_lo;
    ListenerStatus = 1;
    ClearPending();
    SendAck();
    int listener = *(int *)(ListenerFunction - 1);
    kdebugheap->top -= 0x4000;
    if ((long)listener == CONCAT44(unaff_s7_hi,unaff_s7_lo)) {
      while ((long)*(int *)(SqlResult - 1) == CONCAT44(unaff_s7_hi,unaff_s7_lo)) {
        KernelDispatch(*(u32 *)(sync_dispatcher - 1));
        SendAck();
        if ((long)*(int *)(SqlResult - 1) == CONCAT44(unaff_s7_hi,unaff_s7_lo)) {
          int i = 0;
          do {
            i++;
          } while (i < 100000);
        }
      }
    }
    kdebugheap->top += 0x4000;
    return *(int *)(SqlResult - 1);
  }
}

}  // namespace jak3
