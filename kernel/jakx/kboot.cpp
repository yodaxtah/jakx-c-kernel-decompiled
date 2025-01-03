#include "kboot.h"

#include <cstring>

#include "common/log/log.h"
#include "common/repl/repl_wrapper.h"
#include "common/util/Timer.h"

#include "game/common/game_common_types.h"
#include "game/kernel/common/Ptr.h"
#include "game/kernel/common/Symbol4.h"
#include "game/kernel/common/kboot.h"
#include "game/kernel/common/klisten.h"
#include "game/kernel/common/kprint.h"
#include "game/kernel/common/kscheme.h"
#include "game/kernel/common/ksocket.h"
#include "game/kernel/jak3/klisten.h"
#include "game/kernel/jak3/kmachine.h"
#include "game/sce/libscf.h"

// KernelDispatch__3ndiPFv_x
// KernelCheckAndDispatch__3ndiv
// KernelShutdown__3ndii
// main

namespace jak3 {
void KernelCheckAndDispatch();

char DebugBootUser[64];
char DebugBootArtGroup[64];

void kboot_init_globals() {
  memset(DebugBootUser, 0, sizeof(DebugBootUser));
  memset(DebugBootArtGroup, 0, sizeof(DebugBootArtGroup));
  // strcpy(DebugBootUser, "unknown");
  // CHANGED : let's just try to find the username automatically by default!
  // the default is still "unknown"
  auto username = REPL::find_repl_username();
  strcpy(DebugBootUser, username.c_str());
}

s32 goal_main(int argc,const_char **argv) {
  bool bVar1;
  undefined2 uVar2;
  int iVar3;
  uint uVar4;
  undefined8 uVar5;
  char acStack_40 [32];
  
  uVar5 = GetThreadId(argc,argv);
  ChangeThreadPriority(uVar5,0x18);
  sceGsSyncVCallback(0x26a918);
  DAT_002833fc = 1;
  FUN_0025cdcc();
  masterConfig.aspect = sceScfGetAspect();
  uVar2 = sceScfGetLanguage();
  masterConfig.volume = 100;
  masterConfig.inactive_timeout = 0;
  masterConfig.timeout = 0;
  if (false) {
switchD_00266820_caseD_1:
    masterConfig.language = 0;
  }
  else {
    switch(uVar2) {
    case 0:
      masterConfig.language = 6;
      break;
    default:
      goto switchD_00266820_caseD_1;
    case 2:
      masterConfig.language = 1;
      break;
    case 3:
      masterConfig.language = 3;
      break;
    case 4:
      masterConfig.language = 2;
      break;
    case 5:
      masterConfig.language = 4;
      break;
    case 7:
      masterConfig.language = 9;
    }
  }
  iVar3 = strcmp(DebugBootMessage,"demo");
  if ((iVar3 == 0) || (iVar3 = strcmp(DebugBootMessage,"demo-shared"), iVar3 == 0)) {
    masterConfig.aspect = 1;
  }
  DiskBoot = 1;
  MasterDebug = 0;
  DebugSegment = 0;
  DebugSymbols = 0;
  uVar4 = InitMachine();
  bVar1 = (uVar4 & 0xfff00000) == 0xfff00000;
  if (bVar1) {
    printf("kboot: error; failed to initialize machine (result=0x%08x)\n",uVar4);
    iVar3 = 2;
  }
  else {
    iVar3 = KernelCheckAndDispatch();
  }
  ShutdownMachine(iVar3);
  if (force_to_data_G == 2) {
    LoadExecPS2("cdrom0:\\NETGUI\\NTGUI_EU.ELF;1",1,&movie_args_Q);
  }
  else if (force_to_data_G == 3) {
    sprintf(acStack_40,"cdrom0:\\SCES_%.3s.%2s;1","532","86");
  }
  return (uint)bVar1;
}

void KernelDispatch(u32 dispatcher_func) {
  int iVar1;
  code *pcVar2;
  char *msg;
  undefined4 unaff_s7_lo;
  undefined4 unaff_s7_hi;
  
  msg = WaitForMessageAndAck();
  if (msg != (char *)0x0) {
    ProcessListenerMessage(msg);
  }
  iVar1 = *(int *)(ListenerFunction + -1);
  (*(code *)dispatcher_func)();
  ClearPending();
  pcVar2 = *(code **)(KernelFunction + -1);
  if ((long)(int)pcVar2 != CONCAT44(unaff_s7_hi,unaff_s7_lo)) {
    *(undefined4 *)(KernelFunction + -1) = unaff_s7_lo;
    (*pcVar2)();
  }
  if ((MasterDebug != 0) && (*(int *)(ListenerFunction + -1) != iVar1)) {
    SendAck();
    return;
  }
  return;
}

void KernelShutdown(u32 reason) {
  if (force_to_data_G < reason) {
    force_to_data_G = reason;
  }
  return;
}

int KernelCheckAndDispatch(void) {
  while ((force_to_data_G == 0 && (POWERING_OFF_W == false))) {
    KernelDispatch(*(u32 *)(kernel_dispatcher + -1));
  }
  if (POWERING_OFF_W != false) {
    KernelShutdown(3);
  }
  return force_to_data_G;
}

}  // namespace jak3
