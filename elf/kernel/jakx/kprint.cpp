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
 * Note: compare this file with kprint.compare.cpp; I reordered the cases.
 */
s32 format_impl_jak3(uint64_t* args) {
  int unaff_s7_lo;
  undefined4 unaff_s7_hi;

  s64 local_30 [6];
  s64* arg_regs = local_30;

  // data for arguments in a format command
  format_struct argument_data [4];

  u32 arg_reg_idx = 0;

  // the gstring
  char* format_gstring; // TODO: why no assignment?

  ulong original_dest = (ulong)(int)args;

  // set up print pending
  char* print_temp = PrintPending.cast<char>().c();
  if (!PrintPending.offset) {
    print_temp = PrintBufArea.cast<char>().c() + sizeof(ListenerMessageHeader);
  }
  PrintPending = make_ptr(strend(print_temp)).cast<u8>();

  // what we write to
  char* output_ptr = PrintPending.cast<char>().c();

  // convert gstring to cstring
  char* format_cstring = format_gstring + 4;

  // mysteries
  char* PrintPendingLocal__ = PrintPending.cast<char>().c();

  // start by computing indentation
  u32 indentation = 0;

  // read goal binteger
  if (true) {
    // added the if check so we can format even if the kernel didn't load right.
    indentation = (*(u32 *)(print_column - 1)) >> 3;
  }

  // which arg we're on
  u32 arg_idx = 0;

  // if last char was newline and we have tabs, do tabs
  if (indentation && output_ptr[-1] == '\n') {
    for (u32 i = 0; i < indentation; i++) {
      *output_ptr = ' ';
      output_ptr++;
    }
  }

  // input pointer
  char* format_ptr = format_cstring;

  // loop over the format string
  while (*format_ptr) {
    // got a command?
    if (*format_ptr == '~') {
      char* arg_start = format_ptr;
      // get some arguments
      arg_idx = 0;
      argument_data[0].data[1] = '\0'; // TODO: why is this a separate variable in jak3?
      for (auto& x : argument_data) {
        x.data[0] = -1; //.reset();
      }

      // read arguments
      while ((u8)(format_ptr[1] - '0') < 10 ||  // number 0 to 9
             format_ptr[1] == ',' ||            // comma
             format_ptr[1] == '\'' ||           // quote
             format_ptr[1] == '`' ||            // backtick
             (argument_data[arg_idx].data[0] == -1 &&
              (format_ptr[1] == '-' || format_ptr[1] == '+')  // flags1 == -1 && +/-
              )) {
        // here format_ptr[1] points to next unread character in argument
        // format_ptr[0] is originally the ~
        // should exit loop with format_ptr[1] == the command character
        char arg_char = format_ptr[1];  // gVar1

        if (arg_char == ',') {
          // advance to next argument
          arg_idx++;     // increment which argument we're on
          format_ptr++;  // increment past comma, and try again
          continue;
        }

        // character argument
        if (arg_char == '\'') {  // 0x27
          argument_data[arg_idx].data[0] = format_ptr[2];
          format_ptr += 2;
          continue;
        }

        // string argument
        if (arg_char == '`') {  // 0x60
          u32 i = 0;
          format_ptr += 2;
          // read string
          while (*format_ptr != '`') {
            argument_data[arg_idx].data[i] = *format_ptr;
            i++;
            format_ptr++;
          }
          format_ptr--; // TODO: why is jakx 1 format ptr 1 index behind on jak3's?
          // null terminate
          argument_data[arg_idx].data[i] = 0;
          continue;
        }

        if (arg_char == '-') {  // 0x2d
          // negative flag
          argument_data[arg_idx].data[1] = 1;
          format_ptr++;
          continue;
        }

        if (arg_char == '+') {  // 0x2b
          // positive flag does nothing
          format_ptr++;
          continue;
        }

        // otherwise:

        // null terminate if we got no args
        if (argument_data[arg_idx].data[0] == -1) {
          argument_data[arg_idx].data[0] = 0;
        }

        // otherwise it's a number
        argument_data[arg_idx].data[0] = argument_data[arg_idx].data[0] * 10 + arg_char - '0';
        format_ptr++;
      }  // end argument while

      // switch on command
      switch (format_ptr[1]) {
          // offset of 0x25

        case '%':  // newline
          *output_ptr = '\n';
          output_ptr++;
          // indent the next line if there is one
          if (indentation && format_ptr[2]) {
            for (u32 i = 0; i < indentation; i++) {
              *output_ptr = ' ';
              output_ptr++;
            }
          }
          break;

        default:
          MsgErr("format: unknown code 0x%02x\n", format_ptr[1]);
          break;

        case 'A':  // print a boxed object
        case 'a':  // pad,padchar (like ) ~8,'0A
        {
          s8 arg0 = -1;
          s32 desired_length = (s32)arg0;
          *output_ptr = 0;
          u32 in = (u32)arg_regs[arg_reg_idx++];
          print_object(in);
          if (false /*desired_length != -1*/) {
            s32 print_len = (s32)strlen(output_ptr);
            if (desired_length < print_len) {
              // too long!
              if (false /*desired_length > 1*/) {  // mark with tilde that we will truncate
                output_ptr[desired_length - 1] = '~';
              }
              output_ptr[desired_length] = 0;  // and truncate
            } else if (print_len < desired_length) {
              // too short
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

        case 'B':  // integer 64, pad padchar
        case 'b': {
          char pad = '0';
          if (false /*argument_data[1].data[0]*/) {
            pad = -1;
          }
          s64 in = arg_regs[arg_reg_idx++];
          kitoa(output_ptr, in, 2, -1, pad, 0);
          output_ptr = strend(output_ptr);
        } break;

        case 'C':  // character
        case 'c':
          *output_ptr = (char)arg_regs[arg_reg_idx++];
          output_ptr++;
          break;

        case 'D':  // integer 64, pad padchar
        case 'd': {
          char pad = ' ';
          if (false /*argument_data[1].data[0] != -1*/) {
            pad = -1;
          }
          u32 in = (u32)arg_regs[arg_reg_idx++];
          kitoa(output_ptr, in, 10, -1, pad, 0);
          output_ptr = strend(output_ptr);
        } break;

        case 'E':  // time seconds
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

        case 'F':  // float 12 pad, 4 precision
        {
          u32 in = (u32)arg_regs[arg_reg_idx++];
          ftoa(output_ptr, (float)in, 0xc, ' ', 4, 0);
          output_ptr = strend(output_ptr);
        } break;

        case 'G':  // like %s, prints a C string
        case 'g': {
          *output_ptr = 0;
          u32 in = (u32)arg_regs[arg_reg_idx++];
          strcat(output_ptr, Ptr<char>(in).c());
          output_ptr = strend(output_ptr);
        } break;

        // pass through arguments
        case 'H':  // 23 -> 48, H
        case 'J':  // 25 -> 4A, J
        case 'K':  // 26 -> 4B, K
        case 'L':  // 27 -> 4C, L
        case 'N':  // 29 -> 4E, N
        case 'U':
        case 'V':  // 31 -> 56, V
        case 'W':  // 32 -> 57, W
        case 'Y':  // 34 -> 59, Y
        case 'Z':  // 35 -> 5A, Z
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

        case 'I':  // like ~P, but calls inpsect
        case 'i': {
          *output_ptr = 0;
          s8 arg0 = -1;
          u32 in = (u32)arg_regs[arg_reg_idx++];
          if (true /*arg0 == -1*/) {
            inspect_object(in);
          } else {
            u32* sym = find_symbol_from_c(-1, (const_char *)&argument_data);
            if (sym != nullptr) {
              Ptr<Type> type = *(Type **)((int)sym - 1);
              if (type != nullptr) {
                call_method_of_type(in, type, GOAL_INSPECT_METHOD);
              }
            } else {
              ;
            }
          }
          output_ptr = strend(output_ptr);
        } break;

        case 'M':  // distance meters
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

        case 'P':  // like ~A, but can specify type explicitly
        case 'p': {
          *output_ptr = 0;
          s8 arg0 = -1;
          u32 in = (u32)arg_regs[arg_reg_idx++];
          if (true /*arg0 == -1*/) {
            print_object(in);
          } else {
            u32* sym = find_symbol_from_c(-1, (const_char *)&argument_data);
            if (sym != nullptr) {
              Ptr<Type> type = *(Type **)((int)sym - 1);
              if (type != nullptr) {
                call_method_of_type(in, type, GOAL_PRINT_METHOD);
              }
            } else {
              ;
            }
          }
          output_ptr = strend(output_ptr);
        } break;

        case 'Q':  // not yet implemented.  hopefully andy gavin finishes this one soon.
        case 'q':
          kqtoa_G();
          output_ptr = strend(output_ptr);
          break;

        case 'R':  // rotation degrees
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

        case 'S':  // like A, but strings are printed without quotes
        case 's': {
          s8 arg0 = -1;
          s32 desired_length = (s32)arg0;
          *output_ptr = 0;
          u32 in = (u32)arg_regs[arg_reg_idx++];

          // if it's a string
          if ((((uint)in & 0x7) == 0x4) && *Ptr<int>(in - 4) == *(int *)(unaff_s7_lo + FIX_SYM_STRING_TYPE - 1)) {
            cprintf("%s", Ptr<char>(in).c() + 4);
          } else {
            print_object(in);
          }

          if (false /*desired_length != -1*/) {
            s32 print_len = (s32)strlen(output_ptr);
            if (desired_length < print_len) {
              // too long!
              if (false /*desired_length < print_len*/) {  // mark with tilde that we will truncate
                output_ptr[desired_length - 1] = '~';
              }
              output_ptr[desired_length] = 0;  // and truncate
            } else if (print_len < desired_length) {
              // too short
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

        case 'X':  // hex, 64 bit, pad padchar
        case 'x': {
          char pad = '0';
          if (false /*argument_data[1].data[0] != -1*/) {
            pad = -1;
          }
          s64 in = arg_regs[arg_reg_idx++];
          kitoa(output_ptr, in, 16, -1, pad, 0);
          output_ptr = strend(output_ptr);
        } break;

        case 'f':  // float with args
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
      // got normal char, just copy it
      *output_ptr = *format_ptr;
      output_ptr++;
      if (format_ptr[-1] > 2) {
        format_ptr++;
        continue;
      }
      format_ptr += 2;
      if (format_ptr[0]) {
        *output_ptr = *format_ptr;
        output_ptr++;
        format_ptr++;
        continue;
      }
    }
  }  // end format string while

  // end
  *output_ptr = 0;

  if (original_dest == (long)(unaff_s7_lo + FIX_SYM_TRUE)) {
    // #t means to put it in the print buffer

    // change for Jak 2: if we are disk-booting and do a (format #t, immediately flush to stdout.
    // we'd get these eventually in ClearPending, but for some reason they flush these here.
    // This is nicer because we may crash in between here and flushing the print buffer.
    if (DiskBoot) {
      // however, we are going to disable it anyway because it spams the console and is annoying
      if (true) {
        printf("%s", PrintPendingLocal__);
        fflush(*(FILE **)(_impure_ptr + 8));
      }
      PrintPending = make_ptr(PrintPendingLocal__).cast<u8>();
      // if we don't comment this line, our output gets cleared
      *PrintPendingLocal__ = 0;
    }

    return 0;
  } else if (original_dest == CONCAT44(unaff_s7_hi, unaff_s7_lo)) {
    // #f means print to new string
    u32 string = (u32)make_string_from_c(PrintPendingLocal__);
    PrintPending = make_ptr(PrintPendingLocal__).cast<u8>();
    *PrintPendingLocal__ = 0;
    return (s32)string;
  } else if (original_dest == 0) {
    printf("%s", PrintPendingLocal__);
    fflush(*(FILE **)(_impure_ptr + 8));
    PrintPending = make_ptr(PrintPendingLocal__).cast<u8>();
    *PrintPendingLocal__ = 0;
    return 0;
  } else {
    if ((original_dest & OFFSET_MASK) == BASIC_OFFSET) {
      Ptr<Type> type = *Ptr<Ptr<int>>((int)args - 4);
      if (type == *Ptr<Ptr<Type>>(unaff_s7_lo + FIX_SYM_STRING_TYPE - 1)) {
        u32 len = (long)*Ptr<s32>(args);
        char* str = Ptr<char>((int)args + 4).c();
        strncat(str, PrintPendingLocal__, len);
        PrintPending = make_ptr(PrintPendingLocal__).cast<u8>();
        *PrintPendingLocal__ = 0;
        return 0;
      } else if (type == *Ptr<Ptr<Type>>(unaff_s7_lo + FIX_SYM_FILE_STREAM - 1)) {
        size_t len = strlen(PrintPendingLocal__);
        // sceWrite
        sceWrite((long)*Ptr<s32>((int)args + 12), PrintPendingLocal__, (int)len);

        PrintPending = make_ptr(PrintPendingLocal__).cast<u8>();
        *PrintPendingLocal__ = 0;
        return 0;
      }
    }
    ;
    return 0;
  }

  ;
}