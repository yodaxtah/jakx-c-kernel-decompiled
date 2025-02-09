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

void jak3_begin(link_control* this, uint8_t* object_file,
                const char* name,
                int32_t size,
                kheapinfo* heap,
                uint32_t flags) {
  if (heap == &kglobalheapinfo) {
    kmemopen_from_c(&kglobalheapinfo, name);
    this->m_on_global_heap = true;
  }
  else {
    this->m_on_global_heap = false;
  }
  this->m_object_data = object_file;
  strcpy(this->m_object_name, name);
  this->m_object_size = size;
  LinkHeaderV5 *l_hdr = (LinkHeaderV5 *)this->m_object_data;
  this->m_flags = flags;
  uint16_t version = l_hdr->core.version;
  this->m_heap_top = heap->top;
  // TODO: where is unk_init1?
  this->m_busy = 1;
  this->m_heap = heap;
  this->m_entry = (uint8_t *)0x0;
  this->m_keep_debug = 0;
  this->m_link_hdr = &l_hdr->core;
  this->m_code_size = 0;
  this->m_ptr2 = (undefined *)l_hdr;
  this->m_state = 0;
  this->m_segment_process = 0;
  this->m_moved_link_block = false;
  if (version == 4) {
    uint32_t size___ = l_hdr->core.length_to_get_to_link;
    this->m_object_data = (uint8_t *)&l_hdr->core.link_length;
    this->m_code_size = size___;
    this->m_link_hdr = (LinkHeaderV5Core *)(l_hdr->core.name + (size___ - 1));
  } else {
    uint32_t size___ = l_hdr->core.length_to_get_to_code;
    this->m_object_data = (uint8_t *)(l_hdr->core.name + (size___ - 0x15));
    size___ = size - size___;
    if (version == 5) {
      size___ = (size - l_hdr->core.link_length) - 0x50;
    } else {
      ;
    }
    this->m_code_size = size___;
    if ((int)this->m_link_hdr < (int)m_heap->base || (int)this->m_link_hdr >= (int)m_heap->top) {
      if ((int)m_heap->base <= (int)this->m_object_data &&
          (int)this->m_object_data < (int)m_heap->top &&
          (int)this->m_object_data < (int)m_heap->current) {
        m_heap->current = this->m_object_data;
      }
    } else {
      this->m_moved_link_block = true;
      LinkHeaderV5* new_link_block_mem;
      char* old_link_block_G;

      if (m_link_hdr->version == 5) {
        old_link_block_G = (char *)(object_file + m_link_hdr->length_to_get_to_link);

        new_link_block_mem = (LinkHeaderV5 *)kmalloc(this->m_heap, m_link_hdr->link_length + 0x50,
                                                      0x2000, "link-block");

        m_link_hdr->length_to_get_to_link = 0x50;

        memcpy(new_link_block_mem_temp, object_file, 0x50);
        ultimate_memcpy_G(new_link_block_mem + 1, old_link_block_G, m_link_hdr->link_length);
        memcpy(new_link_block_mem, new_link_block_mem_temp, 0x50);
      } else {
        new_link_block_mem = (LinkHeaderV5 *)kmalloc(this->m_heap, m_link_hdr->length_to_get_to_code,
                                                      0x2000, "link-block");
        old_link_block_G = this->m_link_hdr[-1].name + 0x37;
        ultimate_memcpy_G(new_link_block_mem, old_link_block_G,
                          this->m_link_hdr->length_to_get_to_code);
      }

      this->m_link_hdr = &new_link_block_mem->core;

      if ((int)old_link_block_G < (int)this->m_heap->current) {
        this->m_heap->current = (u8 *)old_link_block_G;
      }
    }
  }
  if ((this->m_flags & 0x10) != 0 && MasterDebug != 0 && DiskBoot == 0) {
    this->m_keep_debug = 1;
  }
}

uint32_t jak3_work(link_control* this) {
  int old_debug_segment = DebugSegment;
  if (this->m_keep_debug != 0) {
    DebugSegment = unaff_s7_lo + 4;
  }

  uint32_t rv;

  int unaff_s7_lo;
  uint16_t m_version = this->m_link_hdr->version;
  *(undefined4 *)(this->m_link_hdr[-1].name + 0x37) = *(undefined4 *)(unaff_s7_lo + 0x1f);
  if (m_version == 5) {
    rv = jak3_work_opengoal(this);
  } else {
    rv = 0;
  }

  DebugSegment = old_debug_segment;
  return rv;
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

uint32_t jak3_work_opengoal(link_control* this) {
  int startCycle = (*(code *)kernel.read_clock_G)();
  ObjectFileHeader* ofh = (ObjectFileHeader *)this->m_link_block_ptr;
  if (this->m_state == 0) {
    uint32_t prev_length = this->m_link_hdr->length_to_get_to_link;
    this->m_code_start = (uint8_t *)(uint)this->m_link_hdr->n_segments;
    this->m_link_hdr->length_to_get_to_link = (uint32_t)(this->m_link_hdr->name + (prev_length - 0x15));
    this->m_link_block_ptr = (uint8_t *)(this->m_link_hdr->name + (prev_length - 0x15));
LAB_0026f70c_for_loop:
    for (s32 seg_id = (s32)(uint8_t *)(uint)m_link_hdr->n_segments + -1; seg_id >= 0; seg_id -= 1) {
      (&ofh->code_infos[seg_id - 1].unknown_0xc)[0] += ((int)ofh->code_infos - 4);
      (&ofh->code_infos[seg_id - 1].unknown_0xc)[1] += this->m_object_data;

      if (seg_id == 1) {
        if (DebugSegment == 0) {
          ofh->code_infos[seg_id].offset = 0;
          ofh->code_infos[seg_id].size = 0;
        } else {
          if (ofh->code_infos[seg_id].size == 0) {
            (&code_infos->unknown_0xc)[seg_id] = 0;
          } else {
            void* src = (void *)ofh->code_infos[seg_id].offset;
            ofh->code_infos[seg_id].offset =
                (uint32_t)kmalloc(kdebugheap, ofh->code_infos[seg_id].size, 0, "debug-segment");
            if ((void *)ofh->code_infos[seg_id].offset == (void *)0x0) {
              MsgErr("dkernel: unable to malloc %d bytes for debug-segment~%",
                     ofh->code_infos[seg_id].size);
              return 1;
            }
            ultimate_memcpy_G(ofh->code_infos[seg_id].offset, src, ofh->code_infos[seg_id].size);
          }
        }
      } else if (seg_id == 0) {
        if (ofh->code_infos[seg_id].size == 0) {
          ofh->code_infos[seg_id].offset = 0;
          continue;
        } else if (this->m_moved_link_block == false) {
          do {
            void* src = (void *)ofh->code_infos[seg_id].offset;
            ofh->code_infos[seg_id].offset =
                (uint32_t)kmalloc(this->m_heap, ofh->code_infos[seg_id].size, 0, "main-segment");
            if ((void *)ofh->code_infos[seg_id].offset == (void *)0x0) {
              MsgErr("dkernel: unable to malloc %d bytes for main-segment~%",
                     ofh->code_infos[seg_id].size);
              return 1;
            }
            ultimate_memcpy_G((void *)ofh->code_infos[seg_id].offset, src,
                              ofh->code_infos[seg_id].size);
            goto LAB_0026f70c_for_loop;
          } while ((int)(m_link_hdr->link_length + 0x50) <= (int)m_link_hdr->length_to_get_to_code);
        }
        // m_heap = this->m_heap; // TODO: Why is this assigned?
        m_heap->current = this->m_object_data + this->m_code_size;
        seg_id = -1;
        if (m_heap->current < m_heap->top) {
          MsgErr("dkernel: heap overflow~%");
          return 1;
        }
      } else if (seg_id == 2) {
        if (ofh->code_infos[seg_id].size == 0) {
          (&code_infos->unknown_0xc)[1] = 0;
        } else {
          void* src = (void *)ofh->code_infos[seg_id].offset;
          ofh->code_infos[seg_id].offset =
              (uint32_t)kmalloc(this->m_heap, ofh->code_infos[seg_id].size, 0x2000, "top-level-segment")
                  ;
          if ((void *)ofh->code_infos[seg_id].offset == (void *)0x0) {
            MsgErr("dkernel: unable to malloc %d bytes for top-level-segment~%",
                    ofh->code_infos[seg_id].size);
            return 1;
          }
          ultimate_memcpy_G((void *)ofh->code_infos[seg_id].offset, src,
                            ofh->code_infos[seg_id].size);
        }
      } else {
        ;
      }
    }
    this->m_state = 1;
    this->m_segment_process = 0;
    int currentCycle = (*(code *)kernel.read_clock_G)();
    if (200000 < (uint)(currentCycle - startCycle)) {
      return 0;
    }
  }

  u8 *pVar___;
  uint uVar11;
  uint uVar12;
  byte *pbVar15;
  uint32_t state_W;

LAB_0026f94c:
  while ((int)this->m_state < (int)(this->m_code_start + 1) && this->m_segment_process == 0) {
    state_W = this->m_state;
    ObjectFileHeader* m_link_block_ptr = (ObjectFileHeader *)this->m_link_block_ptr;
    if ((m_link_block_ptr->code_infos[state_W - 1].offset != 0) &&
        (m_link_block_ptr->code_infos[state_W - 1].size != 0)) {
      puVar17 = (uint8_t *)
                m_link_block_ptr->code_infos[state_W - 2].unknown_0xc;
      this->m_segment_process = 1;
      this->m_original_object_location = puVar17;
      *(undefined *)&this->m_loc_ptr = 0;
      puVar17 = (uint8_t *)m_link_block_ptr->code_infos[state_W - 1].offset;
      this->m_object_data = puVar17;
      this->m_base_ptr = puVar17 + -4;
      this->m_reloc_ptr = puVar17;
      break;
    }
    this->m_segment_process = 0;
    this->m_state = state_W + 1;
  }
  if ((int)state_W < (int)(this->m_code_start + 1)) {
    state_W = this->m_segment_process;
    if (state_W == 1) {
      int relocCounter = 0x400;
      if (*this->m_original_object_location != '\0') {
LAB_0026f9e8:
        do {
          byte bVar1 = *(byte *)&this->m_loc_ptr;
          while( true ) {
            int iVar7 = 0;
            if (bVar1 == 0) {
              this->m_base_ptr = this->m_base_ptr + (uint)*this->m_original_object_location * 4;
              puVar17 = this->m_original_object_location;
            }
            else {
              pbVar15 = this->m_original_object_location;
              byte bVar2 = *pbVar15;
              while (bVar2 != 0) {
                u8** ppuVar3 = (u8 **)this->m_base_ptr;
                pVar___ = *ppuVar3;
                uVar12 = (uint)pVar___ >> 8 & 0xf;
                uint* puVar13 = (uint *)(((uint)pVar___ >> 10 & 0x3c) + (int)ppuVar3);
                if ((uint)pVar___ >> 0x18 == 0) {
                  *ppuVar3 = pVar___ + (int)this->m_reloc_ptr;
                }
                else {
                  uVar11 = *(int *)(this->m_link_block_ptr + uVar12 * 0x10 + 4) +
                            (((uint)pVar___ & 0xff) << 0x10 |
                            (uint)*(ushort *)puVar13);
                  if ((DebugSegment == 0) && (uVar12 == 1)) {
                    uVar11 = 0;
                  }
                  *ppuVar3 = (u8 *)((uint)pVar___ & 0xffff0000 | uVar11 >> 0x10);
                  *puVar13 = *puVar13 & 0xffff0000 | uVar11 & 0xffff;
                }
                iVar7 = iVar7 + 1;
                this->m_base_ptr = (u8 *)(ppuVar3 + 1);
                bVar2 = iVar7 < (int)(uint)*pbVar15;
              }
              puVar17 = this->m_original_object_location;
            }
            if (*puVar17 == 0xff) {
              this->m_original_object_location = puVar17 + 1;
              goto LAB_0026f9e8;
            }
            this->m_original_object_location = puVar17 + 1;
            *(byte *)&this->m_loc_ptr = bVar1 ^ 1;
            relocCounter = relocCounter + -1;
            if (puVar17[1] == '\0') goto LAB_0026fb20;
            if (relocCounter == 0) break;
            bVar1 = *(byte *)&this->m_loc_ptr;
          }
          relocCounter = 0x400;
          int currentCycle = (*(code *)kernel.read_clock_G)();
          if (200000 < (uint)(currentCycle - startCycle)) {
            return 0;
          }
        } while( true );
      }
LAB_0026fb20:
      this->m_original_object_location++;
      this->m_segment_process++;
      state_W = this->m_segment_process;
    }
    if (state_W != 2) {
      update_goal_fns();
      return 1;
    }
    pbVar15 = this->m_original_object_location;
    uVar12 = *(uint *)(this->m_link_block_ptr + this->m_state * 0x10 + -4);
    while( true ) {
      bVar1 = *pbVar15;
      uVar11 = (uint)bVar1;
      if (uVar11 == 0) break;
      this->m_original_object_location = pbVar15 + 1;
      Type *pTVar8;
      if ((bVar1 & 0x80) == 0) {
        short sVar4 = *(short *)(pbVar15 + 1);
        this->m_original_object_location = pbVar15 + 3;
        pTVar8 = (Type *)intern_from_c((int)sVar4,uVar11,(const char *)(pbVar15 + 3));
        puVar17 = this->m_original_object_location;
      }
      else {
        u64 methods;
        int iVar6 = (uVar11 & 0x3f) * 4;
        if ((uVar11 & 0x3f) == 0x3f) {
          bVar1 = pbVar15[1];
          this->m_original_object_location = pbVar15 + 2;
          methods = (long)(int)((uint)bVar1 * 4 + 3);
        }
        else {
          methods = (long)iVar6;
          if ((long)iVar6 != 0) {
            methods = (long)(iVar6 + 3);
          }
        }
        short* name = (short *)((int)this->m_original_object_location + 2);
        short sVar4 = *(short *)this->m_original_object_location;
        this->m_original_object_location = (uint8_t *)name;
        pTVar8 = intern_type_from_c((int)sVar4,uVar11,(const char *)name,methods);
        puVar17 = this->m_original_object_location;
      }
      size_t sVar10 = strlen((char *)puVar17);
      this->m_original_object_location = this->m_original_object_location + (int)sVar10 + 1;
      code* pcVar9;
      if ((uVar12 & 1) == 0) {
        puVar17 = this->m_object_data;
        pcVar9 = (code *)symlink3_G;
      }
      else {
        puVar17 = this->m_object_data;
        pcVar9 = (code *)symlink2_G;
      }
      puVar17 = (uint8_t *)(*pcVar9)(puVar17,pTVar8);
      this->m_original_object_location = puVar17;
      int currentCycle = (*(code *)kernel.read_clock_G)();
      if (200000 < (uint)(currentCycle - startCycle)) {
        return 0;
      }
      pbVar15 = this->m_original_object_location;
    }
    this->m_segment_process = 0;
    this->m_state++;
    this->m_entry = this->m_object_data + 4;
    goto LAB_0026f94c;
  } else {
    update_goal_fns();
  }
  return 1;
}

void jak3_finish(link_control *this,bool jump_from_c_to_goal) {
  char *a2;
  int unaff_s7_lo;
  code *m_entry;
  kheapinfo *m_heap;
  LinkHeaderV5Core *m_link_hdr;
  int old_debug_segment;
  uint16_t version;
  
  FlushCache(0);
  FlushCache(2);
  old_debug_segment = DebugSegment;
  if (this->m_keep_debug != 0) {
    DebugSegment = unaff_s7_lo + 4;
  }
  if ((this->m_flags & 0x20) != 0) {
    FastLink = true;
  }
  m_link_hdr = this->m_link_hdr;
  version = m_link_hdr->version;
  *EnableMethodSet = *EnableMethodSet + this->m_keep_debug;
  if (version == 5) {
    m_entry = (code *)this->m_entry;
    if (m_entry != (code *)0x0) {
      if ((*(int *)(m_entry + -4) == *(int *)(unaff_s7_lo + 7)) && ((this->m_flags & 5) != 0)) {
        if ((this->m_flags & 4) == 0) {
          m_entry = *(code **)(unaff_s7_lo + 0x93);
        }
        else {
          (*m_entry)();
          m_entry = *(code **)(unaff_s7_lo + 0x93);
        }
        (*m_entry)();
        if ((this->m_flags & 1) != 0) {
          output_segment_load(m_link_hdr->name,(ObjectFileHeader *)m_link_hdr->length_to_get_to_link
                              ,this->m_flags);
        }
      }
      else if ((m_entry != (code *)0x0) && ((this->m_flags & 4) != 0)) {
        a2 = basename(this->m_object_name);
        call_method_of_type_arg2
                  ((u32)this->m_entry,*(Type **)(this->m_entry + -4),7,(u32)this->m_heap,(u32)a2);
      }
    }
  }
  else {
    MsgErr("dkernel: FATAL ERROR: unknown goal file version %d~%",version);
  }
  m_heap = this->m_heap;
  FastLink = false;
  *EnableMethodSet = *EnableMethodSet - this->m_keep_debug;
  DebugSegment = old_debug_segment;
  m_heap->top = this->m_heap_top;
  this->m_busy = 0;
  if (this->m_on_global_heap != false) {
    kmemclose();
  }
  return;
}


namespace jak3 {

uint8_t * link_and_exec(uint8_t *data, const_char *name, int32_t size, kheapinfo *heap, uint32_t flags, bool jump_from_c_to_goal) {
  uint32_t done;
  long link_busy_result;
  long lVar1;
  uint8_t *lc.m_entry;
  
  lVar1 = (long)(int)data;
  link_busy_result = link_busy();
  if (link_busy_result != 0) {
    printf("-------------> saved link is busy\n");
  }
  jak3_begin((link_control *)&stack0xffffff30,data,name,size,heap,flags);
  do {
    done = jak3_work((link_control *)&stack0xffffff30);
  } while (done == 0);
  jak3_finish((link_control *)&stack0xffffff30,SUB81(lVar1,0));
  return lc.m_entry;
}

u64 link_and_exec_wrapper(u64* args) {
  return link_and_exec(Ptr<u8>(args[0]), Ptr<char>(args[1]).c(), args[2], Ptr<kheapinfo>(args[3]),
                       args[4], false)
      .offset;
}

u32 link_busy() {
  return saved_link_control_WG.m_busy;
}
void link_reset() {
  saved_link_control_WG.m_busy = 0;
  return;
}
uint64_t link_begin(u64 *args) {
  uint32_t work_result;
  undefined jump_from_c_to_goal;
  const_char *in_a1_lo;
  int32_t in_a2_lo;
  kheapinfo *in_a3_lo;
  uint32_t in_t0_lo;
  
  jump_from_c_to_goal = SUB41(args,0);
  jak3_begin(&saved_link_control_WG,(uint8_t *)args,in_a1_lo,in_a2_lo,in_a3_lo,in_t0_lo);
  work_result = jak3_work(&saved_link_control_WG);
  if (work_result != 0) {
    jak3_finish(&saved_link_control_WG,(bool)jump_from_c_to_goal);
  }
  return (ulong)(work_result != 0);
}
uint64_t link_resume() {
  uint32_t uVar1;
  undefined in_a1_lo;
  
  uVar1 = jak3_work(&saved_link_control_WG);
  if (uVar1 != 0) {
    jak3_finish(&saved_link_control_WG,(bool)in_a1_lo);
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
