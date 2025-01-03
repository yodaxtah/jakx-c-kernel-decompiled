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
  void* pvVar1;
  u32 uVar2;
  
  uVar2 = 0xffffffff;
  if (0x17 < protoBlock.last_receive_size) {
    FlushCache(0);
    pvVar1 = protoBlock.receive_buffer;
    uVar2 = *(u32 *)((int)protoBlock.receive_buffer + 0xc);
    if (*(short *)((int)protoBlock.receive_buffer + 4) == -0x1fbe) {
      *(undefined *)((int)protoBlock.receive_buffer + uVar2 + 0x18) = 0;
      protoBlock.msg_id = *(undefined8 *)((int)pvVar1 + 0x10);
      protoBlock.field57_0x48 = (uint)*(ushort *)((int)pvVar1 + 8);
    }
    else {
      MsgErr("dkernel: got a bad packet to goal proto (goal #x%x bytes %d %d %d %d %d)\n",
             protoBlock.receive_buffer,protoBlock.last_receive_size,
             (ulong)*(ushort *)((int)protoBlock.receive_buffer + 8),
             (ulong)*(ushort *)((int)protoBlock.receive_buffer + 10),
             *(undefined8 *)((int)protoBlock.receive_buffer + 0x10),uVar2);
      uVar2 = 0xffffffff;
    }
    protoBlock.last_receive_size = -1;
  }
  return uVar2;
}

/*!
 * Do a DECI2 send and block until it is complete.
 * The message type is OUTPUT
 * DONE, EXACT
 */
s32 SendFromBuffer(char* buff,s32 size) {
  s32 sVar1;
  
  sVar1 = SendFromBufferD(1,0,buff,size);
  return sVar1;
}

/*!
 * Just prepare the Ack buffer, doesn't actually connect.
 * Must be called before attempting to use the socket connection.
 * DONE, EXACT
 */
char* InitListenerConnect() {
  char* in_v0_lo;
  char* pcVar1;
  
  if (MasterDebug != 0) {
    pcVar1 = strcpy(&AckBufArea,"ack\n");
    return pcVar1;
  }
  return in_v0_lo;
}

/*!
 * Does nothing.
 * DONE, EXACT
 */
void InitCheckListener() {
  return;
}

/*!
 * Doesn't actually wait for a message, just checks if there's currently a message.
 * Doesn't actually send an ack either.
 * More accurate name would be "CheckForMessage"
 * Returns pointer to the message.
 * Updates MessCount to be equal to the size of the new message
 * DONE, EXACT
 */
char* WaitForMessageAndAck() {
  u8* puVar1;
  
  if (MasterDebug == 0) {
    MessCount = -1;
  }
  else {
    MessCount = ReceiveToBuffer((char *)(MessBufArea + 0x18));
  }
  if (MessCount < 0) {
    puVar1 = (u8 *)0x0;
  }
  else {
    puVar1 = MessBufArea + 0x18;
  }
  return (char *)puVar1;
}

/*!
 * Doesn't close anything, just print a closed message.
 * DONE, EXACT
 */
void CloseListener() {
  Msg(6,"dconnect: closed socket at kernel side\n");
  return;
}
