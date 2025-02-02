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
  char *prefix_G;
  char *buffer_633;
  kstrcpy(buffer_633, "host:");
  char* buf = strend(buffer_633);

  char prefix_G[128];
  kstrcpy(prefix_G, FOLDER_PREFIX);

  if (type == 1) {
    kstrcpy(buf, "kernel/LISTENERTOKERNEL");
  } else if (type == 2) {
    kstrcpy(buf, "kernel/KERNELTOLISTENER");

  } else if (type == 3) {
    sprintf(buf, "game/obj/%s.o", name);

  } else if (type == 4) {
    sprintf(buffer_633, "pad:0");

  } else if (type <= 5 && type <= 0x20) {
    kstrcpy(buf, "kernel/LISTENERTOKERNEL_LOCK");
  } else if (type == 6) {
    kstrcpy(buf, "kernel/KERNELTOLISTENER_LOCK");

  } else if (type == 8) {
    sprintf(buffer_633, "host0:/usr/local/sce/iop/modules/%s.irx", name);

  } else if (type == 0x20) {
    // sprintf(buf, "%sfinal/%s.go", prefix_G, name);

  } else if (type == 0x21) {
    // sprintf(buf, "%sfinal/texture-page%d/%s.go", prefix_G, (const char *)0x8);

  } else if (type == 0x22) {
    sprintf(buf, "%sdb/artdata%d/%s-ja.go", prefix_G, (const char *)0x8);

  } else if (type == 0x23) {
    sprintf(buf, "%sdb/artdata%d/%s-jg.go", prefix_G, (const char *)0x8);

  } else if (type == 0x24) {
    sprintf(buf, "%sdb/artdata%d/%s-ma.go", prefix_G, (const char *)0x8);

  } else if (type == 0x25) {
    sprintf(buf, "%sdb/artdata%d/%s-mg.go", prefix_G, (const char *)0x8);

  } else if (type == 0x26) {
    sprintf(buf, "%sfinal/%s-tg.go", prefix_G, name);

  } else if (type == 0x27) {
    sprintf(buf, "%sfinal/level%d/%s-bt.go", prefix_G, (const char *)0x25);

  } else if (type == 0x28 || type == 0x29) {
    sprintf(buf, "%sfinal/texture-page%d/%s.go", prefix_G, (const char *)0x8);

  } else if (type == 0x30) {
    // sprintf(buf, "%sfinal/art-group%d/%s-ag.go", prefix_G, (const char *)0x8);

  } else if (type == 0x31) {
    sprintf(buf, "%sfinal/level%d/%s-vs.go", prefix_G, (const char *)0x25);

  } else if (type == 0x32) {
    sprintf(buf, "%sfinal/res%d/%s-tx.go", prefix_G, &DAT_00000001);

  } else if (type == 0x33) {
    sprintf(buf, "%sfinal/level%d/%s-vs.bin", prefix_G, (const char *)0x25);

  } else if (type == 0x34) {
    sprintf(buf, "%sfinal/dgo%d/%s.txt", prefix_G, &DAT_00000001);

  } else if (type == 0x35) {
    sprintf(buf, "%sfinal/level%d/%s", prefix_G, (const char *)0x25);

  } else if (type == 0x36) {
    sprintf(buf, "%sfinal/dgo%d/%s.dgo", prefix_G, &DAT_00000001);
  } else if (type == 0x37) {
    sprintf(buf, "game/dgo%d/%s.dgo", &DAT_00000001, name);
  } else if (type == 0x38) {
    sprintf(buf, "%sfinal/dgo%d/%s.cgo", prefix_G, &DAT_00000001);
  } else if (type == 0x39) {
    sprintf(buf, "game/dgo%d/%s.cgo", &DAT_00000001, name);

  } else if (type == 0x3a) {
    sprintf(buf, "%sfinal/res%d/game-cnt.go", prefix_G, &DAT_00000001);

  } else if (type == 0x3b) {
    sprintf(buf, "%sfinal/res%d/%s.go", prefix_G, name);

  } else if (type == 0x3c) {
    sprintf(buf, "%sfinal/sound%d/%s.bnk", prefix_G, name);

  } else if (type == 0x3d) {
    sprintf(buf, "%sfinal/music%d/%s.bnk", prefix_G, name);

  } else if (type == 0x3e) {
    sprintf(buf, "%sfinal/vagwad/%s.%s", prefix_G, name);

  } else if (type == 0x3f) {
    sprintf(buf, "%sfinal/misc/%s", prefix_G, name);

  } else if (type == 0x40) {
    sprintf(buf, "%sfinal/map%d/%s.go", prefix_G, &DAT_00000001);

  } else if (type == 0x41) {
    sprintf(buf, "%sdb/artdata%d/%s-cl.go", prefix_G, (const char *)0x8);

  } else if (type == 0x42) {
    sprintf(buf, "%sfinal/flash%d/%s.go", prefix_G, &DAT_00000001);

  } else if (type == 0x301) {
    sprintf(buf, "%sdb/config/refplant/%s", prefix_G, name);
  }

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
