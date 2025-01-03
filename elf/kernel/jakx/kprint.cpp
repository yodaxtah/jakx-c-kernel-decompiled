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
s32 format_impl_jak3(uint64_t *args) {
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
  int iVar13;
  byte bVar14;
  byte *__s;
  char *pbVar9;
  byte *pbVar15;
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
  pcVar5 = PrintPending;
  if (PrintPending == (char *)0x0) {
    pcVar5 = PrintBufArea + 0x18;
  }
  __src = (byte *)strend(pcVar5);
  pbVar7 = (byte *)(in_a1_lo + 4);
  local_80 = *(uint *)(print_column + -1) >> 3;
  PrintPending = (char *)__src;
  __s = __src;
  if ((local_80 != 0) && (uVar11 = local_80, __src[-1] == 10)) {
    for (; uVar11 != 0; uVar11 = uVar11 - 1) {
      *__s = 0x20;
      __s = __s + 1;
    }
  }
  psVar16 = local_30;
LAB_00267b8c:
  while (bVar14 = *pbVar7, bVar14 != 0) {
    if (bVar14 == 0x7e) {
      local_17f = '\0';
      local_c0 = 0xff;
      local_180 = 0xff;
      local_140 = 0xff;
      local_100 = 0xff;
      pbVar10 = &local_180;
      pbVar15 = pbVar7;
LAB_00267bfc:
      bVar14 = pbVar15[1];
      iVar12 = (int)(char)bVar14;
      if (iVar12 - 0x30U < 10) {
        iVar13 = (uint)bVar14 << 0x18;
      }
      else {
        if (((iVar12 != 0x2c) && (iVar12 != 0x27)) && (iVar12 != 0x60)) {
          if (*pbVar10 != 0xff) goto LAB_00267c50;
          if (iVar12 != 0x2d) {
            iVar13 = (uint)bVar14 << 0x18;
            if (iVar12 == 0x2b) goto LAB_002682b0;
            goto LAB_00267c50;
          }
        }
        iVar13 = (uint)bVar14 << 0x18;
      }
LAB_002682b0:
      iVar13 = iVar13 >> 0x18;
      if (iVar13 == 0x2c) {
        pbVar10 = pbVar10 + 0x40;
        pbVar15 = pbVar15 + 1;
      }
      else if (iVar13 < 0x2d) {
        if (iVar13 == 0x27) {
          *pbVar10 = pbVar15[2];
          pbVar15 = pbVar15 + 2;
        }
        else if (iVar13 == 0x2b) {
          pbVar15 = pbVar15 + 1;
        }
        else {
          bVar1 = *pbVar10;
LAB_002682dc:
          if (bVar1 == 0xff) {
            *pbVar10 = 0;
          }
          pbVar15 = pbVar15 + 1;
          *pbVar10 = (bVar14 + *pbVar10 * '\n') - 0x30;
        }
      }
      else if (iVar13 == 0x2d) {
        pbVar15 = pbVar15 + 1;
        pbVar10[1] = 1;
      }
      else {
        if (iVar13 != 0x60) {
          bVar1 = *pbVar10;
          goto LAB_002682dc;
        }
        iVar12 = 0;
        bVar14 = pbVar15[2];
        while (pbVar15 = pbVar15 + 1, bVar14 != 0x60) {
          pbVar10[iVar12] = bVar14;
          iVar12 = iVar12 + 1;
          bVar14 = pbVar15[2];
        }
        pbVar15 = pbVar15 + 1;
        pbVar10[iVar12] = 0;
      }
      goto LAB_00267bfc;
    }
    *__s = bVar14;
    __s = __s + 1;
    pbVar9 = (char *)pbVar7;
    if (2 < *pbVar7 - 1) goto LAB_00267bd8;
    pbVar15 = pbVar7 + 1;
    pbVar7 = pbVar7 + 1;
    pbVar9 = (char *)pbVar7;
    if (*pbVar15 != 0) goto LAB_00267bcc;
  }
  *__s = 0;
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
      goto LAB_002683dc;
    }
  }
  printf("%s",__src);
  fflush(*(FILE **)(_impure_ptr + 8));
LAB_002683dc:
  PrintPending = (char *)__src;
  *__src = 0;
  return 0;
LAB_00267c50:
  pbVar9 = (char *)(pbVar15 + 1);
  if (false) {
switchD_00267c7c_caseD_26:
    MsgErr("format: unknown code 0x%02x\n",*pbVar9);
    pbVar7 = pbVar15 + 2;
    goto LAB_00267b8c;
  }
  switch(*pbVar9) {
  case '%':
    *__s = 10;
    __s = __s + 1;
    if (((local_80 != 0) && (pbVar15[2] != 0)) && (iVar12 = 0, local_80 != 0)) {
      do {
        iVar12 = iVar12 + 1;
        *__s = 0x20;
        __s = __s + 1;
      } while (iVar12 < (int)local_80);
      pbVar7 = pbVar15 + 2;
      goto LAB_00267b8c;
    }
    goto LAB_00267bd8;
  default:
    goto switchD_00267c7c_caseD_26;
  case 'A':
  case 'a':
    psVar17 = psVar16 + 1;
    *__s = 0;
    print_object((u32)*(char **)psVar16);
    if (false) {
      sVar4 = strlen((char *)__s);
      if ((long)sVar4 < 0) {
        if ((long)sVar4 < -1) {
          iVar12 = (int)sVar4;
          if (local_17f == '\0') {
LAB_00267e08:
            bVar14 = 0x20;
            if (local_140 != 0xff) {
              bVar14 = local_140;
            }
            kstrinsert((char *)__s,bVar14,-1 - iVar12);
            psVar17 = psVar16 + 1;
          }
          else {
            __s = (byte *)strend((char *)__s);
            iVar12 = -1 - iVar12;
            pbVar7 = __s;
            if (iVar12 < 1) {
              *__s = 0;
            }
            else {
              do {
                __s = pbVar7 + 1;
                bVar14 = local_140;
                if (local_140 == 0xff) {
                  bVar14 = 0x20;
                }
                iVar12 = iVar12 + -1;
                *pbVar7 = bVar14;
                pbVar7 = __s;
              } while (iVar12 != 0);
              *__s = 0;
            }
          }
        }
      }
      else {
        if (false) {
          __s[-2] = 0x7e;
        }
LAB_00267d94:
        __s[-1] = 0;
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
    goto LAB_00267e40;
  case 'C':
  case 'c':
    *__s = *(byte *)psVar16;
    psVar16 = psVar16 + 1;
    __s = __s + 1;
    goto LAB_00267bd8;
  case 'D':
  case 'd':
    value = *psVar16;
    cVar8 = ' ';
    if (false) {
      cVar8 = -1;
    }
    base = 10;
    goto LAB_00267e40;
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
    goto LAB_00267cec;
  case 'F':
    pcVar5 = *(char **)psVar16;
    desired_len = 0xc;
    cVar8 = ' ';
    precision = 4;
    goto LAB_00267cec;
  case 'G':
  case 'g':
    *__s = 0;
    psVar17 = psVar16 + 1;
    strcat((char *)__s,*(char **)psVar16);
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
    if (pbVar7 < pbVar9) {
      do {
        *__s = *pbVar7;
        pbVar7 = pbVar7 + 1;
        __s = __s + 1;
      } while (pbVar7 < pbVar9);
      bVar14 = *pbVar9;
    }
    else {
LAB_00267bcc:
      bVar14 = *pbVar9;
    }
    goto LAB_00267bd0;
  case 'I':
  case 'i':
    *__s = 0;
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
LAB_00267f90:
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
    goto LAB_00267f30;
  case 'O':
  case 'o':
    *__s = 0x7e;
    kitoa((char *)(__s + 1),*psVar16,10,0,' ',0);
    psVar16 = psVar16 + 1;
    __s = (byte *)strend((char *)(__s + 1));
    bVar14 = 0x75;
    goto LAB_00267bd0;
  case 'P':
  case 'p':
    *__s = 0;
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
          goto LAB_00267f90;
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
    goto LAB_00267cec;
  case 'S':
  case 's':
    pcVar5 = *(char **)psVar16;
    psVar17 = psVar16 + 1;
    *__s = 0;
    if ((((uint)pcVar5 & 7) == 4) && (*(int *)(pcVar5 + -4) == *(int *)(unaff_s7_lo + 0xf))) {
      cprintf("%s",pcVar5 + 4);
    }
    else {
      print_object((u32)pcVar5);
    }
    if (false) {
      sVar4 = strlen((char *)__s);
      if (-1 < (long)sVar4) {
        if (false) {
          __s[-2] = 0x7e;
        }
        goto LAB_00267d94;
      }
      if ((long)sVar4 < -1) {
        iVar12 = (int)sVar4;
        if (local_17f == '\0') goto LAB_00267e08;
        __s = (byte *)strend((char *)__s);
        iVar12 = -1 - iVar12;
        pbVar7 = __s;
        if (iVar12 < 1) {
          *__s = 0;
        }
        else {
          do {
            __s = pbVar7 + 1;
            bVar14 = local_140;
            if (local_140 == 0xff) {
              bVar14 = 0x20;
            }
            iVar12 = iVar12 + -1;
            *pbVar7 = bVar14;
            pbVar7 = __s;
          } while (iVar12 != 0);
          *__s = 0;
        }
      }
    }
    break;
  case 'T':
    iVar12 = 1;
    if (false) {
      iVar12 = -1;
    }
    iVar13 = 0;
    if (0 < iVar12) {
      do {
        iVar13 = iVar13 + 1;
        *__s = 9;
        __s = __s + 1;
      } while (iVar13 < iVar12);
      pbVar7 = pbVar15 + 2;
      goto LAB_00267b8c;
    }
    goto LAB_00267bd8;
  case 'X':
  case 'x':
    value = *psVar16;
    cVar8 = '0';
    if (false) {
      cVar8 = -1;
    }
    base = 0x10;
LAB_00267e40:
    kitoa((char *)__s,value,base,-1,cVar8,0);
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
LAB_00267f30:
    desired_len = -1;
LAB_00267cec:
    ftoa((char *)__s,(float)pcVar5,desired_len,cVar8,precision,0);
    psVar17 = psVar16 + 1;
    break;
  case 't':
    iVar12 = 8;
    if (false) {
      iVar12 = -1;
    }
    iVar13 = 0;
    if (0 < iVar12) {
      do {
        iVar13 = iVar13 + 1;
        *__s = 0x20;
        __s = __s + 1;
      } while (iVar13 < iVar12);
      pbVar7 = pbVar15 + 2;
      goto LAB_00267b8c;
    }
    goto LAB_00267bd8;
  case '~':
    bVar14 = 0x7e;
LAB_00267bd0:
    *__s = bVar14;
    __s = __s + 1;
    goto LAB_00267bd8;
  }
  __s = (byte *)strend((char *)__s);
  psVar16 = psVar17;
LAB_00267bd8:
  pbVar7 = (byte *)pbVar9 + 1;
  goto LAB_00267b8c;
}
