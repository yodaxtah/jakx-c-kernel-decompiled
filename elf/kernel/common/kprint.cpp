#include "kprint.h"

#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cstring>

#include "common/cross_os_debug/xdbg.h"
#include "common/listener_common.h"
#include "common/log/log.h"

#include "game/kernel/common/Ptr.h"
#include "game/kernel/common/fileio.h"
#include "game/kernel/common/klink.h"
#include "game/kernel/common/kmalloc.h"
#include "game/kernel/common/kscheme.h"

// Pointer set to something in the middle of the output buffer, if there is something in the buffer.
Ptr<u8> OutputPending;

// Pointer set to something in the middle of the print buffer, if there is something in the buffer
Ptr<u8> PrintPending;

// Size of incoming message.
s32 MessCount;

// Pointer to message buffer, the compiler to target buffer
Ptr<u8> MessBufArea;

// Pointer to the output buffer, the runtime to compiler buffer
Ptr<u8> OutputBufArea;

// Pointer to print buffer, the buffer for printing and string formatting.
Ptr<u8> PrintBufArea;

// integer printing conversion table
char ConvertTable[16];

// buffer for sending an "acknowledge" message to the compiler
char AckBufArea[40];

/*!
 * Initialize global variables for kprint
 */
void kprint_init_globals_common() {
  OutputPending.offset = 0;
  PrintPending.offset = 0;
  MessCount = 0;
  MessBufArea.offset = 0;
  OutputBufArea.offset = 0;
  PrintBufArea.offset = 0;
  memcpy(ConvertTable, "0123456789abcdef", 16);
  memset(AckBufArea, 0, sizeof(AckBufArea));
}

/*!
 * Initialize GOAL Kernel printing/messaging system.
 * Allocates buffers.
 */
void init_output() {
  kheapinfo *heap;
  s32 size;
  
  if ((MasterDebug == 0) && (DebugSegment == 0)) {
    heap = &kglobalheapinfo;
    size = 0x2000;
    MessBufArea = (u8 *)0x0;
    OutputBufArea = (u8 *)0x0;
  }
  else {
    MessBufArea = kmalloc(kdebugheap,0x80000,0x1100,"mess-buf");
    OutputBufArea = kmalloc(kdebugheap,0x80000,0x1100,"output-buf");
    size = 0x200000;
    heap = kdebugheap;
  }
  PrintBufArea = kmalloc(heap,size,0x1100,"print-buf");
  return;
}

/*!
 * Empty output buffer (only if MasterDebug)
 */
void clear_output() {
  if (MasterDebug != 0) {
    strcpy((char *)(OutputBufArea + 0x18),"");
    OutputPending = 0;
  }
  return;
}

/*!
 * Clear all data in the print buffer
 */
void clear_print() {
  PrintBufArea[0x18] = 0;
  PrintPending = (char *)0x0;
  return;
}

/*!
 * Buffer message to compiler indicating the target has reset.
 * Write to the beginning of the output buffer.
 */
void reset_output() {
  undefined *unaff_s7_lo;
  
  if (MasterDebug != 0) {
    sprintf((char *)(OutputBufArea + 0x18),"reset #x%x\n",unaff_s7_lo);
    OutputPending = OutputBufArea + 0x18;
  }
  return;
}

/*!
 * Buffer message to compiler indicating some object file has been unloaded.
 * DONE, EXACT
 */
void output_unload(const char* name) {
  char* __s;
  
  if (MasterDebug != 0) {
    __s = strend((char *)(OutputBufArea + 0x18));
    sprintf(__s,"unload \"%s\"\n",name);
    OutputPending = OutputBufArea + 0x18;
  }
  return;
}

/*!
 * Buffer message to compiler indicating some object file has been loaded.
 */
void output_segment_load(const char* name,void* link_block,u32 flags) {
  char* __s;
  char* pcVar1;
  
  if (MasterDebug != 0) {
    __s = strend((char *)(OutputBufArea + 0x18));
    pcVar1 = "t";
    if ((flags & 2) == 0) {
      pcVar1 = "nil";
    }
    sprintf(__s,"load \"%s\" %s #x%x #x%x #x%x\n",name,pcVar1,*(int *)((int)link_block + 4) + 4,
            *(int *)((int)link_block + 0x14) + 4,*(int *)((int)link_block + 0x24) + 4);
    OutputPending = OutputBufArea + 0x18;
  }
  return;
}

/*!
 * Print to the GOAL print buffer from C
 * seeks PrintPending to begining of what was just printed.
 * This is a different behavior from all the other prints!
 * DONE, EXACT
 */
void cprintf(const char* format,...) {
  char* str;
  undefined8 in_a1;
  undefined8 in_a2;
  undefined8 in_a3;
  undefined8 in_t0;
  undefined8 in_t1;
  undefined8 in_t2;
  undefined8 in_t3;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  undefined8 local_8;
  
  str = PrintPending;
  if (PrintPending == (char *)0x0) {
    str = PrintBufArea + 0x18;
  }
  local_38 = in_a1;
  local_30 = in_a2;
  local_28 = in_a3;
  local_20 = in_t0;
  local_18 = in_t1;
  local_10 = in_t2;
  local_8 = in_t3;
  PrintPending = strend(str);
  vsprintf(PrintPending,format,&local_38);
  return;
}

/*!
 * Print directly to the C stdout
 * The "k" parameter is ignored, so this is just like printf
 * DONE, changed vprintf to lg::printstd
 */
void Msg(s32 k,const char* format,...) {
  undefined8 in_a2;
  undefined8 in_a3;
  undefined8 in_t0;
  undefined8 in_t1;
  undefined8 in_t2;
  undefined8 in_t3;
  undefined8 local_30;
  undefined8 local_28;
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  undefined8 local_8;
  
  local_30 = in_a2;
  local_28 = in_a3;
  local_20 = in_t0;
  local_18 = in_t1;
  local_10 = in_t2;
  local_8 = in_t3;
  vprintf(format,&local_30);
  return;
}

/*!
 * Print directly to the C stdout
 * This is idential to Msg
 * DONE, changed vprintf to lg::printstd
 */
void MsgWarn(const char* format,...) {
  undefined8 in_a1;
  undefined8 in_a2;
  undefined8 in_a3;
  undefined8 in_t0;
  undefined8 in_t1;
  undefined8 in_t2;
  undefined8 in_t3;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  undefined8 local_8;
  
  local_38 = in_a1;
  local_30 = in_a2;
  local_28 = in_a3;
  local_20 = in_t0;
  local_18 = in_t1;
  local_10 = in_t2;
  local_8 = in_t3;
  vprintf(format,&local_38);
  return;
}

/*!
 * Print directly to the C stdout
 * This is idential to Msg
 * DONE, changed vprintf to lg::printstd
 */
void MsgErr(const char* format,...) {
  undefined8 in_a1;
  undefined8 in_a2;
  undefined8 in_a3;
  undefined8 in_t0;
  undefined8 in_t1;
  undefined8 in_t2;
  undefined8 in_t3;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  undefined8 local_8;
  
  local_38 = in_a1;
  local_30 = in_a2;
  local_28 = in_a3;
  local_20 = in_t0;
  local_18 = in_t1;
  local_10 = in_t2;
  local_8 = in_t3;
  vprintf(format,&local_38);
  return;
}

/*!
 * Reverse string in place.
 * DONE, EXACT
 */
void reverse(char* str) {
  char cVar1;
  int iVar2;
  size_t sVar3;
  int iVar4;
  char* pcVar5;
  char* pcVar6;
  
  sVar3 = strlen(str);
  iVar2 = (int)sVar3 + -1;
  if (0 < iVar2) {
    iVar4 = 0;
    do {
      pcVar6 = str + iVar4;
      pcVar5 = str + iVar2;
      cVar1 = *pcVar6;
      iVar4 = iVar4 + 1;
      iVar2 = iVar2 + -1;
      *pcVar6 = *pcVar5;
      *pcVar5 = cVar1;
    } while (iVar4 < iVar2);
  }
  return;
}

/*!
 * Some sort of rounding for printing floating point numbers.
 * It is unused and believed to be not correct.
 * Currently copy-pasta from GHIDRA
 * (not checked in jak2)
 */
char* round(float x,s32* param_2,char* start,char* sEnd,char padchar,s32 *param_6) {
  char cVar1;
  float local_40 [4];
  
  if (x == 0.0) {
    local_40[0] = (float)(padchar + -0x30);
  }
  else {
    modf((double)(long)(int)local_40,(double *)start);
  }
  if (4.0 < local_40[0]) {
    while( true ) {
      if (*sEnd == '.') {
        sEnd = sEnd + -1;
      }
      cVar1 = *sEnd;
      *sEnd = cVar1 + '\x01';
      if ((char)(cVar1 + '\x01') < ':') {
        return start;
      }
      *sEnd = '0';
      if (sEnd == start) break;
      sEnd = sEnd + -1;
    }
    if (param_2 == (s32 *)0x0) {
      start[-1] = '1';
      start = start + -1;
    }
    else {
      *start = '1';
      *param_2 = *param_2 + 1;
    }
  }
  else if (*param_6 == 0x2d) {
    while( true ) {
      if (*sEnd == '.') {
        sEnd = sEnd + -1;
      }
      if (*sEnd != '0') break;
      if (sEnd == start) {
        *param_6 = 0;
      }
      sEnd = sEnd + -1;
    }
  }
  return start;
}

/*!
 * Convert floating point to string intermediate function.
 * Places a null character as the first character, then the integers, decimal, fraction digits
 * Presumably, if rounding worked, it would sometimes add an additional digit in front instead of
 * the null but rounding doesn't, so you get a null in front every time. There is no null terminator
 * added, you have to do it yourself. returned value is length : buff[last_char] - buff[1] (not
 * including the leading null) if the number is negative, *lead_char = '-'.  Otherwise it's '\0'.
 * The negative is not inserted for you.
 * The precision is how many digits after decimal to print.
 * The flag could have a 1 to enable rounding, but this doesn't work, so don't use it.
 * Without rounding the printing is a little bit off but you don't notice unless you look too
 * closely.
 *
 * DONE, added some sanity checks and removed support for "rounding" as round isn't implemented and
 * rounding is never used in the game.
 *
 * Not checked closely in jak 2.
 */
s32 cvt_float(float x,s32 precision,s32* lead_char,char* buff_start,char* buff_end,u32 flags) {
  bool bVar1;
  long lVar2;
  char* pcVar3;
  char* pcVar4;
  char* start;
  int iVar5;
  float x_00;
  float fVar6;
  float local_60;
  float local_5c;
  u32 local_58;
  
  lVar2 = (long)(int)lead_char;
  x_00 = 0.0;
  *buff_start = '\0';
  iVar5 = 0;
  if (x < 0.0) {
    x_00 = -x;
    *lead_char = 0x2d;
    x = x_00;
  }
  else {
    *lead_char = 0;
  }
  local_58 = flags;
  if (((uint)x & 0x7fffffff) == 0x7fffffff) {
    strcpy(buff_start,"NaN");
    return 3;
  }
  start = buff_start + 1;
  pcVar3 = buff_end + -1;
  modf((double)(long)(int)&local_60,(double *)lead_char);
  while ((start <= pcVar3 && (fVar6 = 0.0, local_60 != 0.0))) {
    iVar5 = iVar5 + 1;
    modf((double)(long)(int)&local_60,(double *)lVar2);
    *pcVar3 = (char)(int)(fVar6 * 10.0 + 0.5) + '0';
    pcVar3 = pcVar3 + -1;
    local_5c = fVar6;
  }
  pcVar4 = start;
  if (iVar5 == 0) {
    pcVar4 = buff_start + 2;
    *start = '0';
  }
  else {
    while (pcVar3 = pcVar3 + 1, pcVar3 < buff_end) {
      *pcVar4 = *pcVar3;
      pcVar4 = pcVar4 + 1;
    }
  }
  if (precision != 0) {
    *pcVar4 = '.';
    pcVar4 = pcVar4 + 1;
  }
  bVar1 = x_00 == 0.0;
  if (bVar1) {
    iVar5 = precision + -1;
  }
  else {
    if (precision == 0) {
LAB_002676d4:
      if (bVar1) {
        iVar5 = precision + -1;
        goto LAB_002676b0;
      }
      if ((local_58 & 1) != 0) {
        start = round(x_00,(s32 *)0x0,start,pcVar4 + -1,'\0',lead_char);
      }
    }
    else {
      do {
        x_00 = 0.0;
        precision = precision + -1;
        modf((double)(long)(int)&local_5c,(double *)lVar2);
        bVar1 = x_00 == 0.0;
        *pcVar4 = (char)(int)local_5c + '0';
        pcVar4 = pcVar4 + 1;
        if (precision == 0) goto LAB_002676d4;
      } while (!bVar1);
    }
    iVar5 = precision + -1;
  }
LAB_002676b0:
  for (; iVar5 != -1; iVar5 = iVar5 + -1) {
    *pcVar4 = '0';
    pcVar4 = pcVar4 + 1;
  }
  return (int)pcVar4 - (int)start;
}

/*!
 * Convert floating point to a string.
 * Don't set the precision too high or you get NaN (if float is longer than 31 digits without
 * negative sign) Don't set the flags. Rounding is a little bit off, but it adds character. Highly
 * recommended to pad with spaces, not zeros. If you pad with spaces you get "    -1.23" If you pad
 * with zeros, you get "0000000-1.23" which most people consider to be wrong.
 * @param out_str : output buffer to write null terminated string into
 * @param x : number
 * @param desired_len : length (will pad if under, nothing if over)
 * @param pad_char : character to pad with
 * @param precision
 * @param flags
 *
 * DONE
 * Not checked super closely in jak 2.
 */
void ftoa(char* out_str,float x,s32 desired_len,char pad_char,s32 precision,u32 flags) {
  int iVar1;
  int iVar2;
  char* pcVar3;
  char local_130;
  char acStack_12f [126];
  char acStack_b1 [129];
  int local_30 [4];
  
  iVar1 = cvt_float(x,precision,local_30,&local_130,acStack_b1,flags);
  if (0x3f < iVar1) {
    strcpy(&local_130,"NaN");
    local_30[0] = 0;
    iVar1 = 3;
  }
  pcVar3 = acStack_12f;
  if (local_130 != '\0') {
    pcVar3 = &local_130;
  }
  iVar2 = iVar1 + (uint)(local_30[0] != 0);
  if (((0 < desired_len) && (iVar2 < desired_len)) && (iVar2 = desired_len - iVar2, 0 < iVar2)) {
    do {
      *out_str = pad_char;
      iVar2 = iVar2 + -1;
      out_str = out_str + 1;
    } while (iVar2 != 0);
  }
  if (local_30[0] != 0) {
    *out_str = (char)local_30[0];
    out_str = out_str + 1;
  }
  if (iVar1 < 1) {
    *out_str = '\0';
  }
  else {
    do {
      iVar1 = iVar1 + -1;
      *out_str = *pcVar3;
      pcVar3 = pcVar3 + 1;
      out_str = out_str + 1;
    } while (iVar1 != 0);
    *out_str = '\0';
  }
  return;
}

/*!
 * Convert integer to string.
 * @param buffer : buffer to print into. Must be at least as long as the longest possible number to
 * print
 * @param value  : value to print.
 * @param base   : base to print in (2, 10, 16 supported)
 * @param length : length.  if shorter than length, pad with pad.  If longer, only truncate leading
 * f's 1's in base 16 or 2
 * @param pad    : character to pad with
 * @param flags  : flag.  Only the 2nd bit is used, which will disable negative sings on
 * binary/hexadecimal truncated numbers.  Something like -1 (0xffffffff) will print as -fffffff....
 * Not checked super closely in jak 2
 */
char* kitoa(char* buffer,s64 value,u64 base,s32 length,char pad,u32 flag) {
  int iVar1;
  long lVar2;
  char cVar3;
  char* pcVar4;
  int iVar5;
  int iVar6;
  int local_48;
  
  local_48 = 0;
  lVar2 = value;
  if ((value < 0) && (base == 10)) {
    local_48 = (int)value;
    lVar2 = -value;
  }
  iVar6 = 0;
  do {
    iVar5 = iVar6;
    iVar1 = __umoddi3_Proxy_G(lVar2,(int)base);
    iVar6 = iVar5 + 1;
    buffer[iVar5] = s_0123456789abcdef_00282fa8[iVar1];
    lVar2 = __udivdi3_Proxy_G(lVar2,(int)base);
  } while (lVar2 != 0);
  if (local_48 < 0) {
    buffer[iVar6] = '-';
    iVar6 = iVar5 + 2;
  }
  iVar1 = length - iVar6;
  if (iVar1 < 1) {
    pcVar4 = buffer + iVar6;
    if (((length < 1) || (-1 < value)) || ((base != 2 && (pcVar4 = buffer + iVar6, base != 0x10))))
    goto LAB_00267998;
    if (length < iVar6) {
      cVar3 = 'f';
      if (base != 0x10) {
        cVar3 = '1';
      }
      do {
        if (buffer[iVar6 + -1] != cVar3) break;
        iVar6 = iVar6 + -1;
      } while (length < iVar6);
      pcVar4 = buffer + iVar6;
      if ((flag & 2) != 0) goto LAB_00267998;
      buffer[iVar6] = '-';
      iVar6 = iVar6 + 1;
    }
  }
  else {
    do {
      pcVar4 = buffer + iVar6;
      iVar1 = iVar1 + -1;
      iVar6 = iVar6 + 1;
      *pcVar4 = pad;
    } while (0 < iVar1);
  }
  pcVar4 = buffer + iVar6;
LAB_00267998:
  *pcVar4 = '\0';
  reverse(buffer);
  return buffer;
}

/*!
 * Convert 128-bit integer to string.  Not implemented because it is never used in the game.
 * It would also require passing 128-bit values between GOAL and C++ and this is not worth
 * implementing. It is only used by the "format" function, which cannot use it properly. "format"
 * uses C varags, but 128-bit varags don't work, so "format" always passes 0 for quadword printing.
 */
void kqtoa_G() {
  undefined in_zero_qw [16];
  char* buffer;
  char* in_a0_lo;
  undefined in_a1_qw [16];
  undefined auVar1 [16];
  u64 in_a2;
  int in_a3_lo;
  char in_t0_lo;
  u32 in_t1_lo;
  s64 value;
  undefined auVar2 [16];
  
  auVar2 = _por(in_zero_qw,in_a1_qw);
  auVar1 = _pcpyud(in_a1_qw,in_zero_qw);
  auVar2 = _pcpyud(in_zero_qw,auVar2);
  value = auVar2._0_8_;
  kitoa(in_a0_lo,auVar1._0_8_,in_a2,in_a3_lo + -0x10,in_t0_lo,in_t1_lo);
  buffer = strend(in_a0_lo);
  kitoa(buffer,value,in_a2,0x10,'0',0);
  return;
}
