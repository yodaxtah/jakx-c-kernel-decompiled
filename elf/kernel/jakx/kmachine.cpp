#include "kmachine.h"

#include <cstring>

#include "common/symbols.h"

#include "game/graphics/gfx.h"
#include "game/graphics/jak3_texture_remap.h"
#include "game/graphics/sceGraphicsInterface.h"
#include "game/kernel/common/fileio.h"
#include "game/kernel/common/kdgo.h"
#include "game/kernel/common/kdsnetm.h"
#include "game/kernel/common/kernel_types.h"
#include "game/kernel/common/klink.h"
#include "game/kernel/common/kmachine.h"
#include "game/kernel/common/kmalloc.h"
#include "game/kernel/common/kprint.h"
#include "game/kernel/common/ksocket.h"
#include "game/kernel/common/ksound.h"
#include "game/kernel/common/memory_layout.h"
#include "game/kernel/jak3/kboot.h"
#include "game/kernel/jak3/kdgo.h"
#include "game/kernel/jak3/klisten.h"
#include "game/kernel/jak3/kmachine_extras.h"
#include "game/kernel/jak3/kmalloc.h"
#include "game/kernel/jak3/kscheme.h"
#include "game/kernel/jak3/ksound.h"
#include "game/sce/deci2.h"
#include "game/sce/libdma.h"
#include "game/sce/libgraph.h"
#include "game/sce/sif_ee.h"
#include "game/sce/stubs.h"

namespace jak3 {

using namespace ee;

/*!
 * Initialize global variables based on command line parameters. Not called in retail versions,
 * but it is present in the ELF.
 * DONE
 * Modified to use std::string, and removed call to fflush.
 */
void InitParms(int argc, const char** argv) {
  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];

    if (arg == "-cd") {
      Msg(6, "dkernel: cd mode\n");
      reboot_G_isodrv_G_overlord_S = 0;
      modsrc_S = 0;
      fs_S_FS_INITIALIZED_W = 0;
      isodrv_G_reboot_G = 0;
    }

    if (arg == "-cd-local-overlord") {
      Msg(6, "dkernel: cd local-overlord mode\n");
      reboot_G_isodrv_G_overlord_S = 1;
      modsrc_S = 0;
      fs_S_FS_INITIALIZED_W = 0;
      isodrv_G_reboot_G = 0;
    }

    if (arg == "-cddata") {
      Msg(6, "dkernel: cddata mode\n");
      fs_S_FS_INITIALIZED_W = 0;
      isodrv_G_reboot_G = 1;
      modsrc_S = 1;
      reboot_G_isodrv_G_overlord_S = 1;
    }

    if (arg == "-demo") {
      Msg(6, "dkernel: demo mode\n");
      strcpy(DebugBootMessage, "demo");
    }

    if (arg == "-kiosk") {
      Msg(6, "dkernel: kiosk mode\n");
      strcpy(DebugBootMessage, "kiosk");
    }

    if (arg == "-beta") {
      Msg(6, "dkernel: beta mode\n");
      strcpy(DebugBootMessage, "beta");
    }

    if (arg == "-preview") {
      Msg(6, "dkernel: preview mode\n");
      strcpy(DebugBootMessage, "preview");
    }

    if (arg == "-fakeiso") {
      Msg(6, "dkernel: fakeiso mode\n");
      fs_S_FS_INITIALIZED_W = 1;
      isodrv_G_reboot_G = 1;
      modsrc_S = 1;
      reboot_G_isodrv_G_overlord_S = 1;
    }

    if (arg == "-boot") {
      Msg(6, "dkernel: boot mode\n");
      MasterDebug = 0;
      DiskBoot = 1;
      DebugSegment = 0;
    }

    if (arg == "-debug-boot") {
      Msg(6, "dkernel: debug-boot mode\n");
      MasterDebug = 0;
      DebugSegment = 1;
      DiskBoot = 1;
    }

    if (arg == "-debug") {
      Msg(6, "dkernel: debug mode\n");
      MasterDebug = 1;
      DebugSegment = 1;
    }

    if (arg == "-debug-mem") {
      Msg(6, "dkernel: debug-mem mode\n");
      MasterDebug = 1;
      DebugSegment = 0;
    }

    if (arg == "-overlord") {
      Msg(6, "dkernel: overlord 1 mode\n");
      _USE_OVERLORD2 = 0;
    }

    if (arg == "-overlord2") {
      Msg(6, "dkernel: overlord 2 mode\n");
      _USE_OVERLORD2 = 1;
    }

    if (arg == "-debug-symbols") {
      Msg(6, "dkernel: debug-symbols on\n");
      DebugSymbols = 1;
    }

    if (arg == "-no-debug-symbols") {
      Msg(6, "dkernel: debug-symbols off\n");
      DebugSymbols = 0;
    }

    if ((arg == "-level") && (i + 1 < argc)) {
      std::string levelName = argv[++i];
      std::string symbolId = argv[++i];
      Msg(6, "dkernel: level %s %s\n", levelName.c_str(), symbolId.c_str());
      strcpy(DebugBootLevel, levelName.c_str());
      DebugBootLevelID = DecodeSymbolId(atoi(argv[2])) + 1;
    }

    if ((arg == "-user") && (i + 1 < argc)) {
      i++;
      std::string userName = argv[i];
      Msg(6, "dkernel: user %s\n", userName.c_str());
      strcpy(DebugBootUser, userName.c_str());
    }

    if (arg == "-art") {
      if (i + 1 < argc) { // FIXME
        i++;
        std::string artGroupName = argv[i];
        Msg(6, "dkernel: art-group %s\n", artGroupName.c_str());
        if (strlen(artGroupName) != 0) {
          strcpy(DebugBootArtGroup, artGroupName.c_str());
          strcpy(DebugBootMessage, "art-group");
        }
      }
    }
  }
  fflush(*(FILE **)(_impure_ptr + 8));
}

/*!
 * This is mostly copy-pasted from jak2 and very simplified until we have overlord 2.
 * DONE.
 */
s32 InitIOP() {
  FUN_0027c260_usb();
  if (dnas_S_DNAS_INITIALIZED_W == 0
      && fs_S_FS_INITIALIZED_W != 0
      && modsrc_S != 0
      && reboot_G_isodrv_G_overlord_S != 0
      && isodrv_G_reboot_G != 0
  ) {
    cd_S_INITIALIZE_CD_W = false;
  }
  else {
    cd_S_INITIALIZE_CD_W = true;
  }
  Msg(6, "dkernel: boot:%d dbg:%d mem:%d syms:%d fs:%d mod:%d ovl:%d ioprp:%d cd:%d dnas:%d\n",
      DiskBoot, MasterDebug, DebugSegment, DebugSymbols, fs_S_FS_INITIALIZED_W, modsrc_S,
      reboot_G_isodrv_G_overlord_S, isodrv_G_reboot_G, (uint)cd_S_INITIALIZE_CD_W, dnas_S_DNAS_INITIALIZED_W);
  SifInitRpc(0);
  IOP_CALLED_W = 1;
  InitCD();
  int iopRebootResult;
  do {
    FUN_002684f4_cd_dvd_disk_drive_ready();
    char acStack_5b0 [1024];
    MakeDriverPath_S(acStack_5b0, "dnas300.img", (long)isodrv_G_reboot_G, true);
    if (0x45 < strlen(acStack_5b0)) {
      MsgErr("dkernel: error; invalid ioprp path; %d chars max\n", 0x45);
      FUN_0027c2a4_usb();
      return -1;
    }
    printf("dkernel: Rebooting IOP using \"%s\"...", acStack_5b0);
    iopRebootResult = SifIopReboot(acStack_5b0);
    if (iopRebootResult == 0) {
      printf("  Failed, retrying...\n");
    }
    else {
      printf("  Syncing...");
      while (sceSifSyncIop() == 0) {
        ;
      }
      printf("  Done.\n");
    }
  } while (iopRebootResult == 0);
  SifInitRpc(0);
  sceSifInitIopHeap();
  sceSifLoadFileReset();
  InitCD();
  SifLoadModule_G(sceFsReset());
  FUN_002684f4_cd_dvd_disk_drive_ready();
  DAT_00284af0_sce_or_sif_or_iop_or_fs_ok_W = 1;

  int cdvdModule = sceSifSearchModuleByName("cdvd_ee_driver");
  int result = cdvdModule;
  if (cdvdModule >= 0) {
    undefined auStack_30 [4];
    result = sceSifStopModule(cdvdModule, 0, 0, auStack_30)
    if (result >= 0) {
      result = sceSifUnloadModule(cdvdModule)
    }
  }
  if (result < 0) {
    MsgErr("dkernel: unload cdvd_ee_driver failed %d\n", result);
    FUN_0027c2a4_usb();
    return -1;
  }
  else {
    DumpIOPMemStats_Q("Initial IOP mem stats");
    if (InitUnderlord_S() < 0) {
      FUN_0027c2a4_usb();
      return -1;
    }
    if (FUN_0027483c_implicit_dkernel(s__00282fd8) == 0) {
      s__00282fd8[15] = '\0';
      memset(s__00282fd8, L'0', 0xe);
      s__00282fd8[4] ^= 0x71; // 0x51
      s__00282fd8[5] ^= 0x73; // 0x53
    }
    RUN_AS_DEMO_W = s__00282fd8[4] == 0x54
    while (loadModuleByString_G_underlordRpcCall3_W(&DAT_00282fe8_arg_for_module, s_BOOT2___cdrom0__SCES_532_86_1_VE_00282ff0) == 0) {
      ;
    }
    char acStack_5b0 [1024];
    MakeDriverPath_S(acStack_5b0, "overlay.bin", (long)modsrc_S, false);
    undefined auStack_1b0 [8];
    while (underlordRpcCall0_W(acStack_5b0, auStack_1b0) < 0) {
      ;
    }
    undefined* local_1a8;
    PTR_DAT_002833f0 = local_1a8; // TODO: assigns nullptr?
    Idk1248Data local_170 [3];
    undefined8* itCopy = local_170;
    undefined8* itArray = InitIOPArrayIdk_W;
    do {
      itCopy->value1 = itArray->value1;
      itCopy->value2 = itArray->value2;
      itCopy->value4 = itArray->value4;
      itCopy->value8 = itArray->value8;
      itArray++;
      itCopy++;
    } while (itArray != (Idk1248Data*)"dkernel: boot:%d dbg:%d mem:%d syms:%d fs:%d mod:%d ovl:%d ioprp:%d cd:%d dnas:%d\n"); // this string is just at end(itArray)

    for (int i = 0; i < 12; i++) {
      MakeVagwadPath_S(acStack_5b0, fs_S_FS_INITIALIZED_W != 0, i);
      if (underlordRpcCall0_W(acStack_5b0, auStack_1b0) == 0) {
        AUDIO_LANGUAGE_MASK_G |= (&local_170[0].value1)[i]; // treat array of 3 structs as array of 12 elements
      }
    }
    printf("dkernel: audio language mask = 0x%08x\n", AUDIO_LANGUAGE_MASK_G);
    if (RUN_AS_DEMO_W) {
      if (!strcmp(DebugBootMessage, "demo") || !strcmp(DebugBootMessage, "demo-shared")) {
        masterConfig.aspect = 1;
      }
      else {
        masterConfig.aspect = 0;
      }
      sceScfConfig_W T10kConfig_W;
      T10kConfig_W.field0_0x0 = -0x1e0;
      T10kConfig_W.aspect_W = (byte)masterConfig.aspect;
      T10kConfig_W.field2_0x3 = 1;
      T10kConfig_W.field3_0x4 = 1;
      T10kConfig_W.field4_0x5 = 0;
      T10kConfig_W.field5_0x6 = 0;
      T10kConfig_W.field6_0x7 = 1;
      masterConfig.language = 0;
      masterConfig.inactive_timeout = 0;
      masterConfig.volume = 100;
      masterConfig.timeout = 0;
      sceScfSetT10kConfig(&T10kConfig_W);
    }

    int local_2c [3];
    local_2c[0] = 1;
    if (loadIOPModuleAndStuff_W("dev9.irx", 0, nullptr, (long)(int)local_2c, (long)modsrc_S) < 0) {
      FUN_0027c2a4_usb();
      return -1;
    }
    DEV9_PRESENT_W = local_2c[0] != 1;
    DEV9_PRESENT_PROXY_W = DEV9_PRESENT_W;
    printf("dkernel: dev9 %spresent\n", (DEV9_PRESENT_W) ? "" : "not ");
    initializePowerOffHandler_W();
    if (loadIOPModuleAndStuff_W("sio2man.irx", 0, nullptr, 0, (long)modsrc_S) < 0
        || loadIOPModuleAndStuff_W("sio2d.irx", 0, nullptr, 0, (long)modsrc_S) < 0
        || loadIOPModuleAndStuff_W("dbcman.irx", 0, nullptr, 0, (long)modsrc_S) < 0
        || loadIOPModuleAndStuff_W("mc2_d.irx", 0, nullptr, 0, (long)modsrc_S) < 0
        || loadIOPModuleAndStuff_W("ds2o_d.irx", 0, nullptr, 0, (long)modsrc_S) < 0
        || loadIOPModuleAndStuff_W("ds2o_d.irx", 0, nullptr, 0, (long)modsrc_S) < 0
        || loadIOPModuleAndStuff_W("libsd.irx", 0, nullptr, 0, (long)modsrc_S) < 0
        || loadIOPModuleAndStuff_W("usbd.irx", 0x2b, "hub=1", 0, (long)modsrc_S) < 0
        || loadIOPModuleAndStuff_W("usbkeybd.irx", 0, nullptr, 0, (long)modsrc_S) < 0
        || loadIOPModuleAndStuff_W((_USE_OVERLORD2 == 0) ? "989nostr.irx" : "989nsnm.irx", 9, "do_rpc=0", 0, (long)modsrc_S) < 0
        || loadIOPModuleAndStuff_W("lgaud.irx", 0x2f, "thpri=53", 0, (long)modsrc_S) < 0
    ) {
      FUN_0027c2a4_usb();
      return -1;
    }

    char cStack_130;
    char acStack_12f [255];
    strcpy(&cStack_130, ISO_TYPE_STRINGS_W[fs_S_FS_INITIALIZED_W]);
    size_t length = strlen(&cStack_130);
    char* pcVar7 = acStack_12f + (int)length;
    char *moduleName_W;
    if (strncmp(DebugBootMessage, "demo", 4) == 0) {
      strcpy(pcVar7, "SCREEN1.DEE"); // TODO: won't this be overwritten after the switch?
      moduleName_W = "SCREEN1.EUR";
    }
    else {
      switch(masterConfig.language) {
      case 1:
        moduleName_W = "SCREEN1.FRE";
        break;
      case 2:
        moduleName_W = "SCREEN1.GER";
        break;
      case 3:
        moduleName_W = "SCREEN1.SPA";
        break;
      case 4:
        moduleName_W = "SCREEN1.ITA";
        break;
      case 9:
        moduleName_W = "SCREEN1.POR";
        break;
      default:
        moduleName_W = "SCREEN1.EUR";
        break;
      }
    }
    strcpy(pcVar7, moduleName_W);
    size_t length = strlen(pcVar7);
    if (loadIOPModuleAndStuff_W((_USE_OVERLORD2 == 0) ? "overlord.irx" : "overlrd2.irx", (long)(int)(pcVar7 + (((int)length + 1) - (int)&cStack_130)), &cStack_130, 0, (long)reboot_G_isodrv_G_overlord_S) < 0) {
      FUN_0027c2a4_usb();
      return -1;
    }
    IOP_RUNNING_W = 1;
    int sceDbcInitResult = sceDbcInit_G();
    if (sceDbcInitResult == 1) {
      int sceMc2InitResult = sceMc2Init_G_Proxy();
      if (sceMc2InitResult == 1) {
        FUN_00279c54();
        CatalogOverlayModules_S();
        Msg(6, "InitIOP OK\n");
        FUN_0027c2a4_usb();
        return 0;
      }
      MsgErr("dkernel: error; memcard driver init failed %d\n", sceMc2InitResult);
      FUN_0027c2a4_usb();
      return -1;
    }
    else {
      MsgErr("dkernel: error; DBC driver init failed %d\n", sceDbcInitResult);
      FUN_0027c2a4_usb();
      return -1;
    }
  }
}

int InitMachine() {
  int global_heap_end_W = FUN_00268b40();

  s32 global_heap_size = global_heap_end_W - 0x4000;
  u8* heap_start = malloc((long)global_heap_size);
  if (heap_start == nullptr) {
    MsgErr("dkernel: out of memory, cannot allocate global heap; exiting\n");
    return -1;
  }
  else {
    s32 global_heap_size__ = 0x5000000;
    if (!((MasterDebug != 0 || DebugSegment != 0) && (0x4ffffff < (ulong)(long)global_heap_size))) {
      global_heap_size__ = global_heap_size;
    }
    kinitheap(kglobalheap, heap_start, global_heap_size__);

    kmemopen_from_c(kglobalheap, "global");
    kmemopen_from_c(kglobalheap, "scheme-globals");

    if ((MasterDebug != 0 || DebugSegment != 0) && (0x4ffffff < (ulong)(long)global_heap_size)) {
      kinitheap(kdebugheap, heap_start + 0x5000000, global_heap_end_W - 0x5004000);
    } else {
      kdebugheap.offset = 0;
    }
    init_output();
    s32 initIopResult = InitIOP();
    if (initIopResult != 0) {
      return initIopResult;
    }
    // sceGsResetPath();
    InitVideo();
    // FlushCache(0);
    // FlushCache(2);
    // sceGsSyncV(0);
    // long scePad2InitResult = scePad2Init(0);
    // if (scePad2InitResult != 1) {
    //   MsgErr("dkernel: scePad2Init() failed; result %d\n", scePad2InitResult);
    //   return -1;
    // }
    undefined4 local_50;
    undefined4 local_4c;
    memset(&local_50,0,0x20);
    local_4c = 0;
    local_50 = 2;
    DAT_00283458_libpad = scePad2CreateSocket(&local_50,0x283480);
    local_4c = 1;
    long lVar5 = scePad2CreateSocket(&local_50,0x283580);
    DAT_0028345c_libpad = (undefined4)lVar5;
    if ((DAT_00283458_libpad < 0) || (lVar5 < 0)) {
      MsgErr("dkernel: scePad2CreateSocket() failed; 0 = 0x%08x, 1 = 0x%08x\n",DAT_00283458_libpad,
             lVar5);
    }
    if (MasterDebug != 0) {
      InitGoalProto();
    }
    Msg(6, "kernel: InitRPC\n");
    if (InitRPC() == 0) {
      reset_output();
      clear_print();
      uint status = InitHeapAndSymbol();
      if ((status & 0xfff00000) == 0xfff00000) {
        return status;
      }
      Msg(6, "kernel: InitListenerConnect\n");
      InitListenerConnect();
      Msg(6, "kernel: InitCheckListener\n");
      InitCheckListener();
      Msg(6, "kernel: machine started\n");
      return 0;
    } else {
      MsgErr("dkernel: fatal error; InitRPC() failed\n");
      return -1;
    }
  }
}

int StopIOP_G() {
  int result = Is_RPC_Initialized_G();
  if ((result != 0) && (IOP_RUNNING_W != false)) {                                                 
    x[2] = 0x10; // TODO: this doesn't look right
    x[3] = 0;
    RpcSync(1);
    result = RpcCallNoCallback(1, 0, false, x, 0x30, nullptr, 0);
    IOP_RUNNING_W = false;
  }
  return result;
}

int ShutdownMachine(int reasonIndex) {
  if (POWERING_OFF_W) {
    reasonIndex = 3;
  }
  char *reasonMessage = ((uint)reasonIndex < 4)
    ? (&SHUTDOWN_MACHINE_REASONS_W)[reasonIndex]
    : "*invalid*"
    ;
  Msg(6, "kernel: machine shutdown (reason=%d, %s)\n",reasonIndex, reasonMessage);
  CloseListener();

  ShutdownGoalProto();
  StopIOP_G();
  if (-1 < knet_eenet_shutdown_Q()) {
    while (knet_eenet_poll_is_shutdown_G() == 1) {
      sceKernelDelayThread_G(10000);
    }
  }
  if (FUN_00273870_mc() != 0) {
    MC_shutdown_G();
  }
  scePad2End();
  if (DEV9_PRESENT_PROXY_W != false) {
    RpcSyncAndCall_implicit_dkernel_G(reasonIndex != 3);
  }
  SifExitCmd();
  sceDmaReset(1);
  return 0;
}

/*!
 * TBD RETURN 0 SKIPPED
 */
u32 KeybdGetData(u32 mouse) {
  undefined1 *puVar1;
  byte bVar2;
  long lVar3;
  char *format;
  int iVar4;
  undefined *puVar5;
  int unaff_s7_lo;
  
  lVar3 = FUN_00279d50(0x2d2dc0);
  if (lVar3 == 0) {
    iVar4 = 0;
    FUN_00279e90(0);
    bVar2 = DAT_002d2dc0;
    while (bVar2 != 0) {
      if ((&DAT_002d2dc2)[iVar4] != '\0') {
        lVar3 = FUN_00279db0(iVar4,0x2d2ec0);
        if (lVar3 != 0) {
          format = "dkernel: sceUsbKeybdRead\n";
          goto LAB_0026a720;
        }
        FUN_00279e90(0);
        if (DAT_002d2ec1 != 0) {
          lVar3 = FUN_00279e20(iVar4,0x2d2e40);
          if (lVar3 == 0) {
            FUN_00279e90(0);
            *(int *)(mouse + 4) = unaff_s7_lo + 4;
            *(undefined *)(mouse + 8) = DAT_002d2ec0;
            *(byte *)(mouse + 9) = DAT_002d2ec1;
            iVar4 = 0;
            if (DAT_002d2ec1 == 0) {
              return mouse;
            }
            puVar5 = (undefined *)(mouse + 10);
            do {
              puVar1 = &DAT_002d2ec2 + iVar4;
              iVar4 = iVar4 + 1;
              *puVar5 = *puVar1;
              puVar5 = puVar5 + 1;
            } while (iVar4 < (int)(uint)DAT_002d2ec1);
            return mouse;
          }
          format = "dkernel: sceUsbKeybdGetLolcation\n";
          goto LAB_0026a720;
        }
      }
      iVar4 = iVar4 + 1;
      bVar2 = iVar4 < (int)(uint)DAT_002d2dc0;
    }
  }
  else {
    format = "dkernel: sceUsbKeybdGetInfo\n";
LAB_0026a720:
    MsgErr(format);
    *(int *)(mouse + 4) = unaff_s7_lo;
  }
  return mouse;
}

u32 MouseGetData(u32 mouse) {
  return mouse;
}

/*!
 * Open a file-stream.  Name is a GOAL string. Mode is a GOAL symbol.  Use 'read for readonly
 * and anything else for write only.
 * DONE
 */
u64 kopen(u64 fs, u64 name, u64 mode) {
  Ptr<FileStream> file_stream = Ptr<FileStream>(fs).c();
  file_stream->mode = (u32)mode;
  file_stream->name = (u32)name;
  file_stream->flags = 0;
  char buffer[128];
  if (*(char *)((u32)name + 4) == '/') {
    sprintf(buffer, "%s", (u32)name + 5);
  } else {
    sprintf(buffer, "host:%s", (u32)name + 4);
  }
  int unaff_s7_lo;
  undefined4 symbol_to_cstring_mode = *(int *)(((u32)mode - unaff_s7_lo) + SymbolString) + 4;
  if (!strcmp((char *)(symbol_to_cstring_mode), "read")) {
    file_stream->file = sceOpen(buffer, SCE_RDONLY);
  } else if (!strcmp((char *)(symbol_to_cstring_mode), "append")) {
    file_stream->file = sceOpen(buffer, SCE_CREAT | SCE_WRONLY);
  } else {
    file_stream->file = sceOpen(buffer, SCE_TRUNC | SCE_CREAT | SCE_WRONLY);
  }

  return fs;
}

void PutDisplayEnv(u32 ptr) {
  uint uVar1;
  
  if (count_618 == 0) {
    sceGsPutDispEnv();
    REG_GS_DISPFB1 = *(undefined8 *)(ptr + 0x10);
    REG_GS_DISPLAY1 = *(undefined8 *)(ptr + 0x18);
  }
  else {
    uVar1 = *(uint *)ptr;
    count_618 = count_618 - 1;
    *(uint *)ptr = uVar1 & 0xfffffffd;
    sceGsPutDispEnv();
    *(uint *)ptr = *(uint *)ptr & 0xfffffffd | (uVar1 >> 1 & 1) << 1;
  }
}

void aybabtu() {}

//// PC Stuff
void InitMachine_PCPort() {
  // PC Port added functions
  init_common_pc_port_functions(
      make_function_symbol_from_c,
      [](const char* name) {
        const auto result = intern_from_c(-1, 0, name);
        InternFromCInfo info{};
        info.offset = result.offset;
        return info;
      },
      make_string_from_c);

  make_function_symbol_from_c("__pc-set-levels", (void*)kmachine_extras::pc_set_levels);
  make_function_symbol_from_c("__pc-set-active-levels",
                              (void*)kmachine_extras::pc_set_active_levels);
  make_function_symbol_from_c("__pc-get-tex-remap", (void*)lookup_jak3_texture_dest_offset);
  // make_function_symbol_from_c("pc-init-autosplitter-struct", (void*)init_autosplit_struct);
  make_function_symbol_from_c("pc-encode-utf8-string", (void*)kmachine_extras::encode_utf8_string);

  // discord rich presence
  make_function_symbol_from_c("pc-discord-rpc-update", (void*)kmachine_extras::update_discord_rpc);

  // debugging tools
  // make_function_symbol_from_c("alloc-vagdir-names", (void*)alloc_vagdir_names);

  // external RPCs
  /*
  make_function_symbol_from_c("pc-fetch-external-speedrun-times",
                              (void*)pc_fetch_external_speedrun_times);
  make_function_symbol_from_c("pc-fetch-external-race-times", (void*)pc_fetch_external_race_times);
  make_function_symbol_from_c("pc-fetch-external-highscores", (void*)pc_fetch_external_highscores);
  make_function_symbol_from_c("pc-get-external-speedrun-time",
                              (void*)pc_get_external_speedrun_time);
  make_function_symbol_from_c("pc-get-external-race-time", (void*)pc_get_external_race_time);
  make_function_symbol_from_c("pc-get-external-highscore", (void*)pc_get_external_highscore);
  make_function_symbol_from_c("pc-get-num-external-speedrun-times",
                              (void*)pc_get_num_external_speedrun_times);
  make_function_symbol_from_c("pc-get-num-external-race-times",
                              (void*)pc_get_num_external_race_times);
  make_function_symbol_from_c("pc-get-num-external-highscores",
                              (void*)pc_get_num_external_highscores);
 */

  // setup string constants
  auto user_dir_path = file_util::get_user_config_dir();
  intern_from_c(-1, 0, "*pc-user-dir-base-path*")->value() =
      make_string_from_c(user_dir_path.string().c_str());
  auto settings_path = file_util::get_user_settings_dir(g_game_version);
  intern_from_c(-1, 0, "*pc-settings-folder*")->value() =
      make_string_from_c(settings_path.string().c_str());
  intern_from_c(-1, 0, "*pc-settings-built-sha*")->value() =
      make_string_from_c(build_revision().c_str());
}
// End PC Stuff

void InitMachineScheme() {
  make_function_symbol_from_c("put-display-env", PutDisplayEnv);
  make_function_symbol_from_c("syncv", sceGsSyncV);
  make_function_symbol_from_c("sync-path", sceGsSyncPath);
  make_function_symbol_from_c("reset-path", sceGsResetPath);
  make_function_symbol_from_c("reset-graph", sceGsResetGraph);
  make_function_symbol_from_c("dma-sync", sceDmaSync);
  make_function_symbol_from_c("gs-put-imr", sceGsPutIMR);
  make_function_symbol_from_c("gs-get-imr", sceGsGetIMR);
  make_function_symbol_from_c("gs-store-image", sceGsExecStoreImage);
  make_function_symbol_from_c("flush-cache", FlushCache);
  make_function_symbol_from_c("cpad-open", CPadOpen);
  make_function_symbol_from_c("cpad-get-data", CPadGetData);
  make_function_symbol_from_c("mouse-get-data", MouseGetData);
  make_function_symbol_from_c("keybd-get-data", KeybdGetData);
  make_function_symbol_from_c("install-handler", InstallHandler);
  make_function_symbol_from_c("install-debug-handler", InstallDebugHandler);
  make_function_symbol_from_c("file-stream-open", kopen);
  make_function_symbol_from_c("file-stream-close", kclose);
  make_function_symbol_from_c("file-stream-length", klength);
  make_function_symbol_from_c("file-stream-seek", kseek);
  make_function_symbol_from_c("file-stream-read", kread);
  make_function_symbol_from_c("file-stream-write", kwrite);
  make_function_symbol_from_c("file-stream-mkdir", kmkdir_G);
  make_function_symbol_from_c("scf-get-language", DecodeLanguage);
  make_function_symbol_from_c("scf-get-time", DecodeTime);
  make_function_symbol_from_c("scf-get-aspect", DecodeAspect);
  make_function_symbol_from_c("scf-get-volume", DecodeVolume);
  make_function_symbol_from_c("scf-get-territory", DecodeTerritory);
  make_function_symbol_from_c("scf-get-timeout", DecodeTimeout);
  make_function_symbol_from_c("scf-get-inactive-timeout", DecodeInactiveTimeout);
  make_function_symbol_from_c("dma-to-iop", dma_to_iop);
  make_function_symbol_from_c("kernel-shutdown", KernelShutdown);
  make_function_symbol_from_c("rpc-call", RpcCallNoCallback);
  make_function_symbol_from_c("rpc-busy?", RpcBusy);
  make_function_symbol_from_c("test-load-dgo-c", LoadDGOTest);

  *(undefined4 *)((int)intern_from_c(-1, 0, "*stack-top*") - 1) = 0x7ffc000;
  *(undefined4 *)((int)intern_from_c(-1, 0, "*stack-base*") - 1) = 0x7ffffff;
  *(undefined4 *)((int)intern_from_c(-1, 0, "*stack-size*") - 1) = 0x4000;
  *(u32 **)((int)intern_from_c(-1, 0, "*kernel-boot-message*") - 1) = intern_from_c(-1, 0, DebugBootMessage);
  *(String **)((int)intern_from_c(-1, 0, "*user*") - 1) = make_string_from_c(DebugBootUser);
  if (DiskBoot != 0) {
    *(u32 **)((int)intern_from_c(-1, 0, "*kernel-boot-mode*") - 1) = intern_from_c(-1, 0, "boot");
  }
  int unaff_s7_lo;
  if (strcmp(DebugBootLevel, "#f") == 0) {
    *(int *)((int)intern_from_c(-1, 0, "*kernel-boot-level*") - 1) = unaff_s7_lo;
  } else {
    *(undefined4 *)((int)intern_from_c(-1, 0, "*kernel-boot-level*") - 1) = *(undefined4 *)((int)intern_from_c((int)(short)DebugBootLevelID, 0x40, DebugBootLevel) + (SymbolString - unaff_s7_lo));
  }
  *(String **)((int)intern_from_c(-1, 0, "*kernel-boot-art-group*") - 1) = make_string_from_c(DebugBootArtGroup);

  if (DiskBoot != 0) {
    *EnableMethodSet = *EnableMethodSet + 1;
    undefined in_t0_lo;
    load_and_link_dgo_from_c("game", kglobalheap,
                             LINK_FLAG_OUTPUT_LOAD | LINK_FLAG_EXECUTE | LINK_FLAG_PRINT_LOGIN,
                             0x400000, (bool)in_t0_lo); // FIXME: why will this result in false while in jak3 it is true?
    *EnableMethodSet = *EnableMethodSet - 1;
    ;

    *(int *)(kernel_packages - 1) =
        (int)new_pair(unaff_s7_lo + FIX_SYM_GLOBAL_HEAP, *(u32 *)(unaff_s7_lo + FIX_SYM_PAIR_TYPE - 1),
                 (u32)make_string_from_c("engine"), *(u32 *)(kernel_packages - 1));
    *(int *)(kernel_packages - 1) =
        (int)new_pair(unaff_s7_lo + FIX_SYM_GLOBAL_HEAP, *(u32 *)(unaff_s7_lo + FIX_SYM_PAIR_TYPE - 1),
                 (u32)make_string_from_c("game"), *(u32 *)(kernel_packages - 1));
    *(int *)(kernel_packages - 1) =
        (int)new_pair(unaff_s7_lo + FIX_SYM_GLOBAL_HEAP, *(u32 *)(unaff_s7_lo + FIX_SYM_PAIR_TYPE - 1),
                 (u32)make_string_from_c("common"), *(u32 *)(kernel_packages - 1));
    call_goal_function_by_name("play-boot");
  }
}

}  // namespace jak3
