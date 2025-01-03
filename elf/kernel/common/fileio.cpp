#include "fileio.h"

#include <cstring>

#include "common/common_types.h"
#include "common/util/Assert.h"

#include "game/kernel/common/Ptr.h"
#include "game/kernel/common/kmalloc.h"
#include "game/kernel/common/kprint.h"
#include "game/sce/sif_ee.h"

using namespace ee;

// buffer for file paths.  This might be static char buffer[512]. Maybe 633 is the line number?
char buffer_633[512];

void fileio_init_globals() {
  memset(buffer_633, 0, 512);
}

/*!
 * Return pointer to null terminator of string.
 * const is for losers.
 * DONE, EXACT
 */
char* strend(char* str) {
  for (; *str != '\0'; str = str + 1) {
  }
  return str;
}

/*!
 * An implementation of Huffman decoding.
 * In this limited decoder, your data must have lower two bits equal to zero.
 * @param loc_ptr pointer to pointer to data to read (will be modified to point to next word)
 * @return decoded word
 * UNUSED, EXACT
 */
u32 ReadHufWord(u8** loc_ptr) {
  byte bVar1;
  byte *pbVar2;
  uint uVar3;
  byte *pbVar4;
  uint uVar5;
  
  pbVar2 = *loc_ptr;
  uVar3 = (uint)*pbVar2;
  uVar5 = uVar3 & 3;
  pbVar4 = pbVar2 + 1;
  if (uVar5 == 2) {
    bVar1 = *pbVar4;
    pbVar4 = pbVar2 + 3;
    uVar3 = uVar3 & 0xfc | (uint)bVar1 << 8 | (uint)pbVar2[2] << 0x10;
  }
  else if (uVar5 < 3) {
    if (uVar5 == 1) {
      bVar1 = *pbVar4;
      pbVar4 = pbVar2 + 2;
      uVar3 = uVar3 & 0xfc | (uint)bVar1 << 8;
    }
  }
  else if (uVar5 == 3) {
    bVar1 = *pbVar4;
    pbVar4 = pbVar2 + 4;
    uVar3 = uVar3 & 0xfc | (uint)bVar1 << 8 | (uint)pbVar2[2] << 0x10 | (uint)pbVar2[3] << 0x18;
  }
  *loc_ptr = pbVar4;
  return uVar3;
}

/*!
 * Copy a string from src to dst. The null terminator is copied too.
 * This is identical to normal strcpy.
 * DONE, EXACT
 */
void kstrcpy(char* dst, const char* src) {
  char cVar1;
  
  cVar1 = *src;
  while (src = src + 1, cVar1 != '\0') {
    *dst = cVar1;
    dst = dst + 1;
    cVar1 = *src;
  }
  *dst = '\0';
  return;
}

/*!
 * Copy a string from src to dst, making all letters upper case.
 * The null terminator is copied too.
 * DONE, EXACT
 */
void kstrcpyup(char* dst,const char* src) {
  char cVar1;
  
  cVar1 = *src;
  while (cVar1 != '\0') {
    if ((int)cVar1 - 0x61U < 0x1a) {
      cVar1 = (char)((uint)((cVar1 + -0x20) * 0x1000000) >> 0x18);
    }
    *dst = cVar1;
    src = src + 1;
    dst = dst + 1;
    cVar1 = *src;
  }
  *dst = '\0';
  return;
}

/*!
 * Concatenate two strings.  Src is added to dest.
 * The new string is null terminated.  No bounds checking is done.
 * DONE, EXACT
 */
void kstrcat(char* dest,const char* src) {
  char cVar1;
  
  cVar1 = *dest;
  while (cVar1 != '\0') {
    dest = dest + 1;
    cVar1 = *dest;
  }
  cVar1 = *src;
  while (src = src + 1, cVar1 != '\0') {
    *dest = cVar1;
    dest = dest + 1;
    cVar1 = *src;
  }
  *dest = '\0';
  return;
}

/*!
 * Concatenate two strings with a maximum length for the resulting string
 * The maximum length should be larger than the length of the original string.
 * The resulting string will be truncated when it reaches the given length.
 * The null terminator is added, but doesn't count toward the length.
 * DONE, EXACT
 */
void kstrncat(char* dest,const char* src,s32 count) {
  int iVar1;
  char cVar2;
  
  iVar1 = 0;
  cVar2 = *dest;
  while (cVar2 != '\0') {
    dest = dest + 1;
    iVar1 = iVar1 + 1;
    cVar2 = *dest;
  }
  cVar2 = *src;
  for (; (cVar2 != '\0' && (iVar1 < count)); iVar1 = iVar1 + 1) {
    *dest = cVar2;
    src = src + 1;
    cVar2 = *src;
    dest = dest + 1;
  }
  *dest = '\0';
  return;
}

/*!
 * Insert the pad char at the beginning of a string, count times.
 * DONE, EXACT
 */
char* kstrinsert(char* str,char pad,s32 count) {
  int iVar1;
  size_t sVar2;
  char* pcVar3;
  
  sVar2 = strlen(str);
  if (-1 < (long)sVar2) {
    pcVar3 = str + (int)sVar2 + count;
    do {
      iVar1 = (int)sVar2;
      sVar2 = (size_t)(iVar1 + -1);
      *pcVar3 = str[iVar1];
      pcVar3 = pcVar3 + -1;
    } while (-1 < (long)sVar2);
  }
  iVar1 = 0;
  pcVar3 = str;
  if (0 < count) {
    do {
      *pcVar3 = pad;
      iVar1 = iVar1 + 1;
      pcVar3 = str + iVar1;
    } while (iVar1 < count);
  }
  return str;
}

/*!
 * Get filename from path.
 * This function is renamed to basename_goal so it doesn't conflict with "basename" that is
 * already defined on my computer.
 * For example:
 *   a/b/c.e will return c.e
 *   a\b\c.e will return c.e
 *   asdf.asdf will return asdf.asdf
 *   DONE, EXACT
 */
char* basename_goal(char* s) {
  char* pcVar1;
  char* pcVar2;
  char cVar3;
  
  cVar3 = *s;
  pcVar2 = s;
  while (cVar3 != '\0') {
    pcVar2 = pcVar2 + 1;
    cVar3 = *pcVar2;
  }
  do {
    pcVar1 = pcVar2;
    if (pcVar1 <= s) {
      return s;
    }
    cVar3 = pcVar1[-1];
  } while ((cVar3 != '\\') && (pcVar2 = pcVar1 + -1, cVar3 != '/'));
  return pcVar1;
}

/*!
 * Does the file exist?  No.  It doesn't.
 * @return 0 always, even if the file exists.
 * DONE, EXACT, UNUSED
 */
u32 FileExists(const char* name) {
  return 0;
}

/*!
 * Does nothing. Likely is supposed to delete a file.
 * @param name
 * DONE, EXACT, UNUSED
 */
void FileDelete(const char* name) {
  return;
}

/*!
 * Does nothing. Likely is supposed to copy a file.
 * @param a
 * @param b
 * DONE, EXACT, UNUSED
 */
void FileCopy(const char* a,const char* b) {
  return;
}

/*!
 * Determine the file length in bytes.
 * DONE, EXACT
 */
s32 FileLength(char* filename) {
  s32 sVar1;
  s32 sVar2;
  
  sVar1 = sceOpen(filename,1);
  if (sVar1 < 0) {
    MsgErr("dkernel: file length !open: \'%s\' (%d)\n",filename,sVar1);
    sVar2 = -5;
  }
  else {
    sVar2 = sceLseek(sVar1,0,2);
    sceClose(sVar1);
  }
  return sVar2;
}

/*!
 * Load a file into memory
 * @param name : file name
 * @param heap : heap to allocate into, if memory is null
 * @param memory : memory to load into. If null, allocates on the given kheap (with 64 extra bytes)
 * @param malloc_flags : flags for the kmalloc
 * @param size_out : file size is written here, if it's not null
 * @return pointer to file data
 * DONE, EXACT
 */
u8* FileLoad(char* name,kheapinfo *heap,u8* memory,u32 malloc_flags,s32* size_out) {
  s32 sVar1;
  u8* puVar2;
  undefined4 uVar3;
  u8* puVar4;
  long lVar5;
  long lVar6;
  
  sVar1 = sceOpen(name,1);
  if (sVar1 < 0) {
    MsgErr("dkernel: file read !open: \'%s\' (%d)\n",name,sVar1);
    puVar2 = (u8 *)0xfffffffb;
  }
  else {
    uVar3 = sceLseek(sVar1,0,1);
    lVar5 = sceLseek(sVar1,0,2);
    sceLseek(sVar1,uVar3,0);
    puVar4 = (u8 *)lVar5;
    puVar2 = puVar4;
    if (0 < lVar5) {
      if ((memory == (u8 *)0x0) &&
         (memory = kmalloc(heap,(s32)(puVar4 + 0x40),malloc_flags,name), memory == (u8 *)0x0)) {
        MsgErr("dkernel: mem full for file read: \'%s\' (%d bytes)\n",name,lVar5);
        puVar2 = (u8 *)0xfffffffd;
      }
      else {
        lVar6 = sceRead(sVar1,memory,puVar4);
        if (lVar6 == lVar5) {
          sceClose(sVar1);
          puVar2 = memory;
          if (size_out != (s32 *)0x0) {
            *size_out = (s32)puVar4;
          }
        }
        else {
          MsgErr("dkernel: can\'t read full file (%d of %d): \'%s\'\n",lVar6,lVar5,name);
          sceClose(sVar1);
          puVar2 = (u8 *)0xfffffffb;
        }
      }
    }
  }
  return puVar2;
}

/*!
 * Write a file.
 * DONE, EXACT
 */
s32 FileSave(char* name,u8* data,s32 size) {
  s32 sVar1;
  int iVar2;
  int iVar4;
  int iVar5;
  long lVar3;
  
  sVar1 = sceOpen(name,0x602);
  lVar3 = (long)sVar1;
  if (lVar3 < 0) {
    MsgErr("dkernel: file write !open: \'%s\'\n",name);
    sVar1 = -6;
  }
  else {
    iVar5 = 0;
    if (size != 0) {
      do {
        iVar4 = 0x1000000;
        if (size < 0x1000000) {
          iVar4 = size;
        }
        iVar2 = sceWrite(lVar3,(char *)(data + iVar5),iVar4);
        iVar5 = iVar5 + iVar2;
        size = size - iVar2;
        if (iVar2 != iVar4) {
          MsgErr("dkernel: can\'t write full file: \'%s\'\n",name);
          sceClose(lVar3);
          return -6;
        }
      } while (size != 0);
    }
    sceClose(lVar3);
    sVar1 = 0;
  }
  return sVar1;
}
