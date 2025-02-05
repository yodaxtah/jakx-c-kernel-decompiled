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
int KernelCheckAndDispatch();

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

s32 goal_main(int argc, const char** argv) {
  s32 thread_id = GetThreadId();
  ChangeThreadPriority(thread_id, 0x18);
  sceGsSyncVCallback(FUN_0026a918_probably_kernel);
  DAT_002833fc = 1;
  InitOnce_WS();

  masterConfig.aspect = sceScfGetAspect();
  undefined2 sony_language = sceScfGetLanguage();
  masterConfig.inactive_timeout = 0;
  masterConfig.volume = 100;
  masterConfig.timeout = 0;
  switch (sony_language) {
    case 0:
      masterConfig.language = 6;
      break;
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
      break;
    default:
      masterConfig.language = 0;
      break;
  }
  if (!strcmp(DebugBootMessage, "demo") || !strcmp(DebugBootMessage, "demo-shared")) {
    masterConfig.aspect = 1;
  }
  DiskBoot = 1;
  MasterDebug = 0;
  DebugSegment = 0;
  DebugSymbols = 0;

  // Launch GOAL!
  uint initMachineResult = InitMachine();
  bool result = (initMachineResult & 0xfff00000) == 0xfff00000;
  int shutdownReason;
  if (result) {
    printf("kboot: error; failed to initialize machine (result=0x%08x)\n", initMachineResult);
    shutdownReason = 2;
  }
  else {
    shutdownReason = KernelCheckAndDispatch();
  }
  ShutdownMachine(shutdownReason);
  if (MasterExit == 2) {
    LoadExecPS2("cdrom0:\\NETGUI\\NTGUI_EU.ELF;1", 1, &movie_args_Q);
  }
  else if (MasterExit == 3) {
    char printBuffer[32];
    sprintf(printBuffer, "cdrom0:\\SCES_%.3s.%2s;1", "532", "86");
  }
  return (uint)result;
}

void KernelDispatch(u32 dispatcher_func) {
  char* new_message = WaitForMessageAndAck();
  if (new_message != nullptr) {
    ProcessListenerMessage(new_message);
  }

  int old_listener_function = *(int *)(ListenerFunction + -1);

  (*(code *)dispatcher_func)();

  ClearPending();

  undefined4 unaff_s7_lo;
  undefined4 unaff_s7_hi;
  code* bonus_function = *(code **)(KernelFunction + -1);
  if ((long)(int)bonus_function != CONCAT44(unaff_s7_hi,unaff_s7_lo)) {
    *(undefined4 *)(KernelFunction + -1) = unaff_s7_lo;
    (*bonus_function)();
  }

  if (MasterDebug != 0 && *(int *)(ListenerFunction + -1) != old_listener_function) {
    SendAck();
  }
}

void KernelShutdown(u32 reason) {
  if (MasterExit < reason) {
    MasterExit = reason;
  }
}

int KernelCheckAndDispatch() {
  while ((MasterExit == 0 && (POWERING_OFF_W == false))) {
    KernelDispatch(*(u32 *)(kernel_dispatcher + -1));
  }
  if (POWERING_OFF_W != false) {
    KernelShutdown(3);
  }
  return MasterExit;
}

}  // namespace jak3
