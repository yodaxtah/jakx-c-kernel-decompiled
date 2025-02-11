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
  size_t sVar4;
  char *pcVar5;
  ulong uVar6;
  int in_a1_lo;
  byte *pbVar7;
  Type *type;
  s32 desired_len;
  s64 value;
  char cVar8;
  u32 method_id;
  u64 base;
  s32 precision;
  byte *pbVar10;
  uint uVar11;
  int iVar12;
  byte format_ptr_asterisk;
  char *pbVar9;
  byte *format_ptr;
  s64 *psVar16;
  s64 *psVar17;
  int unaff_s7_lo;
  undefined4 unaff_s7_hi;
  float fVar18;
  byte local_180;
  char local_17f;
  byte local_140;
  undefined local_100;
  undefined local_c0;
  uint local_80;
  s64 local_30 [6];
  
  uVar6 = (ulong)(int)args;
  char* print_temp = PrintPending;
  if (PrintPending == (char *)0x0) {
    print_temp = PrintBufArea + 0x18;
  }
  __src = (byte *)strend(print_temp);
  PrintPending = (char *)__src;
  byte* output_ptr = __src;

  pbVar7 = (byte *)(in_a1_lo + 4);
  local_80 = *(uint *)(print_column + -1) >> 3;
  if ((local_80 != 0) && (uVar11 = local_80, __src[-1] == 10)) {
    for (; uVar11 != 0; uVar11 = uVar11 - 1) {
      *output_ptr = ' ';
      output_ptr++;
    }
  }
  psVar16 = local_30;
LAB_loop_over_format_string:
  while (format_ptr_asterisk = *pbVar7, format_ptr_asterisk != 0) {
    if (format_ptr_asterisk == '~') {
      int arg_char;
      local_17f = '\0';
      local_c0 = 0xff;
      local_180 = 0xff;
      local_140 = 0xff;
      local_100 = 0xff;
      pbVar10 = &local_180;
      format_ptr = pbVar7;
LAB_00267bfc:
      format_ptr_asterisk = format_ptr[1];
      int iVar12 = (int)(char)format_ptr_asterisk;
      if (iVar12 - 0x30U < 10) {
        arg_char = (uint)format_ptr_asterisk << 0x18;
      }
      else {
        if (((iVar12 != ',') && (iVar12 != '\'')) && (iVar12 != '`')) {
          if (*pbVar10 != 0xff) goto LAB_00267c50;
          if (iVar12 != '-') {
            arg_char = (uint)format_ptr_asterisk << 0x18;
            if (iVar12 == '+') goto LAB_002682b0;
            goto LAB_00267c50;
          }
        }
        arg_char = (uint)format_ptr_asterisk << 0x18;
      }
LAB_002682b0:
      arg_char = arg_char >> 0x18;
      if (arg_char == ',') {
        pbVar10 = pbVar10 + '@';
        format_ptr = format_ptr + 1;
      }
      else if (arg_char < '-') {
        if (arg_char == '\'') {  // 0x27
          *pbVar10 = format_ptr[2];
          format_ptr = format_ptr + 2;
        }
        else if (arg_char == '+') {  // 0x2b
          format_ptr = format_ptr + 1;
        }
        else {
          bVar1 = *pbVar10;
          if (bVar1 == 0xff) {
            *pbVar10 = 0;
          }
          format_ptr = format_ptr + 1;
          *pbVar10 = (format_ptr_asterisk + *pbVar10 * '\n') - '0';
          goto LAB_00267bfc;
        }
      }
      else if (arg_char == '-') {  // 0x2d
        format_ptr = format_ptr + 1;
        pbVar10[1] = 1;
      }
      else if (arg_char != '`') {  // else
        bVar1 = *pbVar10;
        if (bVar1 == 0xff) {
          *pbVar10 = 0;
        }
        format_ptr = format_ptr + 1;
        *pbVar10 = (format_ptr_asterisk + *pbVar10 * '\n') - '0';
        goto LAB_00267bfc;
      } else if (arg_char == '`') {  // 0x60
        int i = 0;
        format_ptr_asterisk = format_ptr[2];
        while (format_ptr = format_ptr + 1, format_ptr_asterisk != '`') {
          pbVar10[i] = format_ptr_asterisk;
          i = i + 1;
          format_ptr_asterisk = format_ptr[2];
        }
        format_ptr = format_ptr + 1;
        pbVar10[i] = 0;
      }
      goto LAB_00267bfc;
    }
    *output_ptr = format_ptr_asterisk;
    output_ptr++;
    pbVar9 = (char *)pbVar7;
    if (2 < *pbVar7 - 1) {
      pbVar7 = (byte *)pbVar9 + 1;
      goto LAB_loop_over_format_string;
    }
    format_ptr = pbVar7 + 1;
    pbVar7 = pbVar7 + 1;
    pbVar9 = (char *)pbVar7;
    if (*format_ptr != 0) {
      format_ptr_asterisk = *pbVar9;
      *output_ptr = format_ptr_asterisk;
      output_ptr++;
      pbVar7 = (byte *)pbVar9 + 1;
      goto LAB_loop_over_format_string;
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
        sVar4 = strlen((char *)__src);
        sceWrite((long)*(int *)((int)args + 0xc),(char *)__src,(int)sVar4);
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
    pbVar7 = format_ptr + 2;
    goto LAB_loop_over_format_string;
  }
  switch (*format_ptr_plus1) {
  case '%':
    *output_ptr = 10;
    output_ptr++;
    if (((local_80 != 0) && (format_ptr[2] != 0)) && (local_80 != 0)) {
      int i = 0;
      do {
        i = i + 1;
        *output_ptr = ' ';
        output_ptr++;
      } while (i < (int)local_80);
      pbVar7 = format_ptr + 2;
      goto LAB_loop_over_format_string;
    }
    pbVar7 = (byte *)format_ptr_plus1 + 1;
    goto LAB_loop_over_format_string;
  default:
    MsgErr("format: unknown code 0x%02x\n",*format_ptr_plus1);
    pbVar7 = format_ptr + 2;
    goto LAB_loop_over_format_string;
  case 'A':
  case 'a':
    psVar17 = psVar16 + 1;
    *output_ptr = 0;
    print_object((u32)*(char **)psVar16);
    if (false) {
      sVar4 = strlen((char *)output_ptr);
      if ((long)sVar4 < 0) {
        if ((long)sVar4 < -1) {
          iVar12 = (int)sVar4;
          if (local_17f == '\0') {
            format_ptr_asterisk = ' ';
            if (local_140 != 0xff) {
              format_ptr_asterisk = local_140;
            }
            kstrinsert((char *)output_ptr,format_ptr_asterisk,-1 - iVar12);
            psVar17 = psVar16 + 1;
            break;
          }
          else {
            output_ptr = (byte *)strend((char *)output_ptr);
            iVar12 = -1 - iVar12;
            pbVar7 = output_ptr;
            if (iVar12 < 1) {
              *output_ptr = 0;
            }
            else {
              do {
                output_ptr = pbVar7 + 1;
                format_ptr_asterisk = local_140;
                if (local_140 == 0xff) {
                  format_ptr_asterisk = ' ';
                }
                iVar12 = iVar12 + -1;
                *pbVar7 = format_ptr_asterisk;
                pbVar7 = output_ptr;
              } while (iVar12 != 0);
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
    break;
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
    break;
  case 'C':
  case 'c':
    *output_ptr = *(byte *)psVar16;
    psVar16 = psVar16 + 1;
    output_ptr++;
    pbVar7 = (byte *)format_ptr_plus1 + 1;
    goto LAB_loop_over_format_string;
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
    break;
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
    break;
  case 'F':
    pcVar5 = *(char **)psVar16;
    desired_len = 0xc;
    cVar8 = ' ';
    precision = 4;
    ftoa((char *)output_ptr,(float)pcVar5,desired_len,cVar8,precision,0);
    psVar17 = psVar16 + 1;
    break;
  case 'G':
  case 'g':
    *output_ptr = 0;
    psVar17 = psVar16 + 1;
    strcat((char *)output_ptr,*(char **)psVar16);
    break;
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
    if (pbVar7 < format_ptr_plus1) {
      do {
        *output_ptr = *pbVar7;
        pbVar7 = pbVar7 + 1;
        output_ptr++;
      } while (pbVar7 < format_ptr_plus1);
    }
    format_ptr_asterisk = *format_ptr_plus1;
    *output_ptr = format_ptr_asterisk;
    output_ptr++;
    pbVar7 = (byte *)format_ptr_plus1 + 1;
    goto LAB_loop_over_format_string;
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
          psVar17 = psVar16 + 1;
          call_method_of_type((u32)pcVar5,type,method_id);
          break;
        }
        pcVar5 = *(char **)psVar16;
      }
    }
    else {
      pcVar5 = *(char **)psVar16;
    }
    psVar17 = psVar16 + 1;
    inspect_object((u32)pcVar5);
    break;
  case 'M':
  case 'm':
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
    break;
  case 'O':
  case 'o': {
    *output_ptr = '~';
    kitoa((char *)(output_ptr + 1),*psVar16,10,0,' ',0);
    psVar16 = psVar16 + 1;
    output_ptr = (byte *)strend((char *)(output_ptr + 1));
    format_ptr_asterisk = 0x75;
    *output_ptr = format_ptr_asterisk;
    output_ptr++;
    pbVar7 = (byte *)format_ptr_plus1 + 1;
    goto LAB_loop_over_format_string;
  }
  case 'P':
  case 'p':
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
          psVar17 = psVar16 + 1;
          call_method_of_type((u32)pcVar5,type,method_id);
          break;
        }
        pcVar5 = *(char **)psVar16;
      }
    }
    else {
      pcVar5 = *(char **)psVar16;
    }
    psVar17 = psVar16 + 1;
    print_object((u32)pcVar5);
    break;
  case 'Q':
  case 'q':
    kqtoa_G();
    psVar17 = psVar16;
    break;
  case 'R':
  case 'r':
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
    break;
  case 'S':
  case 's':
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
      sVar4 = strlen((char *)output_ptr);
      if (-1 < (long)sVar4) {
        if (false) {
          output_ptr[-2] = '~';
        }
        output_ptr[-1] = 0;
        psVar17 = psVar16 + 1;
        break;
      }
      if ((long)sVar4 < -1) {
        iVar12 = (int)sVar4;
        if (local_17f == '\0') {
          format_ptr_asterisk = ' ';
          if (local_140 != 0xff) {
            format_ptr_asterisk = local_140;
          }
          kstrinsert((char *)output_ptr,format_ptr_asterisk,-1 - iVar12);
          psVar17 = psVar16 + 1;
          break;
        };
        output_ptr = (byte *)strend((char *)output_ptr);
        iVar12 = -1 - iVar12;
        pbVar7 = output_ptr;
        if (iVar12 < 1) {
          *output_ptr = 0;
        }
        else {
          do {
            output_ptr = pbVar7 + 1;
            format_ptr_asterisk = local_140;
            if (local_140 == 0xff) {
              format_ptr_asterisk = ' ';
            }
            iVar12 = iVar12 + -1;
            *pbVar7 = format_ptr_asterisk;
            pbVar7 = output_ptr;
          } while (iVar12 != 0);
          *output_ptr = 0;
        }
      }
    }
    break;
  case 'T':
    iVar12 = 1;
    if (false) {
      iVar12 = -1;
    }
    int i = 0;
    if (0 < iVar12) {
      do {
        i = i + 1;
        *output_ptr = 9;
        output_ptr++;
      } while (i < iVar12);
      pbVar7 = format_ptr + 2;
      goto LAB_loop_over_format_string;
    }
    pbVar7 = (byte *)format_ptr_plus1 + 1;
    goto LAB_loop_over_format_string;
  case 'X':
  case 'x':
    value = *psVar16;
    cVar8 = '0';
    if (false) {
      cVar8 = -1;
    }
    base = 0x10;
LAB_00267e40:
    kitoa((char *)output_ptr,value,base,-1,cVar8,0);
    psVar17 = psVar16 + 1;
    break;
  case 'f':
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
    break;
  case 't':
    int stop = 8;
    if (false) {
      stop = -1;
    }
    int i = 0;
    if (0 < stop) {
      do {
        i = i + 1;
        *output_ptr = ' ';
        output_ptr++;
      } while (i < stop);
      pbVar7 = format_ptr + 2;
      goto LAB_loop_over_format_string;
    }
    pbVar7 = (byte *)format_ptr_plus1 + 1;
    goto LAB_loop_over_format_string;
  case '~':
    *output_ptr = '~';
    output_ptr++;
    pbVar7 = (byte *)format_ptr_plus1 + 1;
    goto LAB_loop_over_format_string;
  }
  output_ptr = (byte *)strend((char *)output_ptr);
  psVar16 = psVar17;
  pbVar7 = (byte *)format_ptr_plus1 + 1;
  goto LAB_loop_over_format_string;
}
