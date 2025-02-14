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
  byte bVar1;
  byte *__src;
  Symbol4 *pSVar2;
  String *pSVar3;
  char *pcVar5;
  ulong uVar6;
  int in_a1_lo;
  byte *format_ptr_2__;
  Type *type;
  s32 desired_len;
  s64 value;
  char cVar8;
  u32 method_id;
  u64 base;
  s32 precision;
  byte *argument_data;
  int iVar12;
  char *pbVar9;
  byte *format_ptr;
  s64 *psVar16;
  s64 *psVar17;
  int unaff_s7_lo;
  undefined4 unaff_s7_hi;
  float fVar18;
  byte local_180;
  byte local_140;
  undefined local_100;
  undefined local_c0;
  s64 local_30 [6];
  
  uVar6 = (ulong)(int)args;
  char* print_temp = PrintPending;
  if (PrintPending == (char *)0x0) {
    print_temp = PrintBufArea + 0x18;
  }
  __src = (byte *)strend(print_temp);
  PrintPending = (char *)__src;
  byte* output_ptr = __src;
  
  format_ptr_2__ = (byte *)(in_a1_lo + 4);

  uint indentation = 0;

  indentation = *(uint *)(print_column + -1) >> 3;
  if (indentation != 0 && __src[-1] == '\n') {
    for (uint i = indentation; i != 0; i--) {
      *output_ptr = ' ';
      output_ptr++;
    }
  }
  psVar16 = local_30;
LAB_while:
  while (*format_ptr_2__ != 0) {
    if (*format_ptr_2__ == '~') {
      int arg_char;
      char justify = '\0';
      local_c0 = 0xff;
      local_180 = 0xff;
      local_140 = 0xff;
      local_100 = 0xff;
      argument_data = &local_180;
      format_ptr = format_ptr_2__;
LAB_continue_noinit:
      if ((int)(char)format_ptr[1] - 0x30U < 10) {
        arg_char = (uint)format_ptr[1] << 0x18;
      }
      else {
        if ((((int)(char)format_ptr[1] != ',') && ((int)(char)format_ptr[1] != '\'')) && ((int)(char)format_ptr[1] != '`')) {
          if (*argument_data != 0xff) goto LAB_00267c50;
          if ((int)(char)format_ptr[1] != '-') {
            arg_char = (uint)format_ptr[1] << 0x18;
            if ((int)(char)format_ptr[1] == '+') goto LAB_002682b0;
            goto LAB_00267c50;
          }
        }
        arg_char = (uint)format_ptr[1] << 0x18;
      }

LAB_002682b0:
      arg_char = arg_char >> 0x18;
      if (arg_char == ',') {
        argument_data = argument_data + '@';
        format_ptr++;
        goto LAB_continue_noinit;
      }
      
      if (arg_char == '\'') {  // 0x27
        *argument_data = format_ptr[2];
        format_ptr += 2;
        goto LAB_continue_noinit;
      }

      if (arg_char == '`') {  // 0x60
        s32 i = 0;
        byte temp = format_ptr[2];
        while (temp != '`') {
          argument_data[i] = temp;
          i++;
          format_ptr++;
          temp = format_ptr[2];
        }
        format_ptr++;
        argument_data[i] = 0;
        goto LAB_continue_noinit;
      }

      if (arg_char == '-') {  // 0x2d
        argument_data[1] = 1;
        format_ptr++;
        goto LAB_continue_noinit;
      }

      if (arg_char == '+') {  // 0x2b
        format_ptr++;
        goto LAB_continue_noinit;
      }
      
      if (arg_char < '-') {
        bVar1 = *argument_data;
        if (bVar1 == 0xff) {
          *argument_data = 0;
        }
        format_ptr++;
        *argument_data = (format_ptr[1] + *argument_data * '\n') - '0';
        goto LAB_continue_noinit;
      }

      if (arg_char != '`' && arg_char >= '-' && arg_char != ',') {  // else
        bVar1 = *argument_data;
        if (bVar1 == 0xff) {
          *argument_data = 0;
        }
        format_ptr++;
        *argument_data = (format_ptr[1] + *argument_data * '\n') - '0';
        goto LAB_continue_noinit;
      }
    }
    *output_ptr = *format_ptr_2__;
    output_ptr++;
    pbVar9 = (char *)format_ptr_2__;
    if (2 < *format_ptr_2__ - 1) {
      format_ptr_2__ = (byte *)pbVar9 + 1;
      goto LAB_while;
    }
    format_ptr = format_ptr_2__ + 1;
    format_ptr_2__ = format_ptr_2__ + 1;
    pbVar9 = (char *)format_ptr_2__;
    if (*format_ptr != 0) {
      byte format_ptr_asterisk___ = *pbVar9;
      *output_ptr = format_ptr_asterisk___;
      output_ptr++;
      format_ptr_2__ = (byte *)pbVar9 + 1;
      goto LAB_while;
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
      if (*(int *)((int)args + -4) == *(int *)(unaff_s7_lo + 0xf)) {
        strncat((char *)((int)args + 4),(char *)__src,(long)*(int *)args);
      }
      else {
        if (*(int *)((int)args + -4) != *(int *)(unaff_s7_lo + 0x8b)) {
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
LAB_00267c50:
  char* format_ptr_plus1 = (char *)(format_ptr + 1);
  if (false) {
    MsgErr("format: unknown code 0x%02x\n",*format_ptr_plus1);
    format_ptr_2__ = format_ptr + 2;
    goto LAB_while;
  }
  switch (*format_ptr_plus1) {
  case '%':
    *output_ptr = '\n';
    output_ptr++;
    if (((indentation != 0) && (format_ptr[2] != 0)) && (indentation != 0)) {
      for (int i = 0; i < (int)indentation; i++) {
        *output_ptr = ' ';
        output_ptr++;
      }
      format_ptr_2__ = format_ptr + 2;
      goto LAB_while;
    }
    format_ptr_2__ = (byte *)format_ptr_plus1 + 1;
    goto LAB_while;

  default:
    MsgErr("format: unknown code 0x%02x\n",*format_ptr_plus1);
    format_ptr_2__ = format_ptr + 2;
    goto LAB_while;

  case 'A':
  case 'a':
  {
    psVar17 = psVar16 + 1;
    *output_ptr = 0;
    print_object((u32)*(char **)psVar16);
    if (false) {
      size_t print_len_size_t = strlen((char *)output_ptr);
      if ((long)print_len_size_t < 0) {
        if ((long)print_len_size_t < -1) {
          int print_len = (int)print_len_size_t;
          if (justify == '\0') {
            byte pad = ' ';
            if (local_140 != 0xff) {
              pad = local_140;
            }
            kstrinsert((char *)output_ptr,pad,-1 - print_len);
            psVar17 = psVar16 + 1;
            output_ptr = (byte *)strend((char *)output_ptr);
            psVar16 = psVar17;
            format_ptr_2__ = (byte *)format_ptr_plus1 + 1;
            goto LAB_while;
          }
          else {
            output_ptr = (byte *)strend((char *)output_ptr);
            print_len = -1 - print_len;
            format_ptr_2__ = output_ptr;
            if (print_len < 1) {
              *output_ptr = 0;
            }
            else {
              do {
                output_ptr = format_ptr_2__ + 1;
                byte pad = local_140;
                if (local_140 == 0xff) {
                  pad = ' ';
                }
                print_len = print_len + -1;
                *format_ptr_2__ = pad;
                format_ptr_2__ = output_ptr;
              } while (print_len != 0);
              *output_ptr = 0;
            }
          }
        }
      }
      else {
        if (false) {
          output_ptr[-2] = '~';
        }
        output_ptr[-1] = 0;
        psVar17 = psVar16 + 1;
      }
    }
    output_ptr = (byte *)strend((char *)output_ptr);
    psVar16 = psVar17;
    format_ptr_2__ = (byte *)format_ptr_plus1 + 1;
    goto LAB_while;
  }

  case 'B':
  case 'b':
    value = *psVar16;
    cVar8 = '0';
    if (false) {
      cVar8 = -1;
    }
    base = 2;
    kitoa((char *)output_ptr,value,base,-1,cVar8,0);
    psVar17 = psVar16 + 1;
    output_ptr = (byte *)strend((char *)output_ptr);
    psVar16 = psVar17;
    format_ptr_2__ = (byte *)format_ptr_plus1 + 1;
    goto LAB_while;

  case 'C':
  case 'c':
    *output_ptr = *(byte *)psVar16;
    psVar16 = psVar16 + 1;
    output_ptr++;
    format_ptr_2__ = (byte *)format_ptr_plus1 + 1;
    goto LAB_while;

  case 'D':
  case 'd':
    value = *psVar16;
    cVar8 = ' ';
    if (false) {
      cVar8 = -1;
    }
    base = 10;
    kitoa((char *)output_ptr,value,base,-1,cVar8,0);
    psVar17 = psVar16 + 1;
    output_ptr = (byte *)strend((char *)output_ptr);
    psVar16 = psVar17;
    format_ptr_2__ = (byte *)format_ptr_plus1 + 1;
    goto LAB_while;

  case 'E':
  case 'e':
    pcVar5 = *(char **)psVar16;
    if ((int)pcVar5 < 0) {
      fVar18 = (float)((uint)pcVar5 & 1 | (uint)pcVar5 >> 1);
      fVar18 = fVar18 + fVar18;
    }
    else {
      fVar18 = (float)(int)pcVar5;
    }
    desired_len = -1;
    pcVar5 = (char *)(fVar18 / 300.0);
    cVar8 = ' ';
    if (false) {
      cVar8 = -1;
    }
    precision = 4;
    if (false) {
      precision = -1;
    }
    ftoa((char *)output_ptr,(float)pcVar5,desired_len,cVar8,precision,0);
    psVar17 = psVar16 + 1;
    output_ptr = (byte *)strend((char *)output_ptr);
    psVar16 = psVar17;
    format_ptr_2__ = (byte *)format_ptr_plus1 + 1;
    goto LAB_while;

  case 'F':
  {
    pcVar5 = *(char **)psVar16;
    desired_len = 0xc;
    cVar8 = ' ';
    precision = 4;
    ftoa((char *)output_ptr,(float)pcVar5,desired_len,cVar8,precision,0);
    psVar17 = psVar16 + 1;
    output_ptr = (byte *)strend((char *)output_ptr);
    psVar16 = psVar17;
    format_ptr_2__ = (byte *)format_ptr_plus1 + 1;
    goto LAB_while;
  }

  case 'G':
  case 'g':
    *output_ptr = 0;
    strcat((char *)output_ptr,*(char **)psVar16);
    psVar17 = psVar16 + 1;
    output_ptr = (byte *)strend((char *)output_ptr);
    psVar16 = psVar17;
    format_ptr_2__ = (byte *)format_ptr_plus1 + 1;
    goto LAB_while;

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
    while (format_ptr_2__ < format_ptr_plus1) {
      *output_ptr = *format_ptr_2__;
      format_ptr_2__ = format_ptr_2__ + 1;
      output_ptr++;
    }
    *output_ptr = *format_ptr_plus1;
    output_ptr++;
    format_ptr_2__ = (byte *)format_ptr_plus1 + 1;
    goto LAB_while;

  case 'I':
  case 'i':
    *output_ptr = 0;
    if (false) {
      pSVar2 = find_symbol_from_c(0xffff,(const_char *)&local_180);
      if (pSVar2 == (Symbol4 *)0x0) {
        pcVar5 = *(char **)psVar16;
      }
      else {
        type = *(Type **)((int)&pSVar2[-1].foo + 3);
        method_id = 3;
        if (type != (Type *)0x0) {
          pcVar5 = *(char **)psVar16;
          call_method_of_type((u32)pcVar5,type,method_id);
          psVar17 = psVar16 + 1;
          output_ptr = (byte *)strend((char *)output_ptr);
          psVar16 = psVar17;
          format_ptr_2__ = (byte *)format_ptr_plus1 + 1;
          goto LAB_while;
        }
        pcVar5 = *(char **)psVar16;
      }
    }
    else {
      pcVar5 = *(char **)psVar16;
    }
    inspect_object((u32)pcVar5);
    psVar17 = psVar16 + 1;
    output_ptr = (byte *)strend((char *)output_ptr);
    psVar16 = psVar17;
    format_ptr_2__ = (byte *)format_ptr_plus1 + 1;
    goto LAB_while;
    
  case 'M':
  case 'm': {
    pcVar5 = (char *)((float)*(char **)psVar16 * 0.0002441406);
    cVar8 = ' ';
    if (false) {
      cVar8 = -1;
    }
    precision = 4;
    if (false) {
      precision = -1;
    }
    desired_len = -1;
    ftoa((char *)output_ptr,(float)pcVar5,desired_len,cVar8,precision,0);
    psVar17 = psVar16 + 1;
    output_ptr = (byte *)strend((char *)output_ptr);
    psVar16 = psVar17;
    format_ptr_2__ = (byte *)format_ptr_plus1 + 1;
    goto LAB_while;
  }

  case 'O':
  case 'o': {
    *output_ptr = '~';
    output_ptr++;
    kitoa((char *)output_ptr,*psVar16,10,0,' ',0);
    psVar16 = psVar16 + 1;
    output_ptr = (byte *)strend((char *)output_ptr);
    *output_ptr = 'u';
    output_ptr++;
    format_ptr_2__ = (byte *)format_ptr_plus1 + 1;
    goto LAB_while;
  }

  case 'P':
  case 'p': {
    *output_ptr = 0;
    if (false) {
      pSVar2 = find_symbol_from_c(0xffff,(const_char *)&local_180);
      if (pSVar2 == (Symbol4 *)0x0) {
        pcVar5 = *(char **)psVar16;
      }
      else {
        type = *(Type **)((int)&pSVar2[-1].foo + 3);
        method_id = 2;
        if (type != (Type *)0x0) {
          pcVar5 = *(char **)psVar16;
          call_method_of_type((u32)pcVar5,type,method_id);
          psVar17 = psVar16 + 1;
          output_ptr = (byte *)strend((char *)output_ptr);
          psVar16 = psVar17;
          format_ptr_2__ = (byte *)format_ptr_plus1 + 1;
          goto LAB_while;
        }
        pcVar5 = *(char **)psVar16;
      }
    }
    else {
      pcVar5 = *(char **)psVar16;
    }
    print_object((u32)pcVar5);
    psVar17 = psVar16 + 1;
    output_ptr = (byte *)strend((char *)output_ptr);
    psVar16 = psVar17;
    format_ptr_2__ = (byte *)format_ptr_plus1 + 1;
    goto LAB_while;
  }

  case 'Q':
  case 'q':
    kqtoa_G();
    psVar17 = psVar16;
    output_ptr = (byte *)strend((char *)output_ptr);
    psVar16 = psVar17;
    format_ptr_2__ = (byte *)format_ptr_plus1 + 1;
    goto LAB_while;

  case 'R':
  case 'r': {
    cVar8 = ' ';
    if (false) {
      cVar8 = -1;
    }
    desired_len = -1;
    precision = 4;
    if (false) {
      precision = -1;
    }
    pcVar5 = (char *)((float)*(char **)psVar16 * 360.0 * 1.525879e-05);
    ftoa((char *)output_ptr,(float)pcVar5,desired_len,cVar8,precision,0);
    psVar17 = psVar16 + 1;
    output_ptr = (byte *)strend((char *)output_ptr);
    psVar16 = psVar17;
    format_ptr_2__ = (byte *)format_ptr_plus1 + 1;
    goto LAB_while;
  }

  case 'S':
  case 's': {
    pcVar5 = *(char **)psVar16;
    psVar17 = psVar16 + 1;
    *output_ptr = 0;
    if ((((uint)pcVar5 & 7) == 4) && (*(int *)(pcVar5 + -4) == *(int *)(unaff_s7_lo + 0xf))) {
      cprintf("%s",pcVar5 + 4);
    }
    else {
      print_object((u32)pcVar5);
    }

    if (false) {
      size_t print_len = strlen((char *)output_ptr);
      if (-1 < (long)print_len) {
        if (false) {
          output_ptr[-2] = '~';
        }
        output_ptr[-1] = 0;
        psVar17 = psVar16 + 1;
        output_ptr = (byte *)strend((char *)output_ptr);
        psVar16 = psVar17;
        format_ptr_2__ = (byte *)format_ptr_plus1 + 1;
        goto LAB_while;
      } else if ((long)print_len < -1) {
        iVar12 = (int)print_len;
        if (justify == '\0') {
          byte format_ptr_asterisk___ = ' ';
          if (local_140 != 0xff) {
            format_ptr_asterisk___ = local_140;
          }
          kstrinsert((char *)output_ptr,format_ptr_asterisk___,-1 - iVar12);
          psVar17 = psVar16 + 1;
          output_ptr = (byte *)strend((char *)output_ptr);
          psVar16 = psVar17;
          format_ptr_2__ = (byte *)format_ptr_plus1 + 1;
          goto LAB_while;
        };
        output_ptr = (byte *)strend((char *)output_ptr);
        iVar12 = -1 - iVar12;
        format_ptr_2__ = output_ptr;
        if (iVar12 < 1) {
          *output_ptr = 0;
        }
        else {
          do {
            output_ptr = format_ptr_2__ + 1;
            byte format_ptr_asterisk___ = local_140;
            if (local_140 == 0xff) {
              format_ptr_asterisk___ = ' ';
            }
            iVar12 = iVar12 + -1;
            *format_ptr_2__ = format_ptr_asterisk___;
            format_ptr_2__ = output_ptr;
          } while (iVar12 != 0);
          *output_ptr = 0;
        }
      }
    }
    // psVar17 = psVar16 + 1 before if statement in this case
    output_ptr = (byte *)strend((char *)output_ptr);
    psVar16 = psVar17;
    format_ptr_2__ = (byte *)format_ptr_plus1 + 1;
    goto LAB_while;
  }

  case 'T':
    iVar12 = 1;
    if (false) {
      iVar12 = -1;
    }
    int i = 0;
    if (0 < iVar12) {
      for (int i = 0; i < iVar12; i++) {
        *output_ptr = 9;
        output_ptr++;
      }
      format_ptr_2__ = format_ptr + 2;
      goto LAB_while;
    }
    format_ptr_2__ = (byte *)format_ptr_plus1 + 1;
    goto LAB_while;

  case 'X':
  case 'x': {
    value = *psVar16;
    cVar8 = '0';
    if (false) {
      cVar8 = -1;
    }
    base = 0x10;
LAB_00267e40:
    kitoa((char *)output_ptr,value,base,-1,cVar8,0);
    psVar17 = psVar16 + 1;
    output_ptr = (byte *)strend((char *)output_ptr);
    psVar16 = psVar17;
    format_ptr_2__ = (byte *)format_ptr_plus1 + 1;
    goto LAB_while;
  }

  case 'f':
  {
    pcVar5 = *(char **)psVar16;
    cVar8 = ' ';
    if (false) {
      cVar8 = -1;
    }
    precision = 4;
    if (false) {
      precision = -1;
    }
    desired_len = -1;
    ftoa((char *)output_ptr,(float)pcVar5,desired_len,cVar8,precision,0);
    psVar17 = psVar16 + 1;
    output_ptr = (byte *)strend((char *)output_ptr);
    psVar16 = psVar17;
    format_ptr_2__ = (byte *)format_ptr_plus1 + 1;
    goto LAB_while;
  }

  case 't':
    int stop = 8;
    if (false) {
      stop = -1;
    }
    int i = 0;
    if (0 < stop) {
      for (int i = 0; i < stop; i++) {
        *output_ptr = ' ';
        output_ptr++;
      }
      format_ptr_2__ = format_ptr + 2;
      goto LAB_while;
    }
    format_ptr_2__ = (byte *)format_ptr_plus1 + 1;
    goto LAB_while;

  case '~':
    *output_ptr = '~';
    output_ptr++;
    format_ptr_2__ = (byte *)format_ptr_plus1 + 1;
    goto LAB_while;
  }
}
