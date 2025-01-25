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
 * TBD
 * Modified to use std::string, and removed call to fflush.
 */
void InitParms(int argc, const char** argv) {  
  if (argc != 0) {
    char *__src;
    do {
      if (strcmp(*argv,"-cd") == 0) {
        Msg(6,"dkernel: cd mode\n");
        reboot_G_isodrv_G_overlord_S = 0;
LAB_00268668:
        modsrc_S = 0;
        fs_S_FS_INITIALIZED_W = (char **)0x0;
        isodrv_G_reboot_G = 0;
LAB_00268670:
        argc = argc + -1;
      } else if (strcmp(*argv,"-cd-local-overlord") == 0) {
        Msg(6,"dkernel: cd local-overlord mode\n");
        reboot_G_isodrv_G_overlord_S = 1;
        goto LAB_00268668;
      } else if (strcmp(*argv,"-cddata") == 0) {
        Msg(6,"dkernel: cddata mode\n");
        fs_S_FS_INITIALIZED_W = (char **)0x0;
LAB_00268710:
        isodrv_G_reboot_G = 1;
        modsrc_S = 1;
        reboot_G_isodrv_G_overlord_S = 1;
        goto LAB_00268670;
      } else if (strcmp(*argv,"-demo") == 0) {
        Msg(6,"dkernel: demo mode\n");
        __src = "demo";
LAB_00268760:
        argc = argc + -1;
        strcpy(DebugBootMessage,__src);
        goto LAB_00268674;
      } else if (strcmp(*argv,"-kiosk") == 0) {
        Msg(6,"dkernel: kiosk mode\n");
        __src = "kiosk";
        goto LAB_00268760;
      } else if (strcmp(*argv,"-beta") == 0) {
        Msg(6,"dkernel: beta mode\n");
        __src = "beta";
        goto LAB_00268760;
      } else if (strcmp(*argv,"-preview") == 0) {
        Msg(6,"dkernel: preview mode\n");
        __src = "preview";
        goto LAB_00268760;
      } else if (strcmp(*argv,"-fakeiso") == 0) {
        Msg(6,"dkernel: fakeiso mode\n");
        fs_S_FS_INITIALIZED_W = (char **)0x1;
        goto LAB_00268710;
      } else if (strcmp(*argv,"-boot") == 0) {
        Msg(6,"dkernel: boot mode\n");
        DiskBoot = 1;
        MasterDebug = 0;
LAB_00268884:
        DebugSegment = 0;
        goto LAB_00268670;
      } else if (strcmp(*argv,"-debug-boot") == 0) {
        Msg(6,"dkernel: debug-boot mode\n");
        DebugSegment = 1;
        MasterDebug = 0;
        DiskBoot = 1;
        goto LAB_00268670;
      } else if (strcmp(*argv,"-debug") == 0) {
        Msg(6,"dkernel: debug mode\n");
        MasterDebug = 1;
        DebugSegment = 1;
        goto LAB_00268670;
      } else if (strcmp(*argv,"-debug-mem") == 0) {
        Msg(6,"dkernel: debug-mem mode\n");
        MasterDebug = 1;
        goto LAB_00268884;
      } else if (strcmp(*argv,"-overlord") == 0) {
        Msg(6,"dkernel: overlord 1 mode\n");
        _USE_OVERLORD2 = 0;
        goto LAB_00268670;
      } else if (strcmp(*argv,"-overlord2") == 0) {
        Msg(6,"dkernel: overlord 2 mode\n");
        _USE_OVERLORD2 = 1;
        goto LAB_00268670;
      } else if (strcmp(*argv,"-debug-symbols") == 0) {
        Msg(6,"dkernel: debug-symbols on\n");
        DebugSymbols = 1;
        goto LAB_00268670;
      } else if (strcmp(*argv,"-no-debug-symbols") == 0) {
        Msg(6,"dkernel: debug-symbols off\n");
        DebugSymbols = 0;
        goto LAB_00268670;
      } else if ((strcmp(*argv,"-level") == 0) && (1 < argc)) {
        argc = argc + -2;
        Msg(6,"dkernel: level %s %s\n",argv[1],argv[2]);
        strcpy(DebugBootLevel,argv[1]);
        DebugBootLevelID = DecodeSymbolId(atoi(argv[2])) + 1;
        argv = argv + 2;
        goto LAB_00268670;
      } else if ((strcmp(*argv,"-user") == 0) && (1 < argc)) {
        Msg(6,"dkernel: user %s\n",argv[1]);
        strcpy(DebugBootUser,argv[1]);
LAB_00268ac4:
        argc = argc + -1;
        argv = argv + 1;
        goto LAB_00268670;
      } else if (strcmp(*argv,"-art") == 0) {
        if (1 < argc) {
          Msg(6,"dkernel: art-group %s\n",argv[1]);
          if (strlen(argv[1]) != 0) {
            strcpy(DebugBootArtGroup,argv[1]);
            strcpy(DebugBootMessage,"art-group");
          }
          goto LAB_00268ac4;
        } else {
          argc = argc + -1;
          goto LAB_00268674;
        }
      } else {
        argc = argc + -1;
        goto LAB_00268674;
      }
LAB_00268674:
      argv = argv + 1;
    } while (argc != 0);
  }
  fflush(*(FILE **)(_impure_ptr + 8));
}

/*!
 * This is mostly copy-pasted from jak2 and very simplified until we have overlord 2.
 */
s32 InitIOP() {
  bool bVar1;
  int iVar2;
  int iVar3;
  size_t sVar4;
  undefined8 uVar5;
  long lVar6;
  char *pcVar7;
  char *pcVar8;
  undefined8 *puVar9;
  undefined8 *puVar10;
  char acStack_5b0 [1024];
  undefined auStack_1b0 [8];
  undefined *local_1a8;
  undefined8 local_170 [6];
  undefined2 local_140;
  undefined local_13e;
  undefined local_13d;
  undefined local_13c;
  undefined local_13b;
  undefined local_13a;
  undefined local_139;
  char cStack_130;
  char acStack_12f [255];
  undefined auStack_30 [4];
  int local_2c [3];
  
  FUN_0027c260_usb();
  if ((((dnas_S_DNAS_INITIALIZED_W == 0) && (fs_S_FS_INITIALIZED_W != (char **)0x0)) &&
      (modsrc_S != 0)) && ((reboot_G_isodrv_G_overlord_S != 0 && (isodrv_G_reboot_G != 0)))) {
    cd_S_INITIALIZE_CD_W = 0;
  }
  else {
    cd_S_INITIALIZE_CD_W = 1;
  }
  Msg(6,"dkernel: boot:%d dbg:%d mem:%d syms:%d fs:%d mod:%d ovl:%d ioprp:%d cd:%d dnas:%d\n",
      DiskBoot,MasterDebug,DebugSegment,DebugSymbols,fs_S_FS_INITIALIZED_W,modsrc_S,
      reboot_G_isodrv_G_overlord_S,isodrv_G_reboot_G,(uint)cd_S_INITIALIZE_CD_W,
      dnas_S_DNAS_INITIALIZED_W);
  SifInitRpc(0);
  IOP_CALLED_W = 1;
  InitCD();
  do {
    FUN_002684f4_cd_dvd_disk_drive_ready();
    MakeDriverPath_S(acStack_5b0,"dnas300.img",(long)isodrv_G_reboot_G,true);
    sVar4 = strlen(acStack_5b0);
    if (0x45 < sVar4) {
      iVar2 = 0x45;
      pcVar7 = "dkernel: error; invalid ioprp path; %d chars max\n";
      goto LAB_002697f0;
    }
    printf("dkernel: Rebooting IOP using \"%s\"...",acStack_5b0);
    iVar2 = SifIopReboot(acStack_5b0);
    if (iVar2 == 0) {
      pcVar7 = "  Failed, retrying...\n";
    }
    else {
      printf("  Syncing...");
      do {
        lVar6 = sceSifSyncIop();
      } while (lVar6 == 0);
      pcVar7 = "  Done.\n";
    }
    printf(pcVar7);
  } while (iVar2 == 0);
  SifInitRpc(0);
  sceSifInitIopHeap();
  sceSifLoadFileReset();
  uVar5 = sceFsReset();
  InitCD();
  SifLoadModule_G(uVar5);
  FUN_002684f4_cd_dvd_disk_drive_ready();
  DAT_00284af0_sce_or_sif_or_iop_or_fs_ok_W = 1;
  iVar3 = sceSifSearchModuleByName("cdvd_ee_driver");
  iVar2 = iVar3;
  if (((iVar3 < 0) || (iVar2 = sceSifStopModule(iVar3,0,0,auStack_30), iVar2 < 0)) ||
     (iVar2 = sceSifUnloadModule(iVar3), iVar2 < 0)) {
    pcVar7 = "dkernel: unload cdvd_ee_driver failed %d\n";
  }
  else {
    DumpIOPMemStats_Q("Initial IOP mem stats");
    lVar6 = InitUnderlord_S();
    if (lVar6 < 0) goto LAB_002697f8;
    lVar6 = FUN_0027483c_implicit_dkernel(0x282fd8);
    if (lVar6 == 0) {
      DAT_00282fe6 = 0;
      memset(&DAT_00282fd8,0x30,0xe);
      CHAR_J_00282fdc = CHAR_J_00282fdc ^ 0x71;
      s_C20121227_00282fdd[0] = s_C20121227_00282fdd[0] ^ 0x73;
    }
    RUN_AS_DEMO_W = CHAR_J_00282fdc == 'T';
    do {
      iVar2 = loadModuleByString_G
                        (&DAT_00282fe8_arg_for_module,s_BOOT2___cdrom0__SCES_532_86_1_VE_00282ff0);
    } while (iVar2 == 0);
    MakeDriverPath_S(acStack_5b0,"overlay.bin",(long)modsrc_S,false);
    do {
      lVar6 = FUN_00274684_implicit_dkernel(acStack_5b0,auStack_1b0);
    } while (lVar6 < 0);
    PTR_DAT_002833f0 = local_1a8;
    bVar1 = fs_S_FS_INITIALIZED_W != (char **)0x0;
    puVar9 = local_170;
    puVar10 = &DAT_0027df98;
    do {
      uVar5 = puVar10[1];
      *puVar9 = *puVar10;
      puVar9[1] = uVar5;
      puVar10 = puVar10 + 2;
      puVar9 = puVar9 + 2;
    } while (puVar10 !=
             (undefined8 *)
             "dkernel: boot:%d dbg:%d mem:%d syms:%d fs:%d mod:%d ovl:%d ioprp:%d cd:%d dnas:%d\n");
    iVar2 = 0;
    do {
      MakeVagwadPath_S(acStack_5b0,bVar1,iVar2);
      lVar6 = FUN_00274684_implicit_dkernel(acStack_5b0,auStack_1b0);
      if (lVar6 == 0) {
        AUDIO_LANGUAGE_MASK_G = AUDIO_LANGUAGE_MASK_G | *(uint *)((int)local_170 + iVar2 * 4);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0xc);
    printf("dkernel: audio language mask = 0x%08x\n",AUDIO_LANGUAGE_MASK_G);
    if (RUN_AS_DEMO_W != '\0') {
      iVar2 = strcmp(DebugBootMessage,"demo");
      if (iVar2 == 0) {
LAB_002699e0:
        masterConfig.aspect = 1;
      }
      else {
        iVar2 = strcmp(DebugBootMessage,"demo-shared");
        masterConfig.aspect = 0;
        if (iVar2 == 0) goto LAB_002699e0;
      }
      local_13b = 0;
      local_13a = 0;
      local_139 = 1;
      local_13d = 1;
      masterConfig.language = 0;
      masterConfig.inactive_timeout = 0;
      masterConfig.volume = 100;
      local_13e = (undefined)masterConfig.aspect;
      masterConfig.timeout = 0;
      local_140 = 0xfe20;
      local_13c = 1;
      sceScfSetT10kConfig(&local_140);
    }
    local_2c[0] = 1;
    lVar6 = loadIOPModuleAndStuff_W("dev9.irx",0,(char *)0x0,(long)(int)local_2c,(long)modsrc_S);
    if (lVar6 < 0) goto LAB_002697f8;
    DEV9_PRESENT_W = local_2c[0] != 1;
    if (DEV9_PRESENT_W) {
      pcVar7 = "";
    }
    else {
      pcVar7 = "not ";
    }
    DEV9_PRESENT_PROXY_W = DEV9_PRESENT_W;
    printf("dkernel: dev9 %spresent\n",pcVar7);
    initializePowerOffHandler_W();
    lVar6 = loadIOPModuleAndStuff_W("sio2man.irx",0,(char *)0x0,0,(long)modsrc_S);
    if ((((lVar6 < 0) ||
         (lVar6 = loadIOPModuleAndStuff_W("sio2d.irx",0,(char *)0x0,0,(long)modsrc_S), lVar6 < 0))
        || (lVar6 = loadIOPModuleAndStuff_W("dbcman.irx",0,(char *)0x0,0,(long)modsrc_S), lVar6 < 0)
        ) || (lVar6 = loadIOPModuleAndStuff_W("mc2_d.irx",0,(char *)0x0,0,(long)modsrc_S), lVar6 < 0
             )) goto LAB_002697f8;
    lVar6 = loadIOPModuleAndStuff_W("ds2o_d.irx",0,(char *)0x0,0,(long)modsrc_S);
    if (((lVar6 < 0) ||
        (lVar6 = loadIOPModuleAndStuff_W("ds2o_d.irx",0,(char *)0x0,0,(long)modsrc_S), lVar6 < 0))
       || ((lVar6 = loadIOPModuleAndStuff_W("libsd.irx",0,(char *)0x0,0,(long)modsrc_S), lVar6 < 0
           || ((lVar6 = loadIOPModuleAndStuff_W("usbd.irx",0x2b,"hub=1",0,(long)modsrc_S), lVar6 < 0
               || (lVar6 = loadIOPModuleAndStuff_W("usbkeybd.irx",0,(char *)0x0,0,(long)modsrc_S),
                  lVar6 < 0)))))) goto LAB_002697f8;
    if (_USE_OVERLORD2 == 0) {
      pcVar7 = "989nostr.irx";
    }
    else {
      pcVar7 = "989nsnm.irx";
    }
    lVar6 = loadIOPModuleAndStuff_W(pcVar7,9,"do_rpc=0",0,(long)modsrc_S);
    if ((lVar6 < 0) ||
       (lVar6 = loadIOPModuleAndStuff_W("lgaud.irx",0x2f,"thpri=53",0,(long)modsrc_S), lVar6 < 0))
    goto LAB_002697f8;
    strcpy(&cStack_130,*(char **)((int)fs_S_FS_INITIALIZED_W * 4 + 0x283410));
    sVar4 = strlen(&cStack_130);
    pcVar7 = acStack_12f + (int)sVar4;
    iVar2 = strncmp(DebugBootMessage,"demo",4);
    if (iVar2 == 0) {
      strcpy(pcVar7,"SCREEN1.DEE");
switchD_00269d84_caseD_5:
      pcVar8 = "SCREEN1.EUR";
    }
    else {
      if (false) goto switchD_00269d84_caseD_5;
      switch(masterConfig.language) {
      case 1:
        pcVar8 = "SCREEN1.FRE";
        break;
      case 2:
        pcVar8 = "SCREEN1.GER";
        break;
      case 3:
        pcVar8 = "SCREEN1.SPA";
        break;
      case 4:
        pcVar8 = "SCREEN1.ITA";
        break;
      default:
        goto switchD_00269d84_caseD_5;
      case 9:
        pcVar8 = "SCREEN1.POR";
      }
    }
    strcpy(pcVar7,pcVar8);
    sVar4 = strlen(pcVar7);
    if (_USE_OVERLORD2 == 0) {
      pcVar8 = "overlord.irx";
    }
    else {
      pcVar8 = "overlrd2.irx";
    }
    lVar6 = loadIOPModuleAndStuff_W
                      (pcVar8,(long)(int)(pcVar7 + (((int)sVar4 + 1) - (int)&cStack_130)),
                       &cStack_130,0,(long)reboot_G_isodrv_G_overlord_S);
    if (lVar6 < 0) goto LAB_002697f8;
    IOP_RUNNING_W = 1;
    iVar2 = sceDbcInit_G();
    if (iVar2 == 1) {
      iVar2 = sceMc2Init_G_Proxy();
      if (iVar2 == 1) {
        FUN_00279c54();
        CatalogOverlayModules_S();
        Msg(6,"InitIOP OK\n");
        FUN_0027c2a4_usb();
        return 0;
      }
      pcVar7 = "dkernel: error; memcard driver init failed %d\n";
    }
    else {
      pcVar7 = "dkernel: error; DBC driver init failed %d\n";
    }
  }
LAB_002697f0:
  MsgErr(pcVar7,iVar2);
LAB_002697f8:
  FUN_0027c2a4_usb();
  return -1;
}

// NOTE: This is a new function
void InitVideo() {
  bool bVar1;
  int iVar2;
  undefined auStack_b0 [96];
  ulong local_50;
  ulong local_48;
  ulong local_40;
  ulong local_38;
  undefined local_30;
  undefined local_2f;
  undefined local_2e;
  
  thunkSceGsResetGraph(0,1,3,0);
  sceGsSetDefLoadImage(auStack_b0,0x2c00,8,0,0,0,0x200,0xe0);
  FlushCache(0);
  sceGsExecLoadImage(auStack_b0,0x1000000);
  sceGsSetDefLoadImage(auStack_b0,0x2c00,8,0,0,0xe0,0x200,0xe0);
  FlushCache(0);
  sceGsExecLoadImage(auStack_b0,0x1070000);
  memset(&local_50,0,0x28);
  local_48 = local_48 & 0xfffffffffffffffd | 1;
  local_50 = local_50 & 0xfffffffffffffffd | 0x60;
  local_40 = local_40 & 0xffc00000fff00000 | 0x1160;
  if (false) {
    trap(7);
  }
  local_38 = local_38 & 0xff800000e0000000 | 0x1bf9ff0204a28c;
  local_30 = 0;
  local_2f = 0;
  local_2e = 0;
  thunkSceGsSyncV(0);
  sceGsPutDispEnv(&local_50);
  iVar2 = 4;
  do {
    thunkSceGsSyncV(0);
    bVar1 = -1 < iVar2;
    iVar2 = iVar2 + -1;
  } while (bVar1);
  local_50 = local_50 | 2;
  sceGsPutDispEnv(&local_50);
  return;
}

int InitMachine() {
  bool bVar1;
  int iVar2;
  u8 *mem;
  s32 sVar3;
  uint uVar4;
  long lVar5;
  char *format;
  int iVar6;
  undefined4 local_50;
  undefined4 local_4c;
  
  iVar2 = FUN_00268b40();
  iVar6 = iVar2 + -0x4000;
  mem = (u8 *)malloc((long)iVar6);
  if (mem == (u8 *)0x0) {
    format = "dkernel: out of memory, cannot allocate global heap; exiting\n";
  }
  else {
    bVar1 = false;
    if ((MasterDebug != 0) || (DebugSegment != 0)) {
      bVar1 = 0x4ffffff < (ulong)(long)iVar6;
    }
    sVar3 = 0x5000000;
    if (!bVar1) {
      sVar3 = iVar6;
    }
    kinitheap((kheapinfo *)&DAT_0025bb70,mem,sVar3);
    kmemopen_from_c((kheapinfo *)&DAT_0025bb70,"global");
    kmemopen_from_c((kheapinfo *)&DAT_0025bb70,"scheme-globals");
    if (bVar1) {
      kinitheap(kdebugheap,mem + 0x5000000,iVar2 + -0x5004000);
    }
    else {
      kdebugheap = (kheapinfo *)0x0;
    }
    init_output();
    sVar3 = InitIOP();
    if (sVar3 != 0) {
      return sVar3;
    }
    sceGsResetPath();
    InitVideo();
    FlushCache(0);
    FlushCache(2);
    thunkSceGsSyncV(0);
    lVar5 = scePad2Init(0);
    if (lVar5 != 1) {
      MsgErr("dkernel: scePad2Init() failed; result %d\n",lVar5);
      return -1;
    }
    memset(&local_50,0,0x20);
    local_4c = 0;
    local_50 = 2;
    DAT_00283458_libpad = scePad2CreateSocket(&local_50,0x283480);
    local_4c = 1;
    lVar5 = scePad2CreateSocket(&local_50,0x283580);
    DAT_0028345c_libpad = (undefined4)lVar5;
    if ((DAT_00283458_libpad < 0) || (lVar5 < 0)) {
      MsgErr("dkernel: scePad2CreateSocket() failed; 0 = 0x%08x, 1 = 0x%08x\n",DAT_00283458_libpad,
             lVar5);
    }
    if (MasterDebug != 0) {
      InitGoalProto();
    }
    Msg(6,"kernel: InitRPC\n");
    sVar3 = InitRPC();
    if (sVar3 == 0) {
      reset_output();
      clear_print();
      uVar4 = InitHeapAndSymbol();
      if ((uVar4 & 0xfff00000) == 0xfff00000) {
        return uVar4;
      }
      Msg(6,"kernel: InitListenerConnect\n");
      InitListenerConnect();
      Msg(6,"kernel: InitCheckListener\n");
      InitCheckListener();
      Msg(6,"kernel: machine started\n");
      return 0;
    }
    format = "dkernel: fatal error; InitRPC() failed\n";
  }
  MsgErr(format);
  return -1;
}

int StopIOP_G() {
  int iVar1;
  
  iVar1 = Is_RPC_Initialized_G();
  if ((iVar1 != 0) && (IOP_RUNNING_W != '\0')) {
    DAT_002d2d82 = 0x10;
    RpcSync(1);
    iVar1 = RpcCallProxy(1,0,false,&DAT_002d2d80,0x30,(void *)0x0,0);
    IOP_RUNNING_W = '\0';
  }
  return iVar1;
}

int ShutdownMachine(int reasonIndex) {
  long lVar1;
  char *pcVar2;
  
  if (POWERING_OFF_W) {
    reasonIndex = 3;
  }
  if ((uint)reasonIndex < 4) {
    pcVar2 = (&SHUTDOWN_MACHINE_REASONS_W)[reasonIndex];
  }
  else {
    pcVar2 = "*invalid*";
  }
  Msg(6,"kernel: machine shutdown (reason=%d, %s)\n",reasonIndex,pcVar2);
  CloseListener();
  ShutdownGoalProto();
  StopIOP_G();
  lVar1 = knet_eenet_shutdown_Q();
  if (-1 < lVar1) {
    while (lVar1 = knet_eenet_poll_is_shutdown_G(), lVar1 == 1) {
      sceKernelDelayThread_G(10000);
    }
  }
  lVar1 = FUN_00273870_mc();
  if (lVar1 != 0) {
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
 */
u64 kopen(u64 fs,u64 name,u64 mode) {
  s32 sVar1;
  undefined4 *puVar2;
  char *__format;
  int iVar3;
  int iVar4;
  int unaff_s7_lo;
  const_char acStack_a0 [128];
  
  puVar2 = (undefined4 *)fs;
  iVar4 = (int)name;
  puVar2[2] = iVar4;
  iVar3 = iVar4 + 5;
  *puVar2 = 0;
  puVar2[1] = (int)mode;
  if (*(char *)(iVar4 + 4) == '/') {
    __format = "%s";
  }
  else {
    __format = "host:%s";
    iVar3 = iVar4 + 4;
  }
  sprintf(acStack_a0,__format,iVar3);
  iVar4 = (int)mode - unaff_s7_lo;
  iVar3 = strcmp((char *)(*(int *)(iVar4 + SymbolString) + 4),"read");
  sVar1 = 1;
  if (iVar3 != 0) {
    iVar3 = strcmp((char *)(*(int *)(iVar4 + SymbolString) + 4),"append");
    sVar1 = 0x202;
    if (iVar3 != 0) {
      sVar1 = 0x602;
    }
  }
  sVar1 = sceOpen(acStack_a0,sVar1);
  puVar2[3] = sVar1;
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
    count_618 = count_618 + -1;
    *(uint *)ptr = uVar1 & 0xfffffffd;
    sceGsPutDispEnv();
    *(uint *)ptr = *(uint *)ptr & 0xfffffffd | (uVar1 >> 1 & 1) << 1;
  }
  return;
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
  u32 *puVar1;
  u32 *puVar2;
  String *pSVar3;
  int iVar4;
  u64 uVar5;
  undefined in_t0_lo;
  int unaff_s7_lo;
  
  make_function_symbol_from_c("put-display-env",PutDisplayEnv);
  make_function_symbol_from_c("syncv",thunkSceGsSyncV);
  make_function_symbol_from_c("sync-path",sceGsSyncPath);
  make_function_symbol_from_c("reset-path",sceGsResetPath);
  make_function_symbol_from_c("reset-graph",thunkSceGsResetGraph);
  make_function_symbol_from_c("dma-sync",sceDmaSync);
  make_function_symbol_from_c("gs-put-imr",sceGsPutIMR);
  make_function_symbol_from_c("gs-get-imr",sceGsGetIMR);
  make_function_symbol_from_c("gs-store-image",sceGsExecStoreImage);
  make_function_symbol_from_c("flush-cache",FlushCache);
  make_function_symbol_from_c("cpad-open",CPadOpen);
  make_function_symbol_from_c("cpad-get-data",CPadGetData);
  make_function_symbol_from_c("mouse-get-data",MouseGetData);
  make_function_symbol_from_c("keybd-get-data",KeybdGetData);
  make_function_symbol_from_c("install-handler",InstallHandler);
  make_function_symbol_from_c("install-debug-handler",InstallDebugHandler);
  make_function_symbol_from_c("file-stream-open",kopen);
  make_function_symbol_from_c("file-stream-close",kclose);
  make_function_symbol_from_c("file-stream-length",klength);
  make_function_symbol_from_c("file-stream-seek",kseek);
  make_function_symbol_from_c("file-stream-read",kread);
  make_function_symbol_from_c("file-stream-write",kwrite);
  make_function_symbol_from_c("file-stream-mkdir",kmkdir_G);
  make_function_symbol_from_c("scf-get-language",DecodeLanguage);
  make_function_symbol_from_c("scf-get-time",DecodeTime);
  make_function_symbol_from_c("scf-get-aspect",DecodeAspect);
  make_function_symbol_from_c("scf-get-volume",DecodeVolume);
  make_function_symbol_from_c("scf-get-territory",DecodeTerritory);
  make_function_symbol_from_c("scf-get-timeout",DecodeTimeout);
  make_function_symbol_from_c("scf-get-inactive-timeout",DecodeInactiveTimeout);
  make_function_symbol_from_c("dma-to-iop",dma_to_iop);
  make_function_symbol_from_c("kernel-shutdown",KernelShutdown);
  make_function_symbol_from_c("rpc-call",RpcCallProxy);
  make_function_symbol_from_c("rpc-busy?",RpcBusy);
  make_function_symbol_from_c("test-load-dgo-c",LoadDGOTest);
  puVar1 = intern_from_c(-1,0,"*stack-top*");
  *(undefined4 *)((int)puVar1 + -1) = 0x7ffc000;
  puVar1 = intern_from_c(-1,0,"*stack-base*");
  *(undefined4 *)((int)puVar1 + -1) = 0x7ffffff;
  puVar1 = intern_from_c(-1,0,"*stack-size*");
  *(undefined4 *)((int)puVar1 + -1) = 0x4000;
  puVar1 = intern_from_c(-1,0,"*kernel-boot-message*");
  puVar2 = intern_from_c(-1,0,DebugBootMessage);
  *(u32 **)((int)puVar1 + -1) = puVar2;
  puVar1 = intern_from_c(-1,0,"*user*");
  pSVar3 = make_string_from_c(DebugBootUser);
  *(String **)((int)puVar1 + -1) = pSVar3;
  if (DiskBoot != 0) {
    puVar1 = intern_from_c(-1,0,"*kernel-boot-mode*");
    puVar2 = intern_from_c(-1,0,"boot");
    *(u32 **)((int)puVar1 + -1) = puVar2;
  }
  puVar1 = intern_from_c(-1,0,"*kernel-boot-level*");
  iVar4 = strcmp(DebugBootLevel,"#f");
  if (iVar4 == 0) {
    *(int *)((int)puVar1 + -1) = unaff_s7_lo;
  }
  else {
    puVar2 = intern_from_c((int)(short)DebugBootLevelID,0x40,DebugBootLevel);
    *(undefined4 *)((int)puVar1 + -1) = *(undefined4 *)((int)puVar2 + (SymbolString - unaff_s7_lo));
  }
  puVar1 = intern_from_c(-1,0,"*kernel-boot-art-group*");
  pSVar3 = make_string_from_c(DebugBootArtGroup);
  *(String **)((int)puVar1 + -1) = pSVar3;
  if (DiskBoot != 0) {
    *EnableMethodSet = *EnableMethodSet + 1;
    load_and_link_dgo_from_c("game",(kheapinfo *)&DAT_0025bb70,0xd,0x400000,(bool)in_t0_lo);
    iVar4 = kernel_packages;
    *EnableMethodSet = *EnableMethodSet + -1;
    pSVar3 = make_string_from_c("engine");
    uVar5 = new_pair(unaff_s7_lo + 0xa0,*(u32 *)(unaff_s7_lo + 0x6f),(u32)pSVar3,
                     *(u32 *)(kernel_packages + -1));
    *(int *)(iVar4 + -1) = (int)uVar5;
    iVar4 = kernel_packages;
    pSVar3 = make_string_from_c("game");
    uVar5 = new_pair(unaff_s7_lo + 0xa0,*(u32 *)(unaff_s7_lo + 0x6f),(u32)pSVar3,
                     *(u32 *)(kernel_packages + -1));
    *(int *)(iVar4 + -1) = (int)uVar5;
    iVar4 = kernel_packages;
    pSVar3 = make_string_from_c("common");
    uVar5 = new_pair(unaff_s7_lo + 0xa0,*(u32 *)(unaff_s7_lo + 0x6f),(u32)pSVar3,
                     *(u32 *)(kernel_packages + -1));
    *(int *)(iVar4 + -1) = (int)uVar5;
    call_goal_function_by_name("play-boot");
    return;
  }
  return;
}

}  // namespace jak3
