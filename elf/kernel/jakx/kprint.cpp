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
  int unaff_s7_lo;
  undefined4 unaff_s7_hi;

  s64 local_30 [6];
  s64* arg_regs = local_30;

  format_struct argument_data [4];

  u32 arg_reg_idx = 0;

  char* format_gstring; // TODO: why no assignment?

  ulong original_dest = (ulong)(int)args;

  char* print_temp = PrintPending;
  if (PrintPending == (char *)0x0) {
    print_temp = PrintBufArea + 0x18;
  }
  PrintPending = (char *)strend(print_temp);

  char* output_ptr = PrintPending;

  char* format_cstring = format_gstring + 4;

  char* PrintPendingLocal__ = PrintPending;
  u32 indentation = 0;

  indentation = (*(u32 *)(print_column - 1)) >> 3;

  u32 arg_idx = 0;

  if (indentation != 0 && output_ptr[-1] == '\n') {
    for (u32 i = 0; i < indentation; i++) {
      *output_ptr = ' ';
      output_ptr++;
    }
  }

  char* format_ptr = format_cstring;

  while (*format_ptr != 0) {
    if (*format_ptr == '~') {
      char* arg_start = format_ptr;
      arg_idx = 0;
      argument_data[0].data[1] = '\0'; // TODO: why is this a separate variable in jak3?
      for (auto& x : argument_data) {
        x.data[0] = -1; //.reset();
      }

      while ((u8)(format_ptr[1] - '0') < 10 ||
             format_ptr[1] == ',' ||
             format_ptr[1] == '\'' ||
             format_ptr[1] == '`' ||
             (argument_data[arg_idx].data[0] == -1 &&
              (format_ptr[1] == '-' || format_ptr[1] == '+')
              )) {
        char arg_char = format_ptr[1];
        if (arg_char == ',') {
          arg_idx++;
          format_ptr++;
          continue;
        }

        if (arg_char == '\'') {  // 0x27
          argument_data[arg_idx].data[0] = format_ptr[2];
          format_ptr += 2;
          continue;
        }

        if (arg_char == '`') {  // 0x60
          u32 i = 0;
          format_ptr += 2;
          while (*format_ptr != '`') {
            argument_data[arg_idx].data[i] = *format_ptr;
            i++;
            format_ptr++;
          }
          format_ptr--; // TODO: why is jakx 1 format ptr 1 index behind on jak3's?
          argument_data[arg_idx].data[i] = 0;
          continue;
        }

        if (arg_char == '-') {  // 0x2d
          argument_data[arg_idx].data[1] = 1;
          format_ptr++;
          continue;
        }

        if (arg_char == '+') {  // 0x2b
          format_ptr++;
          continue;
        }

        if (argument_data[arg_idx].data[0] == -1) {
          argument_data[arg_idx].data[0] = 0;
        }

        argument_data[arg_idx].data[0] = argument_data[arg_idx].data[0] * 10 + arg_char - '0';
        format_ptr++;
      }

      switch (format_ptr[1]) {

        case '%':
          *output_ptr = '\n';
          output_ptr++;
          if (indentation != 0 && format_ptr[2] != 0) {
            for (u32 i = 0; i < indentation; i++) {
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
          s8 arg0 = -1;
          s32 desired_length = (s32)arg0;
          *output_ptr = 0;
          u32 in = (u32)arg_regs[arg_reg_idx++];
          print_object(in);
          if (false /*desired_length != -1*/) {
            s32 print_len = (s32)strlen(output_ptr);
            if (desired_length < print_len) {
              if (false /*desired_length > 1*/) {
                output_ptr[desired_length - 1] = '~';
              }
              output_ptr[desired_length] = 0;
            } else if (print_len < desired_length) {
              if (argument_data[0].data[1] == '\0') {
                char pad = ' ';
                if (argument_data[1].data[0] != -1) {
                  pad = argument_data[1].data[0];
                }
                kstrinsert(output_ptr, pad, desired_length - print_len);
              } else {
                ;
                output_ptr = strend(output_ptr);
                s32 print_len__ = desired_length - print_len; // TODO: why this assignment?
                while (0 < print_len__) {
                  char pad = ' ';
                  if (argument_data[1].data[0] != -1) {
                    pad = argument_data[1].data[0];
                  }
                  print_len__--;
                  output_ptr[0] = pad;
                  output_ptr++;
                };
                *output_ptr = 0;
              }
            }
          }
          output_ptr = strend(output_ptr);

        } break;

        case 'B':
        case 'b': {
          char pad = '0';
          if (false /*argument_data[1].data[0]*/) {
            pad = -1;
          }
          s64 in = arg_regs[arg_reg_idx++];
          kitoa(output_ptr, in, 2, -1, pad, 0);
          output_ptr = strend(output_ptr);
        } break;

        case 'C':
        case 'c':
          *output_ptr = (char)arg_regs[arg_reg_idx++];
          output_ptr++;
          break;

        case 'D':
        case 'd': {
          char pad = ' ';
          if (false /*argument_data[1].data[0] != -1*/) {
            pad = -1;
          }
          u32 in = (u32)arg_regs[arg_reg_idx++];
          kitoa(output_ptr, in, 10, -1, pad, 0);
          output_ptr = strend(output_ptr);
        } break;

        case 'E':
        case 'e': {
          u32 in = (u32)arg_regs[arg_reg_idx++];
          s8 desired_len = -1;
          s8 pad_char = -1;
          if (pad_char == -1)
            pad_char = ' ';
          s8 precision = -1;
          if (precision == -1)
            precision = 4;
          float value;
          if ((int)in < 0) {
            value = (float)((uint)in & 1 | (uint)in >> 1);
            value = value + value;
          } else {
            value = (float)(int)in; // FIXME: why is this in the else case?
          }
          ftoa(output_ptr, (float)value / 300.0, desired_len, pad_char, precision, 0);
          output_ptr = strend(output_ptr);
        } break;

        case 'F':
        {
          u32 in = (u32)arg_regs[arg_reg_idx++];
          ftoa(output_ptr, (float)in, 0xc, ' ', 4, 0);
          output_ptr = strend(output_ptr);
        } break;

        case 'G':
        case 'g': {
          *output_ptr = 0;
          u32 in = (u32)arg_regs[arg_reg_idx++];
          strcat(output_ptr, in);
          output_ptr = strend(output_ptr);
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
          while (arg_start < format_ptr + 1) {
            *output_ptr = *arg_start;
            arg_start++;
            output_ptr++;
          }
          *output_ptr = format_ptr[1];
          output_ptr++;
          break;

        case 'I':
        case 'i': {
          *output_ptr = 0;
          s8 arg0 = -1;
          u32 in = (u32)arg_regs[arg_reg_idx++];
          if (true /*arg0 == -1*/) {
            inspect_object(in);
          } else {
            u32* sym = find_symbol_from_c(-1, (const_char *)&argument_data);
            if (sym != nullptr) {
              Type* type = *(Type **)((int)sym + -1);
              if (type != nullptr) {
                call_method_of_type(in, type, 3);
              }
            } else {
              ;
            }
          }
          output_ptr = strend(output_ptr);
        } break;

        case 'M':
        case 'm': {
          float in = (float)arg_regs[arg_reg_idx++];
          s8 pad_length = -1;
          s8 pad_char = -1;
          if (pad_char == -1)
            pad_char = ' ';
          s8 precision = -1;
          if (precision == -1)
            precision = 4;
          ftoa(output_ptr, in * 0.0002441406, pad_length, pad_char, precision, 0);
          output_ptr = strend(output_ptr);
        } break;

        case 'O':
        case 'o': {
          *output_ptr = '~';
          output_ptr++;
          kitoa(output_ptr, arg_regs[arg_reg_idx++], 10, 0, ' ', 0);
          output_ptr = strend(output_ptr);
          *output_ptr = 'u';
          output_ptr++;
        } break;

        case 'P':
        case 'p': {
          *output_ptr = 0;
          s8 arg0 = -1;
          u32 in = (u32)arg_regs[arg_reg_idx++];
          if (true /*arg0 == -1*/) {
            print_object(in);
          } else {
            u32* sym = find_symbol_from_c(-1, (const_char *)&argument_data);
            if (sym != nullptr) {
              Type* type = *(Type **)((int)sym + -1);
              if (type != nullptr) {
                call_method_of_type(in, type, 2);
              }
            } else {
              ;
            }
          }
          output_ptr = strend(output_ptr);
        } break;

        case 'Q':
        case 'q':
          kqtoa_G();
          output_ptr = strend(output_ptr);
          break;

        case 'R':
        case 'r': {
          u32 in = (u32)arg_regs[arg_reg_idx++];
          s8 pad_length = -1;
          s8 pad_char = -1;
          if (pad_char == -1)
            pad_char = ' ';
          s8 precision = -1;
          if (precision == -1)
            precision = 4;
          ftoa(output_ptr, (float)in * 360.0 * 1.525879e-05, pad_length, pad_char, precision, 0);
          output_ptr = strend(output_ptr);
        } break;

        case 'S':
        case 's': {
          s8 arg0 = -1;
          s32 desired_length = (s32)arg0;
          *output_ptr = 0;
          u32 in = (u32)arg_regs[arg_reg_idx++];

          if ((((uint)in & 0x7) == 0x4) && (*(int *)(in - 4) == *(int *)(unaff_s7_lo + 0xf))) {
            cprintf("%s", in + 4);
          } else {
            print_object(in);
          }

          if (false /*desired_length != -1*/) {
            s32 print_len = (s32)strlen(output_ptr);
            if (desired_length < print_len) {
              if (false /*desired_length < print_len*/) {
                output_ptr[desired_length - 1] = '~';
              }
              output_ptr[desired_length] = 0;
            } else if (print_len < desired_length) {
              if (argument_data[0].data[1] == '\0') {
                char pad = ' ';
                if (argument_data[1].data[0] != -1) {
                  pad = argument_data[1].data[0];
                }
                kstrinsert(output_ptr, pad, desired_length - print_len);
              } else {
                ;
                output_ptr = strend(output_ptr);
                s32 print_len__ = print_len - 1;
                while (0 < print_len__) {
                  // char* l108

                  char pad = ' ';
                  if (argument_data[1].data[0] != -1) {
                    pad = argument_data[1].data[0];
                  }
                  print_len__--;
                  output_ptr[0] = pad;
                  output_ptr++;
                };
                *output_ptr = 0;
              }
            }
          }
          output_ptr = strend(output_ptr);
        } break;

        case 'T': {
          int stop = 1;
          if (false)
            stop = -1;
          for (int i = 0; i < stop; i++) {
            *output_ptr = '\t';
            output_ptr++;
          }
        } break;

        case 'X':
        case 'x': {
          char pad = '0';
          if (false /*argument_data[1].data[0] != -1*/) {
            pad = -1;
          }
          s64 in = arg_regs[arg_reg_idx++];
          kitoa(output_ptr, in, 16, -1, pad, 0);
          output_ptr = strend(output_ptr);
        } break;

        case 'f':
        {
          u32 in = (u32)arg_regs[arg_reg_idx++];
          s8 pad_length = -1;
          s8 pad_char = -1;
          if (pad_char == -1)
            pad_char = ' ';
          s8 precision = -1;
          if (precision == -1)
            precision = 4;
          ftoa(output_ptr, (float)in, pad_length, pad_char, precision, 0);
          output_ptr = strend(output_ptr);
        } break;

        case 't':
          int stop = 8;
          if (false)
            stop = -1;
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
      if (format_ptr[-1] > 2) {
        format_ptr++;
        continue;
      }
      format_ptr += 2;
      if (format_ptr[0] != 0) {
        *output_ptr = *format_ptr;
        output_ptr++;
        format_ptr++;
        continue;
      }
    }
  }

  *output_ptr = 0;

  if (original_dest == (long)(unaff_s7_lo + 4)) {
    if (DiskBoot != 0) {
      if (true) {
        printf("%s", PrintPendingLocal__);
        fflush(*(FILE **)(_impure_ptr + 8));
      }
      PrintPending = PrintPendingLocal__;
      *PrintPendingLocal__ = 0;
    }

    return 0;
  } else if (original_dest == CONCAT44(unaff_s7_hi, unaff_s7_lo)) {
    u32 string = (u32)make_string_from_c(PrintPendingLocal__);
    PrintPending = PrintPendingLocal__;
    *PrintPendingLocal__ = 0;
    return (s32)string;
  } else if (original_dest == 0) {
    printf("%s", PrintPendingLocal__);
    fflush(*(FILE **)(_impure_ptr + 8));
    PrintPending = PrintPendingLocal__;
    *PrintPendingLocal__ = 0;
    return 0;
  } else {
    if ((original_dest & 7) == 4) {
      if (*(int *)((int)args - 4) == *(int *)(unaff_s7_lo + 0xf)) {
        u32 len = (long)*(int *)args;
        char* str = (char *)((int)args + 4);
        strncat(str, PrintPendingLocal__, len);
        PrintPending = PrintPendingLocal__;
        *PrintPendingLocal__ = 0;
        return 0;
      } else if (*(int *)((int)args - 4) == *(int *)(unaff_s7_lo + 0x8b)) {
        size_t len = strlen(PrintPendingLocal__);
        sceWrite((long)*(int *)((int)args + 12), PrintPendingLocal__, (int)len);

        PrintPending = PrintPendingLocal__;
        *PrintPendingLocal__ = 0;
        return 0;
      }
    }
    return 0;
  }

}