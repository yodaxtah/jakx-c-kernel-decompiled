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
char* DecodeFileName(const char* name) {
  char* result;

  if (name[0] == '$') {
    if (strncmp(name, "$TEXTURE/", 9) == 0) {
      result = MakeFileName(TX_PAGE_FILE_TYPE, name + 9, 0);
    } else if (strncmp(name, "$ART_GROUP/", 0xb) == 0) {
      result = MakeFileName(ART_GROUP_FILE_TYPE, name + 0xb, 0);
    } else if (strncmp(name, "$LEVEL/", 7) == 0) {
      size_t len = strlen(name);
      if (name[(int)len - 4] == '.') {
        result = MakeFileName(LEVEL_WITH_EXTENSION_FILE_TYPE, name + 7, 0);
      } else {
        result = MakeFileName(LEVEL_FILE_TYPE, name + 7, 0);
      }
    } else if (strncmp(name, "$FINAL/", 6) == 0) {
      result = MakeFileName(DATA_FILE_TYPE, name + 6, 0);
    } else if (strncmp(name, "$CODE/", 6) == 0) {
      result = MakeFileName(CODE_FILE_TYPE, name + 6, 0);
    } else if (strncmp(name, "$RES/", 5) == 0) {
      result = MakeFileName(RES_FILE_TYPE, name + 5, 0);
    } else if (strncmp(name, "$MISC/", 6) == 0) {
      result = MakeFileName(MISC_FILE_TYPE, name + 6, 0);
    } else if (strncmp(name, "$MAP/", 5) == 0) {
      result = MakeFileName(MAP_FILE_TYPE, name + 5, 0);
    } else if (strncmp(name, "$FLASH/", 7) == 0) {
      result = MakeFileName(FLASH_FILE_TYPE, name + 7, 0);
    } else {
      result = nullptr;
    }
  } else {
    return MakeFileName(CODE_FILE_TYPE, name, 0);
  }
  return result;
}

/*!
 * Create a file name that looks in the appropriate folder in ND's development environment.
 * This is a bit of dumping ground for all possible files they'd load.
 * DONE
 */
char* MakeFileName(int type, const char* name, int new_string) {
  char *prefix;
  char *buffer_633;
  kstrcpy(buffer_633, "host:");
  char* buf = strend(buffer_633);

  char prefix[128];
  kstrcpy(prefix, FOLDER_PREFIX);

  switch (type) {
    case LISTENER_TO_KERNEL_FILE_TYPE:
      kstrcpy(buf, "kernel/LISTENERTOKERNEL");
      break;
    case KERNEL_TO_LISTENER_FILE_TYPE:
      kstrcpy(buf, "kernel/KERNELTOLISTENER");
      break;

    case CODE_FILE_TYPE:
      sprintf(buf, "game/obj/%s.o", name);
      break;

    case GAMEPAD_FILE_TYPE:
      sprintf(buffer_633, "pad:0");
      break;

    case LISTENER_TO_KERNEL_LOCK_FILE_TYPE:
      kstrcpy(buf, "kernel/LISTENERTOKERNEL_LOCK");
      break;
    case KERNEL_TO_LISTENER_LOCK_FILE_TYPE:
      kstrcpy(buf, "kernel/KERNELTOLISTENER_LOCK");
      break;

    case IOP_MODULE_FILE_TYPE:  // 8
      sprintf(buffer_633, "host0:/usr/local/sce/iop/modules/%s.irx", name);
      break;

    case DATA_FILE_TYPE:  // 0x20
      sprintf(buf, "%sfinal/%s.go", prefix, name);
      break;

    case TX_PAGE_FILE_TYPE:  // 0x21
      sprintf(buf, "%sfinal/texture-page%d/%s.go", prefix, TX_PAGE_VERSION, name);
      break;

    case JA_FILE_TYPE:  // 0x22
      sprintf(buf, "%sdb/artdata%d/%s-ja.go", prefix, ART_FILE_VERSION, name);
      break;

    case JG_FILE_TYPE:  // 0x23
      sprintf(buf, "%sdb/artdata%d/%s-jg.go", prefix, ART_FILE_VERSION, name);
      break;

    case MA_FILE_TYPE:  // 0x24
      sprintf(buf, "%sdb/artdata%d/%s-ma.go", prefix, ART_FILE_VERSION, name);
      break;

    case MG_FILE_TYPE:  // 0x25
      sprintf(buf, "%sdb/artdata%d/%s-mg.go", prefix, ART_FILE_VERSION, name);
      break;

    case TG_FILE_TYPE:
      sprintf(buf, "%sfinal/%s-tg.go", prefix, name);
      break;

    case LEVEL_FILE_TYPE:  // 0x27
      sprintf(buf, "%sfinal/level%d/%s-bt.go", prefix, LEVEL_FILE_VERSION, name);
      break;

    case 0x28:  // 0x28
    case 0x29:  // 0x29
      sprintf(buf, "%sfinal/texture-page%d/%s.go", prefix, ART_FILE_VERSION, name);
      break;

    case ART_GROUP_FILE_TYPE:  // 0x30
      // sprintf(buf, "%sfinal/art-group%d/%s-ag.go", prefix, ART_FILE_VERSION, name);
      break;

    case VS_FILE_TYPE:  // 0x31
      sprintf(buf, "%sfinal/level%d/%s-vs.go", prefix, LEVEL_FILE_VERSION, name);
      break;

    case TX_FILE_TYPE:  // 0x32
      sprintf(buf, "%sfinal/res%d/%s-tx.go", prefix, DGO_FILE_VERSION, name);
      break;

    case VS_BIN_FILE_TYPE:  // 0x33
      sprintf(buf, "%sfinal/level%d/%s-vs.bin", prefix, LEVEL_FILE_VERSION, name);
      break;

    case DGO_TXT_FILE_TYPE:  // 0x34
      sprintf(buf, "%sfinal/dgo%d/%s.txt", prefix, DGO_FILE_VERSION, name);
      break;

    case LEVEL_WITH_EXTENSION_FILE_TYPE:  // 0x35
      sprintf(buf, "%sfinal/level%d/%s", prefix, LEVEL_FILE_VERSION, name);
      break;

    case DATA_DGO_FILE_TYPE:  // 0x36
      sprintf(buf, "%sfinal/dgo%d/%s.dgo", prefix, DGO_FILE_VERSION, name);
      break;
    case GAME_DGO_FILE_TYPE:  // 0x37
      sprintf(buf, "game/dgo%d/%s.dgo", DGO_FILE_VERSION, name);
      break;
    case DATA_CGO_FILE_TYPE:  // 0x38
      sprintf(buf, "%sfinal/dgo%d/%s.cgo", prefix, DGO_FILE_VERSION, name);
      break;
    case GAME_CGO_FILE_TYPE:  // 0x39
      sprintf(buf, "game/dgo%d/%s.cgo", DGO_FILE_VERSION, name);
      break;

    case CNT_FILE_TYPE:  // 0x3a
      sprintf(buf, "%sfinal/res%d/game-cnt.go", prefix, DGO_FILE_VERSION);
      break;

    case RES_FILE_TYPE:  // 0x3b
      sprintf(buf, "%sfinal/res%d/%s.go", prefix, /*1,*/ name);
      break;

    case SND_BNK_FILE_TYPE:
      sprintf(buf, "%sfinal/sound%d/%s.bnk", prefix, /*1,*/ name);
      break;

    case MUSIC_BNK_FILE_TYPE:
      sprintf(buf, "%sfinal/music%d/%s.bnk", prefix, /*1,*/ name);
      break;

    case VAG_FILE_TYPE:  // 0x3e
      sprintf(buf, "%sfinal/vagwad/%s.%s", prefix, name);
      break;

    case MISC_FILE_TYPE:  // 0x3f
      sprintf(buf, "%sfinal/misc/%s", prefix, name);
      break;

    case MAP_FILE_TYPE:
      sprintf(buf, "%sfinal/map%d/%s.go", prefix, DGO_FILE_VERSION, name);
      break;

    case CL_FILE_TYPE:  // 0x41
      sprintf(buf, "%sdb/artdata%d/%s-cl.go", prefix, ART_FILE_VERSION, name);
      break;

    case FLASH_FILE_TYPE // 0x42:
      sprintf(buf, "%sfinal/flash%d/%s.go", prefix, DGO_FILE_VERSION, name);
      break;

    case REFPLANT_FILE_TYPE:  // 0x301
      sprintf(buf, "%sdb/config/refplant/%s", prefix, name);
      break;
    default:
      break;
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
