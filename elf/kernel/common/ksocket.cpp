#include "ksocket.h"

#include "game/kernel/common/fileio.h"
#include "game/kernel/common/kdsnetm.h"
#include "game/kernel/common/kprint.h"

/*!
 * Update GOAL message header after receiving and verify message is ok.
 * Return the size of the message in bytes (not including DECI or GOAL headers)
 * Return -1 on error.
 * The buffer parameter is unused.
 * DONE, removed call to FlushCache(0);
 */
u32 ReceiveToBuffer(char* buff) {
  if (0x17 >= protoBlock.last_receive_size) {
    return -1;
  }

  // FlushCache(0);
  ListenerMessageHeader* gbuff = protoBlock.receive_buffer;
  u32 msg_size = gbuff->msg_size;

  if (gbuff->deci2_header.proto == 0xe042) {
    *(undefined *)((int)&protoBlock.receive_buffer[1].deci2_header.len + msg_size) = 0;
    protoBlock.msg_kind = (u32)(ushort)gbuff->msg_kind;
    protoBlock.msg_id = gbuff->msg_id;
    protoBlock.last_receive_size = -1;
  } else {
    MsgErr("dkernel: got a bad packet to goal proto (goal #x%x bytes %d %d %d %d %d)\n",
           protoBlock.receive_buffer, protoBlock.last_receive_size,
           (ulong)(ushort)protoBlock.receive_buffer->msg_kind, (ulong)protoBlock.receive_buffer->u6,
           protoBlock.receive_buffer->msg_id, msg_size);
    protoBlock.last_receive_size = -1;
    return -1;
  }
  return msg_size;
}

/*!
 * Do a DECI2 send and block until it is complete.
 * The message type is OUTPUT
 * DONE, EXACT
 */
s32 SendFromBuffer(char* buff, s32 size) {
  return SendFromBufferD(1, 0, buff, size);
}

/*!
 * Just prepare the Ack buffer, doesn't actually connect.
 * Must be called before attempting to use the socket connection.
 * DONE, EXACT
 */
void InitListenerConnect() {
  if (MasterDebug != 0) {
    return strcpy(&AckBufArea, "ack\n");
  }
}

/*!
 * Does nothing.
 * DONE, EXACT
 */
void InitCheckListener() {}

/*!
 * Doesn't actually wait for a message, just checks if there's currently a message.
 * Doesn't actually send an ack either.
 * More accurate name would be "CheckForMessage"
 * Returns pointer to the message.
 * Updates MessCount to be equal to the size of the new message
 * DONE, EXACT
 */
char* WaitForMessageAndAck() {
  if (MasterDebug == 0) {
    MessCount = -1;
  } else {
    MessCount = ReceiveToBuffer((char *)(MessBufArea + 0x18));
  }

  if (MessCount < 0) {
    return nullptr;
  }

  return MessBufArea + 0x18;
}

/*!
 * Doesn't close anything, just print a closed message.
 * DONE, EXACT
 */
void CloseListener() {
  Msg(6, "dconnect: closed socket at kernel side\n");
}