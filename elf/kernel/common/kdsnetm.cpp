#include "kdsnetm.h"

#include <cstdio>

#include "game/kernel/common/kprint.h"
#include "game/sce/deci2.h"
#include "game/system/deci_common.h"

/*!
 * Current state of the GOAL Protocol
 */

GoalProtoBlock protoBlock;

/*!
 * Initialize global variables for kdsnetm
 */
void kdsnetm_init_globals_common() {
  protoBlock.reset();
}

/*!
 * Register GOAL DECI2 Protocol Driver with DECI2 service
 * DONE, EXACT
 */
void InitGoalProto() {
  protoBlock.socket = sceDeci2Open(DECI2_PROTOCOL, &protoBlock, GoalProtoHandler);
  if (protoBlock.socket < 0) {
    MsgErr("gproto: open proto error\n");
  } else {
    protoBlock.send_buffer = nullptr;
    protoBlock.receive_buffer = MessBufArea.c();
    protoBlock.send_status = -1;
    protoBlock.last_receive_size = -1;
    protoBlock.receive_progress = 0;
    protoBlock.deci2count.offset = 0;
    Msg(6, "gproto: proto open at socket %d\n", protoBlock.socket);
  }
}

/*!
 * Close the DECI2 Protocol Driver
 * DONE, EXACT
 */
void ShutdownGoalProto() {
  if (protoBlock.socket > 0) {
    sceDeci2Close(protoBlock.socket);
  }
}

/*!
 * Handle a DECI2 Protocol Event for the GOAL Proto.
 * Called by the DECI2 Protocol driver
 * DONE, added print statements on errors for debugging, EI and SYNC at the end were removed
 */
void GoalProtoHandler(int event, int param, void* opt) {
  GoalProtoBlock* pb = (GoalProtoBlock*)opt;
  if (&protoBlock != pb) {
    Msg(6, "gproto: BAD OPT POINTER PASSED IN!!!!\n");
    pb = &protoBlock;
  }

  if (pb->deci2count.offset != 0) {
    *(int *)(pb->deci2count - 1) = *(int *)(pb->deci2count - 1) + 1;
  }

  pb->most_recent_event = event;
  pb->most_recent_param = param;

  switch (event) {
    case DECI2_READ:
      if (pb->receive_progress + param <= DEBUG_MESSAGE_BUFFER_SIZE) {
        s32 received =
            sceDeci2ExRecv(pb->socket, (void *)((int)pb->receive_buffer) + pb->receive_progress, (u16)param);

        if (-1 < received) { // FIXME: why is this opposite to other 
          pb->receive_progress += received;
        }
      } else {
        pb->last_receive_size = -1;
        protoBlock.receive_progress = 0;
      }
      break;

    case DECI2_READDONE:
      pb->last_receive_size = pb->receive_progress;
      pb->receive_progress = 0;
      break;

    case DECI2_WRITE: {
      s32 sent = sceDeci2ExSend(pb->socket, pb->send_ptr, (u16)pb->send_remaining);
      if (sent < 0) {
        pb->send_status = sent;
      } else {
        pb->send_ptr += sent;
        pb->send_remaining -= sent;
      }
    } break;

    case DECI2_WRITEDONE:
      if (pb->send_remaining <= 0) {
        pb->send_status = 0;
      } else {
        s32 a = pb->send_remaining;
        if (a < 0) {
          a = -a;
        }
        pb->send_status = -a;
      }
      break;

    case DECI2_CHSTATUS:
      break;

    default:
      pb->last_receive_size = -1;
      break;
  }
  // SYNC(0);
  // EI();
}

/*!
 * Low level DECI2 send
 * Will block until send is complete.
 * DONE, original version used an uncached address and had a FlushCache call, which were both
 * removed
 */
s32 SendFromBufferD(s32 msg_kind, u64 msg_id, char* data, s32 size) {
  while (protoBlock.send_status > 0) {
    ;
  }

  for (s32 i = 0; i < 10; i++) {
    ListenerMessageHeader* header = (ListenerMessageHeader*)((uint)(data - 0x18) | 0x20000000); // SIZEOF
    protoBlock.send_remaining = size + 0x18; // SIZEOF
    protoBlock.send_buffer = header;
    protoBlock.send_ptr = (u8*)header;

    protoBlock.send_status = size + 0x18; // SIZEOF
    // FlushCache(0);

    header->deci2_header.len = protoBlock.send_remaining;
    header->deci2_header.rsvd = 0;
    header->deci2_header.proto = DECI2_PROTOCOL;
    header->deci2_header.src = 'E';
    header->deci2_header.dst = 'H';

    header->msg_kind = (ListenerMessageKind)msg_kind;
    header->u6 = 0;
    header->msg_size = size;
    header->msg_id = msg_id;

    long rv = sceDeci2ReqSend(protoBlock.socket, 0x48);
    if (rv < 0) {
      printf("1sceDeci2ReqSend fail, reason code = %08x\n", rv);
      return -6;
    }
    while (protoBlock.send_status > 0) {
      ;
    }

    if (protoBlock.send_status > -1) { // TODO: Why not check 0 anymore?
      break;
    }
  }

  return 0;
}

/*!
 * Print GOAL Protocol status
 */
void GoalProtoStatus() {
  Msg(6, "gproto: got %d %d\n", protoBlock.most_recent_event, protoBlock.most_recent_param);
  Msg(6, "gproto: %d %d\n", protoBlock.last_receive_size, protoBlock.send_remaining);
}
