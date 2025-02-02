#include "fileio.h"

#include <cstring>

#include "game/kernel/common/fileio.h"

namespace jak3 {

// This file naming system was used only in development, as it loads files from the development PC
// connected to the PS2 dev-kit.
// My theory is that the developers would use this to debug their level/art tools. They could use
// these file names to quickly load in new files and see if they worked correctly with the renderer,
// without needing to create/load entire new DGO files.
// They've been adding to this file over all 3 games, so I believe it is more than just a leftover
// from early jak 1.

/*!
 * Convert a file-name like $CODE/thing to the appropriate file path on the development computer.
 */
char * DecodeFileName(const_char *name) {
  int iVar1;
  char *pcVar2;
  size_t sVar3;
  const_char *name_00;
  
  name_00 = name;
  if (*name == '$') {
    iVar1 = strncmp(name,"$TEXTURE/",9);
    if (iVar1 == 0) {
      name_00 = name + 9;
      iVar1 = 0x21;
      goto LAB_00259b04;
    }
    iVar1 = strncmp(name,"$ART_GROUP/",0xb);
    if (iVar1 == 0) {
      name_00 = name + 0xb;
      iVar1 = 0x30;
      goto LAB_00259b04;
    }
    iVar1 = strncmp(name,"$LEVEL/",7);
    if (iVar1 == 0) {
      sVar3 = strlen(name);
      name_00 = name + 7;
      if (name[(int)sVar3 + -4] == '.') {
        iVar1 = 0x35;
      }
      else {
        iVar1 = 0x27;
      }
      goto LAB_00259b04;
    }
    iVar1 = strncmp(name,"$FINAL/",6);
    if (iVar1 == 0) {
      name_00 = name + 6;
      iVar1 = 0x20;
      goto LAB_00259b04;
    }
    iVar1 = strncmp(name,"$CODE/",6);
    name_00 = name + 6;
    if (iVar1 != 0) {
      iVar1 = strncmp(name,"$RES/",5);
      if (iVar1 == 0) {
        name_00 = name + 5;
        iVar1 = 0x3b;
      }
      else {
        iVar1 = strncmp(name,"$MISC/",6);
        if (iVar1 == 0) {
          name_00 = name + 6;
          iVar1 = 0x3f;
        }
        else {
          iVar1 = strncmp(name,"$MAP/",5);
          if (iVar1 == 0) {
            name_00 = name + 5;
            iVar1 = 0x40;
          }
          else {
            iVar1 = strncmp(name,"$FLASH/",7);
            if (iVar1 != 0) {
              return (char *)0x0;
            }
            name_00 = name + 7;
            iVar1 = 0x42;
          }
        }
      }
      goto LAB_00259b04;
    }
  }
  iVar1 = 3;
LAB_00259b04:
  pcVar2 = MakeFileName(iVar1,name_00,0);
  return pcVar2;
}

/*!
 * Create a file name that looks in the appropriate folder in ND's development environment.
 * This is a bit of dumping ground for all possible files they'd load.
 */
char* MakeFileName(int type, const char* name, int new_string) {
  size_t sVar1;
  char *pcVar2;
  char *pcVar3;
  
  pcVar2 = prefix_G;
  pcVar3 = buffer_633;
  kstrcpy(buffer_633,"host:");
  char* buf = strend(buffer_633);

  char prefix_G [128];
  kstrcpy(prefix_G, FOLDER_PREFIX);

  if (type == 0x31) {
    // pcVar3 = "%sfinal/level%d/%s-vs.go";
    // name = (const char *)0x25;
    // goto LAB_00259ec4;
    sprintf(buf, "%sfinal/level%d/%s-vs.go", prefix_G, (const char *)0x25);
  } else if (type < 0x32) {
    if (type == 0x21) {
LAB_00259f40:
      sprintf(buf, "%sfinal/texture-page%d/%s.go", prefix_G, (const char *)0x8);
    } else {
      if (type < 0x22) {
        if (type == 4) {
          sprintf(buffer_633,"pad:0");
          goto LAB_00259d2c;
        } else if (type < 5) {
          if (type == 2) {
            kstrcpy(buf,"kernel/KERNELTOLISTENER");
            goto LAB_00259d2c;
          } else if (2 < type) {
            pcVar2 = "game/obj/%s.o";
            pcVar3 = buf;
LAB_00259dc8:
            sprintf(pcVar3,pcVar2,name);
            goto LAB_00259d2c;
          } else if (type != 1) {
            goto LAB_00259d2c;
          } else {
            kstrcpy(buf,"kernel/LISTENERTOKERNEL");
            goto LAB_00259d2c;
          }
        } else if (type == 6) {
          kstrcpy(buf,"kernel/KERNELTOLISTENER_LOCK");
          goto LAB_00259d2c;
        } else if (5 < type) {
          if (type != 8) {
            if (type != 0x20) {
              goto LAB_00259d2c;
            } else {
              pcVar3 = "%sfinal/%s.go";
              pcVar2 = prefix_G;
              goto LAB_00259e20;
            }
          } else {
            pcVar2 = "host0:/usr/local/sce/iop/modules/%s.irx";
            goto LAB_00259dc8;
          }
        } else {
          kstrcpy(buf, "kernel/LISTENERTOKERNEL_LOCK");
          goto LAB_00259d2c;
        }
      } else if (type == 0x26) {
        pcVar3 = "%sfinal/%s-tg.go";
        pcVar2 = prefix_G;
        goto LAB_00259e20;
      } else if (type < 0x27) {
        if (type == 0x23) {
          sprintf(buf, "%sdb/artdata%d/%s-jg.go", prefix_G, (const char *)0x8);
        } else if (type < 0x23) {
          sprintf(buf, "%sdb/artdata%d/%s-ja.go", prefix_G, (const char *)0x8);
        } else if (type == 0x24) {
          sprintf(buf, "%sdb/artdata%d/%s-ma.go", prefix_G, (const char *)0x8);
        } else if (type != 0x25) {
          goto LAB_00259d2c;
        } else {
          sprintf(buf, "%sdb/artdata%d/%s-mg.go", prefix_G, (const char *)0x8);
        }
      } else if (type < 0x2a) {
        if (type < 0x28) {
          sprintf(buf, "%sfinal/level%d/%s-bt.go", prefix_G, (const char *)0x25);
        } else {
          goto LAB_00259f40;
        }
      } else if (type != 0x30) {
        goto LAB_00259d2c;
      } else {
        pcVar3 = "%sfinal/art-group%d/%s-ag.go";
        name = (const char *)0x8;
LAB_00259ec4:
        sprintf(buf, pcVar3, prefix_G, name);
      }
    }
  } else {
    if (type == 0x3a) {
      pcVar3 = "%sfinal/res%d/game-cnt.go";
      name = &DAT_00000001;
      pcVar2 = prefix_G;
    } else if (type < 0x3b) {
      if (type == 0x35) {
        pcVar3 = "%sfinal/level%d/%s";
      } else if (0x35 < type) {
        if (type != 0x37) {
          if (type < 0x37) {
            pcVar3 = "%sfinal/dgo%d/%s.dgo";
            // LAB_00259fd0:
            name = &DAT_00000001;
            goto LAB_00259ec4;
          } else if (type != 0x38) {
            if (type != 0x39) {
              goto LAB_00259d2c;
            } else {
              pcVar3 = "game/dgo%d/%s.cgo";
              goto LAB_0025a024;
            }
          } else {
            pcVar3 = "%sfinal/dgo%d/%s.cgo";
            // LAB_00259fd0:
            name = &DAT_00000001;
            goto LAB_00259ec4;
          }
        } else {
          pcVar3 = "game/dgo%d/%s.dgo";
LAB_0025a024:
          pcVar2 = &DAT_00000001;
          goto LAB_00259e20;
        }
      } else if (type != 0x33) {
        pcVar3 = "%sfinal/dgo%d/%s.txt";
        if (type < 0x34) {
          pcVar3 = "%sfinal/res%d/%s-tx.go";
        }
        name = &DAT_00000001;
        goto LAB_00259ec4;
      } else {
        pcVar3 = "%sfinal/level%d/%s-vs.bin";
      }
LAB_00259f30:
      name = (const char *)0x25;
      goto LAB_00259ec4;
    } else if (type != 0x3f) {
      if (type < 0x40) {
        if (type == 0x3c) {
          pcVar3 = "%sfinal/sound%d/%s.bnk";
        } else if (type < 0x3c) {
          pcVar3 = "%sfinal/res%d/%s.go";
        } else if (type != 0x3d) {
          if (type != 0x3e) {
            goto LAB_00259d2c;
          } else {
            pcVar3 = "%sfinal/vagwad/%s.%s";
            goto LAB_00259ec4;
          }
        } else {
          pcVar3 = "%sfinal/music%d/%s.bnk";
        }
      } else if (type == 0x41) {
        sprintf(buf, "%sdb/artdata%d/%s-cl.go", prefix_G, (const char *)0x8);
        goto LAB_00259d2c;
      } else if (type < 0x41) {
        pcVar3 = "%sfinal/map%d/%s.go";
        name = &DAT_00000001;
        goto LAB_00259ec4;
      } else if (type != 0x42) {
        if (type != 0x301) {
          goto LAB_00259d2c;
        } else {
          pcVar3 = "%sdb/config/refplant/%s";
          pcVar2 = prefix_G;
          goto LAB_00259e20;
        }
      } else {
        pcVar3 = "%sfinal/flash%d/%s.go";
        name = &DAT_00000001;
        goto LAB_00259ec4;
      }
    } else {
      pcVar3 = "%sfinal/misc/%s";
    }
LAB_00259e20:
    sprintf(buf, pcVar3, pcVar2, name);
  }

LAB_00259d2c:
  char* result;
  if (new_string == 0) {
    result = buffer_633;
  } else {
    int l = strlen(buffer_633);
    result = (char*)kmalloc(&kglobalheapinfo, (int)l + 1, 0, "filename");
    kstrcpy(result, buffer_633);
  }

  return result;
}

}  // namespace jak3
