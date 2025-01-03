#include "klink.h"

#include "common/common_types.h"
#include "common/goal_constants.h"
#include "common/symbols.h"

#include "game/kernel/common/fileio.h"
#include "game/kernel/common/klink.h"
#include "game/kernel/common/kprint.h"
#include "game/kernel/common/memory_layout.h"
#include "game/kernel/jak3/kmalloc.h"
#include "game/kernel/jak3/kscheme.h"
#include "game/mips2c/mips2c_table.h"

#include "fmt/core.h"

namespace {
bool is_opengoal_object(void* data) {
  u32 first_word;
  memcpy(&first_word, data, 4);
  return first_word != 0 && first_word != UINT32_MAX;
}
constexpr bool link_debug_printfs = false;
}  // namespace

void jak3_begin(uint8_t *object_file,const_char *name,int32_t size,kheapinfo heap,uint32_t flags) {
  short sVar1;
  int iVar2;
  kheapinfo *heap_00;
  s32 *psVar3;
  u8 *puVar4;
  undefined *in_t0_lo;
  undefined4 in_t1_lo;
  int iVar5;
  uint uVar6;
  uint32_t *src;
  
  if (in_t0_lo == &DAT_0025bb70) {
    kmemopen_from_c((kheapinfo *)&DAT_0025bb70,(const_char *)size);
    object_file[0x94] = '\x01';
  }
  else {
    object_file[0x94] = '\0';
  }
  *(const_char **)object_file = name;
  strcpy((char *)(object_file + 4),(char *)size);
  iVar2 = *(int *)object_file;
  *(undefined4 *)(object_file + 0x58) = *(undefined4 *)(in_t0_lo + 4);
  *(undefined4 *)(object_file + 0x4c) = in_t1_lo;
  *(uint32_t *)(object_file + 0x44) = flags;
  *(undefined4 *)(object_file + 0x50) = 1;
  *(undefined **)(object_file + 0x48) = in_t0_lo;
  *(undefined4 *)(object_file + 0x54) = 0;
  *(undefined4 *)(object_file + 0x5c) = 0;
  *(int *)(object_file + 0x60) = iVar2 + 4;
  *(undefined4 *)(object_file + 100) = 0;
  *(int *)(object_file + 0x90) = iVar2;
  *(undefined4 *)(object_file + 0x68) = 0;
  *(undefined4 *)(object_file + 0x6c) = 0;
  object_file[0x95] = '\0';
  sVar1 = *(short *)(iVar2 + 8);
  if (sVar1 == 4) {
    iVar5 = *(int *)(iVar2 + 0xc);
    *(int *)object_file = iVar2 + 0x10;
    *(int *)(object_file + 100) = iVar5;
    *(int *)(object_file + 0x60) = iVar2 + iVar5 + 0x14;
  }
  else {
    iVar5 = *(int *)(iVar2 + 4);
    *(int *)object_file = iVar2 + iVar5;
    iVar5 = flags - iVar5;
    if (sVar1 == 5) {
      iVar5 = (flags - *(int *)(iVar2 + 0x10)) + -0x50;
    }
    *(int *)(object_file + 100) = iVar5;
    heap_00 = *(kheapinfo **)(object_file + 0x48);
    psVar3 = *(s32 **)(object_file + 0x60);
    if ((int)psVar3 < (int)heap_00->base) {
      puVar4 = *(u8 **)object_file;
    }
    else {
      if ((int)psVar3 < (int)heap_00->top) {
        sVar1 = *(short *)(psVar3 + 1);
        object_file[0x95] = '\x01';
        if (sVar1 == 5) {
          src = (uint32_t *)(name + psVar3[2]);
          puVar4 = kmalloc(heap_00,psVar3[3] + 0x50,0x2000,"link-block");
          psVar3[2] = 0x50;
          memcpy(&DAT_002d2f48,name,0x50);
          ultimate_memcpy_G(puVar4 + 0x50,src,psVar3[3]);
          memcpy(puVar4,&DAT_002d2f48,0x50);
        }
        else {
          puVar4 = kmalloc(heap_00,*psVar3,0x2000,"link-block");
          src = *(uint32_t **)(object_file + 0x60) + -1;
          ultimate_memcpy_G(puVar4,src,**(uint32_t **)(object_file + 0x60));
        }
        *(u8 **)(object_file + 0x60) = puVar4 + 4;
        if ((int)src < *(int *)(*(int *)(object_file + 0x48) + 8)) {
          *(uint32_t **)(*(int *)(object_file + 0x48) + 8) = src;
        }
        goto LAB_0026f558;
      }
      puVar4 = *(u8 **)object_file;
    }
    if ((int)puVar4 < (int)heap_00->base) {
      uVar6 = *(uint *)(object_file + 0x4c);
      goto LAB_0026f55c;
    }
    if ((int)heap_00->top <= (int)puVar4) {
      uVar6 = *(uint *)(object_file + 0x4c);
      goto LAB_0026f55c;
    }
    if ((int)heap_00->current <= (int)puVar4) {
      uVar6 = *(uint *)(object_file + 0x4c);
      goto LAB_0026f55c;
    }
    heap_00->current = puVar4;
  }
LAB_0026f558:
  uVar6 = *(uint *)(object_file + 0x4c);
LAB_0026f55c:
  if ((((uVar6 & 0x10) != 0) && (MasterDebug != 0)) && (DiskBoot == 0)) {
    *(undefined4 *)(object_file + 0x5c) = 1;
  }
  return;
}

uint32_t jak3_work() {
  int iVar1;
  int iVar2;
  uint32_t uVar3;
  int in_a0_lo;
  int unaff_s7_lo;
  
  iVar2 = DebugSegment;
  if (*(int *)(in_a0_lo + 0x5c) != 0) {
    DebugSegment = unaff_s7_lo + 4;
  }
  iVar1 = *(int *)(in_a0_lo + 0x60);
  *(undefined4 *)(iVar1 + -4) = *(undefined4 *)(unaff_s7_lo + 0x1f);
  uVar3 = 0;
  if (*(short *)(iVar1 + 4) == 5) {
    uVar3 = jak3_work_opengoal();
  }
  DebugSegment = iVar2;
  return uVar3;
}

namespace jak3 {
void ultimate_memcpy(void* dst, void* src, uint32_t size);
}

uint32_t link_control::jak3_work_v5() {
  if (m_state == 0) {
    // here, we change length_to_get_to_link to an actual pointer to the link table.
    // since we need 32-bits, we'll store offset from g_ee_mem.
    u8* link_data = ((u8*)m_link_hdr) - 4 + m_link_hdr->length_to_get_to_link;
    m_link_hdr->length_to_get_to_link = link_data - g_ee_main_mem;

    m_n_segments = m_link_hdr->n_segments;

    // the link segments table is just at the start of the link data:
    m_link_segments_table = (SegmentInfoV5*)link_data;
    /*
    for (int i = 0; i < m_n_segments; i++) {
      printf(" %d: reloc %d, data %d, size %d, magic %d\n", i, m_link_segments_table[i].relocs,
             m_link_segments_table[i].data, m_link_segments_table[i].size,
             m_link_segments_table[i].magic);
    }
    */
    // for now, only supporting 1 segment
    ASSERT(m_n_segments == 1);

    // fixup the relocs/data offsets into addresses (again, offsets from g_ee_main_mem)
    // relocs is relative to this link data
    m_link_segments_table[0].relocs += (link_data - g_ee_main_mem);
    // data is relative to usual object_data
    m_link_segments_table[0].data += m_object_data.offset;
    ASSERT(m_link_segments_table[0].magic == 1);

    // see if there's even data
    if (m_link_segments_table[0].size == 0) {
      // no data.
      m_link_segments_table[0].data = 0;
    } else {
      // check if we need to move the main segment.
      if (!m_moved_link_block ||
          ((m_link_hdr->link_length + 0x50) <= m_link_hdr->length_to_get_to_code)) {
        // printf(" v5 linker allocating for main segment... (%d)\n", m_moved_link_block);
        auto old_data_offset = m_link_segments_table[0].data;  // 25
        auto new_data = kmalloc(m_heap, m_link_segments_table[0].size, 0, "main-segment");
        m_link_segments_table[0].data = new_data.offset;
        if (!new_data.offset) {
          MsgErr("dkernel: unable to malloc %d bytes for main-segment\n",
                 m_link_segments_table[0].size);
          return 1;
        }
        jak3::ultimate_memcpy(new_data.c(), old_data_offset + g_ee_main_mem,
                              m_link_segments_table[0].size);
      } else {
        m_heap->current = m_object_data + m_code_size;
        if (m_heap->top.offset <= m_heap->current.offset) {
          MsgErr("dkernel: heap overflow\n");
          return 1;
        }
      }
    }

    m_segment_process = 0;
    m_state = 1;
    m_object_data.offset = m_link_segments_table[0].data;

    Ptr<u8> base_ptr(m_link_segments_table[0].data);
    Ptr<u8> data_ptr = base_ptr - 4;
    Ptr<u8> link_ptr(m_link_segments_table[0].relocs);

    bool fixing = false;
    if (*link_ptr) {
      // we have pointers
      while (true) {
        while (true) {
          if (!fixing) {
            // seeking
            data_ptr.offset += 4 * (*link_ptr);
          } else {
            // fixing.
            for (uint32_t i = 0; i < *link_ptr; i++) {
              // uint32_t old_code = *(const uint32_t*)(&data.at(data_ptr));
              u32 old_code = *data_ptr.cast<u32>();
              if ((old_code >> 24) == 0) {
                // printf("modifying pointer at 0x%x (old 0x%x) : now ", data_ptr.offset,
                //      *data_ptr.cast<u32>());
                *data_ptr.cast<u32>() += base_ptr.offset;
                // printf("0x%x\n", *data_ptr.cast<u32>());
              } else {
                ASSERT_NOT_REACHED();
                /*
                f.stats.v3_split_pointers++;
                auto dest_seg = (old_code >> 8) & 0xf;
                auto lo_hi_offset = (old_code >> 12) & 0xf;
                ASSERT(lo_hi_offset);
                ASSERT(dest_seg < 3);
                auto offset_upper = old_code & 0xff;
                uint32_t low_code = *(const uint32_t*)(&data.at(data_ptr + 4 * lo_hi_offset));
                uint32_t offset = low_code & 0xffff;
                if (offset_upper) {
                  offset += (offset_upper << 16);
                }
                f.pointer_link_split_word(seg_id, data_ptr - base_ptr,
                                          data_ptr + 4 * lo_hi_offset - base_ptr, dest_seg, offset);
                */
              }
              data_ptr.offset += 4;
            }
          }

          if (*link_ptr != 0xff)
            break;
          link_ptr.offset++;
          if (*link_ptr == 0) {
            link_ptr.offset++;
            fixing = !fixing;
          }
        }

        link_ptr.offset++;
        fixing = !fixing;
        if (*link_ptr == 0)
          break;
      }
    }
    link_ptr.offset++;

    // symbol linking.
    if (*link_ptr) {
      auto sub_link_ptr = link_ptr;

      while (true) {
        auto reloc = *sub_link_ptr;
        auto next_link_ptr = sub_link_ptr + 1;
        link_ptr = next_link_ptr;

        if ((reloc & 0x80) == 0) {
          link_ptr = sub_link_ptr + 3;  //
          const char* sname = link_ptr.cast<char>().c();
          link_ptr.offset += strlen(sname) + 1;
          // printf("linking symbol %s\n", sname);
          auto goalObj = jak3::intern_from_c(-1, 0, sname);
          link_ptr = c_symlink2(m_object_data, goalObj.cast<u8>(), link_ptr);

        } else if ((reloc & 0x3f) == 0x3f) {
          ASSERT(false);  // todo, does this ever get hit?
        } else {
          int n_methods_base = reloc & 0x3f;
          int n_methods = n_methods_base * 4;
          if (n_methods_base) {
            n_methods += 3;
          }
          link_ptr.offset +=
              2;  // ghidra misses some aliasing here and would have you think this is +1!
          const char* sname = link_ptr.cast<char>().c();
          // printf("linking type %s\n", sname);
          link_ptr.offset += strlen(sname) + 1;
          auto goalObj = jak3::intern_type_from_c(-1, 0, sname, n_methods);
          link_ptr = c_symlink2(m_object_data, goalObj.cast<u8>(), link_ptr);
        }

        sub_link_ptr = link_ptr;
        if (!*sub_link_ptr)
          break;
      }
    }
    m_entry = m_object_data + 4;
    return 1;
  } else {
    ASSERT_NOT_REACHED();
  }
}

namespace {
/*!
 * Link a single relative offset (used for RIP)
 */
uint32_t cross_seg_dist_link_v3(Ptr<uint8_t> link,
                                ObjectFileHeader* ofh,
                                int current_seg,
                                int size) {
  // target seg, dist into mine, dist into target, patch loc in mine
  uint8_t target_seg = *link;
  ASSERT(target_seg < ofh->segment_count);

  uint32_t* link_data = (link + 1).cast<uint32_t>().c();
  int32_t mine = link_data[0] + ofh->code_infos[current_seg].offset;
  int32_t tgt = link_data[1] + ofh->code_infos[target_seg].offset;
  int32_t diff = tgt - mine;
  uint32_t offset_of_patch = link_data[2] + ofh->code_infos[current_seg].offset;

  // second debug segment case added for jak 2.
  if (!ofh->code_infos[target_seg].offset || (!DebugSegment && target_seg == DEBUG_SEGMENT)) {
    // we want to address GOAL 0. In the case where this is a rip-relative load or store, this
    // will crash, which is what we want. If it's an lea and just getting an address, this will get
    // us a nullptr. If you do a method-set! with a null pointer it does nothing, so it's safe to
    // method-set! to things that are in unloaded segments and it'll just keep the old method.
    diff = -mine;
  }
  // printf("link object in seg %d diff %d at %d (%d + %d)\n", target_seg, diff, offset_of_patch,
  // link_data[2], ofh->code_infos[current_seg].offset);

  // both 32-bit and 64-bit pointer links are supported, though 64-bit ones are no longer in use.
  // we still support it just in case we want to run ancient code.
  if (size == 4) {
    *Ptr<int32_t>(offset_of_patch).c() = diff;
  } else if (size == 8) {
    *Ptr<int64_t>(offset_of_patch).c() = diff;
  } else {
    ASSERT(false);
  }

  return 1 + 3 * 4;
}

uint32_t ptr_link_v3(Ptr<u8> link, ObjectFileHeader* ofh, int current_seg) {
  auto* link_data = link.cast<u32>().c();
  u32 patch_loc = link_data[0] + ofh->code_infos[current_seg].offset;
  u32 patch_value = link_data[1] + ofh->code_infos[current_seg].offset;
  *Ptr<u32>(patch_loc).c() = patch_value;
  return 8;
}

/*!
 * Link type pointers for a single type in "v3 equivalent" link data
 * Returns a pointer to the link table data after the typelinking data.
 */
uint32_t typelink_v3(Ptr<uint8_t> link, Ptr<uint8_t> data) {
  // get the name of the type
  uint32_t seek = 0;
  char sym_name[256];
  while (link.c()[seek]) {
    sym_name[seek] = link.c()[seek];
    seek++;
    ASSERT(seek < 256);
  }
  sym_name[seek] = 0;
  seek++;

  // determine the number of methods
  uint32_t method_count = link.c()[seek++];
  // jak2 special
  method_count *= 4;
  if (method_count) {
    method_count += 3;
  }

  // intern the GOAL type, creating the vtable if it doesn't exist.
  auto type_ptr = jak3::intern_type_from_c(-1, 0, sym_name, method_count);

  // prepare to read the locations of the type pointers
  Ptr<uint32_t> offsets = link.cast<uint32_t>() + seek;
  uint32_t offset_count = *offsets;
  offsets = offsets + 4;
  seek += 4;

  // write the type pointers into memory
  for (uint32_t i = 0; i < offset_count; i++) {
    *(data + offsets.c()[i]).cast<int32_t>() = type_ptr.offset;
    seek += 4;
  }

  return seek;
}
/*!
 * Link symbols (both offsets and pointers) in "v3 equivalent" link data.
 * Returns a pointer to the link table data after the linking data for this symbol.
 */
uint32_t symlink_v3(Ptr<uint8_t> link, Ptr<uint8_t> data) {
  // get the symbol name
  uint32_t seek = 0;
  char sym_name[256];
  while (link.c()[seek]) {
    sym_name[seek] = link.c()[seek];
    seek++;
    ASSERT(seek < 256);
  }
  sym_name[seek] = 0;
  seek++;

  // intern
  auto sym = jak3::intern_from_c(-1, 0, sym_name);
  int32_t sym_offset = sym.cast<u32>() - s7;
  uint32_t sym_addr = sym.cast<u32>().offset;

  // prepare to read locations of symbol links
  Ptr<uint32_t> offsets = link.cast<uint32_t>() + seek;
  uint32_t offset_count = *offsets;
  offsets = offsets + 4;
  seek += 4;

  for (uint32_t i = 0; i < offset_count; i++) {
    uint32_t offset = offsets.c()[i];
    seek += 4;
    auto data_ptr = (data + offset).cast<int32_t>();

    if (*data_ptr == -1) {
      // a "-1" indicates that we should store the address.
      *(data + offset).cast<int32_t>() = sym_addr;
    } else if (*(data_ptr.cast<u32>()) == LINK_SYM_NO_OFFSET_FLAG) {
      *(data + offset).cast<int32_t>() = sym_offset - 1;
    } else {
      // otherwise store the offset to st.
      *(data + offset).cast<int32_t>() = sym_offset;
    }
  }

  return seek;
}
}  // namespace

uint32_t jak3_work_opengoal() {
  byte bVar1;
  byte bVar2;
  int *piVar3;
  int iVar4;
  uint *puVar5;
  short sVar6;
  int iVar7;
  u8 *puVar8;
  Type *pTVar9;
  code *pcVar10;
  size_t sVar11;
  int *in_a0_lo;
  kheapinfo *heap;
  void *dst;
  char *pcVar12;
  void *src;
  undefined4 uVar13;
  uint uVar14;
  uint32_t size;
  u64 methods;
  uint *puVar15;
  uint uVar16;
  int *piVar17;
  byte *pbVar18;
  short *name;
  uint uVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  
  iVar7 = (*(code *)PTR_read_clock_code_002836d0)();
  if (in_a0_lo[0x1a] == 0) {
    piVar3 = (int *)in_a0_lo[0x18];
    bVar1 = *(byte *)(piVar3 + 4);
    iVar20 = (int)piVar3 + piVar3[2] + -4;
    in_a0_lo[0x1c] = (uint)bVar1;
    piVar3[2] = iVar20;
    iVar22 = bVar1 - 1;
    in_a0_lo[0x23] = iVar20;
LAB_0026f70c:
    do {
      iVar20 = iVar22 * 0x10;
      if (iVar22 < 0) {
        in_a0_lo[0x1b] = 0;
        in_a0_lo[0x1a] = 1;
        iVar20 = (*(code *)PTR_read_clock_code_002836d0)();
        if (200000 < (uint)(iVar20 - iVar7)) {
          return 0;
        }
        goto LAB_0026f94c;
      }
      iVar21 = in_a0_lo[0x23];
      iVar4 = *in_a0_lo;
      piVar17 = (int *)(iVar20 + iVar21);
      *piVar17 = iVar21 + *piVar17;
      piVar17[1] = iVar4 + piVar17[1];
      if (iVar22 == 1) {
        iVar20 = iVar21 + 0x10;
        if (DebugSegment == 0) {
          *(undefined4 *)(iVar21 + 0x18) = 0;
          *(undefined4 *)(iVar21 + 0x14) = 0;
        }
        else {
          if (*(int *)(iVar21 + 0x18) != 0) {
            src = *(void **)(iVar21 + 0x14);
            puVar8 = kmalloc(kdebugheap,*(int *)(iVar21 + 0x18),0,"debug-segment");
            iVar20 = in_a0_lo[0x23];
            *(u8 **)(iVar21 + 0x14) = puVar8;
            dst = *(void **)(iVar20 + 0x14);
            if (dst == (void *)0x0) {
              uVar13 = *(undefined4 *)(iVar20 + 0x18);
              pcVar12 = "dkernel: unable to malloc %d bytes for debug-segment~%";
              goto LAB_0026f838;
            }
            size = *(uint32_t *)(iVar20 + 0x18);
            goto LAB_0026f81c;
          }
LAB_0026f8a4:
          *(undefined4 *)(iVar20 + 4) = 0;
        }
        goto LAB_0026f754;
      }
      if (1 < iVar22) {
        if (iVar22 == 2) {
          iVar20 = iVar21 + 0x20;
          if (*(int *)(iVar21 + 0x28) == 0) goto LAB_0026f8a4;
          src = *(void **)(iVar21 + 0x24);
          puVar8 = kmalloc((kheapinfo *)in_a0_lo[0x12],*(int *)(iVar21 + 0x28),0x2000,
                           "top-level-segment");
          iVar20 = in_a0_lo[0x23];
          *(u8 **)(iVar21 + 0x24) = puVar8;
          dst = *(void **)(iVar20 + 0x24);
          if (dst == (void *)0x0) {
            uVar13 = *(undefined4 *)(iVar20 + 0x28);
            pcVar12 = "dkernel: unable to malloc %d bytes for top-level-segment~%";
            goto LAB_0026f838;
          }
          size = *(uint32_t *)(iVar20 + 0x28);
LAB_0026f81c:
          iVar22 = iVar22 + -1;
          ultimate_memcpy_G(dst,src,size);
        }
        else {
          iVar22 = iVar22 + -1;
        }
        goto LAB_0026f70c;
      }
      if (iVar22 != 0) {
LAB_0026f754:
        iVar22 = iVar22 + -1;
        goto LAB_0026f70c;
      }
      if (*(int *)(iVar21 + 8) == 0) {
        *(undefined4 *)(iVar21 + 4) = 0;
        goto LAB_0026f754;
      }
      iVar21 = iVar20 + iVar21;
      if (*(char *)((int)in_a0_lo + 0x95) == '\0') {
        heap = (kheapinfo *)in_a0_lo[0x12];
LAB_0026f7e8:
        src = *(void **)(iVar21 + 4);
        puVar8 = kmalloc(heap,*(s32 *)(iVar21 + 8),0,"main-segment");
        iVar4 = in_a0_lo[0x23];
        *(u8 **)(iVar21 + 4) = puVar8;
        iVar20 = iVar20 + iVar4;
        dst = *(void **)(iVar20 + 4);
        if (dst == (void *)0x0) {
          uVar13 = *(undefined4 *)(iVar20 + 8);
          pcVar12 = "dkernel: unable to malloc %d bytes for main-segment~%";
LAB_0026f838:
          MsgErr(pcVar12,uVar13);
          return 1;
        }
        size = *(uint32_t *)(iVar20 + 8);
        goto LAB_0026f81c;
      }
      if (piVar3[3] + 0x50 <= *piVar3) {
        heap = (kheapinfo *)in_a0_lo[0x12];
        goto LAB_0026f7e8;
      }
      iVar20 = in_a0_lo[0x12];
      uVar19 = iVar4 + in_a0_lo[0x19];
      *(uint *)(iVar20 + 8) = uVar19;
      iVar22 = -1;
    } while (uVar19 < *(uint *)(iVar20 + 4));
    MsgErr("dkernel: heap overflow~%");
  }
  else {
LAB_0026f94c:
    iVar20 = in_a0_lo[0x1a];
    if ((iVar20 < in_a0_lo[0x1c] + 1) && (in_a0_lo[0x1b] == 0)) {
      iVar22 = in_a0_lo[0x23] + iVar20 * 0x10;
      if ((*(int *)(iVar22 + -0xc) != 0) && (*(int *)(iVar22 + -8) != 0)) {
        iVar21 = *(int *)(iVar22 + -0x10);
        in_a0_lo[0x1b] = 1;
        in_a0_lo[0x1f] = iVar21;
        *(undefined *)(in_a0_lo + 0x22) = 0;
        iVar22 = *(int *)(iVar22 + -0xc);
        *in_a0_lo = iVar22;
        in_a0_lo[0x21] = iVar22 + -4;
        in_a0_lo[0x20] = iVar22;
        goto LAB_0026f9c0;
      }
      in_a0_lo[0x1b] = 0;
      in_a0_lo[0x1a] = iVar20 + 1;
      goto LAB_0026f94c;
    }
LAB_0026f9c0:
    if (iVar20 < in_a0_lo[0x1c] + 1) {
      iVar20 = in_a0_lo[0x1b];
      if (iVar20 == 1) {
        iVar20 = 0x400;
        if (*(char *)in_a0_lo[0x1f] != '\0') {
LAB_0026f9e8:
          do {
            bVar1 = *(byte *)(in_a0_lo + 0x22);
            while( true ) {
              iVar22 = 0;
              if (bVar1 == 0) {
                in_a0_lo[0x21] = in_a0_lo[0x21] + (uint)*(byte *)in_a0_lo[0x1f] * 4;
                pcVar12 = (char *)in_a0_lo[0x1f];
              }
              else {
                pbVar18 = (byte *)in_a0_lo[0x1f];
                bVar2 = *pbVar18;
                while (bVar2 != 0) {
                  puVar5 = (uint *)in_a0_lo[0x21];
                  uVar19 = *puVar5;
                  uVar14 = uVar19 >> 8 & 0xf;
                  puVar15 = (uint *)((uVar19 >> 10 & 0x3c) + (int)puVar5);
                  if (uVar19 >> 0x18 == 0) {
                    *puVar5 = uVar19 + in_a0_lo[0x20];
                  }
                  else {
                    uVar16 = *(int *)(uVar14 * 0x10 + in_a0_lo[0x23] + 4) +
                             ((uVar19 & 0xff) << 0x10 | (uint)*(ushort *)puVar15);
                    if ((DebugSegment == 0) && (uVar14 == 1)) {
                      uVar16 = 0;
                    }
                    *puVar5 = uVar19 & 0xffff0000 | uVar16 >> 0x10;
                    *puVar15 = *puVar15 & 0xffff0000 | uVar16 & 0xffff;
                  }
                  iVar22 = iVar22 + 1;
                  in_a0_lo[0x21] = (int)(puVar5 + 1);
                  bVar2 = iVar22 < (int)(uint)*pbVar18;
                }
                pcVar12 = (char *)in_a0_lo[0x1f];
              }
              if (*pcVar12 == -1) {
                in_a0_lo[0x1f] = (int)(pcVar12 + 1);
                goto LAB_0026f9e8;
              }
              in_a0_lo[0x1f] = (int)(pcVar12 + 1);
              *(byte *)(in_a0_lo + 0x22) = bVar1 ^ 1;
              iVar20 = iVar20 + -1;
              if (pcVar12[1] == '\0') goto LAB_0026fb20;
              if (iVar20 == 0) break;
              bVar1 = *(byte *)(in_a0_lo + 0x22);
            }
            iVar22 = (*(code *)PTR_read_clock_code_002836d0)();
            iVar20 = 0x400;
            if (200000 < (uint)(iVar22 - iVar7)) {
              return 0;
            }
          } while( true );
        }
LAB_0026fb20:
        in_a0_lo[0x1f] = in_a0_lo[0x1f] + 1;
        in_a0_lo[0x1b] = in_a0_lo[0x1b] + 1;
        iVar20 = in_a0_lo[0x1b];
      }
      if (iVar20 != 2) goto LAB_0026fcac;
      pbVar18 = (byte *)in_a0_lo[0x1f];
      uVar19 = *(uint *)(in_a0_lo[0x23] + in_a0_lo[0x1a] * 0x10 + -4);
      while( true ) {
        bVar1 = *pbVar18;
        uVar14 = (uint)bVar1;
        if (uVar14 == 0) break;
        in_a0_lo[0x1f] = (int)(pbVar18 + 1);
        if ((bVar1 & 0x80) == 0) {
          sVar6 = *(short *)(pbVar18 + 1);
          in_a0_lo[0x1f] = (int)(pbVar18 + 3);
          pTVar9 = (Type *)intern_from_c((int)sVar6,uVar14,(const_char *)(pbVar18 + 3));
          pcVar12 = (char *)in_a0_lo[0x1f];
        }
        else {
          iVar20 = (uVar14 & 0x3f) * 4;
          if ((uVar14 & 0x3f) == 0x3f) {
            bVar1 = pbVar18[1];
            in_a0_lo[0x1f] = (int)(pbVar18 + 2);
            methods = (long)(int)((uint)bVar1 * 4 + 3);
          }
          else {
            methods = (long)iVar20;
            if ((long)iVar20 != 0) {
              methods = (long)(iVar20 + 3);
            }
          }
          name = (short *)in_a0_lo[0x1f] + 1;
          sVar6 = *(short *)in_a0_lo[0x1f];
          in_a0_lo[0x1f] = (int)name;
          pTVar9 = intern_type_from_c((int)sVar6,uVar14,(const_char *)name,methods);
          pcVar12 = (char *)in_a0_lo[0x1f];
        }
        sVar11 = strlen(pcVar12);
        in_a0_lo[0x1f] = in_a0_lo[0x1f] + (int)sVar11 + 1;
        if ((uVar19 & 1) == 0) {
          iVar20 = *in_a0_lo;
          pcVar10 = (code *)symlink3_G;
        }
        else {
          iVar20 = *in_a0_lo;
          pcVar10 = (code *)symlink2_G;
        }
        iVar20 = (*pcVar10)(iVar20,pTVar9);
        in_a0_lo[0x1f] = iVar20;
        iVar20 = (*(code *)PTR_read_clock_code_002836d0)();
        if (200000 < (uint)(iVar20 - iVar7)) {
          return 0;
        }
        pbVar18 = (byte *)in_a0_lo[0x1f];
      }
      in_a0_lo[0x1b] = 0;
      in_a0_lo[0x1a] = in_a0_lo[0x1a] + 1;
      in_a0_lo[0x15] = *in_a0_lo + 4;
      goto LAB_0026f94c;
    }
LAB_0026fcac:
    update_goal_fns();
  }
  return 1;
}

void jak3_finish(bool jump_from_c_to_goal) {
  short sVar1;
  int iVar2;
  int iVar3;
  code *pcVar4;
  char *a2;
  int iVar5;
  int iVar6;
  int unaff_s7_lo;
  int iVar7;
  
  FlushCache(0);
  FlushCache(2);
  iVar3 = DebugSegment;
  if (*(int *)(jump_from_c_to_goal + 0x5c) != 0) {
    DebugSegment = unaff_s7_lo + 4;
  }
  if ((*(uint *)(jump_from_c_to_goal + 0x4c) & 0x20) != 0) {
    FastLink = 1;
  }
  iVar5 = (int)jump_from_c_to_goal;
  iVar2 = *(int *)(iVar5 + 0x60);
  sVar1 = *(short *)(iVar2 + 4);
  *EnableMethodSet = *EnableMethodSet + *(int *)(iVar5 + 0x5c);
  iVar6 = (int)jump_from_c_to_goal;
  iVar7 = (int)jump_from_c_to_goal;
  if (sVar1 == 5) {
    pcVar4 = *(code **)(iVar5 + 0x54);
    if (pcVar4 != (code *)0x0) {
      if ((*(int *)(pcVar4 + -4) == *(int *)(unaff_s7_lo + 7)) &&
         ((*(uint *)(iVar5 + 0x4c) & 5) != 0)) {
        if ((*(uint *)(iVar5 + 0x4c) & 4) == 0) {
          pcVar4 = *(code **)(unaff_s7_lo + 0x93);
        }
        else {
          (*pcVar4)();
          pcVar4 = *(code **)(unaff_s7_lo + 0x93);
        }
        (*pcVar4)();
        if ((*(uint *)(iVar7 + 0x4c) & 1) != 0) {
          output_segment_load((const_char *)(iVar2 + 0x11),*(void **)(iVar2 + 8),
                              *(uint *)(iVar7 + 0x4c));
        }
      }
      else if ((pcVar4 != (code *)0x0) && ((*(uint *)(iVar7 + 0x4c) & 4) != 0)) {
        a2 = basename_goal((char *)(iVar6 + 4));
        call_method_of_type_arg2
                  (*(u32 *)(iVar6 + 0x54),*(Type **)(*(u32 *)(iVar6 + 0x54) - 4),7,
                   *(u32 *)(iVar6 + 0x48),(u32)a2);
      }
    }
  }
  else {
    MsgErr("dkernel: FATAL ERROR: unknown goal file version %d~%");
  }
  iVar2 = *(int *)(iVar6 + 0x48);
  FastLink = 0;
  *EnableMethodSet = *EnableMethodSet - *(int *)(iVar6 + 0x5c);
  DebugSegment = iVar3;
  *(undefined4 *)(iVar2 + 4) = *(undefined4 *)(iVar6 + 0x58);
  *(undefined4 *)(iVar7 + 0x50) = 0;
  if (*(char *)(iVar7 + 0x94) != '\0') {
    kmemclose();
  }
  return;
}


namespace jak3 {

uint8_t * link_and_exec(uint8_t *data,const_char *name,int32_t size,kheapinfo *heap,uint32_t flags, bool jump_from_c_to_goal) {
  uint32_t uVar1;
  long lVar2;
  kheapinfo in_stack_ffffff30;
  uint8_t *local_7c;
  
  lVar2 = link_busy();
  if (lVar2 != 0) {
    printf("-------------> saved link is busy\n");
  }
  jak3_begin(&stack0xffffff30,(const_char *)data,(int32_t)name,in_stack_ffffff30,size);
  do {
    uVar1 = jak3_work();
  } while (uVar1 == 0);
  jak3_finish(SUB41(&stack0xffffff30,0));
  return local_7c;
}

u64 link_and_exec_wrapper(u64* args) {
  return link_and_exec(Ptr<u8>(args[0]), Ptr<char>(args[1]).c(), args[2], Ptr<kheapinfo>(args[3]),
                       args[4], false)
      .offset;
}

u32 link_busy() {
  return saved_link_control.m_busy;
}
void link_reset() {
  saved_link_control.m_busy = 0;
}
uint64_t link_begin(u64 *args) {
  kheapinfo heap;
  uint32_t uVar1;
  int32_t in_a1_lo;
  uint32_t in_a2_lo;
  undefined8 unaff_s0;
  undefined8 unaff_retaddr;
  
  heap._8_8_ = unaff_retaddr;
  heap._0_8_ = unaff_s0;
  jak3_begin(&DAT_002d2f98,(const_char *)args,in_a1_lo,heap,in_a2_lo);
  uVar1 = jak3_work();
  if (uVar1 != 0) {
    jak3_finish(true);
  }
  return (ulong)(uVar1 != 0);
}
uint64_t link_resume() {
  uint32_t uVar1;
  
  uVar1 = jak3_work();
  if (uVar1 != 0) {
    jak3_finish(true);
  }
  return (ulong)(uVar1 != 0);
}

// Note: update_goal_fns changed to skip the hashtable lookup since symlink2/symlink3 are now fixed
// symbols.

/*!
 * The ULTIMATE MEMORY COPY
 * IT IS VERY FAST
 * but it may use the scratchpad.  It is implemented in GOAL, and falls back to normal C memcpy
 * if GOAL isn't loaded, or if the alignment isn't good enough.
 */
void ultimate_memcpy_G(void *dst,void *src,uint32_t size) {
  code *pcVar1;
  int iVar2;
  ulong __n;
  int unaff_s7_lo;
  
  __n = (ulong)(int)size;
  if ((src < dst) && ((int)((int)dst - size) < (int)src)) {
    for (iVar2 = size - 1; iVar2 != -1; iVar2 = iVar2 + -1) {
      *(undefined *)((int)dst + iVar2) = *(undefined *)((int)src + iVar2);
    }
  }
  else {
    if ((((((uint)src & 0xf) != 0) || (((uint)dst & 0xf) != 0)) || ((__n & 0xf) != 0)) ||
       ((__n < 0x1000 ||
        ((pcVar1 = DAT_002836f8, DAT_002836f8 == (code *)0x0 &&
         (pcVar1 = *(code **)(unaff_s7_lo + 0x283), *(code **)(unaff_s7_lo + 0x283) == (code *)0x0))
        )))) {
      memcpy(dst,src,__n);
      return;
    }
    DAT_002836f8 = pcVar1;
    (*DAT_002836f8)();
  }
  return;
}

}  // namespace jak3

#define LINK_V2_STATE_INIT_COPY 0
#define LINK_V2_STATE_OFFSETS 1
#define LINK_V2_STATE_SYMBOL_TABLE 2
#define OBJ_V2_CLOSE_ENOUGH 0x90
#define OBJ_V2_MAX_TRANSFER 0x80000

uint32_t link_control::jak3_work_v2_v4() {
  //  u32 startCycle = kernel.read_clock(); todo

  if (m_state == LINK_V2_STATE_INIT_COPY) {  // initialization and copying to heap
    // we move the data segment to eliminate gaps
    // very small gaps can be tolerated, as it is not worth the time penalty to move large objects
    // many bytes. if this requires copying a large amount of data, we will do it in smaller chunks,
    // allowing the copy to be spread over multiple game frames

    // state initialization
    if (m_segment_process == 0) {
      m_heap_gap =
          m_object_data - m_heap->current;  // distance between end of heap and start of object
    }

    if (m_heap_gap <
        OBJ_V2_CLOSE_ENOUGH) {  // close enough, don't relocate the object, just expand the heap
      if (link_debug_printfs) {
        printf("[work_v2] close enough, not moving\n");
      }
      m_heap->current = m_object_data + m_code_size;
      if (m_heap->top.offset <= m_heap->current.offset) {
        MsgErr("dkernel: heap overflow\n");  // game has ~% instead of \n :P
        return 1;
      }

      // added in jak 2, move the link block to the top of the heap so we can allocate on
      // the level heap during linking without overwriting link data. this is used for level types
      u32 link_block_size = *m_link_block_ptr.cast<u32>();
      auto new_link_block = kmalloc(m_heap, link_block_size, KMALLOC_TOP, "link-block");
      memmove(new_link_block.c(), m_link_block_ptr.c() - 4, link_block_size);
      m_link_block_ptr = Ptr<uint8_t>(new_link_block.offset + 4);  // basic offset

    } else {  // not close enough, need to move the object
      // on the first run of this state...
      if (m_segment_process == 0) {
        m_original_object_location = m_object_data;
        // allocate on heap, will have no gap
        m_object_data = kmalloc(m_heap, m_code_size, 0, "data-segment");
        if (link_debug_printfs) {
          printf("[work_v2] moving from 0x%x to 0x%x\n", m_original_object_location.offset,
                 m_object_data.offset);
        }
        if (!m_object_data.offset) {
          MsgErr("dkernel: unable to malloc %d bytes for data-segment\n", m_code_size);
          return 1;
        }
      }

      // the actual copy
      Ptr<u8> source = m_original_object_location + m_segment_process;
      u32 size = m_code_size - m_segment_process;

      if (size > OBJ_V2_MAX_TRANSFER) {  // around .5 MB
        jak3::ultimate_memcpy((m_object_data + m_segment_process).c(), source.c(),
                              OBJ_V2_MAX_TRANSFER);
        m_segment_process += OBJ_V2_MAX_TRANSFER;
        return 0;  // return, don't want to take too long.
      }

      // if we have bytes to copy, but they are less than the max transfer, do it in one shot!
      if (size) {
        jak3::ultimate_memcpy((m_object_data + m_segment_process).c(), source.c(), size);
        if (m_segment_process > 0) {  // if we did a previous copy, we return now....
          m_state = LINK_V2_STATE_OFFSETS;
          m_segment_process = 0;
          return 0;
        }
      }
    }

    // otherwise go straight into the next state.
    m_state = LINK_V2_STATE_OFFSETS;
    m_segment_process = 0;
  }

  // init offset phase
  if (m_state == LINK_V2_STATE_OFFSETS && m_segment_process == 0) {
    m_reloc_ptr = m_link_block_ptr + 8;  // seek to link table
    if (*m_reloc_ptr == 0) {             // do we have pointer links to do?
      m_reloc_ptr.offset++;              // if not, seek past the \0, and go to next state
      m_state = LINK_V2_STATE_SYMBOL_TABLE;
      m_segment_process = 0;
    } else {
      m_base_ptr = m_object_data;  // base address for offsetting.
      m_loc_ptr = m_object_data;   // pointer which seeks thru the code
      m_table_toggle = 0;          // are we seeking or fixing?
      m_segment_process = 1;       // we've done first time setup
    }
  }

  if (m_state == LINK_V2_STATE_OFFSETS) {  // pointer fixup
    // this state reads through a table. Values alternate between "seek amount" and "number of
    // consecutive 4-byte
    //  words to fix up".  The counts are encoded using a variable length encoding scheme.  They use
    //  a very stupid
    // method of encoding values which requires O(n) bytes to store the value n.

    // to avoid dropping a frame, we check every 0x400 relocations to see if 0.5 milliseconds have
    // elapsed.
    u32 relocCounter = 0x400;
    while (true) {    // loop over entire table
      while (true) {  // loop over current mode

        // read and seek table
        u8 count = *m_reloc_ptr;
        m_reloc_ptr.offset++;

        if (!m_table_toggle) {  // seek mode
          m_loc_ptr.offset +=
              4 *
              count;  // perform seek (MIPS instructions are 4 bytes, so we >> 2 the seek amount)
        } else {      // offset mode
          for (u32 i = 0; i < count; i++) {
            if (m_loc_ptr.offset % 4) {
              ASSERT(false);
            }
            u32 code = *(m_loc_ptr.cast<u32>());
            code += m_base_ptr.offset;
            *(m_loc_ptr.cast<u32>()) = code;
            m_loc_ptr.offset += 4;
          }
        }

        if (count != 0xff) {
          break;
        }

        if (*m_reloc_ptr == 0) {
          m_reloc_ptr.offset++;
          m_table_toggle = m_table_toggle ^ 1;
        }
      }

      // reached the end of the tableToggle mode
      m_table_toggle = m_table_toggle ^ 1;
      if (*m_reloc_ptr == 0) {
        break;  // end of the state
      }
      relocCounter--;
      if (relocCounter == 0) {
        //        u32 clock_value = kernel.read_clock();
        //        if(clock_value - startCycle > 150000) { // 0.5 milliseconds
        //          return 0;
        //        }
        relocCounter = 0x400;
      }
    }
    m_reloc_ptr.offset++;
    m_state = 2;
    m_segment_process = 0;
  }

  if (m_state == 2) {  // GOAL object fixup
    if (*m_reloc_ptr == 0) {
      m_state = 3;
      m_segment_process = 0;
    } else {
      while (true) {
        u32 relocation = *m_reloc_ptr;
        m_reloc_ptr.offset++;
        Ptr<u8> goalObj;
        char* name;
        if ((relocation & 0x80) == 0) {
          // symbol!
          if (relocation > 9) {
            m_reloc_ptr.offset--;  // no idea what this is.
          }
          name = m_reloc_ptr.cast<char>().c();
          if (link_debug_printfs) {
            printf("[work_v2] symlink: %s\n", name);
          }
          goalObj = jak3::intern_from_c(-1, 0, name).cast<u8>();
        } else {
          // type!
          u8 nMethods = relocation & 0x7f;
          if (nMethods == 0) {
            nMethods = 1;
          }
          name = m_reloc_ptr.cast<char>().c();
          if (link_debug_printfs) {
            printf("[work_v2] symlink -type: %s\n", name);
          }
          goalObj = jak3::intern_type_from_c(-1, 0, name, nMethods).cast<u8>();
        }
        m_reloc_ptr.offset += strlen(name) + 1;
        // DECOMPILER->hookStartSymlinkV3(_state - 1, _objectData, std::string(name));
        m_reloc_ptr = c_symlink2(m_object_data, goalObj, m_reloc_ptr);
        // DECOMPILER->hookFinishSymlinkV3();
        if (*m_reloc_ptr == 0) {
          break;  // done
        }
        //        u32 currentCycle = kernel.read_clock();
        //        if(currentCycle - startCycle > 150000) {
        //          return 0;
        //        }
      }
      m_state = 3;
      m_segment_process = 0;
    }
  }
  m_entry = m_object_data + 4;
  return 1;
}
