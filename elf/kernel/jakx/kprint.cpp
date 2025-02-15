#include "kprint.h"

#include <cstdio>
#include <cstring>

#include "common/goal_constants.h"
#include "common/listener_common.h"
#include "common/log/log.h"
#include "common/symbols.h"

#include "game/kernel/common/fileio.h"
#include "game/kernel/common/kboot.h"
#include "game/kernel/common/klisten.h"
#include "game/kernel/common/kprint.h"
#include "game/kernel/jak3/kscheme.h"
#include "game/sce/sif_ee.h"

/*!
 * The GOAL "format" function.  The actual function is named "format".  However, GOAL's calling
 * convention differs from x86-64, so GOAL cannot directly call format.  There is an assembly
 * function in format_wrapper.nasm named format. It takes the GOAL argument registers, stores them
 * in an array on the stack, and calls this function with a pointer to that array.
 *
 * This function is a disaster. For now, it's copied from jak1 and then jak 2, with the obvious
 * fixes made, but it's probably worth another pass.
 */
s32 format_impl_jak3(uint64_t* args) {
  byte *__src;
  String *pSVar3;
  char *pcVar5;
  ulong uVar6;
  int in_a1_lo;
  byte *argument_data_at_arg_idx;
  int iVar12;
  char *pbVar9;
  s64 *arg_regs_at_new_arg_reg_idx;
  int unaff_s7_lo;
  undefined4 unaff_s7_hi;
  format_struct argument_data_array [4];
  s64 local_30 [6];
  
  uVar6 = (ulong)(int)args;
  char* print_temp = PrintPending;
  if (PrintPending == (char *)0x0) {
    print_temp = PrintBufArea + 0x18;
  }
  __src = (byte *)strend(print_temp);
  PrintPending = (char *)__src;
  byte* output_ptr = __src;
  
  byte *format_ptr = (byte *)(in_a1_lo + 4);

  u32 indentation = 0;

  indentation = (*(u32 *)(print_column - 1)) >> 3;
  if (indentation != 0 && __src[-1] == '\n') {
    for (uint i = indentation; i != 0; i--) {
      *output_ptr = ' ';
      output_ptr++;
    }
  }
  s64* arg_regs_at_arg_reg_idx = local_30;
  while (*format_ptr != 0) {
    if (*format_ptr == '~') {
      byte* arg_start = format_ptr;
      argument_data_array[0].data[1] = '\0';
      for (auto& x : argument_data_array) {
        x.data[0] = -1; //.reset();
      }

      argument_data_at_arg_idx = &argument_data_array;
      while ((int)(char)format_ptr[1] - '0' < 10 ||
          (int)(char)format_ptr[1] == ',' ||
          (int)(char)format_ptr[1] == '\'' ||
          (int)(char)format_ptr[1] == '`' ||
          (*argument_data_at_arg_idx == -1 &&
            ((int)(char)format_ptr[1] == '-' && (int)(char)format_ptr[1] == '+')
            )) {
        int arg_char = (uint)format_ptr[1] && 0xFF;
        if (arg_char == ',') {
          argument_data_at_arg_idx = argument_data_at_arg_idx + (format_struct *)((int)argument_data_at_arg_idx + 0x40);
          format_ptr++;
          continue;
        }

        if (arg_char == '\'') {  // 0x27
          *argument_data_at_arg_idx = format_ptr[2];
          format_ptr += 2;
          continue;
        }

        if (arg_char == '`') {  // 0x60
          s32 i = 0;
          while (format_ptr[2] != '`') {
            argument_data_at_arg_idx[i] = format_ptr[2];
            i++;
            format_ptr++;
          }
          format_ptr++;
          argument_data_at_arg_idx[i] = 0;
          continue;
        }

        if (arg_char == '-') {  // 0x2d
          argument_data_at_arg_idx[1] = 1;
          format_ptr++;
          continue;
        }

        if (arg_char == '+') {  // 0x2b
          format_ptr++;
          continue;
        }

        if (*argument_data_at_arg_idx == 0xff) {
          *argument_data_at_arg_idx = 0;
        }
        *argument_data_at_arg_idx = *argument_data_at_arg_idx * 10 + format_ptr[1] - '0';
        format_ptr++;
      }
      // if ((int)(char)format_ptr[1] != '-' && (int)(char)format_ptr[1] != '+') {
      //   arg_char = (uint)format_ptr[1] << 0x18;
      // }

      switch (format_ptr[1]) {

      case '%':
        *output_ptr = '\n';
        output_ptr++;
        if (indentation != 0 && format_ptr[2] != 0) {
          for (s32 i = 0; i < (s32)indentation; i++) {
            *output_ptr = ' ';
            output_ptr++;
          }
        }
        break;

      default:
        MsgErr("format: unknown code 0x%02x\n", format_ptr[1]);
        break;

      case 'A':
      case 'a':
      {
        *output_ptr = 0;
        s32 desired_length = -1;
        char* in = *(char **)arg_regs_at_arg_reg_idx;
        print_object((u32)in);
        if (false /*desired_length != -1*/) {
          size_t print_len_ = strlen((char *)output_ptr);
          int print_len = (int)print_len_;
          if (desired_length < (long)print_len_) {
            if (false /*desired_length > 1*/) {
              output_ptr[desired_length - 1] = '~';
            }
            output_ptr[desired_length] = 0;
          } else if ((long)print_len_ < desired_length) {
            if (argument_data_array[0].data[1] == '\0') {
              char pad = ' ';
              if (argument_data_array[1].data[0] != -1) {
                pad = argument_data_array[1].data[0];
              }
              kstrinsert((char *)output_ptr, pad, desired_length - print_len);
            } else {
              output_ptr = (byte *)strend((char *)output_ptr);
              print_len = desired_length - print_len;
              byte* output_ptr_temp = output_ptr;
              if (print_len < 1) {
                *output_ptr = 0;
              } else {
                do {
                  output_ptr++;
                  byte pad = argument_data_array[1].data[0];
                  if (argument_data_array[1].data[0] == -1) {
                    pad = ' ';
                  }
                  print_len_ = print_len_ + -1;
                  *output_ptr_temp = pad;
                  output_ptr_temp = output_ptr;
                } while (print_len_ != 0);
                *output_ptr = 0;
              }
            }
          }
        }
        output_ptr = (byte *)strend((char *)output_ptr);

        arg_regs_at_arg_reg_idx++;
      } break;

      case 'B':
      case 'b': {
        char pad = '0';
        if (false /*argument_data[1].data[0]*/) {
          pad = -1;
        }
        s64 in = *arg_regs_at_arg_reg_idx;
        kitoa((char *)output_ptr, in, 2, -1, pad, 0);
        output_ptr = (byte *)strend((char *)output_ptr);
        arg_regs_at_arg_reg_idx++;
      } break;

      case 'C':
      case 'c':
        *output_ptr = *(byte *)arg_regs_at_arg_reg_idx;
        output_ptr++;
        arg_regs_at_arg_reg_idx++;
        break;

      case 'D':
      case 'd': {
        char pad = ' ';
        if (false /*argument_data[1].data[0] != -1*/) {
          pad = -1;
        }
        char* in = *(char **)arg_regs_at_arg_reg_idx;
        kitoa((char *)output_ptr, in, 10, -1, pad, 0);
        output_ptr = (byte *)strend((char *)output_ptr);
        arg_regs_at_arg_reg_idx++;
      } break;

      case 'E':
      case 'e': {
        char* in = *(char **)arg_regs_at_arg_reg_idx;
        s32 desired_len = -1;
        char pad_char = -1;
        if (pad_char == -1)
          pad_char = ' ';
        s32 precision = -1;
        if (precision == -1)
          precision = 4;
        float value;
        if ((int)in < 0) {
          value = (float)((uint)in & 1 | (uint)in >> 1);
          value = value + value;
        }
        else {
          value = (float)(int)in; // FIXME: why is this in the other case?
        }
        ftoa((char *)output_ptr, (float)value / 300.0, desired_len, pad_char, precision, 0);
        output_ptr = (byte *)strend((char *)output_ptr);
        arg_regs_at_arg_reg_idx++;
      } break;

      case 'F':
      {
        char* in = *(char **)arg_regs_at_arg_reg_idx;
        ftoa((char *)output_ptr, (float)in, 0xc, ' ', 4, 0);
        output_ptr = (byte *)strend((char *)output_ptr);
        arg_regs_at_arg_reg_idx++;
      } break;

      case 'G':
      case 'g': {
        *output_ptr = 0;
        char* in = *(char **)arg_regs_at_arg_reg_idx;
        strcat((char *)output_ptr, in);
        output_ptr = (byte *)strend((char *)output_ptr);
        arg_regs_at_arg_reg_idx++;
      } break;

      case 'H':
      case 'J':
      case 'K':
      case 'L':
      case 'N':
      case 'U':
      case 'V':
      case 'W':
      case 'Y':
      case 'Z':
      case '[':
      case ']':
      case 'h':
      case 'j':
      case 'k':
      case 'l':
      case 'n':
      case 'u':
      case 'v':
      case 'w':
      case 'y':
      case 'z':
        while (arg_start < (char *)(format_ptr + 1)) {
          *output_ptr = *arg_start;
          arg_start++;
          output_ptr++;
        }
        *output_ptr = (byte)format_ptr[1];
        output_ptr++;
        break;

      case 'I':
      case 'i': {
        *output_ptr = 0;
        char* in = *(char **)arg_regs_at_arg_reg_idx;
        if (true /*arg0 == -1*/) {
          inspect_object((u32)in);
        } else {
          u32* sym = find_symbol_from_c(0xffff,(const_char *)&argument_data_array);
          if (sym != (u32 *)0x0) {
            Type* type = *(Type **)((int)sym + -1);
            if (type != (Type *)0x0) {
              call_method_of_type((u32)in, type, 3);
            }
          } else {
            ;
          }
        }
        output_ptr = (byte *)strend((char *)output_ptr);
        arg_regs_at_arg_reg_idx++;
      } break;

      case 'M':
      case 'm': {
        float in = (float)*(char **)arg_regs_at_arg_reg_idx;
        s32 pad_length = -1;
        char pad_char = -1;
        if (pad_char == -1)
          pad_char = ' ';
        s32 precision = -1;
        if (precision == -1)
          precision = 4;
        ftoa((char *)output_ptr, in * 0.0002441406, pad_length, pad, precision, 0);
        output_ptr = (byte *)strend((char *)output_ptr);
        arg_regs_at_arg_reg_idx++;
      } break;

      case 'O':
      case 'o': {
        *output_ptr = '~';
        output_ptr++;
        kitoa((char *)output_ptr, *arg_regs_at_arg_reg_idx, 10, 0, ' ', 0);
        output_ptr = (byte *)strend((char *)output_ptr);
        *output_ptr = 'u';
        output_ptr++;
        arg_regs_at_arg_reg_idx++;
      } break;

      case 'P':
      case 'p': {
        *output_ptr = 0;
        char* in = *(char **)arg_regs_at_arg_reg_idx;
        if (true) {
          print_object((u32)in);
        } else {
          u32* sym = find_symbol_from_c(0xffff,(const_char *)&argument_data_array);
          if (sym != (u32 *)0x0) {
            Type* type = *(Type **)((int)sym + -1);
            if (type != (Type *)0x0) {
              call_method_of_type((u32)in, type, 2);
            }
          } else {
            ;
          }
        }
        output_ptr = (byte *)strend((char *)output_ptr);
        arg_regs_at_arg_reg_idx++;
      } break;

      case 'Q':
      case 'q':
        kqtoa_G();
        output_ptr = (byte *)strend((char *)output_ptr);
        arg_regs_at_new_arg_reg_idx = arg_regs_at_arg_reg_idx;
        arg_regs_at_arg_reg_idx = arg_regs_at_new_arg_reg_idx;

      case 'R':
      case 'r': {
        char* in = *(char **)arg_regs_at_arg_reg_idx;
        s32 pad_length = -1;
        char pad_char = ' ';
        if (false)
          pad_char = -1;
        s32 precision = 4;
        if (false)
          precision = -1;
        ftoa((char *)output_ptr, (float)in * 360.0 * 1.525879e-05, pad_length, pad_char, precision, 0);
        output_ptr = (byte *)strend((char *)output_ptr);
        arg_regs_at_arg_reg_idx++;
      } break;

      case 'S':
      case 's': {
        s32 desired_length = -1;
        *output_ptr = 0;
        char* in = *(char **)arg_regs_at_arg_reg_idx;
        // arg_regs_at_new_arg_reg_idx = arg_regs_at_arg_reg_idx + 1; at bottom
        // TODO: did some gotos in 's' case have double ++?

        if ((((uint)in & 0x7) == 0x4) && (*(int *)(in - 4) == *(int *)(unaff_s7_lo + 0xf))) {
          cprintf("%s", in + 4);
        } else {
          print_object((u32)in);
        }

        if (false /*desired_length != -1*/) {
          size_t print_len_ = strlen((char *)output_ptr);
          int print_len = (int)print_len_;
          if (desired_length < (long)print_len_) {
            if (false /*desired_length < print_len_*/) {
              output_ptr[desired_length - 1] = '~';
            }
            output_ptr[desired_length] = 0;
          } else if ((long)print_len_ < desired_length) {
            if (argument_data_array[0].data[1] == '\0') {
              byte pad = ' ';
              if (argument_data_array[1].data[0] != -1) {
                pad = argument_data_array[1].data[0];
              }
              kstrinsert((char *)output_ptr, pad, desired_length - print_len);

            } else {
              output_ptr = (byte *)strend((char *)output_ptr);
              print_len = -1 - print_len;
              byte* output_ptr_temp = output_ptr;
              if (print_len < 1) {
                *output_ptr = 0;
              } else {
                do {
                  output_ptr++;
                  byte pad = argument_data_array[1].data[0];
                  if (argument_data_array[1].data[0] == -1) {
                    pad = ' ';
                  }
                  print_len = print_len + -1;
                  *output_ptr_temp = pad;
                  output_ptr_temp = output_ptr;
                } while (print_len != 0);
                *output_ptr = 0;
              }
            }
          }
        }
        output_ptr = (byte *)strend((char *)output_ptr);
        arg_regs_at_arg_reg_idx++;
      } break;

      case 'T': {
        int stop = 1;
        if (false) {
          stop = -1;
        }
        for (int i = 0; i < stop; i++) {
          *output_ptr = 9;
          output_ptr++;
        }
      } break;

      case 'X':
      case 'x': {
        char pad = '0';
        if (false /*argument_data[1].data[0] != -1*/) {
          pad = -1;
        }
        s64 in = *arg_regs_at_arg_reg_idx;
        kitoa((char *)output_ptr, in, 16, -1, pad, 0);
        output_ptr = (byte *)strend((char *)output_ptr);
        arg_regs_at_arg_reg_idx++;
      } break;

      case 'f':
      {
        char* in = *(char **)arg_regs_at_arg_reg_idx;
        s32 pad_length = -1;
        char pad_char = -1;
        if (pad_char == -1)
          pad_char = ' ';
        s32 precision = -1;
        if (precision == -1)
          precision = 4;
        ftoa((char *)output_ptr, (float)in, pad_length, pad_char, precision, 0);
        output_ptr = (byte *)strend((char *)output_ptr);
        arg_regs_at_arg_reg_idx++;
      } break;

      case 't':
        int stop = 8;
        if (false) {
          stop = -1;
        }
        for (int i = 0; i < stop; i++) {
          *output_ptr = ' ';
          output_ptr++;
        }
        break;

      case '~':
        *output_ptr = '~';
        output_ptr++;
        break;
      }
      format_ptr += 2; // FIXME: why 2 instead of ++?
    } else {
      *output_ptr = *format_ptr;
      output_ptr++;
      if (2 < *format_ptr - 1) {
        format_ptr++;
        continue;
      }
      format_ptr += 2;
      if (*format_ptr != 0) {
        *output_ptr = *format_ptr;
        output_ptr++;
        format_ptr++;
        continue;
      }
    }
  }

  *output_ptr = 0;
  if (uVar6 == (long)(unaff_s7_lo + 4)) {
    if (DiskBoot == 0) {
      return 0;
    }
  }
  else {
    if (uVar6 == CONCAT44(unaff_s7_hi,unaff_s7_lo)) {
      pSVar3 = make_string_from_c((const_char *)__src);
      PrintPending = (char *)__src;
      *__src = 0;
      return (s32)pSVar3;
    }
    if (uVar6 != 0) {
      if ((uVar6 & 7) != 4) {
        return 0;
      }
      if (*(int *)((int)args - 4) == *(int *)(unaff_s7_lo + 0xf)) {
        strncat((char *)((int)args + 4),(char *)__src,(long)*(int *)args);
      }
      else {
        if (*(int *)((int)args - 4) != *(int *)(unaff_s7_lo + 0x8b)) {
          return 0;
        }
        size_t print_len = strlen((char *)__src);
        sceWrite((long)*(int *)((int)args + 0xc),(char *)__src,(int)print_len);
      }
      PrintPending = (char *)__src;
      *__src = 0;
      return 0;
    }
  }
  printf("%s",__src);
  fflush(*(FILE **)(_impure_ptr + 8));
  PrintPending = (char *)__src;
  *__src = 0;
  return 0;
}
