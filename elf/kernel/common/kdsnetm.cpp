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
 * TBD, EXACT
 */
void InitGoalProto()
{
  protoBlock.socket = sceDeci2Open(0xe042,&protoBlock,GoalProtoHandler);
  if (protoBlock.socket < 0) {
    MsgErr("gproto: open proto error\n");
    return;
  }
  protoBlock.send_status = -1;
  protoBlock.last_receive_size = -1;
  protoBlock.deci2count = 0;
  protoBlock.receive_progress = 0;
  protoBlock.send_buffer = (int *)0x0;
  protoBlock.receive_buffer = MessBufArea;
  Msg(6,"gproto: proto open at socket %d\n",protoBlock.socket);
  return;
}

/*!
 * Close the DECI2 Protocol Driver
 * TBD, EXACT
 */
void ShutdownGoalProto()
{
  if (0 < protoBlock.socket) {
    sceDeci2Close(protoBlock.socket);
    return;
  }
  return;
}

/*!
 * Handle a DECI2 Protocol Event for the GOAL Proto.
 * Called by the DECI2 Protocol driver
 * TBD, added print statements on errors for debugging, EI and SYNC at the end were removed
 */
void GoalProtoHandler(int event,int param,GoalProtoBlock *opt) {
  s32 sVar1;
  int iVar2;
  
  if (opt != &protoBlock) {
    opt = &protoBlock;
    Msg(6,"gproto: BAD OPT POINTER PASSED IN!!!!\n");
  }
  iVar2 = opt->deci2count;
  if (iVar2 != 0) {
    *(int *)(iVar2 + -1) = *(int *)(iVar2 + -1) + 1;
  }
  opt->some_event = event;
  opt->some_param = param;
  if (false) {
switchD_00266c5c_caseD_6:
    opt->last_receive_size = -1;
  }
  else {
    switch(event) {
    case 1:
      if ((opt->receive_progress + param < 0x80001) &&
         (sVar1 = sceDeci2ExRecv(opt->socket,
                                 (void *)((int)opt->receive_buffer + opt->receive_progress),
                                 (u16)param), -1 < sVar1)) {
        opt->receive_progress = opt->receive_progress + sVar1;
      }
      else {
        opt->last_receive_size = -1;
        protoBlock.receive_progress = 0;
      }
      break;
    case 2:
      opt->last_receive_size = opt->receive_progress;
      opt->receive_progress = 0;
      break;
    case 3:
      sVar1 = sceDeci2ExSend(opt->socket,opt->send_ptr,(u16)opt->send_remaining);
      if (sVar1 < 0) {
        opt->send_status = sVar1;
      }
      else {
        opt->send_ptr = (void *)((int)opt->send_ptr + sVar1);
        opt->send_remaining = opt->send_remaining - sVar1;
      }
      break;
    case 4:
      if (opt->send_remaining < 1) {
        opt->send_status = 0;
      }
      else {
        iVar2 = opt->send_remaining;
        if (iVar2 < 0) {
          iVar2 = -iVar2;
        }
        opt->send_status = -iVar2;
      }
      break;
    case 5:
      break;
    default:
      goto switchD_00266c5c_caseD_6;
    }
  }
  SYNC(0);
  EI();
  return;
}

/*!
 * Low level DECI2 send
 * Will block until send is complete.
 * TBD, original version used an uncached address and had a FlushCache call, which were both
 * removed
 */
s32 SendFromBufferD(s32 msg_kind,u64 msg_id,char* data,s32 size) {
  bool bVar1;
  s32 sVar2;
  long lVar3;
  int* piVar4;
  int iVar5;
  
  iVar5 = 0;
  do {
  } while (0 < protoBlock.send_status);
  while( true ) {
    piVar4 = (int *)((uint)(data + -0x18) | 0x20000000);
    protoBlock.send_remaining = size + 0x18;
    protoBlock.send_buffer = piVar4;
    protoBlock.send_ptr = piVar4;
    protoBlock.send_status = size + 0x18;
    FlushCache(0);
    sVar2 = protoBlock.send_remaining;
    *(undefined2 *)((int)piVar4 + 2) = 0;
    *(undefined *)((int)piVar4 + 6) = 0x45;
    piVar4[3] = size;
    *(short *)piVar4 = (short)sVar2;
    *(undefined *)((int)piVar4 + 7) = 0x48;
    *(undefined2 *)((int)piVar4 + 10) = 0;
    sVar2 = protoBlock.socket;
    *(undefined2 *)(piVar4 + 1) = 0xe042;
    *(u64 *)(piVar4 + 4) = msg_id;
    *(short *)(piVar4 + 2) = (short)msg_kind;
    lVar3 = sceDeci2ReqSend(sVar2,0x48);
    if (lVar3 < 0) {
      printf("1sceDeci2ReqSend fail, reason code = %08x\n",lVar3);
      return -6;
    }
    do {
    } while (0 < protoBlock.send_status);
    if (-1 < protoBlock.send_status) break;
    bVar1 = 9 < iVar5;
    iVar5 = iVar5 + 1;
    if (bVar1) {
      return 0;
    }
  }
  return 0;
}

/*!
 * Print GOAL Protocol status
 */
void GoalProtoStatus() {
  Msg(6,"gproto: got %d %d\n",protoBlock.some_event,protoBlock.some_param);
  Msg(6,"gproto: %d %d\n",protoBlock.last_receive_size,protoBlock.send_remaining);
  return;
}
