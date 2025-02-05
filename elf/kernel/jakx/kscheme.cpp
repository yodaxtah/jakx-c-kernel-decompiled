#include "kscheme.h"

#include <unordered_map>

#include "common/common_types.h"
#include "common/goal_constants.h"
#include "common/log/log.h"
#include "common/symbols.h"

#include "game/kernel/common/Symbol4.h"
#include "game/kernel/common/fileio.h"
#include "game/kernel/common/kdsnetm.h"
#include "game/kernel/common/klink.h"
#include "game/kernel/common/kmalloc.h"
#include "game/kernel/common/kmemcard.h"
#include "game/kernel/common/kprint.h"
#include "game/kernel/common/kscheme.h"
#include "game/kernel/jak3/fileio.h"
#include "game/kernel/jak3/kdgo.h"
#include "game/kernel/jak3/klink.h"
#include "game/kernel/jak3/klisten.h"
#include "game/kernel/jak3/kmachine.h"
#include "game/kernel/jak3/kmalloc.h"
#include "game/kernel/jak3/kprint.h"

#define JAK3_HASH_TABLE

namespace jak3 {

using namespace jak3_symbols;

Ptr<u32> SymbolString;
Ptr<Symbol4<u32>> CollapseQuote;
Ptr<Symbol4<u32>> LevelTypeList;
Ptr<String> UnknownName;
bool DebugSymbols = false;
Ptr<u32> KernelDebug;
Ptr<Symbol4<u32>> SqlResult;

#ifdef JAK3_HASH_TABLE
std::unordered_map<std::string, int> g_symbol_hash_table;
#endif

void kscheme_init_globals() {
  LevelTypeList.offset = 0;
  SymbolString.offset = 0;
  CollapseQuote.offset = 0;
  UnknownName.offset = 0;
  DebugSymbols = false;
  KernelDebug.offset = 0;
  SqlResult.offset = 0;
#ifdef JAK3_HASH_TABLE
  g_symbol_hash_table.clear();
#endif
}

u32 u32_in_fixed_sym(u32 offset) {
  return Ptr<Symbol4<u32>>(s7.offset + offset)->value();
}

namespace {
void fixed_sym_set(u32 offset, u32 value) {
  Ptr<Symbol4<u32>>(s7.offset + offset)->value() = value;
}
}  // namespace

u64 new_illegal(u32 allocation, u32 type) {
  int unaff_s7_lo;
  undefined4 unaff_s7_hi;
  
  MsgErr("dkernel: illegal attempt to call new method of static object type %s\n",
         *(int *)((*(int *)type - unaff_s7_lo) + SymbolString) + 4);
  return CONCAT44(unaff_s7_hi, unaff_s7_lo);
}

u64 alloc_from_heap(u32 heap_symbol, u32 type, s32 size, u32 pp) {
  int unaff_s6_lo;
  int unaff_s7_lo;
  u64 heap_symbol_ = (u64)(int)heap_symbol_;
  kheapinfo* heap_ptr = *(kheapinfo **)(heap_symbol_ - 1);
  s32 aligned_size = ((size + 0xf) / 0x10) * 0x10;
  if (heap_symbol_ == (long)(unaff_s7_lo + 0xa0) ||
      heap_symbol_ == (long)(unaff_s7_lo + 0xa4) ||
      heap_symbol_ == (long)(unaff_s7_lo + 0xa8) ||
      heap_symbol_ == (long)(unaff_s7_lo + 0xb0)) {
    if (type == 0) {
      return (long)(int)kmalloc(heap_ptr, size, 0x1000, "global-object");
    }

    if (*(int *)type == 0) {
      return (long)(int)kmalloc(heap_ptr, size, 0x1000, "global-object");
    }

    char *gstr = (char *)(aligned_size + 4);
    gstr_len = *(int *)((*(int *)type - unaff_s7_lo) + SymbolString);
    if (gstr_len == 0)) {
      return (long)(int)kmalloc(heap_ptr, size, 0x1000, "global-object");
    }

    return (long)(int)kmalloc(heap_ptr, size, 0x1000, gstr);
  } else if (heap_symbol_ == (long)(unaff_s7_lo + 100)) {
    u32 start = *(u32 *)(unaff_s6_lo + 0x74);
    u32 heapEnd = *(u32 *)(unaff_s6_lo + 0x70);
    u32 allocEnd = start + aligned_size;

    if (allocEnd < heapEnd) {
      *(u32 *)(unaff_s6_lo + 0x74) = allocEnd;
      memset((void *)start, 0, (long)aligned_size);
      return (u64)start;
    } else {
      MsgErr("kmalloc: !alloc mem in heap for #<process @ #x%x> (%d bytes / %d bytes free)\n");
      return 0;
    }
  } else if (heap_symbol_ == (long)(unaff_s7_lo + 0xb8)) {
    // TBD
    void *__s = *(void **)(unaff_s7_lo + 0xbb);
    heap_symbol_ = (u64)(int)__s;
    *(int *)(unaff_s7_lo + 0xbb) = *(int *)(unaff_s7_lo + 0xbb) + aligned_size;
    memset(__s, 0, (long)aligned_size);
    return heap_symbol_;
  } else {
    memset((void *)heap_symbol_, 0, (long)aligned_size);
    return heap_symbol_;
  }
}

/*!
 * Allocate untyped memory.
 */
u64 alloc_heap_memory(u32 heap, u32 size) {
  u32 in_a3_lo;
  return alloc_from_heap(heap, 0, size, in_a3_lo);
}

/*!
 * Allocate memory and add type tag for an object.
 * For allocating basics.
 * Called from GOAL.
 */
u64 alloc_heap_object(u32 heap, u32 type, u32 size, u32 pp) {
  u64 mem = alloc_from_heap(heap, type, size, pp);
  if (mem == 0) {
    return 0;
  }

  *(u32 *)mem = type;
  return (u64)(int)((u32 *)mem + 1);
}

/*!
 * Allocate a structure and get the structure size from the type.
 */
u64 new_structure(u32 heap, u32 type) {
  u32 in_a3_lo;
  return alloc_from_heap(heap, type, (uint)*(ushort *)(type + 8), in_a3_lo);
}

/*!
 * Allocate a structure with a dynamic size
 */
u64 new_dynamic_structure(u32 heap_symbol, u32 type, u32 size) {
  u32 in_a3_lo;
  return alloc_from_heap(heap_symbol, type, size, in_a3_lo);
}

/*!
 * Delete a structure.  Not supported, as it uses kfree, which doesn't do anything.
 */
void delete_structure(u32 s) {
  kfree((u8 *)s);
}

/*!
 * Allocate a basic of fixed size.
 */
u64 new_basic(u32 heap, u32 type, u32 size, u32 pp) {
  return alloc_heap_object(heap, type, (uint)*(ushort *)(type + 8), pp);
}

/*!
 * Delete a basic.  Not supported, as it uses kfree.
 */
void delete_basic(u32 s) {
  kfree((u8 *)(s - 0x10));
}

/*!
 * Allocate a new pair and set its car and cdr.
 */
u64 new_pair(u32 heap, u32 type, u32 car, u32 cdr) {
  u64 mem = alloc_from_heap(heap, type, (uint)*(ushort *)(type + 8), cdr);
  if (mem == 0) {
    return 0;
  }

  u32* m = (u32 *)mem;
  m[0] = car;
  m[1] = cdr;
  return (u64)((int)m + 2);
}

/*!
 * Delete a pair.  BUG
 */
void delete_pair(u32 s) {
  kfree((u8 *)(s - 8));
}

u64 make_string(u32 size) {
  int mem_size = size + 1;
  if (mem_size < 9) {
    mem_size = 8;
  }

  u32 in_a3_lo;
  int unaff_s7_lo;
  u64 mem =
      alloc_heap_object(unaff_s7_lo + 0xa0, *(u32 *)(unaff_s7_lo + 0xf),
                        mem_size + 8, in_a3_lo);

  if (mem != 0) {
    *(u32*)mem = size;
  }
  return mem;
}

/*!
 * Convert a C string to a GOAL string.
 * Allocates from the global heap and copies the string data.
 */
u64 make_string_from_c(const char* c_str) {
  size_t str_size = strlen(c_str);
  int mem_size = (int)str_size + 1;
  if (mem_size < 9) {
    mem_size = 8;
  }

  u32 in_a3_lo;
  int unaff_s7_lo;
  u64 mem =
      alloc_heap_object(unaff_s7_lo + 0xa0,*(u32 *)(unaff_s7_lo + 0xf),
                        mem_size + 8,in_a3_lo);

  *(int *)mem = (int)str_size;

  strcpy((char *)((int *)mem + 1),c_str);
  return mem;
}

u64 make_debug_string_from_c(const char* c_str) {
  size_t str_size = strlen(c_str);
  int mem_size = (int)str_size + 1;
  if (mem_size < 9) {
    mem_size = 8;
  }

  u32 in_a3_lo;
  int unaff_s7_lo;
  u64 mem = alloc_heap_object(unaff_s7_lo + 0xa4,*(u32 *)(unaff_s7_lo + 0xf),
                              mem_size + 8,in_a3_lo);
  
  *(int *)mem = (int)str_size;

  strcpy((char *)((int *)mem + 1),c_str);
  return mem;
}

extern "C" {
#ifndef __aarch64__
#ifdef __APPLE__
void _arg_call_systemv() asm("_arg_call_systemv");
void _stack_call_systemv() asm("_stack_call_systemv");
void _stack_call_win32() asm("_stack_call_win32");
#else
void _arg_call_systemv();
void _stack_call_systemv();
void _stack_call_win32();
#endif
#else
#if defined(__APPLE__)
void _arg_call_arm64() asm("_arg_call_arm64");
void _stack_call_arm64() asm("_stack_call_arm64");
#else
void _arg_call_arm64();
void _stack_call_arm64();
#endif
#endif
}

/*!
 * This creates an OpenGOAL function from a C++ function. Only 6 arguments can be accepted.
 * But calling this function is fast. It used to be really fast but wrong.
 */
Ptr<Function> make_function_from_c_systemv(void* func, bool arg3_is_pp) {
  auto mem = Ptr<u8>(alloc_heap_object(s7.offset + FIX_SYM_GLOBAL_HEAP,
                                       u32_in_fixed_sym(FIX_SYM_FUNCTION_TYPE), 0x40, UNKNOWN_PP));
  auto f = (uint64_t)func;
  auto target_function = (u8*)&f;
#ifndef __aarch64__
  auto trampoline_function_addr = _arg_call_systemv;
#else
  auto trampoline_function_addr = _arg_call_arm64;
#endif
  auto trampoline = (u8*)&trampoline_function_addr;
  // TODO - x86 code still being emitted below

  // movabs rax, target_function
  int offset = 0;
  mem.c()[offset++] = 0x48;
  mem.c()[offset++] = 0xb8;
  for (int i = 0; i < 8; i++) {
    mem.c()[offset++] = target_function[i];
  }

  // push rax
  mem.c()[offset++] = 0x50;

  // movabs rax, trampoline
  mem.c()[offset++] = 0x48;
  mem.c()[offset++] = 0xb8;
  for (int i = 0; i < 8; i++) {
    mem.c()[offset++] = trampoline[i];
  }

  if (arg3_is_pp) {
    // mov rcx, r13. Puts pp in the third argument.
    mem.c()[offset++] = 0x4c;
    mem.c()[offset++] = 0x89;
    mem.c()[offset++] = 0xe9;
  }

  // jmp rax
  mem.c()[offset++] = 0xff;
  mem.c()[offset++] = 0xe0;
  // the asm function's ret will return to the caller of this (GOAL code) directlyz.

  // CacheFlush(mem, 0x34);

  return mem.cast<Function>();
}

/*!
 * Create a GOAL function from a C function. This doesn't export it as a global function, it just
 * creates a function object on the global heap.
 *
 * This creates a simple trampoline function which jumps to the C function and reorders the
 * arguments to be correct for Windows.
 */
Ptr<Function> make_function_from_c_win32(void* func, bool arg3_is_pp) {
  // allocate a function object on the global heap
  auto mem = Ptr<u8>(alloc_heap_object(s7.offset + FIX_SYM_GLOBAL_HEAP,
                                       u32_in_fixed_sym(FIX_SYM_FUNCTION_TYPE), 0x80, UNKNOWN_PP));
  auto f = (uint64_t)func;
  auto fp = (u8*)&f;

  int i = 0;
  // we will put the function address in RAX with a movabs rax, imm8
  mem.c()[i++] = 0x48;
  mem.c()[i++] = 0xb8;
  for (int j = 0; j < 8; j++) {
    mem.c()[i++] = fp[j];
  }

  /*
    push rdi
    push rsi
    push rdx
    push rcx
    pop r9
    pop r8
    pop rdx
    pop rcx
    push r10
    push r11
    sub rsp, 40
   */
  for (auto x : {0x57, 0x56, 0x52, 0x51, 0x41, 0x59, 0x41, 0x58, 0x5A, 0x59, 0x41, 0x52, 0x41, 0x53,
                 0x48, 0x83, 0xEC, 0x28}) {
    mem.c()[i++] = x;
  }

  if (arg3_is_pp) {
    // mov r9, r13. Puts pp in the third argument.
    mem.c()[i++] = 0x4d;
    mem.c()[i++] = 0x89;
    mem.c()[i++] = 0xe9;
  }

  /*
    call rax
    add rsp, 40
    pop r11
    pop r10
    ret
   */
  for (auto x : {0xFF, 0xD0, 0x48, 0x83, 0xC4, 0x28, 0x41, 0x5B, 0x41, 0x5A, 0xC3}) {
    mem.c()[i++] = x;
  }

  // CacheFlush(mem, 0x34);

  return mem.cast<Function>();
}

Ptr<Function> make_stack_arg_function_from_c_systemv(void* func) {
  // allocate a function object on the global heap
  auto mem = Ptr<u8>(alloc_heap_object(s7.offset + FIX_SYM_GLOBAL_HEAP,
                                       u32_in_fixed_sym(FIX_SYM_FUNCTION_TYPE), 0x40, UNKNOWN_PP));
  auto f = (uint64_t)func;
  auto target_function = (u8*)&f;
#ifndef __aarch64__
  auto trampoline_function_addr = _stack_call_systemv;
#else
  auto trampoline_function_addr = _stack_call_arm64;
#endif
  auto trampoline = (u8*)&trampoline_function_addr;

  // movabs rax, target_function
  int offset = 0;
  mem.c()[offset++] = 0x48;
  mem.c()[offset++] = 0xb8;
  for (int i = 0; i < 8; i++) {
    mem.c()[offset++] = target_function[i];
  }

  // push rax
  mem.c()[offset++] = 0x50;

  // movabs rax, trampoline
  mem.c()[offset++] = 0x48;
  mem.c()[offset++] = 0xb8;
  for (int i = 0; i < 8; i++) {
    mem.c()[offset++] = trampoline[i];
  }

  // jmp rax
  mem.c()[offset++] = 0xff;
  mem.c()[offset++] = 0xe0;

  // CacheFlush(mem, 0x34);

  return mem.cast<Function>();
}

#ifdef _WIN32
/*!
 * Create a GOAL function from a C function.  This calls a windows function, but doesn't scramble
 * the argument order.  It's supposed to be used with _format_win32 which assumes GOAL order.
 */
Ptr<Function> make_stack_arg_function_from_c_win32(void* func) {
  // allocate a function object on the global heap
  auto mem = Ptr<u8>(alloc_heap_object(s7.offset + FIX_SYM_GLOBAL_HEAP,
                                       u32_in_fixed_sym(FIX_SYM_FUNCTION_TYPE), 0x80, UNKNOWN_PP));
  auto f = (uint64_t)func;
  auto fp = (u8*)&f;
  auto trampoline_function_addr = _stack_call_win32;
  auto trampoline = (u8*)&trampoline_function_addr;

  int i = 0;
  // we will put the function address in RAX with a movabs rax, imm8
  mem.c()[i++] = 0x48;
  mem.c()[i++] = 0xb8;
  for (int j = 0; j < 8; j++) {
    mem.c()[i++] = fp[j];
  }

  // push rax
  mem.c()[i++] = 0x50;

  // we will put the function address in RAX with a movabs rax, imm8
  mem.c()[i++] = 0x48;
  mem.c()[i++] = 0xb8;
  for (int j = 0; j < 8; j++) {
    mem.c()[i++] = trampoline[j];
  }

  /*
   * jmp rax
   */
  for (auto x : {0xFF, 0xE0}) {
    mem.c()[i++] = x;
  }

  return mem.cast<Function>();
}
#endif

/*!
 * Create a GOAL function from a C function. This doesn't export it as a global function, it just
 * creates a function object on the global heap.
 *
 * The implementation is to create a simple trampoline function which jumps to the C function.
 * TBD
 */
Function * make_function_from_c(void *func,bool arg3_is_pp) {
  u64 uVar1;
  u32 in_a3_lo;
  undefined4 *mem;
  int unaff_s7_lo;
  
  uVar1 = alloc_heap_object(unaff_s7_lo + 0xa0,*(u32 *)(unaff_s7_lo + 7),0x50,in_a3_lo);
  mem = (undefined4 *)uVar1;
  mem[0x10] = 0x67bd0040;
  mem[10] = 0;
  mem[0x11] = 0;
  mem[5] = 0x3c1c002d;
  mem[0x12] = 0;
  mem[6] = 0x379c2b80;
  mem[7] = (uint)func >> 0x10 | 0x3c190000;
  mem[8] = (uint)func & 0xffff | 0x37390000;
  mem[1] = 0xffbf0000;
  mem[0] = 0x67bdffc0;
  mem[2] = 0xffbc0010;
  mem[3] = 0xffb60020;
  mem[4] = 0xffb70030;
  mem[9] = 0x320f809;
  mem[0xc] = 0xdfbc0010;
  mem[0xd] = 0xdfb60020;
  mem[0xe] = 0xdfb70030;
  mem[0xb] = 0xdfbf0000;
  mem[0xf] = 0x3e00008;
  CacheFlush(mem, 0x4c);
  return (Function *)mem;
}

Ptr<Function> make_stack_arg_function_from_c(void* func) {
#ifdef __linux__
  return make_stack_arg_function_from_c_systemv(func);
#elif __APPLE__
  return make_stack_arg_function_from_c_systemv(func);
#elif _WIN32
  return make_stack_arg_function_from_c_win32(func);
#endif
}

/*!
 * Create a GOAL function which does nothing and immediately returns.
 */
u64 make_nothing_func() {
  u32 in_a3_lo;
  int unaff_s7_lo;
  undefined4 *mem = (undefined4 *)alloc_heap_object(unaff_s7_lo + 0xa0,
                                                    *(u32 *)(unaff_s7_lo + 7), 0x14, in_a3_lo);

  mem[0] = 0x3e00008;
  mem[1] = 0;
  mem[2] = 0;
  mem[3] = 0;
  // CacheFlush(mem, 0x10);
  return (u64)mem;
}

/*!
 * Create a GOAL function which returns 0.
 */
u64 make_zero_func() {
  u32 in_a3_lo;
  int unaff_s7_lo;
  undefined4 *mem = alloc_heap_object(unaff_s7_lo + 0xa0,
                                      *(u32 *)(unaff_s7_lo + 7), 0x14, in_a3_lo);
  mem[0] = 0x3e00008;
  mem[1] = 0x24020000;
  mem[2] = 0;
  mem[3] = 0;
  // CacheFlush(mem, 0x10);
  return (u64)mem;
}

u64 symbol_to_string_from_c(u32 sym) {
  int unaff_s7_lo;
  undefined4 unaff_s7_hi;
  int name = *(int *)((sym - unaff_s7_lo) + SymbolString);
  if ((u64)name == (long)UnknownName ||
      (0 < (long)(u64)name &&
       (DebugSegment == 0 || (long)*(int *)(unaff_s7_lo + 0x28f) != CONCAT44(unaff_s7_hi, unaff_s7_lo)))) {
    MsgWarn(
        "dkernel: doing a symbol->string on %s (addr #x%x), but the symbol has not been marked as "
        "symbol-export-string\n",
        name + 4, sym);
  }
  return (u64)name;
}

/*!
 * Given a C function and a name, create a GOAL function and store it in the symbol with the given
 * name. This effectively creates a global GOAL function with the given name which calls the given C
 * function.
 *
 * This work on both Linux and Windows, but only supports up to 6 arguments.
 */
void* make_function_symbol_from_c(const char* name, void* f) {
  u32 *sym = intern_from_c(-1, 0, name);
  Function *func = make_function_from_c(f, false);
  *(Function **)((int)sym + -1) = func;
  return func;
}

/*!
 * Like make_function_symbol_from_c, but all 8 GOAL arguments are put into an array on the stack.
 * The address of this array is passed as the first and only argument to f.
 */
Ptr<Function> make_stack_arg_function_symbol_from_c(const char* name, void* f) {
  auto sym = intern_from_c(-1, 0, name);
  auto func = make_stack_arg_function_from_c(f);
  sym->value() = func.offset;
  return func;
}

u32 make_raw_function_symbol_from_c(const char* name, u32 value) {
  *(u32 *)((int)intern_from_c(-1, 0, name) + -1) = value;
  return value;
}

u32* set_fixed_symbol(FixedSymbolOffset offset, const char* name, u32 value) {
  int unaff_s7_lo;
  u32* sym = (u32*)(unaff_s7_lo + offset);
  *(u32*)((int)sym + -1) = value;
  kheaplogging = true;
  *(String **)((int)sym + (SymbolString - unaff_s7_lo)) = make_string_from_c(name);
  NumSymbols = NumSymbols + 1;
  kheaplogging = false;
  return sym;
}

u32* find_symbol_in_area(const char* name, u32 start, u32 end) {
  for (u32 i = start; i < end; i += 4) {
    int unaff_s7_lo;
    int str = *(int *)(i + (SymbolString - unaff_s7_lo));
    if ((str != 0) && !strcmp((char *)(iVar1 + 4), name)) {
      return (u32*)i;
    }
  }

  return nullptr;
}

#ifdef JAK3_HASH_TABLE
Ptr<Symbol4<u32>> find_symbol_from_c_ht(const char* name) {
  const auto& it = g_symbol_hash_table.find(name);
  if (it == g_symbol_hash_table.end()) {
    return Ptr<Symbol4<u32>>(0);
  } else {
    return Ptr<Symbol4<u32>>(s7.offset + it->second * 4);
  }
}

Ptr<Symbol4<u32>> find_slot_in_area(u32 start, u32 end) {
  for (u32 i = start; i < end; i += 4) {
    auto sym = Ptr<Symbol4<u32>>(i);
    auto str = sym_to_string(sym);
    if (!str.offset) {
      return sym;
    }
  }

  // failed
  return Ptr<Symbol4<u32>>(0);
}

Ptr<Symbol4<u32>> intern_from_c_ht(const char* name) {
  auto existing = find_symbol_from_c_ht(name);
  if (existing.offset) {
    return existing;
  }

  auto slot = find_slot_in_area(s7.offset, LastSymbol.offset);
  if (!slot.offset) {
    slot = find_slot_in_area(SymbolTable2.offset, s7.offset - 0x10);
  }
  ASSERT(slot.offset);  // out of symbols!!

  NumSymbols++;
  *sym_to_string_ptr(slot) = Ptr<String>(make_string_from_c(name));
  g_symbol_hash_table[name] = (slot.offset - s7.offset) / 4;
  return slot;
}

#endif

/*!
 * Get a pointer to a symbol. Can provide the symbol id, the name, or both.
 */
u32* find_symbol_from_c(uint16_t sym_id, const char* name) {
  u32 unaff_s7_lo;
  undefined4 unaff_s7_hi;
  int extended_sym_id = (int)(short)sym_id;
  if (sym_id == 0xffff) {
    if (name == nullptr) {
      MsgErr("dkernel: attempted to find symbol with NULL name and id #x%x\n", extended_sym_id);
      return nullptr;
    } else {
      u32* lookup_result = find_symbol_in_area(name,unaff_s7_lo,LastSymbol);
      if (lookup_result == nullptr) {
        lookup_result = find_symbol_in_area(name,SymbolTable2,unaff_s7_lo - 0x10);
      }

      if ((DebugSegment == 0) || ((long)*(int *)(unaff_s7_lo + 0x28f) != CONCAT44(unaff_s7_hi,unaff_s7_lo))) {
        if (lookup_result == nullptr) {
          MsgWarn("dkernel: doing a string->symbol on %s, but could not find the name\n", name);
        } else {
          int sym_string = *(int *)((int)lookup_result + (SymbolString - unaff_s7_lo));
          if ((sym_string == UnknownName) || (sym_string >= 1)) {
            MsgWarn(
                "dkernel: doing a string->symbol on %s, but the symbol has not been marked "
                "as symbol-export-string\n",
                name);
          }
        }
      }

      return lookup_result;
    }
  } else {
    u32* sym = (u32 *)(unaff_s7_lo + extended_sym_id + -1);
    if (sym != (u32 *)(unaff_s7_lo - 7)) {
      int existing_name = = *(int *)((int)sym + (SymbolString - unaff_s7_lo));
      if (existing_name != 0 && existing_name != UnknownName && strcmp((char *)(existing_name + 4), name)) { // TODO: Why not !strcmp in Jak X like Jak 3?
        MsgWarn(
            "dkernel: WARNING: attempting to find symbol %s at id #x%x but symbol %s was "
            "already there.\n",
            name, extended_sym_id, (char *)(existing_name + 4));
      }
    }
    return sym;
  }
}

/*!
 * Find or create a symbol.
 * New for Jak 3 is that there is no longer a symbol hash table. So there are some significant
 * changes to how this works. Also, many symbols do not store their name, to save memory.
 *
 * @param sym_id The symbol ID. This _must_ be provided if the symbol does not exist yet, or if the
 * symbol's name isn't known. Use -1 if the symbol ID is unknown.
 *
 * @param name The name. This can be used instead of the ID if the symbol's name is stored.
 *
 * @param flags Optional flag (0x40) can force the symbol's name to be stored. This uses memory.
 *
 */
u32* intern_from_c(int sym_id, int flags, const char* name) {
  u32* symbol = find_symbol_from_c((uint16_t)sym_id, name);
  kheaplogging = true;

  if (symbol == nullptr) {
    MsgErr("dkernel: attempted to intern symbol %s using the name, but could not find it\n",name);
    kheaplogging = false;
    return nullptr;
  }

  int unaff_s7_lo;
  if (symbol == (u32 *)(unaff_s7_lo + -7)) {
    kheaplogging = false;
    return symbol;
  }

  int* sptr = (int *)((int)symbol + (SymbolString - unaff_s7_lo));
  int current_string = *sptr;
  if (current_string != 0) {
    if ((flags & 0x40U) == 0) {
      kheaplogging = false;
      return symbol;
    }

    if ((current_string != UnknownName) &&
        (current_string < 1)) {
      kheaplogging = false;
      return symbol;
    }

    MsgWarn("dkernel: upgrading symbol %s (flags #x%x) from debug heap to global\n",name,flags);
    *sptr = make_string_from_c(name);
    kheaplogging = false;
    return symbol;
  }

  u64 new_string;
  if ((DebugSymbols == 0) && ((flags & 0x40U) == 0)) {
    if (DebugSegment == 0) {
      *sptr = UnknownName;
    } else {
      new_string = make_debug_string_from_c(name);
      *sptr = new_string;
    }
  } else {
    new_string = make_string_from_c(name);
    *sptr = new_string;
  }
  // *sptr = new_string;

  NumSymbols++;

  kheaplogging = false;
  return symbol;
}

u64 intern(u32 name) {
  return (long)(int)intern_from_c(-1, 0x40, (const char*)(name + 4));
}

/*!
 * Configure a type.
 */
Type* set_type_values(Type* type, Type* parent, u64 flags) {
  type->parent = parent;
  type->allocated_size = (u16)flags;
  type->heap_base = (u16)(flags >> 16);
  type->padded_size = (u16)flags + 0xf & 0xfff0;

  // ushort new_methods = type->num_methods;
  if ((ulong)type->num_methods < ((long)flags >> 32 & 0xffffU)) {
    type->num_methods = (ushort)(flags >> 32);;
  }

  return type;
}

static bool in_valid_memory_for_new_type(u32 addr) {
  if (SymbolTable2.offset <= addr && addr < 0x8000000) {
    return true;
  }

  if (addr < 0x100000 && addr >= 0x84000) {
    return true;
  }
  return false;
}
u32 size_of_type(u32 method_count) {
  return (4 * method_count + 0x23) & 0xfffffff0;
}

static bool is_valid_type(u32 addr) {
  if ((addr & 7) != 4) {
    return false;
  }

  if (*Ptr<u32>(addr - 4) != u32_in_fixed_sym(FIX_SYM_TYPE_TYPE)) {
    return false;
  }

  return true;
}

/*!
 * Given a symbol for the type name, allocate memory for a type and add it to the symbol table.
 * New: in Jak 2, there's a level type list
 * TBD
 */
Type* alloc_and_init_type(undefined* sym,
                          u32 method_count,
                          bool force_global_type) {
  u32 in_a3_lo;
  int unaff_s7_lo;
  kheaplogging = true;
  u32 u32_in_fixed_sym_FIX_SYM_TYPE_TYPE_ = *(u32 *)(unaff_s7_lo + 0x17);
  uint type_size = method_count * 4 + 0x23 & 0xfffffff0;
  u32 type_mem = 0;

  if (!force_global_type
      && *(int *)(unaff_s7_lo + 0xa7) != *(int *)(unaff_s7_lo + 0x9f)) {
    Type** type_list_ptr = *(Type ***)(LevelTypeList + -1);
    if (type_list_ptr == nullptr) {
      MsgErr("dkernel: trying to init loading level type \'%s\' while type-list is undefined\n",
             *(int *)(sym + (SymbolString - unaff_s7_lo)) + 4);
      type_mem = alloc_heap_object(unaff_s7_lo + 0xa0, u32_in_fixed_sym_FIX_SYM_TYPE_TYPE_, type_size, in_a3_lo);
      Type* the_type = (Type *)type_mem;
      *(Type **)(sym + -1) = the_type;
      the_type->allocated_size = (u16)type_size;
      the_type->padded_size = (u16)type_size;
      kheaplogging = false;
      return the_type;
    } else {
      type_mem = alloc_heap_object(unaff_s7_lo + 0xa8,
                                   u32_in_fixed_sym_FIX_SYM_TYPE_TYPE_, type_size, in_a3_lo);
      Type* old_head = *type_list_ptr;
      *type_list_ptr = (Type *)type_mem;
      type_mem->memusage_method = (Function *)old_head;
      Type* the_type = (Type *)type_mem;
      *(Type **)(sym + -1) = the_type;
      the_type->allocated_size = (u16)type_size;
      the_type->padded_size = (u16)type_size;
      kheaplogging = false;
      return the_type;
    }
  } else {
    type_mem = alloc_heap_object(unaff_s7_lo + 0xa0,
                                 u32_in_fixed_sym_FIX_SYM_TYPE_TYPE_, type_size, in_a3_lo);
  }

  Type* the_type = (Type *)type_mem;
  *(Type **)(sym + -1) = the_type;
  the_type->allocated_size = (u16)type_size;
  the_type->padded_size = (u16)type_size;
  kheaplogging = false;
  return the_type;
}

/*!
 * Like intern, but returns a type instead of a symbol. If the type doesn't exist, a new one is
 * allocated.
 */
Type* intern_type_from_c(int a, int b, const char* name, u64 methods) {
  Type** symbol = (Type **)intern_from_c((int)(short)a, b, name);
  Type* sym_value = *(Type **)((int)symbol + -1);
  if (sym_value == nullptr) {
    if (methods == 0) {
      methods = 0xc;
    } else if (methods == 1) {
      methods = 0x2c;
    }
    Type* type = alloc_and_init_type((undefined *)symbol,(u32)methods,false);
    type->symbol = symbol;
    type->num_methods = (u16)methods;
    return type;
  } else {
    Type* type = sym_value;
    if ((ulong)(long)(int)((uint)type->num_methods * 4 + 0x23 & 0xfffffff0) < (methods * 4 + 0x23 & 0xfffffff0)) {
      MsgErr(
          "dkernel: trying to redefine a type \'%s\' with %d methods when it had %d, try "
          "restarting\n",
          name, methods);
    }
    return type;
  }
}

/*!
 * Wrapper of intern_type_from_c to use with GOAL. It accepts a gstring as a name.
 */
Type* intern_type(u32 name, u64 methods) {
  return intern_type_from_c(-1, 0, (const char*)(name + 4), methods);
}

/*!
 * Setup a type which is located in a fixed spot of the symbol table.
 */
Type* set_fixed_type(FixedSymbolTypeOffset offset,
                     const char* name,
                     Symbol4 *parent_symbol,
                     u64 flags,
                     u32 print,
                     u32 inspect) {
  int unaff_s7_lo;
  kheaplogging = true;
  Type** type_symbol = (Type **)(unaff_s7_lo + offset);
  Type* symbol_value = *(Type **)((int)type_symbol + -1);

  kheaplogging = false;
  *(String **)((int)type_symbol + (SymbolString - unaff_s7_lo)) = make_string_from_c(name);
  NumSymbols++;

  if (symbol_value == nullptr) {
    symbol_value = alloc_and_init_type((undefined *)type_symbol, (uint)(flags >> 0x20) & 0xffff, true);
  }

  symbol_value->symbol = type_symbol;
  symbol_value[-1].memusage_method = *(Function **)(unaff_s7_lo + 0x17);

  Type* parent_type = *(Type **)((int)parent_type_symbol + -1);
  set_type_values(symbol_value, parent_type, flags);

  symbol_value->new_method = parent_type->new_method;
  symbol_value->delete_method = parent_type->delete_method;

  if (print == 0) {
    symbol_value->print_method = (u32)parent_type->print_method;
  } else {
    symbol_value->print_method = (Function *)print;
  }

  if (inspect == 0) {
    symbol_value->inpsect_method = (u32)parent_type->inpsect_method;
  } else {
    symbol_value->inpsect_method = (Function *)inspect;
  }

  symbol_value->length_method = *(Function **)(unaff_s7_lo + 0xbf);
  symbol_value->asize_of_method = parent_type->asize_of_method;
  symbol_value->copy_method = parent_type->copy_method;
  return symbol_value;
}

// TBD
Type * new_type(u32 symbol, u32 parent, u64 flags) {
  ushort uVar1;
  Function *pFVar2;
  Type *pTVar3;
  const char* name;
  long lVar4;
  int iVar5;
  ulong uVar6;
  Function **ppFVar7;
  ulong methods;
  int iVar8;
  int unaff_s7_lo;
  undefined4 unaff_s7_hi;
  
  methods = (long)flags >> 0x20 & 0xffff;
  iVar8 = symbol - unaff_s7_lo;
  uVar1 = *(ushort *)(parent + 0xe);
  name = (const char* )(*(int *)(iVar8 + SymbolString) + 4);
  if (*(int *)(iVar8 + SymbolString) == 0) {
    name = (const char* )0x0;
  }
  if (methods == 0) {
    methods = 0xc;
  }
  pTVar3 = intern_type_from_c((iVar8 + 1) * 0x10000 >> 0x10,0x80,name,methods);
  pFVar2 = pTVar3->memusage_method;
  uVar6 = (ulong)(int)pFVar2;
  if (methods != 0) {
    lVar4 = 0;
    ppFVar7 = &pTVar3->new_method;
    iVar5 = 0;
    do {
      if (lVar4 < (long)(ulong)uVar1) {
        *ppFVar7 = *(Function **)(iVar5 + parent + 0x10);
      }
      else {
        *ppFVar7 = (Function *)0x0;
      }
      lVar4 = (long)((int)lVar4 + 1);
      ppFVar7 = ppFVar7 + 1;
      iVar5 = iVar5 + 4;
    } while (lVar4 < (long)methods);
  }
  if (*(int *)(unaff_s7_lo + 0xa7) == *(int *)(unaff_s7_lo + 0x9f)) {
    if (uVar6 != 0) {
      if (uVar6 == CONCAT44(unaff_s7_hi,unaff_s7_lo)) {
        pTVar3->memusage_method = pFVar2;
      }
      else if (((((ulong)(long)SymbolTable2 <= uVar6) && (uVar6 < 0x8000000)) ||
               (pFVar2 + -0x84000 < (Function *)0x7c000)) &&
              (((uVar6 & 7) == 4 && (*(int *)(pFVar2 + -4) == *(int *)(unaff_s7_lo + 0x17))))) {
        pTVar3->memusage_method = pFVar2;
      }
    }
  } else if (uVar6 == 0) {
    MsgWarn("dkernel: loading-level init of type %s, but was interned global (this is okay)\n",
            *(int *)(iVar8 + SymbolString) + 4);
  } else {
    pTVar3->memusage_method = pFVar2;
  }
  Type* ret = set_type_values(pTVar3, (Type *)parent, flags);
  return ret;
}

/*!
 * Is t1 a t2?
 */
u64 type_typep(Type* t1, Type* t2) {
  int unaff_s7_lo;
  if (t1 != t2) {
    for (Type *t1_ = t1->parent; t1_ != t2; t1_ = t1_->parent) {
      if (t1_ == nullptr || t1_ == *(Type **)(unaff_s7_lo + 0x1b)) {
        undefined4 unaff_s7_hi;
        return CONCAT44(unaff_s7_hi, unaff_s7_lo);
      }
    }
  }
  return (long)(unaff_s7_lo + 4);
}

// TBD
u64 method_set(u32 type_, u32 method_id, u32 method) {
  Type *pTVar2;
  u64 uVar4;
  int unaff_s7_lo;
  undefined4 unaff_s7_hi;
  
  u64 method_ = (u64)(int)method;
  int iVar7 = method_id * 4;
  Function* pFVar1 = *(Function **)(iVar7 + type_ + 0x10);
  ulong uVar8 = CONCAT44(unaff_s7_hi,unaff_s7_lo);
  if (method_ == 1) {
    method_ = 0;
  } else if (method_ == 0) {
    return 0;
  }
  else if (method_ == 2) {
    method_ = (u64)*(int *)(iVar7 + *(int *)(type_ + 4) + 0x10);
  }
  Function* pFVar5 = (Function *)method_;
  *(Function **)(iVar7 + type_ + 0x10) = pFVar5;
  if (*EnableMethodSet != 0 || (FastLink == false && MasterDebug != 0 && DiskBoot == 0)) {
    if (uVar8 < (ulong)(long)LastSymbol) {
      do {
        iVar7 = (int)uVar8;
        pTVar2 = *(Type **)(iVar7 + -1);
        if (((((SymbolTable2 <= pTVar2) && (pTVar2 < (Type *)0x8000000)) ||
             (&pTVar2[-0x289e].print_method < (Function **)0x7c000)) &&
            ((((uint)pTVar2 & 7) == 4 &&
             (pTVar2[-1].memusage_method == *(Function **)(unaff_s7_lo + 0x17))))) &&
           (((int)method_id < (int)(uint)pTVar2->num_methods &&
            (((&pTVar2->new_method)[method_id] == pFVar1 &&
             (uVar4 = type_typep(pTVar2,(Type *)type_), uVar4 != CONCAT44(unaff_s7_hi,unaff_s7_lo)))
            )))) {
          if (FastLink != false) {
            printf("************ WARNING **************\n");
            printf("method %d of %s redefined - you must define class heirarchies in order now\n",
                   method_id,*(int *)((iVar7 - unaff_s7_lo) + SymbolString) + 4);
            printf("***********************************\n");
          }
          (&pTVar2->new_method)[method_id] = pFVar5;
        }
        uVar8 = (ulong)(iVar7 + 4);
      } while (uVar8 < (ulong)(long)LastSymbol);
    }
    
    uVar8 = (ulong)(int)SymbolTable2;
    if (uVar8 < CONCAT44(unaff_s7_hi,unaff_s7_lo)) {
      do {
        iVar7 = (int)uVar8;
        pTVar2 = *(Type **)(iVar7 + -1);
        if (((pTVar2 < SymbolTable2) || ((Type *)0x7ffffff < pTVar2)) &&
           ((Function **)0x7bfff < &pTVar2[-0x289e].print_method)) {
          uVar8 = (ulong)(iVar7 + 4);
        }
        else if (((uint)pTVar2 & 7) == 4) {
          if (pTVar2[-1].memusage_method == *(Function **)(unaff_s7_lo + 0x17)) {
            if ((int)method_id < (int)(uint)pTVar2->num_methods) {
              if ((&pTVar2->new_method)[method_id] != pFVar1) {
                uVar8 = (ulong)(iVar7 + 4);
                goto LAB_0026c6c8;
              }
              uVar4 = type_typep(pTVar2,(Type *)type_);
              if (uVar4 != CONCAT44(unaff_s7_hi,unaff_s7_lo)) {
                if (FastLink == false) {
                  (&pTVar2->new_method)[method_id] = pFVar5;
                }
                else {
                  printf("************ WARNING **************\n");
                  printf("method %d of %s redefined - you must define class heirarchies in order now\n"
                         ,method_id,*(int *)((iVar7 - unaff_s7_lo) + SymbolString) + 4);
                  printf("***********************************\n");
                  (&pTVar2->new_method)[method_id] = pFVar5;
                }
              }
            }
            uVar8 = (ulong)(iVar7 + 4);
          }
          else {
            uVar8 = (ulong)(iVar7 + 4);
          }
        }
        else {
          uVar8 = (ulong)(iVar7 + 4);
        }
LAB_0026c6c8:
      } while (uVar8 < CONCAT44(unaff_s7_hi,unaff_s7_lo));
    }
  }
  return method_;
}

/*!
 * Call a GOAL method of a given type.
 */
u64 call_method_of_type(u32 arg, Type* type, u32 method_id) {
  u64 arg_ = (u64)(int)arg;
  if ((((type < SymbolTable2) || ((Type *)0x7ffffff < type)) &&
       ((Function **)0x7bfff < &type[-0x289e].print_method))
      || (((uint)type & 7) != 4)) {
    cprintf("#<#x%x has invalid type ptr #x%x>\n", arg_, type);
  } else {
    int unaff_s7_lo;
    Type* type_tag = (Type *)type[-1].memusage_method;
    if (type_tag == *(Type **)(unaff_s7_lo + 0x17)) {
      return (*(code *)(&type->new_method)[method_id])(arg_,arg_,type_tag);
    } else {
      cprintf("#<#x%x has invalid type ptr #x%x, bad type #x%x>\n", arg_, // TODO: why is type not in this list?
              type_tag);
    }
  }
  return arg_;
}

/*!
 * Call a GOAL function with 2 arguments.
 */
u64 call_goal_function_arg2(Function* func, u64 a, u64 b) {
  return (*(code *)func)(a, b);
}

/*!
 * Call a global GOAL function by name.
 */
u64 call_goal_function_by_name(const char* name) {
  return call_goal_function(*(Function **)((int)intern_from_c(-1, 0, name) + -1));
}

u64 print_object(u32 obj);
u64 print_pair(u32 obj);
u64 print_symbol(u32 obj);

/*!
 * Print an object with a newline after it to the GOAL PrintBuffer (not stdout)
 */
u64 sprint(u32 obj) {
  u64 rv = print_object(obj);
  cprintf("\n");
  return rv;
}

/*!
 * Like call_method_of_type, but has two arguments. Used to "relocate" v2/s4 loads.
 */
u64 call_method_of_type_arg2(u32 arg, Type* type, u32 method_id, u32 a1, u32 a2) {
  u64 arg_ = (u64)(int)arg;
  if ((((type < SymbolTable2) || ((Type *)0x7ffffff < type)) &&
       ((Function **)0x7bfff < &type[-0x289e].print_method))
      || (((uint)type & 7) != 4)) {
    cprintf("#<#x%x has invalid type ptr #x%x>\n", arg_, type);
  } else {
    int unaff_s7_lo;
    Type* type_tag = (Type *)type[-1].memusage_method;
    if (type_tag == *(Type **)(unaff_s7_lo + 0x17)) {
      return (*(code *)(&type->new_method)[method_id])(arg_,a1,a2);
    } else {
      cprintf("#<#x%x has invalid type ptr #x%x, bad type #x%x>\n", arg_,
              type_tag);
    }
  }
  return arg_;
}

/*!
 * Most generic printing method.
 * Does not correctly handle 64 bit boxed integers or object64's correctly.
 * It is important that no objects of type object actually exist or this will loop!
 */
u64 print_object(u32 obj) {
  u64 obj_ = (u64)(int)obj;
  if ((obj_ & 7) == 0) {
    return (u64)(int)print_binteger((ulong)obj);
  } else {
    if ((obj_ < (ulong)(long)SymbolTable2 || 0x7ffffff < obj_) &&
        (0x7bfff < obj - 0x84000)) {
    cprintf("#<invalid object #x%x>",obj_);
    } else if ((obj_ & 7) == 2) {
      return print_pair(obj);
    } else if ((obj_ & 1 != 0) && (ulong)(long)SymbolTable2 <= obj_ &&
               obj_ < (ulong)(long)LastSymbol) {
      return print_symbol(obj);
    } else if ((obj_ & 7) == 4) {
      return call_method_of_type(obj,*(Type **)(obj - 4),2);
    } else {
      cprintf("#<unknown type %d @ #x%x>", obj_ & 7, obj_);
    }
  }
  return obj_;
}

/*!
 * Default print method a basic.
 * Confirms basic is valid and prints the type name.
 */
u64 print_basic(u32 obj) {
  int unaff_s7_lo;
  undefined4 unaff_s7_hi;
  ulong obj_ = (ulong)(int)obj;
  if (((obj_ < (ulong)(long)SymbolTable2 || 0x7ffffff < obj_) &&
       (0x7bfff < obj - 0x84000))
      || ((obj_ & 7) != 4)) {
    if (obj_ == CONCAT44(unaff_s7_hi,unaff_s7_lo)) {
      cprintf("#f");
    } else {
      cprintf("#<invalid basic #x%x>",obj_);
    }
  } else {
    cprintf("#<%s @ #x%x>",*(int *)((**(int **)(obj - 4) - unaff_s7_lo) + SymbolString) + 4, (ulong)obj);
  }
  return obj_;
}

/*!
 * Print a pair as a LISP list.  Don't try to print circular lists or it will get stuck
 * Can print improper lists
 * TBD
 */
u64 print_pair(u32 obj) {
  uint uVar1;
  char *format;
  u32 obj_00;
  ulong uVar3;
  int unaff_s7_lo;
  undefined4 unaff_s7_hi;
  
  ulong obj_ = (ulong)(int)obj;
  if (obj_ == (long)(unaff_s7_lo + -7)) {
    cprintf("()");
  }
  else {
    if (((((long)*(int *)(CollapseQuote + -1) != CONCAT44(unaff_s7_hi,unaff_s7_lo)) &&
         ((obj_ & 7) == 2)) && (*(int *)(obj - 2) == unaff_s7_lo + 0xe8)) &&
       ((uVar1 = *(uint *)(obj + 2), (uVar1 & 7) == 2 &&
        ((long)*(int *)(uVar1 + 2) == (long)(unaff_s7_lo + -7))))) {
      cprintf("\'");
      print_object(*(u32 *)(uVar1 - 2));
      return obj_;
    }
    cprintf("(");
    uVar3 = obj_;
    while (obj_00 = (u32)uVar3, (uVar3 & 7) == 2) {
      print_object(*(u32 *)(obj_00 - 2));
      uVar3 = (ulong)*(int *)(obj_00 + 2);
      if (uVar3 == (long)(unaff_s7_lo + -7)) {        
        cprintf(")");
        return obj_;
      }
      cprintf(" ");
    }
    cprintf(". ");
    print_object(obj_00);
    cprintf(")");
  }
  return obj_;
}

/*!
 * Print method for symbol.  Just prints the name without quotes or anything fancy.
 * TBD
 */
u64 print_symbol(u32 obj) {
  int unaff_s7_lo;
  ulong obj_ = (ulong)(int)obj;
  if ((((ulong)(long)SymbolTable2 <= obj_ && obj_ < 0x8000000)
        || obj - 0x84000 < 0x7c000)
      && ((obj_ ^ 1) & 1) == 0) {
    if (obj_ < (ulong)(long)SymbolTable2) {
      cprintf("#<invalid symbol #x%x>", obj_);
      return obj_;
    } else if (obj_ < (ulong)(long)LastSymbol) {
      ulong str = obj_;
      str = (ulong)(*(int *)((obj - unaff_s7_lo) + SymbolString) + 4);
      cprintf("%s", str);
      return obj_;
    }
  }
  cprintf("#<invalid symbol #x%x>", obj_);
  return obj_;
}

/*!
 * Print method for type.  Just prints the name without quotes
 */
u64 print_type(u32 obj) {
  int unaff_s7_lo;
  ulong obj_ = (ulong)(int)obj;
  if (((obj_ < (ulong)(long)SymbolTable2 || 0x7ffffff < obj_) &&
       (0x7bfff < obj - 0x84000))
      || ((obj_ & 7) != 4 || (*(int *)(obj - 4) != *(int *)(unaff_s7_lo + 0x17)))) {
    cprintf("#<invalid type #x%x>", obj_);
  } else {
    cprintf("%s", (long)(*(int *)((*(int *)obj - unaff_s7_lo) + SymbolString) + 4));
  }
  return obj_;
}

/*!
 * Print method for string.  Prints the string in quotes.
 */
u64 print_string(u32 obj) {
  int unaff_s7_lo;
  undefined4 unaff_s7_hi;
  ulong obj_ = (ulong)(int)obj;
  if ((((obj_ < (ulong)(long)SymbolTable2) || (0x7ffffff < obj_)) && (0x7bfff < obj - 0x84000)) ||
     (((obj_ & 7) != 4 || (*(int *)(obj - 4) != *(int *)(unaff_s7_lo + 0xf))))) {
    if (obj_ == CONCAT44(unaff_s7_hi,unaff_s7_lo)) {
      cprintf("#f");

    } else {
      cprintf("#<invalid string #x%x>", obj_);
    }
  } else {
    cprintf("\"%s\"", (ulong)(int)(obj + 4));
  }
  return obj_;
}

/*!
 * Print method for function. Just prints the address because functions can't identify themselves.
 */
u64 print_function(u32 obj) {
  int unaff_s7_lo;
  cprintf("#<compiled %s @ #x%x>", *(int *)((**(int **)(obj - 4) - unaff_s7_lo) + SymbolString) + 4,
          (long)(int)obj);
  return (long)(int)obj;
}

/*!
 * Get the allocated size field of a basic.  By default we grab this from the type struct.
 * Dynamically sized basics should override this method.
 */
u64 asize_of_basic(u32 it) {
  return (ulong)*(ushort *)(*(int *)(it - 4) + 8);
}

/*!
 * Create a copy of a basic.  If the destination isn't identified as a symbol, treat it as an
 * address. This seems a little bit unsafe to me, as it reads the 4-bytes before the given address
 * and checks it against the symbol type pointer to see if its a symbol. It seems possible to have a
 * false positive for this check.
 */
u64 copy_basic(u32 obj, u32 heap, u32 unused, u32 pp) {
  u64 heap_ = (u64)(int)heap;
  u64 size = call_method_of_type(obj, *(Type **)(obj - 4), 5);
  u64 result;

  if ((heap_ & 1) != 0) {
    result = alloc_heap_object(heap, *(u32 *)(obj - 4), (u32)size, pp);
    memcpy((void *)result, (void *)obj, (u64)(int)((u32)size - 4));
  } else {
    memcpy((void *)(heap - 4), (void *)(obj - 4), size);
    result = heap_;
  }
  return result;
}

u64 inspect_pair(u32 obj);
u64 inspect_symbol(u32 obj);
/*!
 * Highest level inspect method. Won't inspect 64-bit bintegers correctly.
 */
u64 inspect_object(u32 obj) {
  u64 obj_ = (u64)(int)obj;
  if (obj_ & 7 == 0) {
    return (u64)(int)inspect_binteger((ulong)obj);
  } else {
    if (((obj_ < (ulong)(long)SymbolTable2) || (0x7ffffff < obj_)) &&
        (0x7bfff < obj - 0x84000)) {
      cprintf("#<invalid object #x%x>\n", obj_);
    } else if (obj_ & 7 == 2) {
      return inspect_pair(obj);
    } else if ((obj_ & 1) != 0 && (ulong)(long)SymbolTable2 <= obj_ &&
               obj_ < (ulong)(long)LastSymbol) {
      return inspect_symbol(obj);
    } else if (obj_ & 7 == 4) {
      return call_method_of_type(obj, *(Type **)(obj - 4),
                                 3);
    } else {
      cprintf("#<unknown type %d @ #x%x>", obj_ & 7, obj_);
    }
  }
  return obj_;
}

/*!
 * Inspect a pair.
 */
u64 inspect_pair(u32 obj) {
  cprintf("[%8x] pair ", (long)(int)obj);
  print_pair(obj);
  cprintf("\n");
  return (long)(int)obj;
}

/*!
 * Inspect a string. There's a typo in allocated_length (has underscore instead of dash).
 * This typo is fixed in later games.
 */
u64 inspect_string(u32 obj) {
  int unaff_s7_lo;
  ulong obj_ = (ulong)(int)obj;
  if (((obj_ < (ulong)(long)SymbolTable2 || 0x7ffffff < obj_) &&
      (0x7bfff < obj - 0x84000))
      || ((obj_ & 7) != 4 ||
      *(int *)(obj - 4) != *(int *)(unaff_s7_lo + 0xf))) {
    cprintf("#<invalid string #x%x>\n",obj_);
  } else {
    const char* str = (const char*)obj;
    cprintf("[%8x] string\n\tallocated-length: %d\n\tdata: \"%s\"\n", obj_, *(undefined4 *)str, str + 4);
  }
  return obj_;
}

/*!
 * Inspect a symbol.
 */
u64 inspect_symbol(u32 obj) {
  int unaff_s7_lo;  
  ulong obj_ = (ulong)(int)obj;
  if (((obj_ < (ulong)(long)SymbolTable2 || 0x7ffffff < obj_) &&
       (0x7bfff < obj - 0x84000))
      || ((obj_ ^ 1) & 1) != 0 || obj_ < (ulong)(long)SymbolTable2 || (ulong)(long)LastSymbol <= obj_) {
    cprintf("#<invalid symbol #x%x>\n", obj_);
  } else {
    cprintf("[%8x] symbol\n\tname: %s\n\tvalue: ", obj_, *(int *)((obj - unaff_s7_lo) + SymbolString) + 4);
    print_object(*(u32 *)(obj - 1));
    cprintf("\n");
  }
  return obj_;
}

/*!
 * Inspect a type.
 */
u64 inspect_type(u32 obj) {
  int unaff_s7_lo;
  ulong obj_ = (ulong)(int)obj;
  if (((obj_ < (ulong)(long)SymbolTable2 || 0x7ffffff < obj_) &&
       (0x7bfff < obj - 0x84000))
      || ((obj_ & 7) != 4 ||
      *(int *)(obj - 4) != *(int *)(unaff_s7_lo + 0x17))) {
    cprintf("#<invalid type #x%x>\n",obj_);
  } else {
    Type* typ = (Type*)obj;

    cprintf("[%8x] type\n\tname: %s\n\tparent: ", obj_, *(int *)((int)typ->symbol + (SymbolString - unaff_s7_lo)) + 4);
    print_object((u32)typ->parent);
    cprintf("\n\tsize: %d/%d\n\theap-base: %d\n\tallocated-length: %d\n\tprint: ",
            (ulong)typ->allocated_size, (ulong)typ->padded_size, (ulong)typ->heap_base, (ulong)typ->num_methods);
    print_object((u32)typ->print_method);
    cprintf("\n\tinspect: ");
    print_object((u32)typ->inpsect_method);
    cprintf("\n\tmem-usage: ");
    print_object((u32)typ->memusage_method);
    cprintf("\n");
  }
  return obj_;
}

/*!
 * Inspect a basic. This is just a fallback for basics which don't know how to inspect themselves.
 * We just use print_object.
 */
u64 inspect_basic(u32 obj) {
  ulong unaff_s7;
  ulong obj_ = (ulong)(int)obj;
  if (((obj_ < (ulong)(long)SymbolTable2 || 0x7ffffff < obj_) &&
       (0x7bfff < obj - 0x84000))
      || ((obj_ & 7) != 4)) {
    if (obj_ == unaff_s7) {
      return inspect_symbol(obj);
    } else {
      cprintf("#<invalid basic #x%x>\n", obj_);
    }
  } else {
    cprintf("[%8x] ", obj_);
    print_object(*(u32*)(obj - 4));
    cprintf("\n");
  }
  return obj_;
}

/*!
 * Inspect a link block. This link block doesn't seem to be used at all.
 */
u64 inspect_link_block(u32 ob) {
  struct LinkBlock {
    u32 length;
    u32 version;
  };

  LinkBlock* lb = (LinkBlock*)ob;
  cprintf("[%8x] link-block\n\tallocated-length: %d\n\tversion: %d\n\tfunction: ", ob, lb->length,
          *(short *)&lb->version);
  print_object((int)&lb->length + lb->length);
  cprintf("\n");
  return ob;
}

namespace {
Ptr<Symbol4<Ptr<Type>>> get_fixed_type_symbol(u32 offset) {
  return (s7 + offset).cast<Symbol4<Ptr<Type>>>();
}

u64 pack_type_flag(u64 methods, u64 heap_base, u64 size) {
  return (methods << 32) + (heap_base << 16) + (size);
}
}  // namespace

int InitHeapAndSymbol() {
  u8 *symbol_table;
  u8 *SymbolString_;
  u8 *value;
  Type *iVar1;
  Type *iVar16;
  Type *iVar17;
  Type *iVar18;
  Type *iVar10;
  Type *iVar19;
  Type *iVar20;
  Type *iVar10_00;
  Type *iVar10_01;
  Type *iVar10_02;
  Type *iVar10_03;
  Type *iVar12;
  Type *iVar11;
  Type *iVar13;
  Type *iVar14;
  Type *iVar15;
  
  symbol_table =
      kmalloc(&kglobalheapinfo, 0x10000, 0x1000, "symbol-table");
  SymbolString_ =
      kmalloc(&kglobalheapinfo, 0x10000, 0x1000, "string-table");
  SymbolString = SymbolString_ + 0x8000;
  LastSymbol = symbol_table + 0xff00;
  SymbolTable2 = symbol_table + 5;
  value = symbol_table + 0x8001;
  NumSymbols = 0;
  reset_output();
  *(u8 **)(symbol_table + 0x7ff8) = symbol_table + 0x7ffa;
  *(kheapinfo **)(symbol_table + 0x80a0) = &kglobalheapinfo;
  *(u8 **)(symbol_table + 0x7ffc) = symbol_table + 0x7ffa;

  UnknownName = (undefined4)make_string_from_c("*unknown-symbol-name*");
  alloc_and_init_type(symbol_table + 0x8019, 9, true);
  alloc_and_init_type(symbol_table + 0x8015, 9, true);
  alloc_and_init_type(symbol_table + 0x8011, 9, true);
  alloc_and_init_type(symbol_table + 0x8009, 9, true);

  set_fixed_symbol(FIX_SYM_FALSE, "#f", (u32)value);
  set_fixed_symbol(FIX_SYM_TRUE, "#t", (u32)(symbol_table + 0x8005));
  set_fixed_symbol(FIX_SYM_NOTHING_FUNC, "nothing", make_nothing_func());
  set_fixed_symbol(FIX_SYM_ZERO_FUNC, "zero-func", make_zero_func());
  set_fixed_symbol(FIX_SYM_ASIZE_OF_BASIC_FUNC, "asize-of-basic-func",
                   (u32)make_function_from_c(asize_of_basic, (bool)0x60));
  set_fixed_symbol(FIX_SYM_COPY_BASIC_FUNC, "asize-of-basic-func",
                   (u32)make_function_from_c(copy_basic, (bool)0x20));
  set_fixed_symbol(FIX_SYM_DELETE_BASIC, "delete-basic",
                   (u32)make_function_from_c(delete_basic, (bool)0x20));
  set_fixed_symbol(FIX_SYM_GLOBAL_HEAP, "global", (u32)&kglobalheapinfo);
  set_fixed_symbol(FIX_SYM_DEBUG, "debug", (u32)kdebugheap);
  set_fixed_symbol(FIX_SYM_STATIC, "static", (u32)(symbol_table + 0x809d));
  set_fixed_symbol(FIX_SYM_LOADING_LEVEL, "loading-level", (u32)&kglobalheapinfo);
  set_fixed_symbol(FIX_SYM_LOADING_PACKAGE, "loading-package", (u32)&kglobalheapinfo);
  set_fixed_symbol(FIX_SYM_PROCESS_LEVEL_HEAP, "process-level-heap", (u32)&kglobalheapinfo);
  set_fixed_symbol(FIX_SYM_STACK, "stack", (u32)(symbol_table + 0x80b5));
  set_fixed_symbol(FIX_SYM_SCRATCH, "scratch", (u32)(symbol_table + 0x80b9));
  set_fixed_symbol(FIX_SYM_SCRATCH_TOP, "*scratch-top*", 0x70000000);
  set_fixed_symbol(FIX_SYM_LEVEL, "level", 0);
  set_fixed_symbol(FIX_SYM_ART_GROUP, "art-group", 0);
  set_fixed_symbol(FIX_SYM_TEXTURE_PAGE_DIR, "texture-page-dir", 0);
  set_fixed_symbol(FIX_SYM_TEXTURE_PAGE, "texture-page", 0);

  set_fixed_symbol(FIX_SYM_SOUND, "sound", 0);
  set_fixed_symbol(FIX_SYM_DGO, "dgo", 0);
  set_fixed_symbol(FIX_SYM_TOP_LEVEL, "top-level", *(u32 *)(symbol_table + 0x8094));
  set_fixed_symbol(FIX_SYM_QUOTE, "quote", (u32)(symbol_table + 0x80e9));
  set_fixed_symbol(FIX_SYM_LISTENER_LINK_BLOCK, "*listener-link-block*", 0);
  set_fixed_symbol(FIX_SYM_LISTENER_FUNCTION, "*listener-function*", 0x0);
  set_fixed_symbol(FIX_SYM_STACK_TOP, "*stack-top*", 0x0);
  set_fixed_symbol(FIX_SYM_STACK_BASE, "*stack-base*", 0x0);
  set_fixed_symbol(FIX_SYM_STACK_SIZE, "*stack-size*", 0x0);
  set_fixed_symbol(FIX_SYM_KERNEL_FUNCTION, "*kernel-function*", 0x0);
  set_fixed_symbol(FIX_SYM_KERNEL_PACKAGES, "*kernel-packages*", 0x0);
  set_fixed_symbol(FIX_SYM_KERNEL_BOOT_MESSAGE, "*kernel-boot-message*", 0x0);
  set_fixed_symbol(FIX_SYM_KERNEL_BOOT_MODE, "*kernel-boot-mode*", 0x0);
  set_fixed_symbol(FIX_SYM_KERNEL_BOOT_LEVEL, "*kernel-boot-level*", 0x0);
  set_fixed_symbol(FIX_SYM_KERNEL_BOOT_ART_GROUP, "*kernel-boot-art-group*", 0x0);
  set_fixed_symbol(FIX_SYM_KERNEL_DEBUG, "*kernel-debug*", 0x0);
  set_fixed_symbol(FIX_SYM_KERNEL_VERSION, "*kernel-version*", 0x0);
  set_fixed_symbol(FIX_SYM_KERNEL_DISPATCHER, "kernel-dispatcher", 0x0);
  set_fixed_symbol(FIX_SYM_SYNC_DISPATCHER, "sync-dispatcher", 0x0);
  set_fixed_symbol(FIX_SYM_PRINT_COLLUMN, "*print-column*", 0x0);
  set_fixed_symbol(FIX_SYM_DEBUG_SEGMENT, "*debug-segment*", 0x0);
  set_fixed_symbol(FIX_SYM_ENABLE_METHOD_SET, "*enable-method-set*", 0x0);
  set_fixed_symbol(FIX_SYM_SQL_RESULT, "*sql-result*", 0x0);
  set_fixed_symbol(FIX_SYM_COLLAPSE_QUOTE, "*collapse-quote*", 0x0);
  set_fixed_symbol(FIX_SYM_LEVEL_TYPE_LIST, "*level-type-list*", 0x0);
  set_fixed_symbol(FIX_SYM_DECI_COUNT, "*deci-count*", 0x0);
  set_fixed_symbol(FIX_SYM_USER, "*user*", 0x0);
  set_fixed_symbol(FIX_SYM_VIDEO_MODE, "*video-mode*", 0x0);
  set_fixed_symbol(FIX_SYM_BOOT_VIDEO_MODE, "*boot-video-mode*", 0x0);
  set_fixed_symbol(FIX_SYM_BOOT, "boot", 0x0);
  set_fixed_symbol(FIX_SYM_DEMO, "demo", 0x0);
  set_fixed_symbol(FIX_SYM_DEMO_SHARED, "demo-shared", 0x0);
  set_fixed_symbol(FIX_SYM_PREVIEW, "preview", 0x0);
  set_fixed_symbol(FIX_SYM_KIOSK, "kiosk", 0x0);
  set_fixed_symbol(FIX_SYM_BETA, "beta", 0x0);
  set_fixed_symbol(FIX_SYM_PLAY_BOOT, "play-boot", 0x0);
  set_fixed_symbol(FIX_SYM_SIN, "sin", 0x0);
  set_fixed_symbol(FIX_SYM_COS, "cos", 0x0);
  set_fixed_symbol(FIX_SYM_PUT_DISPLAY_ENV, "put-display-env", 0x0);
  set_fixed_symbol(FIX_SYM_SYNCV, "syncv", 0x0);
  set_fixed_symbol(FIX_SYM_SYNC_PATH, "sync-path", 0x0);

  set_fixed_symbol(FIX_SYM_RESET_PATH, "reset-path", 0x0);
  set_fixed_symbol(FIX_SYM_RESET_GRAPH, "reset-graph", 0x0);
  set_fixed_symbol(FIX_SYM_DMA_SYNC, "dma-sync", 0x0);
  set_fixed_symbol(FIX_SYM_GS_PUT_IMR, "gs-put-imr", 0x0);
  set_fixed_symbol(FIX_SYM_GS_GET_IMR, "gs-get-imr", 0x0);
  set_fixed_symbol(FIX_SYM_GS_STORE_IMAGE, "gs-store-image", 0x0);
  set_fixed_symbol(FIX_SYM_FLUSH_CACHE, "flush-cache", 0x0);
  set_fixed_symbol(FIX_SYM_CPAD_OPEN, "cpad-open", 0x0);
  set_fixed_symbol(FIX_SYM_CPAD_GET_DATA, "cpad-get-data", 0x0);
  set_fixed_symbol(FIX_SYM_MOUSE_GET_DATA, "mouse-get-data", 0x0);
  set_fixed_symbol(FIX_SYM_KEYBD_GET_DATA, "keybd-get-data", 0x0);
  set_fixed_symbol(FIX_SYM_INSTALL_HANDLER, "install-handler", 0x0);
  set_fixed_symbol(FIX_SYM_INSTALL_DEBUG_HANDLER, "install-debug-handler", 0x0);
  set_fixed_symbol(FIX_SYM_FILE_STREAM_OPEN, "file-stream-open", 0x0);
  set_fixed_symbol(FIX_SYM_FILE_STREAM_CLOSE, "file-stream-close", 0x0);
  set_fixed_symbol(FIX_SYM_FILE_STREAM_LENGTH, "file-stream-length", 0x0);
  set_fixed_symbol(FIX_SYM_FILE_STREAM_SEEK, "file-stream-seek", 0x0);
  set_fixed_symbol(FIX_SYM_FILE_STREAM_READ, "file-stream-read", 0x0);
  set_fixed_symbol(FIX_SYM_FILE_STREAM_WRITE, "file-stream-write", 0x0);
  // set_fixed_symbol(FIX_SYM_FILE_STREAM_WRITE, "file-stream-write", 0x0);
  set_fixed_symbol(FIX_SYM_FILE_STREAM_MKDIR, "file-stream-mkdir", 0x0);
  set_fixed_symbol(FIX_SYM_SCF_GET_LANGUAGE, "scf-get-language", 0x0);
  set_fixed_symbol(FIX_SYM_SCF_GET_TIME, "scf-get-time", 0x0);
  set_fixed_symbol(FIX_SYM_SCF_GET_ASPECT, "scf-get-aspect", 0x0);
  set_fixed_symbol(FIX_SYM_SCF_GET_VOLUME, "scf-get-volume", 0x0);
  set_fixed_symbol(FIX_SYM_SCF_GET_TERRITORY, "scf-get-territory", 0x0);
  set_fixed_symbol(FIX_SYM_SCF_GET_TIMEOUT, "scf-get-timeout", 0x0);
  set_fixed_symbol(FIX_SYM_SCF_GET_INACTIVE_TIMEOUT, "scf-get-inactive-timeout", 0x0);
  set_fixed_symbol(FIX_SYM_DMA_TO_IOP, "dma-to-iop", 0x0);
  set_fixed_symbol(FIX_SYM_KERNEL_SHUTDOWN, "kernel-shutdown", 0x0);
  set_fixed_symbol(FIX_SYM_AYBABTU, "aybabtu", 0x0);
  set_fixed_symbol(FIX_SYM_STRING_TO_SYMBOL, "string->symbol", 0x0);
  set_fixed_symbol(FIX_SYM_SYMBOL_TO_STRING, "symbol->string", 0x0);
  set_fixed_symbol(FIX_SYM_PRINT, "print", 0x0);
  set_fixed_symbol(FIX_SYM_INSPECT, "inspect", 0x0);
  set_fixed_symbol(FIX_SYM_LOAD, "load", 0x0);
  set_fixed_symbol(FIX_SYM_LOADB, "loadb", 0x0);
  set_fixed_symbol(FIX_SYM_LOADO, "loado", 0x0);
  set_fixed_symbol(FIX_SYM_UNLOAD, "unload", 0x0);
  set_fixed_symbol(FIX_SYM_FORMAT, "_format", 0x0);
  set_fixed_symbol(FIX_SYM_MALLOC, "malloc", 0x0);
  set_fixed_symbol(FIX_SYM_KMALLOC, "kmalloc", 0x0);
  set_fixed_symbol(FIX_SYM_KMEMOPEN, "kmemopen", 0x0);
  set_fixed_symbol(FIX_SYM_KMEMCLOSE, "kmemclose", 0x0);
  set_fixed_symbol(FIX_SYM_NEW_DYNAMIC_STRUCTURE, "new-dynamic-structure", 0x0);
  set_fixed_symbol(FIX_SYM_METHOD_SET, "method-set!", 0x0);
  set_fixed_symbol(FIX_SYM_LINK, "link", 0x0);
  set_fixed_symbol(FIX_SYM_LINK_BUSY, "link-busy?", 0x0);
  set_fixed_symbol(FIX_SYM_LINK_RESET, "link-reset", 0x0);
  set_fixed_symbol(FIX_SYM_LINK_BEGIN, "link-begin", 0x0);
  set_fixed_symbol(FIX_SYM_LINK_RESUME, "link-resume", 0x0);
  set_fixed_symbol(FIX_SYM_DGO_LOAD, "dgo-load", 0x0);
  set_fixed_symbol(FIX_SYM_SQL_QUERY, "sql-query", 0x0);
  set_fixed_symbol(FIX_SYM_MC_RUN, "mc-run", 0x0);
  set_fixed_symbol(FIX_SYM_MC_FORMAT, "mc-format", 0x0);
  set_fixed_symbol(FIX_SYM_MC_UNFORMAT, "mc-unformat", 0x0);
  set_fixed_symbol(FIX_SYM_MC_CREATE_FILE, "mc-create-file", 0x0);
  set_fixed_symbol(FIX_SYM_MC_SAVE, "mc-save", 0x0);
  set_fixed_symbol(FIX_SYM_MC_LOAD, "mc-load", 0x0);
  set_fixed_symbol(FIX_SYM_MC_CHECK_RESULT, "mc-check-result", 0x0);
  set_fixed_symbol(FIX_SYM_MC_GET_SLOT_INFO, "mc-get-slot-info", 0x0);
  set_fixed_symbol(FIX_SYM_MC_MAKEFILE, "mc-makefile", 0x0);
  set_fixed_symbol(FIX_SYM_KSET_LANGUAGE, "kset-language", 0x0);
  set_fixed_symbol(FIX_SYM_RPC_CALL, "rpc-call", 0x0);
  set_fixed_symbol(FIX_SYM_RPC_BUSY, "rpc-busy?", 0x0);
  set_fixed_symbol(FIX_SYM_TEST_LOAD_DGO_C, "test-load-dgo-c", 0x0);
  set_fixed_symbol(FIX_SYM_SYMLINK2, "symlink2", 0x0);
  set_fixed_symbol(FIX_SYM_SYMLINK3, "symlink3", 0x0);
  set_fixed_symbol(FIX_SYM_ULTIMATE_MEMCPY, "ultimate-memcpy", 0x0);
  set_fixed_symbol(FIX_SYM_PLAY, "play", 0x0);

  set_fixed_symbol(FIX_SYM_SYMBOL_STRING, "*symbol-string*", (u32)SymbolString);
  set_fixed_symbol(FIX_SYM_KERNEL_SYMBOL_WARNINGS, "*kernel-symbol-warnings*",
                   (u32)(symbol_table + 0x8005));
  set_fixed_symbol(FIX_SYM_NETWORK_BOOTSTRAP, "network-bootstrap", 0);

  Function* new_illegal_func = make_function_from_c(new_illegal, (bool)0x48);
  Function* delete_illegal_func = make_function_from_c(delete_illegal, (bool)0x48);
  Function* print_object_func = make_function_from_c(print_object, (bool)0x48);
  Function* inspect_object_func = make_function_from_c(inspect_object, (bool)0x48);

  set_fixed_type(FIX_SYM_OBJECT_TYPE, "object", (u32 *)(symbol_table + 0x801d), 0x900000004, 
                 (u32)print_object_func, (u32)inspect_object_func);
  iVar12 = *(Type **)(symbol_table + 0x801c);
  iVar11 = *(Type **)(symbol_table + 0x801c);
  iVar12->new_method = *(Function **)(symbol_table + 0x8094);
  iVar15 = *(Type **)(symbol_table + 0x801c);
  iVar11->delete_method = delete_illegal_func;
  iVar12->asize_of_method = *(Function **)(symbol_table + 0x80c0);
  print_object_func = make_function_from_c(copy_fixed, (bool)0x60);
  iVar15->copy_method = print_object_func;

  set_fixed_type(FIX_SYM_STRUCTURE, "structure", (u32 *)(symbol_table + 0x801d),
                 0x900000004, (u32)make_function_from_c(print_structure, (bool)0x60),
                 (u32)make_function_from_c(inspect_structure, (bool)0x60));
  iVar14 = *(Type **)(symbol_table + 0x806c);
  print_object_func = make_function_from_c(new_structure, (bool)0x68);
  iVar14->new_method = print_object_func;
  iVar13 = *(Type **)(symbol_table + 0x806c);
  print_object_func = make_function_from_c(delete_structure, (bool)0x68);
  iVar13->delete_method = print_object_func;

  set_fixed_type(FIX_SYM_BASIC, "basic", (u32 *)(symbol_table + 0x806d),
                 0x900000004, (u32)make_function_from_c(print_basic, (bool)0x68),
                 (u32)make_function_from_c(inspect_basic, (bool)0x68));
  iVar17 = *(Type **)(symbol_table + 0x800c);
  print_object_func = make_function_from_c(new_basic, (bool)0x78);
  iVar1 = *(Type **)(symbol_table + 0x800c);
  iVar17->new_method = print_object_func;
  iVar16 = *(Type **)(symbol_table + 0x800c);
  iVar1->delete_method = *(Function **)(symbol_table + 0x8098);
  iVar16->asize_of_method = *(Function **)(symbol_table + 0x80c4);
  iVar1->copy_method = *(Function **)(symbol_table + 0x80c8);

  set_fixed_type(FIX_SYM_SYMBOL_TYPE, "symbol", (u32 *)(symbol_table + 0x801d),
                 0x900000004, (u32)make_function_from_c(print_symbol, (bool)0x78),
                 (u32)make_function_from_c(inspect_symbol, (bool)0x78));
  iVar19 = *(Type **)(symbol_table + 0x8014);
  *(Function **)(*(int *)(symbol_table + 0x8014) + 0x10) = new_illegal_func;
  iVar19->delete_method = delete_illegal_func;

  set_fixed_type(FIX_SYM_TYPE_TYPE, "type", (u32 *)(symbol_table + 0x800d),
                 0x900000038, (u32)make_function_from_c(print_type, (bool)0x80),
                 (u32)make_function_from_c(inspect_type, (bool)0x80));
  iVar18 = *(Type **)(symbol_table + 0x8018);
  print_object_func = make_function_from_c(new_type, (bool)0x88);
  iVar10 = *(Type **)(symbol_table + 0x8018);
  iVar18->new_method = print_object_func;
  iVar10->delete_method = delete_illegal_func;

  set_fixed_type(FIX_SYM_STRING_TYPE, "string", (u32 *)(symbol_table + 0x800d),
                 0x900000008, (u32)make_function_from_c(print_string, (bool)0x88),
                 (u32)make_function_from_c(inspect_string, (bool)0x88));
  print_object_func = make_function_from_c(print_function, (bool)0x90);

  set_fixed_type(FIX_SYM_FUNCTION_TYPE, "function", (u32 *)(symbol_table + 0x800d), 0x900000004, 
                 (u32)print_object_func, 0);
  iVar10_03 = *(Type **)(symbol_table + 0x8008);
  *(Function **)(*(int *)(symbol_table + 0x8008) + 0x10) = new_illegal_func;
  iVar10_03->delete_method = delete_illegal_func;

  set_fixed_type(FIX_SYM_VU_FUNCTION, "vu-function", (u32 *)(symbol_table + 0x806d),
                 0x900000010, (u32)make_function_from_c(print_vu_function, (bool)0x98),
                 (u32)make_function_from_c(inspect_vu_function, (bool)0x98));
  *(Function **)(*(int *)(symbol_table + 0x8080) + 0x14) = delete_illegal_func;

  set_fixed_type(FIX_SYM_LINK_BLOCK, "link-block", (u32 *)(symbol_table + 0x800d),
                 0x90000000c, 0, 
                 (u32)make_function_from_c(inspect_link_block, (bool)0xa8));
  iVar20 = *(Type **)(symbol_table + 0x8020);
  *(Function **)(*(int *)(symbol_table + 0x8020) + 0x10) = new_illegal_func;
  iVar20->delete_method = delete_illegal_func;

  set_fixed_type(FIX_SYM_HEAP, "kheap", (u32 *)(symbol_table + 0x806d),
                 0x900000010, 0, (u32)make_function_from_c(kheapstatus, (bool)0xb8));

  set_fixed_type(FIX_SYM_ARRAY, "array", (u32 *)(symbol_table + 0x800d),
                 0x900000010, 0, 0);

  set_fixed_type(FIX_SYM_PAIR_TYPE, "pair", (u32 *)(symbol_table + 0x801d),
                 0x900000008, (u32)make_function_from_c(print_pair, (bool)0xd0),
                 (u32)make_function_from_c(inspect_pair, (bool)0xd0));
  iVar10_00 = *(Type **)(symbol_table + 0x8070);
  delete_illegal_func = make_function_from_c(new_pair, (bool)0xd8);
  iVar10_00->new_method = delete_illegal_func;
  iVar10_01 = *(Type **)(symbol_table + 0x8070);
  delete_illegal_func = make_function_from_c(delete_pair, (bool)0xd8);
  iVar10_01->delete_method = delete_illegal_func;

  set_fixed_type(FIX_SYM_PROCESS_TREE, "process-tree", (u32 *)(symbol_table + 0x800d),
                 0xf0000002c, 0, 0);
  set_fixed_type(FIX_SYM_PROCESS_TYPE, "process", (u32 *)(symbol_table + 0x8061),
                 0xf00000090, 0, 0);
  set_fixed_type(FIX_SYM_THREAD, "thread", (u32 *)(symbol_table + 0x800d),
                 0xc00000028, 0, 0);
  set_fixed_type(FIX_SYM_CONNECTABLE, "connectable", (u32 *)(symbol_table + 0x806d),
                 0x900000010, 0, 0);
  set_fixed_type(FIX_SYM_STACK_FRAME, "stack-frame", (u32 *)(symbol_table + 0x800d),
                 0x90000000c, 0, 0);
  set_fixed_type(FIX_SYM_FILE_STREAM, "file-stream", (u32 *)(symbol_table + 0x800d),
                 0x900000014, 0, 0);
  set_fixed_type(FIX_SYM_POINTER, "pointer", (u32 *)(symbol_table + 0x801d),
                 0x900000004, 0, 0);
  *(Function **)(*(int *)(symbol_table + 0x8074) + 0x10) = new_illegal_func;

  set_fixed_type(FIX_SYM_NUMBER, "number", (u32 *)(symbol_table + 0x801d),
                 0x900000008, make_function_from_c(print_integer, (bool)0x30),
                 make_function_from_c(inspect_integer, (bool)0x30));
  *(Function **)(*(int *)(symbol_table + 0x8078) + 0x10) = new_illegal_func;

  set_fixed_type(FIX_SYM_FLOAT, "float", (u32 *)(symbol_table + 0x8079),
                 0x900000004, (u32)make_function_from_c(print_float, (bool)0x38),
                 (u32)make_function_from_c(inspect_float, (bool)0x38));

  set_fixed_type(FIX_SYM_INTEGER, "integer", (u32 *)(symbol_table + 0x8079),
                 0x900000008, 0, 0); // NOTE: swapped with binteger

  set_fixed_type(FIX_SYM_BINTEGER, "binteger", (u32 *)(symbol_table + 0x8025),
                 0x900000008, make_function_from_c(print_binteger, (bool)0x48),
                 make_function_from_c(inspect_binteger, (bool)0x48));

  set_fixed_type(FIX_SYM_SINTEGER, "sinteger", (u32 *)(symbol_table + 0x8025),
                 0x900000008, 0, 0);
  set_fixed_type(FIX_SYM_INT8, "int8", (u32 *)(symbol_table + 0x8029),
                 0x900000001, 0, 0);
  set_fixed_type(FIX_SYM_INT16, "int16", (u32 *)(symbol_table + 0x8029),
                 0x900000002, 0, 0);
  set_fixed_type(FIX_SYM_INT32, "int32", (u32 *)(symbol_table + 0x8029),
                 0x900000004, 0, 0);
  set_fixed_type(FIX_SYM_INT64, "int64", (u32 *)(symbol_table + 0x8029),
                 0x900000008, 0, 0);
  set_fixed_type(FIX_SYM_INT128, "int128", (u32 *)(symbol_table + 0x8029),
                 0x900000010, 0, 0);

  set_fixed_type(FIX_SYM_UINTEGER, "uinteger", (u32 *)(symbol_table + 0x8025),
                 0x900000008, 0, 0);
  set_fixed_type(FIX_SYM_UINT8, "uint8", (u32 *)(symbol_table + 0x802d),
                 0x900000001, 0, 0);
  set_fixed_type(FIX_SYM_UINT16, "uint16", (u32 *)(symbol_table + 0x802d),
                 0x900000002, 0, 0);
  set_fixed_type(FIX_SYM_UINT32, "uint32", (u32 *)(symbol_table + 0x802d),
                 0x900000004, 0, 0);
  set_fixed_type(FIX_SYM_UINT64, "uint64", (u32 *)(symbol_table + 0x802d),
                 0x900000008, 0, 0);
  set_fixed_type(FIX_SYM_UINT128, "uint128", (u32 *)(symbol_table + 0x802d),
                 0x900000010, 0, 0);
  iVar10_02 = *(Type **)(symbol_table + 0x801c);
  new_illegal_func = make_function_from_c(alloc_heap_object, (bool)200);
  iVar10_02->new_method = new_illegal_func;

  make_function_symbol_from_c("string->symbol", intern);
  make_function_symbol_from_c("symbol->string", symbol_to_string_from_c);
  make_function_symbol_from_c("print", sprint);
  make_function_symbol_from_c("inspect", inspect_object);
  make_function_symbol_from_c("load", load);
  make_function_symbol_from_c("loadb", loadb);
  make_function_symbol_from_c("loado", loado);
  make_function_symbol_from_c("unload", unload);
  make_function_symbol_from_c("_format", format_impl_jak3);
  make_function_symbol_from_c("malloc", alloc_heap_memory);
  make_function_symbol_from_c("kmalloc", goal_malloc);
  make_function_symbol_from_c("kmemopen", kmemopen);
  make_function_symbol_from_c("kmemclose", kmemclose);
  make_function_symbol_from_c("new-dynamic-structure", new_dynamic_structure);
  make_function_symbol_from_c("method-set!", method_set);
  make_function_symbol_from_c("link", link_and_exec);
  make_function_symbol_from_c("link-busy?", link_busy);
  make_function_symbol_from_c("link-reset", link_reset);
  make_function_symbol_from_c("dgo-load", load_and_link_dgo);
  make_raw_function_symbol_from_c("ultimate-memcpy", 0);
  make_raw_function_symbol_from_c("symlink2", 0);
  make_raw_function_symbol_from_c("symlink3", 0);
  make_function_symbol_from_c("link-begin", link_begin);
  make_function_symbol_from_c("link-resume", link_resume);
  make_function_symbol_from_c("sql-query", sql_query_sync);
  make_function_symbol_from_c("mc-run", MC_run);
  make_function_symbol_from_c("mc-format", MC_format);
  make_function_symbol_from_c("mc-unformat", MC_unformat);
  make_function_symbol_from_c("mc-create-file", MC_createfile);
  make_function_symbol_from_c("mc-save", MC_save);
  make_function_symbol_from_c("mc-load", MC_load);
  make_function_symbol_from_c("mc-check-result", MC_check_result);
  make_function_symbol_from_c("mc-get-slot-info", MC_get_status);
  make_function_symbol_from_c("mc-makefile", MC_makefile);
  make_function_symbol_from_c("kset-language", MC_set_language);
  make_function_symbol_from_c("network-bootstrap", network_bootstrapProxy);

  u32* ds_symbol = intern_from_c(-1, 0, "*debug-segment*");
  if (DebugSegment == 0) {
    *(u8 **)((int)ds_symbol + -1) = symbol_table + 0x8001;;
  } else {
    *(u8 **)((int)ds_symbol + -1) = symbol_table + 0x8005;
  }

  u32* method_set_symbol = intern_from_c(-1, 0, "*enable-method-set*");
  EnableMethodSet = (int *)((int)method_set_symbol + -1);
  *(undefined4 *)((int)method_set_symbol + -1) = 0;

  KernelDebug = (int)intern_from_c(-1, 0, "*kernel-debug*") + -1;
  *(undefined4 *)(KernelDebug) = 0;
  *(undefined4 *)((int)intern_from_c(-1, 0, "*boot-video-mode*") + -1) = 1;
  *(undefined4 *)((int)intern_from_c(-1, 0, "*video-mode*") + -1) = 1;

  SqlResult = intern_from_c(-1, 0, "*sql-result*");
  *(u8 **)((int)SqlResult + -1) = value;

  CollapseQuote = intern_from_c(-1, 0, "*collapse-quote*");
  *(u8 **)((int)CollapseQuote + -1) = symbol_table + 0x8005;

  LevelTypeList = intern_from_c(-1, 0, "*level-type-list*");

  *EnableMethodSet = *EnableMethodSet + 1;
  load_and_link_dgo_from_c("kernel", &kglobalheapinfo,
                          0xd,
                          0x400000, (bool)0); // TODO: false?
  *EnableMethodSet = *EnableMethodSet + -1;

  kernel_version = *(uint *)((int)intern_from_c(-1, 0, "*kernel-version*") + -1);
  if (kernel_version == 0 || ((kernel_version >> 0x13) != 0x16)) {
    MsgErr("\n");
    MsgErr("dkernel: compiled C kernel version is %d.%d but the goal kernel is %d.%d!\n\tfrom the go al> prompt (:mch) then mkee your kernel in linux.\n"
           , 0x16, 0, kernel_version >> 0x13, kernel_version >> 3 & 0xffff);
    return -1;
  }

  protoBlock.deci2count = (s32)intern_from_c(-1, 0, "*deci-count*");
  InitListener();
  InitMachineScheme();
  kmemclose();
  return 0;
}

// TBD
u64 load(u32 file_name_in,u32 heap_in) {
  undefined4 uVar1;
  char *__src;
  u64 uVar2;
  int unaff_s7_lo;
  undefined4 unaff_s7_hi;
  char acStack_120 [256];
  
  uVar1 = *(undefined4 *)(unaff_s7_lo + 0xab);
  *(u32 *)(unaff_s7_lo + 0xab) = heap_in;
  __src = DecodeFileName((const char* )(file_name_in + 4));
  strcpy(acStack_120,__src);
  uVar2 = load_and_link((const char* )(file_name_in + 4),acStack_120,(kheapinfo *)heap_in,0xf);
  *(undefined4 *)(unaff_s7_lo + 0xab) = uVar1;
  if ((uVar2 & 0xfffffffffff00000) == 0xfffffffffff00000) {
    uVar2 = CONCAT44(unaff_s7_hi,unaff_s7_lo);
  }
  return uVar2;
}

// TBD
u64 loadb(u32 file_name_in, u32 heap_in, u32 param3) {
  char *__src;
  u8 *puVar1;
  ulong uVar2;
  u64 unaff_s7;
  char acStack_120 [256];
  
  __src = DecodeFileName((const char* )(file_name_in + 4));
  strcpy(acStack_120,__src);
  puVar1 = FileLoad(acStack_120,(kheapinfo *)heap_in,(u8 *)0x0,0x40,(s32 *)param3);
  uVar2 = (long)(int)puVar1;
  if (((long)(int)puVar1 & 0xfffffffffff00000U) == 0xfffffffffff00000) {
    uVar2 = unaff_s7;
  }
  return uVar2;
}

// TBD
u64 loadc(const char* file_name,kheapinfo *heap,u32 flags) {
  undefined4 uVar1;
  char *__src;
  u64 uVar2;
  int unaff_s7_lo;
  undefined4 unaff_s7_hi;
  char acStack_130 [256];
  
  uVar1 = *(undefined4 *)(unaff_s7_lo + 0xab);
  *(kheapinfo **)(unaff_s7_lo + 0xab) = heap;
  printf("****** CALL TO loadc() ******\n");
  __src = MakeFileName(3,file_name,0);
  strcpy(acStack_130,__src);
  uVar2 = load_and_link(file_name,acStack_130,heap,flags);
  *(undefined4 *)(unaff_s7_lo + 0xab) = uVar1;
  if ((uVar2 & 0xfffffffffff00000) == 0xfffffffffff00000) {
    uVar2 = CONCAT44(unaff_s7_hi,unaff_s7_lo);
  }
  return uVar2;
}

u64 loado(u32 file_name_in, u32 heap_in) {
  char loadName[256];
  printf("****** CALL TO loado(%s) ******\n", (const char* )(file_name_in + 4));
  strcpy(loadName, MakeFileName(0x20, (const char* )(file_name_in + 4), 0));
  ulong returnValue = load_and_link((const char* )(file_name_in + 4), loadName, (kheapinfo *)heap_in, 8);

  if ((returnValue & 0xfffffffffff00000) == 0xfffffffffff00000) {
    u64 unaff_s7;
    return unaff_s7;
  } else {
    return returnValue;
  }
}

/*!
 * "Unload". Doesn't free memory, just informs listener we unloaded.
 */
u64 unload(u32 name) {
  output_unload((const char* )(name + 4));
  return 0;
}

s64 load_and_link(const char* filename, char* decode_name, kheapinfo* heap, u32 flags) {
  int32_t sz[4];
  u8* data = FileLoad(decode_name, heap, (u8 *)0x0, 0x40, sz);
  ulong rv = (ulong)(int)data;
  if ((rv & 0xfffffffffff00000) != 0xfffffffffff00000) {
    return (ulong)(int)link_and_exec(data, decode_name, sz[0], heap, flags, false);
  }
  return rv;
}

}  // namespace jak3
