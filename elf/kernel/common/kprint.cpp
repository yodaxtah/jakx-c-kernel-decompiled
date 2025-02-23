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
  bool use_debug;
  use_debug = MasterDebug == 0 && DebugSegment == 0; // TODO: Why Jak2 and not Jak3?

  if (use_debug) {
    MessBufArea = kmalloc(kdebugheap, DEBUG_MESSAGE_BUFFER_SIZE, KMALLOC_MEMSET | KMALLOC_ALIGN_256,
                          "mess-buf");
    OutputBufArea = kmalloc(kdebugheap, DEBUG_OUTPUT_BUFFER_SIZE,
                            KMALLOC_MEMSET | KMALLOC_ALIGN_256, "output-buf");
    PrintBufArea = kmalloc(kdebugheap, DEBUG_PRINT_BUFFER_SIZE, KMALLOC_MEMSET | KMALLOC_ALIGN_256,
                           "print-buf");
  } else {
    MessBufArea = Ptr<u8>(0);
    OutputBufArea = Ptr<u8>(0);

    PrintBufArea =
        kmalloc(kglobalheap, PRINT_BUFFER_SIZE, KMALLOC_MEMSET | KMALLOC_ALIGN_256, "print-buf");
  }
}

/*!
 * Empty output buffer (only if MasterDebug)
 */
void clear_output() {
  if (MasterDebug != 0) {
    strcpy((char*)Ptr<u8>(OutputBufArea + 0x18).c(), ""); // SIZEOF, TODO: .cast<char>?
    OutputPending = Ptr<u8>(0);
  }
}

/*!
 * Clear all data in the print buffer
 */
void clear_print() {
  *Ptr<u8>(PrintBufArea + 0x18) = 0; // SIZEOF
  PrintPending = Ptr<u8>(0);
}

/*!
 * Buffer message to compiler indicating the target has reset.
 * Write to the beginning of the output buffer.
 */
void reset_output() {
  if (MasterDebug != 0) {
    undefined *unaff_s7_lo;
    sprintf(OutputBufArea.cast<char>() + 0x18, "reset #x%x\n", // SIZEOF
            unaff_s7_lo);

    OutputPending = OutputBufArea + 0x18; // SIZEOF
  }
}

/*!
 * Buffer message to compiler indicating some object file has been unloaded.
 * DONE, EXACT
 */
void output_unload(const char* name) {
  if (MasterDebug != 0) {
    sprintf(strend((char *)(OutputBufArea.cast<char>().c() + 0x18)), // SIZEOF
            "unload \"%s\"\n", name);
    OutputPending = OutputBufArea + 0x18; // SIZEOF
  }
}

/*!
 * Buffer message to compiler indicating some object file has been loaded.
 */
void output_segment_load(const char* name, Ptr<u8> link_block, u32 flags) {
  if (MasterDebug != 0) {
    char* buffer = strend(OutputBufArea.cast<char>().c() + 0x18); // SIZEOF
    char true_str[] = "t";
    char false_str[] = "nil";
    char* flag_str = ((flags & LINK_FLAG_OUTPUT_TRUE) != 0) ? true_str : false_str;
    ObjectFileHeader* lbp = link_block.cast<ObjectFileHeader>();
    sprintf(buffer, "load \"%s\" %s #x%x #x%x #x%x\n", name, flag_str,
            lbp->code_infos[0].offset + 4, lbp->code_infos[1].offset + 4, lbp->code_infos[2].offset + 4);
    // TODO: Why +4? The struct SegmentInfo might itself be nested at 0x4 in another one:
    // ObjectFileHeader --contains--> SomeStruct of 16 bytes --contains--> SegmentInfo.
    OutputPending = OutputBufArea + 0x18; // SIZEOF
  }
}

/*!
 * Print to the GOAL print buffer from C
 * seeks PrintPending to begining of what was just printed.
 * This is a different behavior from all the other prints!
 * DONE, EXACT
 */
void cprintf(const char* format, ...) {
  va_list args;
  va_start(args, format);
  char* str = PrintPending.cast<char>().c();
  if (PrintPending.offset == 0)
    str = PrintBufArea.cast<char>().c() + 0x18; // SIZEOF
  PrintPending = make_ptr(strend(str));
  vsprintf((char*)PrintPending.c(), format, args); // NOTE: .cast<char>().c() ?

  va_end(args);
}

/*!
 * Print directly to the C stdout
 * The "k" parameter is ignored, so this is just like printf
 * DONE, changed vprintf to lg::printstd
 */
void Msg(s32 k, const char* format, ...) {
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
}

/*!
 * Print directly to the C stdout
 * This is idential to Msg
 * DONE, changed vprintf to lg::printstd
 */
void MsgWarn(const char* format, ...) {
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
}

/*!
 * Print directly to the C stdout
 * This is idential to Msg
 * DONE, changed vprintf to lg::printstd
 */
void MsgErr(const char* format, ...) {
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
}

/*!
 * Reverse string in place.
 * DONE, EXACT
 */
void reverse(char* str) {
  s32 i = 0;
  s32 end = (s32)strlen(str);
  while (end--, i < end) {
    char c = str[i];
    str[i] = str[end];
    str[end] = c;
    i++;
  }
}

/*!
 * Some sort of rounding for printing floating point numbers.
 * It is unused and believed to be not correct.
 * Currently copy-pasta from GHIDRA
 * (not checked in jak2)
 * TBD SKIPPED
 */
char* round(float x, s32* param1, char* start, char* sEnd, char padchar, s32 *param4) {
  char cVar1;
  float f;
  float local_40 [4];

  if (x == 0.00000000) {
    f = (float)(padchar - '0');
  } else {
    modf((double)(long)(int)local_40,(double *)start);  // Why is this not ':'?
  }
  if (4.00000000 < f) {
    while (true) {
      if (*sEnd == '.') {
        sEnd = sEnd - 1;
      }
      cVar1 = *sEnd;
      *sEnd = cVar1 + 1;
      if ((char)(cVar1 + 1) < ':') { // Why is this not <= '9'?
        return start;
      }
      *sEnd = '0';
      if (sEnd == start)
        break;
      sEnd = sEnd - 1;
    }
    if (param1 == (int*)0x0) {
      start[-1] = '1'; // Why is this not sEnd?
      start = start - 1;
    } else {
      *start = '1'; // Why is this not sEnd?
      *param1 = *param1 + 1;
    }
  } else {
    if (*param4 == 0x2d) {
      while (true) {
        if (*sEnd == '.') {
          sEnd = sEnd - 1;
        }
        if (*sEnd != '0')
          break;
        if (sEnd == start) {
          *param4 = 0;
        }
        sEnd = sEnd - 1;
      }
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
 * TBD, added some sanity checks and removed support for "rounding" as round isn't implemented and
 * rounding is never used in the game.
 *
 * Not checked closely in jak 2.
 */
s32 cvt_float(float x, s32 precision, s32* lead_char, char* buff_start, char* buff_end, u32 flags) {
  long lVar2;
  float x_00;
  float fVar6;
  float local_60;
  float local_5c;
  u32 local_58;
  
  lVar2 = (long)(int)lead_char;
  x_00 = 0.0;

  *buff_start = 0;
  s32 forward_count = 0;

  if (x < 0.0f) {
    x_00 = -x;
    *lead_char = '-';
    x = x_00;
  } else {
    *lead_char = 0;
  }

  local_58 = flags;
  if (((uint)x & 0x7fffffff) == 0x7fffffff) {
    strcpy(buff_start, "NaN");
    return 3;
  }

  char* start_ptr = buff_start + 1;
  char* end_ptr = buff_end - 1;
  modf((double)(long)(int)&local_60,(double *)lead_char);
  while ((start_ptr <= end_ptr && (fVar6 = 0.0, local_60 != 0.0))) {
    modf((double)(long)(int)&local_60,(double *)lVar2);
    *end_ptr = (char)(int)(fVar6 * 10.0 + 0.5) + '0';
    end_ptr--;

    forward_count++;
    local_5c = fVar6;
  }

  char* count_chrp = start_ptr;
  if (forward_count == 0) {
    *start_ptr = '0';
    count_chrp = buff_start + 2;
  } else {
    while (end_ptr = end_ptr + 1,
           end_ptr < buff_end) {
      *count_chrp = *end_ptr;
      count_chrp++;
    }
  }

  if (precision != 0) {
    *count_chrp = '.';
    count_chrp++;
  }

  s32 prec = 0;

  if (x_00 == 0.0) {
    prec = precision - 1;
  }
  else {
    if (precision == 0) {
LAB_002676d4:
      if (x_00 == 0.0) {
        prec = precision - 1;
        goto LAB_002676b0;
      }
      if ((local_58 & 1) != 0) {
        start_ptr = round(x_00,(s32 *)0x0,start_ptr,count_chrp - 1,'\0',lead_char);
      }
    }
    else {
      do {
        x_00 = 0.0;
        modf((double)(long)(int)&local_5c,(double *)lVar2);
        *count_chrp = (char)(int)local_5c + '0';
        count_chrp++;
        precision--;
        if (precision == 0) goto LAB_002676d4;
      } while (true && (x_00 != 0.0));
    }
    prec = precision - 1;
  }

LAB_002676b0:
  while (prec = prec - 1, prec != -1) {
    *count_chrp = '0';
    count_chrp++;
  }
  return (int)count_chrp - (int)start_ptr;
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
 * Not checked super closely in jak 2.
 */
void ftoa(char* out_str, float x, s32 desired_len, char pad_char, s32 precision, u32 flags) {
  char buff_130;       // 256
  char buff_12f [126]; // 256
  char buff_b1 [129];  // 256
  char* current_buff = buff_12f;
  s32 lead_char;

  s32 count = cvt_float(x, precision, &lead_char, &buff_130, buff_b1, flags);

  if (count > 0x3f) {
    strcpy(&buff_130, "NaN");
    count = 3;
    lead_char = 0;
  }

  if (buff_130 != '\0') {
    current_buff = &buff_130;
  }

  s32 real_count = (uint)(lead_char != 0) + count;

  char* out_ptr = out_str;

  if ((desired_len > 0) && (desired_len > real_count) && 0 < i) {
    for (s32 i = 0; i < (desired_len - real_count); i++) {
      *out_ptr = pad_char;
      out_ptr++;
    }
  }

  if (lead_char != 0) {
    *out_ptr = (char)lead_char;
    out_ptr++;
  }

  for (s32 i = 0; i < count; i++) {
    *out_ptr = *current_buff;
    out_ptr++;
    current_buff++;
  }

  *out_ptr = '\0';
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
 * TBD
 */
char* kitoa(char* buffer, s64 value, u64 base, s32 length, char pad, u32 flag) {
  s32 negativeValue = 0;
  s64 value_to_print = value;

  if ((value < 0) && base == 10) {
    negativeValue = (s32)value;
    value_to_print = -value;
  }

  int count = 0;
  do {
    buffer[count++] = ConvertTable_G[__umoddi3_Proxy_G(value_to_print,(int)base)];
    value_to_print = __udivdi3_Proxy_G(value_to_print, (int)base);
  } while (value_to_print != 0);

  if (negativeValue < 0) {
    buffer[count++] = '-';
  }

  s32 rLen = length;
  if (1 > length - count) {
    if (((length < 1) || (-1 < value)) || ((base != 2 && (base != 16)))) {
      buffer[count] = '\0';
    }
    else if (length < count) {
      char c = (base == 16) ? 'f' : '1';

      while (length < count && (buffer[count - 1] == c)) {
        count--;
      }

      if ((flag & 2) != 0) {
        buffer[count] = '\0';
      }
      else {
        buffer[count++] = '-';
      }
    }
  }
  if (0 < length - count) {
    rLen = length - count;
    while (0 < rLen) {
      buffer[count++] = pad;
      rLen--;
    }
  }
  buffer[count] = '\0';
  reverse(buffer);
  return buffer;
}

/*!
 * Convert 128-bit integer to string.  Not implemented because it is never used in the game.
 * It would also require passing 128-bit values between GOAL and C++ and this is not worth
 * implementing. It is only used by the "format" function, which cannot use it properly. "format"
 * uses C varags, but 128-bit varags don't work, so "format" always passes 0 for quadword printing.
 * TBD SKIPPED
 */
void kqtoa_G() {
  undefined in_zero_qw [16];
  char* in_a0_lo;
  undefined in_a1_qw [16];
  undefined auVar1 [16];
  u64 in_a2;
  int in_a3_lo;
  char in_t0_lo;
  u32 in_t1_lo;
  undefined auVar2 [16];
  
  auVar2 = _por(in_zero_qw, in_a1_qw);
  auVar1 = _pcpyud(in_a1_qw, in_zero_qw);
  auVar2 = _pcpyud(in_zero_qw, auVar2);
  s64 value = auVar2._0_8_;
  kitoa(in_a0_lo, auVar1._0_8_, in_a2, in_a3_lo - 0x10, in_t0_lo, in_t1_lo);
  char* buffer = strend(in_a0_lo);
  kitoa(buffer, value, in_a2, 0x10, '0', 0);
}
