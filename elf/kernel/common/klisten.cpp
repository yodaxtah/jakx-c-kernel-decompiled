#include "klisten.h"

#include <cstdio>
#include <cstring>

#include "common/listener_common.h"
#include "common/log/log.h"

#include "game/kernel/common/kdsnetm.h"
#include "game/kernel/common/kprint.h"
#include "game/kernel/common/ksocket.h"

Ptr<u32> print_column;
u32 ListenerStatus;

void klisten_init_globals() {
  print_column.offset = 0;
  ListenerStatus = 0;
}

/*!
 * Flush pending messages.  If debugging, will send to compiler, otherwise to stdout.
 * Changed slightly, it will also print to stdout if there's no compiler connected.
 */
void ClearPending() {
  char* data;
  size_t sVar1;
  int size;
  size_t sVar2;
  
  if (MasterDebug == 0) {
    if (PrintPending != (char *)0x0) {
      sVar1 = strlen(PrintBufArea + 0x18);
      if (0 < (long)sVar1) {
        printf("%s",PrintBufArea + 0x18);
      }
LAB_00270558:
      clear_print();
      return;
    }
  }
  else if (ListenerStatus != 0) {
    if (OutputPending != 0) {
      sVar1 = strlen((char *)(OutputBufArea + 0x18));
      SendFromBuffer((char *)(OutputBufArea + 0x18),(s32)sVar1);
      clear_output();
    }
    if (PrintPending != (char *)0x0) {
      sVar1 = strlen(PrintBufArea + 0x18);
      data = PrintBufArea + 0x18;
      for (; 0 < (long)sVar1; sVar1 = (size_t)((int)sVar1 - size)) {
        sVar2 = 64000;
        if ((long)sVar1 < 64000) {
          sVar2 = sVar1;
        }
        size = (int)sVar2;
        SendFromBufferD(2,0,data,size);
        data = data + size;
      }
      goto LAB_00270558;
    }
  }
  return;
}

/*!
 * Send an "ack" message. The original game had the AckBufArea which stores "ack", but did not
 * calculate the length correctly, so the message would not actually contain the "ack" text.
 * The "ack" text is unimportant, as the compiler can recognize the messages as ACK due to the
 * ListenerMessageKind::MSG_ACK field.  Both the type and msg_id fields are sent, which is enough
 * for it to work.
 * Note: jak2 sent 0 length acks.
 */
void SendAck() {
  if (MasterDebug != 0) {
    SendFromBufferD(0,protoBlock.msg_id,&AckBufArea,0);
    return;
  }
  return;
}