#include "kmalloc.h"

#include <cstdio>
#include <cstring>

#include "common/goal_constants.h"

#include "game/kernel/common/kprint.h"
#include "game/kernel/common/kscheme.h"
#include "game/kernel/common/memory_layout.h"

// global and debug kernel heaps
Ptr<kheapinfo> kglobalheap;
Ptr<kheapinfo> kdebugheap;
// if we should count the number of strings and types allocated on the global heap.
bool kheaplogging = false;
enum MemItemsCategory {
  STRING = 0,
  TYPE = 1,
  NUM_CATEGORIES = 2,
};
int MemItemsCount[NUM_CATEGORIES] = {0, 0};
int MemItemsSize[NUM_CATEGORIES] = {0, 0};

void kmalloc_init_globals_common() {
  // _globalheap and _debugheap
  kglobalheap.offset = GLOBAL_HEAP_INFO_ADDR;
  kdebugheap.offset = DEBUG_HEAP_INFO_ADDR;
  kheaplogging = false;
  for (auto& x : MemItemsCount)
    x = 0;
  for (auto& x : MemItemsSize)
    x = 0;
}

/*!
 * In the game, this wraps PS2's libc's malloc/calloc.
 * These don't work with GOAL's custom memory management, and this function
 * is unused.
 * DONE, malloc/calloc calls commented out because memory allocated with calloc/malloc
 * cannot trivially be accessed from within GOAL.
 */
u8* ksmalloc(kheapinfo* heap, s32 size, u32 flags, char const* name) {
  u32 align = flags & 0xfff;
  u8* mem;

  if ((flags & KMALLOC_MEMSET) == 0) {
    // mem = (u8 *)malloc((long)(int)(size + align));
  } else {
    // mem = (u8 *)calloc(1,(long)(int)(size + align));
  }

  if (align == KMALLOC_ALIGN_64) {
    mem = (u8*)(((uint)mem + 0x3f) & 0xffffffc0);
  } else if (align == KMALLOC_ALIGN_256) {
    mem = (u8*)(((uint)mem + 0xff) & 0xffffff00);
  }

  return mem;
}

/*!
 * Print the status of a kheap.  This prints to stdout on the runtime,
 * which will not be sent to the Listener.
 * DONE, EXACT
 */
kheapinfo* kheapstatus(kheapinfo* heap) {
  Msg(6,
      "[%8x] kheap\n"
      "\tbase: #x%x\n"
      "\ttop-base: #x%x\n"
      "\tcur: #x%x\n"
      "\ttop: #x%x\n",
      heap, heap->base, heap->top_base, heap->current,
      heap->top);
  Msg(6,
      "\t used bot: %d of %d bytes\n"
      "\t used top: %d of %d bytes\n"
      "\t symbols: %d of %d\n",
      (int)heap->current - (int)heap->base, (int)heap->top_base - (int)heap->base, (int)heap->top_base - (int)heap->top,
      (int)heap->top_base - (int)heap->base, NumSymbols, 0x4000);

  if (heap == &kglobalheapinfo) {
    Msg(6, "\t %d bytes before stack\n", GLOBAL_HEAP_END);
  }

  for (int i = 0; i < 2; i++) {
    printf("   %d: %d %d\n", i, MemItemsCount[i], MemItemsSize[i]);
  }

  return heap;
}

/*!
 * Initialize a kheapinfo structure, and clear the kheap's memory to 0.
 * DONE, EXACT
 */
kheapinfo* kinitheap(kheapinfo* heap, u8* mem, s32 size) {
  heap->base = mem;
  heap->current = mem;
  heap->top = mem + size;
  heap->top_base = heap->top;
  memset(mem, 0, (long)size);
  return heap;
}

/*!
 * Return how much of the bottom (non-temp) allocator is used.
 * DONE, EXACT
 */
u32 kheapused(kheapinfo* heap) {
  return (int)heap->current - (int)heap->base;
}

/*!
 * Allocate memory using bump allocation strategy.
 * @param heapPtr : heap to allocate on. If null heap, use global but print a warning
 * @param size    : size of memory needed
 * @param flags   : flags for alignment, top/bottom allocation, set to zero
 * @param name    : name of allocation (printed if things go wrong)
 * @return        : memory.  0 if we run out of room
 * DONE, PRINT ADDED
 */
u8* kmalloc(kheapinfo* heap, s32 size, u32 flags, char const* name) {
  uint alignment_flag = flags & 0xfff;

  if (heap == nullptr) {
    Msg(6, "--------------------> kmalloc: alloc %s mem %s #x%x (a:%d  %d bytes)\n", "DEBUG", name, 0,
        alignment_flag, size);
    heap = &kglobalheapinfo;
  }

  u8* memstart;

  if ((flags & KMALLOC_TOP) == 0) {
    if (alignment_flag == KMALLOC_ALIGN_64)
      memstart = 0xffffffc0 & (uint)(heap->current + 0x40 - 1);
    else if (alignment_flag == KMALLOC_ALIGN_256)
      memstart = 0xffffff00 & (uint)(heap->current + 0x100 - 1);
    else
      memstart = 0xfffffff0 & (uint)(heap->current + 0x10 - 1);

    if (size == 0) {
      return memstart;
    }

    uint32_t memend = memstart + size;

    if (heap->top <= memend) { // FIXME: why is this <= and not <?
      kheapstatus(heap);
      Msg(6, "kmalloc: !alloc mem %s (%d bytes) heap %x\n", name, size, heap);
      return nullptr;
    }

    heap->current = memend;
    if ((flags & KMALLOC_MEMSET) != 0)
      memset(memstart, 0, size);
    // TODO: This if statement wasn't in the code's execution up until jak 3; why?
    // Naughty Dog could have moved this out of the if statement in Jak X...
    if ((heap == &kglobalheapinfo) && ((char)kheaplogging != '\0')) {
      if (strcmp(name, "string") == 0) {
        MemItemsCount[0]++;
        MemItemsSize[0] += size;
      } else if (strcmp(name, "type") == 0) {
        MemItemsCount[1]++;
        MemItemsSize[1] += size;
      }
    }
    return memstart;
  } else {
    if (alignment_flag == 0) {
      alignment_flag = KMALLOC_ALIGN_16;
    }

    memstart = ((u8 *)((int)heap->top - size) & (-alignment_flag));

    if (size == 0) {
      return memstart;
    }

    if (heap->current >= memstart) {
      Msg(6, "kmalloc: !alloc mem from top %s (%d bytes) heap %x\n", name, size, heap);
      kheapstatus(heap);
      return nullptr;
    }

    heap->top = memstart;

    if ((flags & KMALLOC_MEMSET) != 0)
      memset(memstart, 0, size);

    if ((heap == &kglobalheapinfo) && ((char)kheaplogging != '\0')) {
      if (strcmp(name, "string") == 0) {
        MemItemsCount[0]++;
        MemItemsSize[0] += size;
      } else if (strcmp(name, "type") == 0) {
        MemItemsCount[1]++;
        MemItemsSize[1] += size;
      }
    }
    return memstart;
  }
}

/*!
 * GOAL does not support automatic freeing of memory. This function does nothing.
 * Programmers wishing to free memory must do it themselves.
 * DONE, PRINT ADDED
 */
void kfree(u8* a) {}
