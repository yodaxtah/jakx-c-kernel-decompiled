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
Ptr<u8> ksmalloc(Ptr<kheapinfo> heap, s32 size, u32 flags, char const* name) {
  (void)heap;
  (void)size;
  (void)name;
  printf("[ERROR] ksmalloc : cannot be used!\n");
  u32 align = flags & 0xfff;
  Ptr<u8> mem;

  if ((flags & KMALLOC_MEMSET) == 0) {
    // mem = malloc(size + align);
  } else {
    // mem = calloc(1, size + align);
  }

  if (align == KMALLOC_ALIGN_64) {
    mem.offset = (mem.offset + 0x3f) & 0xffffffc0;
  } else if (align == KMALLOC_ALIGN_256) {
    mem.offset = (mem.offset + 0xff) & 0xffffff00;
  }

  return mem;
}

/*!
 * Print the status of a kheap.  This prints to stdout on the runtime,
 * which will not be sent to the Listener.
 * DONE, EXACT
 */
Ptr<kheapinfo> kheapstatus(Ptr<kheapinfo> heap) {
  Msg(6,
      "[%8x] kheap\n"
      "\tbase: #x%x\n"
      "\ttop-base: #x%x\n"
      "\tcur: #x%x\n"
      "\ttop: #x%x\n",
      heap.offset, heap->base.offset, heap->top_base.offset, heap->current.offset,
      heap->top.offset);
  // note: max symbols here is game-version dependent
  Msg(6,
      "\t used bot: %d of %d bytes\n"
      "\t used top: %d of %d bytes\n"
      "\t symbols: %d of %d\n",
      heap->current - heap->base, heap->top_base - heap->base, heap->top_base - heap->top,
      heap->top_base - heap->base, NumSymbols, max_symbols(g_game_version));

  if (heap == kglobalheap) {
    Msg(6, "\t %d bytes before stack\n", GLOBAL_HEAP_END - heap->current.offset);
  }

  for (int i = 0; i < NUM_CATEGORIES; i++) {
    printf("  %d: %d %d\n", i, MemItemsCount[i], MemItemsSize[i]);
  }

  // might not have returned heap in jak 1
  return heap;
}

/*!
 * Initialize a kheapinfo structure, and clear the kheap's memory to 0.
 * DONE, EXACT
 */
Ptr<kheapinfo> kinitheap(Ptr<kheapinfo> heap, Ptr<u8> mem, s32 size) {
  heap->base = mem;
  heap->current = mem;
  heap->top = mem + size;
  heap->top_base = heap->top;
  std::memset(mem.c(), 0, size);
  return heap;
}

/*!
 * Return how much of the bottom (non-temp) allocator is used.
 * DONE, EXACT
 */
u32 kheapused(Ptr<kheapinfo> heap) {
  return heap->current - heap->base;
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
u8* kmalloc(kheapinfo *heap,s32 size,u32 flags,const char* name) {
  u8* puVar1;
  int iVar2;
  char* format;
  size_t __n;
  u8* puVar3;
  uint uVar4;
  
  __n = (size_t)size;
  uVar4 = flags & 0xfff;
  if (heap == (kheapinfo *)0x0) {
    Msg(6,"--------------------> kmalloc: alloc %s mem %s #x%x (a:%d  %d bytes)\n",0x25c618,name,0,
        uVar4,__n);
    heap = &kglobalheapinfo;
  }
  if ((flags & 0x2000) == 0) {
    puVar1 = heap->current;
    if (uVar4 == 0x40) {
      puVar3 = puVar1 + 0x3f;
      uVar4 = 0xffffffc0;
    }
    else {
      puVar3 = puVar1 + 0xff;
      if (uVar4 == 0x100) {
        uVar4 = 0xffffff00;
      }
      else {
        puVar3 = puVar1 + 0xf;
        uVar4 = 0xfffffff0;
      }
    }
    puVar3 = (u8 *)((uint)puVar3 & uVar4);
    if (__n == 0) {
      return puVar3;
    }
    if (heap->top <= puVar3 + size) {
      format = "kmalloc: !alloc mem %s (%d bytes) heap %x\n";
      goto LAB_0025b9c4;
    }
    heap->current = puVar3 + size;
  }
  else {
    if (uVar4 == 0) {
      uVar4 = 0x10;
    }
    puVar3 = (u8 *)((int)heap->top - size & -uVar4);
    if (__n == 0) {
      return puVar3;
    }
    if (puVar3 <= heap->current) {
      format = "kmalloc: !alloc mem from top %s (%d bytes) heap %x\n";
LAB_0025b9c4:
      Msg(6,format,name,__n,heap);
      kheapstatus(heap);
      return (u8 *)0x0;
    }
    heap->top = puVar3;
  }
  if ((flags & 0x1000) != 0) {
    memset(puVar3,0,__n);
  }
  if ((heap == &kglobalheapinfo) && ((char)kheaplogging != '\0')) {
    iVar2 = strcmp(name,"string");
    if (iVar2 == 0) {
      MemItemsCount[0] = MemItemsCount[0] + 1;
      MemItemsSize[0] = MemItemsSize[0] + size;
    }
    else {
      iVar2 = strcmp(name,"type");
      if (iVar2 == 0) {
        MemItemsCount[1] = MemItemsCount[1] + 1;
        MemItemsSize[1] = MemItemsSize[1] + size;
      }
    }
  }
  return puVar3;
}

/*!
 * GOAL does not support automatic freeing of memory. This function does nothing.
 * Programmers wishing to free memory must do it themselves.
 * DONE, PRINT ADDED
 */
void kfree(u8* a) {
  return;
}
