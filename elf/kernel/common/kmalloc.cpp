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
 * TBD, malloc/calloc calls commented out because memory allocated with calloc/malloc
 * cannot trivially be accessed from within GOAL.
 */
u8 * ksmalloc(kheapinfo *heap,s32 size,u32 flags,char *name) {
  u8 *puVar1;
  u8 *puVar2;
  uint uVar3;
  
  uVar3 = flags & 0xfff;
  if ((flags & 0x1000) == 0) {
    puVar1 = (u8 *)malloc((long)(int)(size + uVar3));
  }
  else {
    puVar1 = (u8 *)calloc(1,(long)(int)(size + uVar3));
  }
  puVar2 = puVar1 + 0x3f;
  if (uVar3 == 0x40) {
    uVar3 = 0xffffffc0;
  }
  else {
    puVar2 = puVar1 + 0xff;
    if (uVar3 != 0x100) {
      return puVar1;
    }
    uVar3 = 0xffffff00;
  }
  return (u8 *)((uint)puVar2 & uVar3);
}

/*!
 * Print the status of a kheap.  This prints to stdout on the runtime,
 * which will not be sent to the Listener.
 * TBD, EXACT
 */
kheapinfo * kheapstatus(kheapinfo *heap)

{
  int iVar1;
  int iVar2;
  
  Msg(6,"[%8x] kheap\n\tbase: #x%x\n\ttop-base: #x%x\n\tcur: #x%x\n\ttop: #x%x\n",heap,
      heap->base,heap->top_base,heap->current,heap->top);
  iVar1 = (int)heap->top_base - (int)heap->base;
  Msg(6,"\t used bot: %d of %d bytes\n\t used top: %d of %d bytes\n\t symbols: %d of %d\n",
      (int)heap->current - (int)heap->base,iVar1,(int)heap->top_base - (int)heap->top,
      iVar1,NumSymbols,0x4000);
  if (heap == &kglobalheapinfo) {
    Msg(6,"\t %d bytes before stack\n",0x1ffc000);
  }
  iVar1 = 0;
  do {
    iVar2 = iVar1 + 1;
    printf("   %d: %d %d\n",iVar1,MemItemsCount[iVar1],MemItemsSize[iVar1]);
    iVar1 = iVar2;
  } while (iVar2 < 2);
  return heap;
}

/*!
 * Initialize a kheapinfo structure, and clear the kheap's memory to 0.
 * TBD, EXACT
 */
kheapinfo* kinitheap(kheapinfo* heap, u8* mem, s32 size) {
  heap->top_base = mem + size;
  heap->base = mem;
  heap->current = mem;
  heap->top = mem + size;
  memset(mem,0,(long)size);
  return heap;
}

/*!
 * Return how much of the bottom (non-temp) allocator is used.
 * TBD, EXACT
 */
u32 kheapused(kheapinfo *heap) {
  return (int)heap->current - (int)heap->base;
}

/*!
 * Allocate memory using bump allocation strategy.
 * @param heapPtr : heap to allocate on. If null heap, use global but print a warning
 * @param size    : size of memory needed
 * @param flags   : flags for alignment, top/bottom allocation, set to zero
 * @param name    : name of allocation (printed if things go wrong)
 * @return        : memory.  0 if we run out of room
 * TBD, PRINT ADDED
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
 * TBD, PRINT ADDED
 */
void kfree(u8* a) {
  return;
}
