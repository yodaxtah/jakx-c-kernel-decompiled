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
  if (!MasterDebug) { // TODO: why is ListenerStatus gone?
    if (PrintPending.offset != 0) {
      size_t size = strlen(PrintBufArea.cast<char>().c() + sizeof(ListenerMessageHeader));
      if ((long)size > 0) {
        printf("%s", PrintBufArea.cast<char>().c() + sizeof(ListenerMessageHeader));
      }
      clear_print();
    }
  } else {
    if (ListenerStatus) {
      if (OutputPending.offset != 0) { // TODO: why is the loop gone here?
        char* msg = OutputBufArea.cast<char>().c() + sizeof(ListenerMessageHeader);
        size_t size = strlen(msg);
        SendFromBuffer(msg, (s32)size);
        clear_output();
      }

      if (PrintPending.offset != 0) {
        char* msg = PrintBufArea.cast<char>().c() + sizeof(ListenerMessageHeader);
        size_t size = strlen(msg);
        while (size > 0) {
          size_t send_size = size;
          if ((long)send_size > 64000) {
            send_size = 64000;
          }
          SendFromBufferD(2, 0, msg, (int)send_size);
          size -= send_size;
          msg += send_size;
        }
        clear_print();
      }
    }
  }
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
  if (MasterDebug) {
    SendFromBufferD(0, protoBlock.msg_id,
                    AckBufArea,
                    0);
  }
}
