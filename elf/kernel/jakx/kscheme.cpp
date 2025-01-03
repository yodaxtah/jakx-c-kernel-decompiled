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

u64 new_illegal(u32 allocation,u32 type) {
  int unaff_s7_lo;
  undefined4 unaff_s7_hi;
  
  MsgErr("dkernel: illegal attempt to call new method of static object type %s\n",
         *(int *)((*(int *)type - unaff_s7_lo) + SymbolString) + 4);
  return CONCAT44(unaff_s7_hi,unaff_s7_lo);
}

u64 alloc_from_heap(u32 heapSymbol,u32 type,s32 size,u32 pp) {
  u8 *puVar1;
  u64 uVar2;
  void *__s;
  char *name;
  int iVar3;
  int iVar4;
  int unaff_s6_lo;
  int unaff_s7_lo;
  
  uVar2 = (u64)(int)heapSymbol;
  if (false) {
    trap(7);
  }
  iVar4 = ((size + 0xf) / 0x10) * 0x10;
  if ((((uVar2 == (long)(unaff_s7_lo + 0xa0)) || (uVar2 == (long)(unaff_s7_lo + 0xa4))) ||
      (uVar2 == (long)(unaff_s7_lo + 0xa8))) || (uVar2 == (long)(unaff_s7_lo + 0xb0))) {
    if (((type == 0) || (*(int *)type == 0)) ||
       (iVar4 = *(int *)((*(int *)type - unaff_s7_lo) + SymbolString), name = (char *)(iVar4 + 4),
       iVar4 == 0)) {
      name = "global-object";
    }
    puVar1 = kmalloc(*(kheapinfo **)(heapSymbol - 1),size,0x1000,name);
    return (long)(int)puVar1;
  }
  if (uVar2 == (long)(unaff_s7_lo + 100)) {
    uVar2 = (u64)*(int *)(unaff_s6_lo + 0x74);
    iVar3 = *(int *)(unaff_s6_lo + 0x74) + iVar4;
    if (*(int *)(unaff_s6_lo + 0x70) <= iVar3) {
      MsgErr("kmalloc: !alloc mem in heap for #<process @ #x%x> (%d bytes / %d bytes free)\n");
      return 0;
    }
    *(int *)(unaff_s6_lo + 0x74) = iVar3;
  }
  else if (uVar2 == (long)(unaff_s7_lo + 0xb8)) {
    __s = *(void **)(unaff_s7_lo + 0xbb);
    uVar2 = (u64)(int)__s;
    *(int *)(unaff_s7_lo + 0xbb) = *(int *)(unaff_s7_lo + 0xbb) + iVar4;
    goto LAB_0026b504;
  }
  __s = (void *)uVar2;
LAB_0026b504:
  memset(__s,0,(long)iVar4);
  return uVar2;
}

/*!
 * Allocate untyped memory.
 */
u64 alloc_heap_memory(u32 heap,u32 size) {
  u64 uVar1;
  u32 in_a3_lo;
  
  uVar1 = alloc_from_heap(heap,0,size,in_a3_lo);
  return uVar1;
}

/*!
 * Allocate memory and add type tag for an object.
 * For allocating basics.
 * Called from GOAL.
 */
u64 alloc_heap_object(u32 heap,u32 type,u32 size,u32 pp) {
  u64 uVar1;
  u64 uVar2;
  
  uVar1 = alloc_from_heap(heap,type,size,pp);
  uVar2 = (u64)(int)((u32 *)uVar1 + 1);
  if (uVar1 == 0) {
    uVar2 = 0;
  }
  else {
    *(u32 *)uVar1 = type;
  }
  return uVar2;
}

/*!
 * Allocate a structure and get the structure size from the type.
 */
u64 new_structure(u32 heap,u32 type) {
  u64 uVar1;
  u32 in_a3_lo;
  
  uVar1 = alloc_from_heap(heap,type,(uint)*(ushort *)(type + 8),in_a3_lo);
  return uVar1;
}

/*!
 * Allocate a structure with a dynamic size
 */
u64 new_dynamic_structure(u32 heap_symbol,u32 type,u32 size) {
  u64 uVar1;
  u32 in_a3_lo;
  
  uVar1 = alloc_from_heap(heap_symbol,type,size,in_a3_lo);
  return uVar1;
}

/*!
 * Delete a structure.  Not supported, as it uses kfree, which doesn't do anything.
 */
void delete_structure(u32 s) {
  kfree((u8 *)s);
  return;
}

/*!
 * Allocate a basic of fixed size.
 */
u64 new_basic(u32 heap,u32 type,u32 size,u32 pp) {
  u64 uVar1;
  
  uVar1 = alloc_heap_object(heap,type,(uint)*(ushort *)(type + 8),pp);
  return uVar1;
}

/*!
 * Delete a basic.  Not supported, as it uses kfree.
 */
void delete_basic(u32 s) {
  kfree((u8 *)(s - 0x10));
  return;
}

/*!
 * Allocate a new pair and set its car and cdr.
 */
u64 new_pair(u32 heap,u32 type,u32 car,u32 cdr) {
  u32 *puVar1;
  u64 uVar2;
  u64 uVar3;
  
  uVar2 = alloc_from_heap(heap,type,(uint)*(ushort *)(type + 8),cdr);
  puVar1 = (u32 *)uVar2;
  uVar3 = (u64)((int)puVar1 + 2);
  if (uVar2 == 0) {
    uVar3 = 0;
  }
  else {
    *puVar1 = car;
    puVar1[1] = cdr;
  }
  return uVar3;
}

/*!
 * Delete a pair.  BUG
 */
void delete_pair(u32 s) {
  kfree((u8 *)(s - 8));
  return;
}

u64 make_string(u32 size) {
  u64 uVar1;
  int iVar2;
  u32 in_a3_lo;
  int unaff_s7_lo;
  
  iVar2 = size + 1;
  if (iVar2 < 9) {
    iVar2 = 8;
  }
  uVar1 = alloc_heap_object(unaff_s7_lo + 0xa0,*(u32 *)(unaff_s7_lo + 0xf),iVar2 + 8,in_a3_lo);
  if (uVar1 != 0) {
    *(u32 *)uVar1 = size;
  }
  return uVar1;
}

/*!
 * Convert a C string to a GOAL string.
 * Allocates from the global heap and copies the string data.
 */
String * make_string_from_c(const_char *c_str) {
  String *pSVar1;
  size_t sVar2;
  u64 uVar3;
  int iVar4;
  u32 in_a3_lo;
  int unaff_s7_lo;
  
  sVar2 = strlen(c_str);
  iVar4 = (u32)sVar2 + 1;
  if (iVar4 < 9) {
    iVar4 = 8;
  }
  uVar3 = alloc_heap_object(unaff_s7_lo + 0xa0,*(u32 *)(unaff_s7_lo + 0xf),iVar4 + 8,in_a3_lo);
  pSVar1 = (String *)uVar3;
  pSVar1->len = (u32)sVar2;
  strcpy((char *)(pSVar1 + 1),c_str);
  return pSVar1;
}

u64 make_debug_string_from_c(const_char *c_str) {
  size_t sVar1;
  u64 uVar2;
  int iVar3;
  u32 in_a3_lo;
  int unaff_s7_lo;
  
  sVar1 = strlen(c_str);
  iVar3 = (int)sVar1 + 1;
  if (iVar3 < 9) {
    iVar3 = 8;
  }
  uVar2 = alloc_heap_object(unaff_s7_lo + 0xa4,*(u32 *)(unaff_s7_lo + 0xf),iVar3 + 8,in_a3_lo);
  *(int *)uVar2 = (int)sVar1;
  strcpy((char *)((int *)uVar2 + 1),c_str);
  return uVar2;
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
  *mem = 0x67bdffc0;
  mem[2] = 0xffbc0010;
  mem[3] = 0xffb60020;
  mem[4] = 0xffb70030;
  mem[9] = 0x320f809;
  mem[0xc] = 0xdfbc0010;
  mem[0xd] = 0xdfb60020;
  mem[0xe] = 0xdfb70030;
  mem[0xb] = 0xdfbf0000;
  mem[0xf] = 0x3e00008;
  CacheFlush(mem,0x4c);
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
  undefined4 *mem;
  u64 uVar1;
  u32 in_a3_lo;
  int unaff_s7_lo;
  
  uVar1 = alloc_heap_object(unaff_s7_lo + 0xa0,*(u32 *)(unaff_s7_lo + 7),0x14,in_a3_lo);
  mem = (undefined4 *)uVar1;
  mem[1] = 0;
  mem[2] = 0;
  *mem = 0x3e00008;
  mem[3] = 0;
  CacheFlush(mem,0x10);
  return uVar1;
}

/*!
 * Create a GOAL function which returns 0.
 */
u64 make_zero_func() {
  undefined4 *mem;
  u64 uVar1;
  u32 in_a3_lo;
  int unaff_s7_lo;
  
  uVar1 = alloc_heap_object(unaff_s7_lo + 0xa0,*(u32 *)(unaff_s7_lo + 7),0x14,in_a3_lo);
  mem = (undefined4 *)uVar1;
  mem[2] = 0;
  mem[3] = 0;
  *mem = 0x3e00008;
  mem[1] = 0x24020000;
  CacheFlush(mem,0x10);
  return uVar1;
}

u64 symbol_to_string_from_c(u32 sym) {
  int iVar1;
  u64 uVar2;
  int unaff_s7_lo;
  undefined4 unaff_s7_hi;
  
  iVar1 = *(int *)((sym - unaff_s7_lo) + SymbolString);
  uVar2 = (u64)iVar1;
  if ((uVar2 == (long)UnknownName) ||
     ((0 < (long)uVar2 &&
      ((DebugSegment == 0 ||
       ((long)*(int *)(unaff_s7_lo + 0x28f) != CONCAT44(unaff_s7_hi,unaff_s7_lo))))))) {
    MsgWarn("dkernel: doing a symbol->string on %s (addr #x%x), but the symbol has not been marked as symbol-export-string\n"
            ,iVar1 + 4,sym);
  }
  return uVar2;
}

/*!
 * Given a C function and a name, create a GOAL function and store it in the symbol with the given
 * name. This effectively creates a global GOAL function with the given name which calls the given C
 * function.
 *
 * This work on both Linux and Windows, but only supports up to 6 arguments.
 */
void make_function_symbol_from_c(char *name,void *f) {
  u32 *puVar1;
  Function *pFVar2;
  bool arg3_is_pp;
  
  arg3_is_pp = false;
  puVar1 = intern_from_c(-1,0,name);
  pFVar2 = make_function_from_c(f,arg3_is_pp);
  *(Function **)((int)puVar1 + -1) = pFVar2;
  return;
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

u32 make_raw_function_symbol_from_c(const_char *name,u32 value) {
  u32 *puVar1;
  
  puVar1 = intern_from_c(-1,0,name);
  *(u32 *)((int)puVar1 + -1) = value;
  return value;
}

Symbol4 * set_fixed_symbol(FixedSymbolOffset offset,const_char *name,u32 value) {
  String *pSVar1;
  Symbol4 *pSVar2;
  int unaff_s7_lo;
  
  pSVar2 = (Symbol4 *)(unaff_s7_lo + offset);
  *(u32 *)((int)&pSVar2[-1].foo + 3) = value;
  kheaplogging = 1;
  pSVar1 = make_string_from_c(name);
  kheaplogging = 0;
  *(String **)((int)pSVar2 + (SymbolString - unaff_s7_lo)) = pSVar1;
  NumSymbols = NumSymbols + 1;
  return pSVar2;
}

Symbol4 * find_symbol_in_area(const_char *name,u32 start,u32 end) {
  int iVar1;
  int unaff_s7_lo;
  
  while( true ) {
    if (end <= start) {
      return (Symbol4 *)0x0;
    }
    iVar1 = *(int *)(start + (SymbolString - unaff_s7_lo));
    if ((iVar1 != 0) && (iVar1 = strcmp((char *)(iVar1 + 4),name), iVar1 == 0)) break;
    start = start + 4;
  }
  return (Symbol4 *)start;
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
Symbol4 * find_symbol_from_c(uint16_t sym_id,const_char *name) {
  int iVar1;
  Symbol4 *pSVar2;
  int iVar3;
  char *format;
  int iVar4;
  u32 unaff_s7_lo;
  undefined4 unaff_s7_hi;
  
  iVar4 = (int)(short)sym_id;
  if (sym_id == 0xffff) {
    if (name == (const_char *)0x0) {
      MsgErr("dkernel: attempted to find symbol with NULL name and id #x%x\n",iVar4);
      pSVar2 = (Symbol4 *)0x0;
    }
    else {
      pSVar2 = find_symbol_in_area(name,unaff_s7_lo,LastSymbol);
      if (pSVar2 == (Symbol4 *)0x0) {
        pSVar2 = find_symbol_in_area(name,SymbolTable2,unaff_s7_lo - 0x10);
      }
      if ((DebugSegment == 0) ||
         ((long)*(int *)(unaff_s7_lo + 0x28f) != CONCAT44(unaff_s7_hi,unaff_s7_lo))) {
        if (pSVar2 == (Symbol4 *)0x0) {
          format = "dkernel: doing a string->symbol on %s, but could not find the name\n";
        }
        else {
          iVar4 = *(int *)((int)pSVar2 + (SymbolString - unaff_s7_lo));
          if ((iVar4 != UnknownName) && (iVar4 < 1)) {
            return pSVar2;
          }
          format = 
          "dkernel: doing a string->symbol on %s, but the symbol has not been marked as symbol-export-string\n"
          ;
        }
        MsgWarn(format,name);
      }
    }
  }
  else {
    pSVar2 = (Symbol4 *)(unaff_s7_lo + iVar4 + -1);
    if ((((pSVar2 != (Symbol4 *)(unaff_s7_lo - 7)) &&
         (iVar1 = *(int *)((int)pSVar2 + (SymbolString - unaff_s7_lo)), iVar1 != 0)) &&
        (iVar1 != UnknownName)) && (iVar3 = strcmp((char *)(iVar1 + 4),name), iVar3 != 0)) {
      MsgWarn("dkernel: WARNING: attempting to find symbol %s at id #x%x but symbol %s was already there.\n"
              ,name,iVar4,(char *)(iVar1 + 4));
    }
  }
  return pSVar2;
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
u32 * intern_from_c(int sym_id,int flags,const_char *name) {
  int iVar1;
  Symbol4 *pSVar2;
  String *pSVar3;
  u64 uVar4;
  int *piVar5;
  int unaff_s7_lo;
  
  pSVar2 = find_symbol_from_c((uint16_t)sym_id,name);
  kheaplogging = 1;
  if (pSVar2 == (Symbol4 *)0x0) {
    MsgErr("dkernel: attempted to intern symbol %s using the name, but could not find it\n",name);
    kheaplogging = 0;
    return (u32 *)0x0;
  }
  if (pSVar2 == (Symbol4 *)(unaff_s7_lo + -7)) {
    kheaplogging = 0;
    return (u32 *)pSVar2;
  }
  piVar5 = (int *)((int)pSVar2 + (SymbolString - unaff_s7_lo));
  iVar1 = *piVar5;
  if (iVar1 != 0) {
    if ((flags & 0x40U) == 0) {
      kheaplogging = 0;
      return (u32 *)pSVar2;
    }
    if ((iVar1 != UnknownName) && (iVar1 < 1)) {
      kheaplogging = 0;
      return (u32 *)pSVar2;
    }
    MsgWarn("dkernel: upgrading symbol %s (flags #x%x) from debug heap to global\n",name,flags);
    pSVar3 = make_string_from_c(name);
    *(String **)((int)pSVar2 + (SymbolString - unaff_s7_lo)) = pSVar3;
    kheaplogging = 0;
    return (u32 *)pSVar2;
  }
  if ((DebugSymbols == 0) && ((flags & 0x40U) == 0)) {
    if (DebugSegment == 0) {
      *piVar5 = UnknownName;
      goto LAB_0026bdd0;
    }
    uVar4 = make_debug_string_from_c(name);
    pSVar3 = (String *)uVar4;
  }
  else {
    pSVar3 = make_string_from_c(name);
  }
  *(String **)((int)pSVar2 + (SymbolString - unaff_s7_lo)) = pSVar3;
LAB_0026bdd0:
  NumSymbols = NumSymbols + 1;
  kheaplogging = 0;
  return (u32 *)pSVar2;
}

u64 intern(u32 name) {
  u32 *puVar1;
  
  puVar1 = intern_from_c(-1,0x40,(const_char *)(name + 4));
  return (long)(int)puVar1;
}

/*!
 * Configure a type.
 */
Type * set_type_values(Type *type,Type *parent,u64 flags) {
  ushort uVar1;
  
  uVar1 = type->num_methods;
  type->parent = parent;
  type->allocated_size = (u16)flags;
  type->heap_base = (u16)(flags >> 0x10);
  type->padded_size = (u16)flags + 0xf & 0xfff0;
  if ((ulong)uVar1 < ((long)flags >> 0x20 & 0xffffU)) {
    uVar1 = (ushort)(flags >> 0x20);
  }
  type->num_methods = uVar1;
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
 */
Type * alloc_and_init_type(undefined *sym,u32 method_count,bool force_global_type) {
  Type **ppTVar1;
  Type *pTVar2;
  uint size;
  Type *pTVar3;
  u64 uVar4;
  u32 type;
  u32 in_a3_lo;
  int unaff_s7_lo;
  
  kheaplogging = 1;
  size = method_count * 4 + 0x23 & 0xfffffff0;
  if ((force_global_type) || (*(int *)(unaff_s7_lo + 0xa7) == *(int *)(unaff_s7_lo + 0x9f))) {
    type = *(u32 *)(unaff_s7_lo + 0x17);
  }
  else {
    ppTVar1 = *(Type ***)(LevelTypeList + -1);
    if (ppTVar1 != (Type **)0x0) {
      uVar4 = alloc_heap_object(unaff_s7_lo + 0xa8,*(u32 *)(unaff_s7_lo + 0x17),size,in_a3_lo);
      pTVar2 = *ppTVar1;
      pTVar3 = (Type *)uVar4;
      *ppTVar1 = pTVar3;
      pTVar3->memusage_method = (Function *)pTVar2;
      goto LAB_0026befc;
    }
    MsgErr("dkernel: trying to init loading level type \'%s\' while type-list is undefined\n",
           *(int *)(sym + (SymbolString - unaff_s7_lo)) + 4);
    type = *(u32 *)(unaff_s7_lo + 0x17);
  }
  uVar4 = alloc_heap_object(unaff_s7_lo + 0xa0,type,size,in_a3_lo);
  pTVar3 = (Type *)uVar4;
LAB_0026befc:
  *(Type **)(sym + -1) = pTVar3;
  pTVar3->padded_size = (u16)size;
  pTVar3->allocated_size = (u16)size;
  kheaplogging = 0;
  return pTVar3;
}

/*!
 * Like intern, but returns a type instead of a symbol. If the type doesn't exist, a new one is
 * allocated.
 */
Type * intern_type_from_c(int a,int b,const_char *name,u64 methods) {
  Type **sym;
  Type *pTVar1;
  
  sym = (Type **)intern_from_c((int)(short)a,b,name);
  pTVar1 = *(Type **)((int)sym + -1);
  if (pTVar1 == (Type *)0x0) {
    if (methods == 0) {
      methods = 0xc;
    }
    else if (methods == 1) {
      methods = 0x2c;
    }
    pTVar1 = alloc_and_init_type((undefined *)sym,(u32)methods,false);
    pTVar1->symbol = sym;
    pTVar1->num_methods = (u16)methods;
  }
  else if ((ulong)(long)(int)((uint)pTVar1->num_methods * 4 + 0x23 & 0xfffffff0) <
           (methods * 4 + 0x23 & 0xfffffff0)) {
    MsgErr("dkernel: trying to redefine a type \'%s\' with %d methods when it had %d, try restarting\n"
           ,name,methods);
  }
  return pTVar1;
}

/*!
 * Wrapper of intern_type_from_c to use with GOAL. It accepts a gstring as a name.
 */
Type * intern_type(u32 name,u64 methods) {
  Type *pTVar1;
  
  pTVar1 = intern_type_from_c(-1,0,(const_char *)(name + 4),methods);
  return pTVar1;
}

/*!
 * Setup a type which is located in a fixed spot of the symbol table.
 */
Type * set_fixed_type(FixedSymbolTypeOffset offset,const_char *name,Symbol4 *parent_symbol,u64 flags,u32 print,u32 inspect) {
  Function *pFVar1;
  Type *parent;
  String *pSVar2;
  Type *type;
  Type **sym;
  int unaff_s7_lo;
  
  sym = (Type **)(unaff_s7_lo + offset);
  kheaplogging = 1;
  type = *(Type **)((int)sym + -1);
  pSVar2 = make_string_from_c(name);
  kheaplogging = 0;
  NumSymbols = NumSymbols + 1;
  *(String **)((int)sym + (SymbolString - unaff_s7_lo)) = pSVar2;
  if (type == (Type *)0x0) {
    type = alloc_and_init_type((undefined *)sym,(uint)(flags >> 0x20) & 0xffff,true);
  }
  pFVar1 = *(Function **)(unaff_s7_lo + 0x17);
  type->symbol = sym;
  type[-1].memusage_method = pFVar1;
  parent = *(Type **)((int)&parent_symbol[-1].foo + 3);
  set_type_values(type,parent,flags);
  type->new_method = parent->new_method;
  type->delete_method = parent->delete_method;
  if (print == 0) {
    print = (u32)parent->print_method;
  }
  type->print_method = (Function *)print;
  if (inspect == 0) {
    inspect = (u32)parent->inpsect_method;
  }
  pFVar1 = *(Function **)(unaff_s7_lo + 0xbf);
  type->inpsect_method = (Function *)inspect;
  type->length_method = pFVar1;
  type->asize_of_method = parent->asize_of_method;
  type->copy_method = parent->copy_method;
  return type;
}

Type * new_type(u32 symbol,u32 parent,u64 flags) {
  ushort uVar1;
  Function *pFVar2;
  Type *pTVar3;
  const_char *name;
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
  name = (const_char *)(*(int *)(iVar8 + SymbolString) + 4);
  if (*(int *)(iVar8 + SymbolString) == 0) {
    name = (const_char *)0x0;
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
  }
  else if (uVar6 == 0) {
    MsgWarn("dkernel: loading-level init of type %s, but was interned global (this is okay)\n",
            *(int *)(iVar8 + SymbolString) + 4);
  }
  else {
    pTVar3->memusage_method = pFVar2;
  }
  pTVar3 = set_type_values(pTVar3,(Type *)parent,flags);
  return pTVar3;
}

/*!
 * Is t1 a t2?
 */
u64 type_typep(Type *t1,Type *t2) {
  Type *pTVar1;
  int unaff_s7_lo;
  undefined4 unaff_s7_hi;
  
  if (t1 != t2) {
    for (pTVar1 = t1->parent; pTVar1 != t2; pTVar1 = pTVar1->parent) {
      if (pTVar1 == *(Type **)(unaff_s7_lo + 0x1b)) {
        return CONCAT44(unaff_s7_hi,unaff_s7_lo);
      }
      if (pTVar1 == (Type *)0x0) {
        return CONCAT44(unaff_s7_hi,unaff_s7_lo);
      }
    }
  }
  return (long)(unaff_s7_lo + 4);
}

u64 method_set(u32 type_,u32 method_id,u32 method) {
  Function *pFVar1;
  Type *pTVar2;
  int *piVar3;
  u64 uVar4;
  Function *pFVar5;
  u64 uVar6;
  int iVar7;
  ulong uVar8;
  int unaff_s7_lo;
  undefined4 unaff_s7_hi;
  
  piVar3 = EnableMethodSet;
  uVar6 = (u64)(int)method;
  iVar7 = method_id * 4;
  pFVar1 = *(Function **)(iVar7 + type_ + 0x10);
  uVar8 = CONCAT44(unaff_s7_hi,unaff_s7_lo);
  if (uVar6 == 1) {
    uVar6 = 0;
  }
  else if ((long)uVar6 < 2) {
    if (uVar6 == 0) {
      return 0;
    }
  }
  else if (uVar6 == 2) {
    uVar6 = (u64)*(int *)(iVar7 + *(int *)(type_ + 4) + 0x10);
  }
  pFVar5 = (Function *)uVar6;
  *(Function **)(iVar7 + type_ + 0x10) = pFVar5;
  if ((*piVar3 != 0) || (((FastLink == '\0' && (MasterDebug != 0)) && (DiskBoot == 0)))) {
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
          if (FastLink != '\0') {
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
                if (FastLink == '\0') {
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
  return uVar6;
}

/*!
 * Call a GOAL method of a given type.
 */
u64 call_method_of_type(u32 arg,Type *type,u32 method_id) {
  u64 uVar1;
  char *format;
  Type *pTVar2;
  int unaff_s7_lo;
  
  uVar1 = (u64)(int)arg;
  if ((((type < SymbolTable2) || ((Type *)0x7ffffff < type)) &&
      ((Function **)0x7bfff < &type[-0x289e].print_method)) || (((uint)type & 7) != 4)) {
    format = "#<#x%x has invalid type ptr #x%x>\n";
    pTVar2 = type;
  }
  else {
    pTVar2 = (Type *)type[-1].memusage_method;
    if (pTVar2 == *(Type **)(unaff_s7_lo + 0x17)) {
      uVar1 = (*(code *)(&type->new_method)[method_id])(uVar1,uVar1,pTVar2);
      return uVar1;
    }
    format = "#<#x%x has invalid type ptr #x%x, bad type #x%x>\n";
  }
  cprintf(format,uVar1,pTVar2);
  return uVar1;
}

/*!
 * Call a GOAL function with 2 arguments.
 */
u64 call_goal_function_arg2(Function *func,u64 a,u64 b) {
  u64 uVar1;
  
  uVar1 = (*(code *)func)(a,b);
  return uVar1;
}

/*!
 * Call a global GOAL function by name.
 */
u64 call_goal_function_by_name(const_char *name) {
  u32 *puVar1;
  u64 uVar2;
  
  puVar1 = intern_from_c(-1,0,name);
  uVar2 = call_goal_function(*(Function **)((int)puVar1 + -1));
  return uVar2;
}


u64 print_object(u32 obj);
u64 print_pair(u32 obj);
u64 print_symbol(u32 obj);

/*!
 * Print an object with a newline after it to the GOAL PrintBuffer (not stdout)
 */
u64 sprint(u32 obj) {
  u64 uVar1;
  
  uVar1 = print_object(obj);
  cprintf("\n");
  return uVar1;
}

/*!
 * Like call_method_of_type, but has two arguments. Used to "relocate" v2/s4 loads.
 */
u64 call_method_of_type_arg2(u32 arg,Type *type,u32 method_id,u32 a1,u32 a2) {
  u64 uVar1;
  char *format;
  Type *pTVar2;
  int unaff_s7_lo;
  
  uVar1 = (u64)(int)arg;
  if ((((type < SymbolTable2) || ((Type *)0x7ffffff < type)) &&
      ((Function **)0x7bfff < &type[-0x289e].print_method)) || (((uint)type & 7) != 4)) {
    format = "#<#x%x has invalid type ptr #x%x>\n";
    pTVar2 = type;
  }
  else {
    pTVar2 = (Type *)type[-1].memusage_method;
    if (pTVar2 == *(Type **)(unaff_s7_lo + 0x17)) {
      uVar1 = (*(code *)(&type->new_method)[method_id])(uVar1,a1,a2);
      return uVar1;
    }
    format = "#<#x%x has invalid type ptr #x%x, bad type #x%x>\n";
  }
  cprintf(format,uVar1,pTVar2);
  return uVar1;
}

/*!
 * Most generic printing method.
 * Does not correctly handle 64 bit boxed integers or object64's correctly.
 * It is important that no objects of type object actually exist or this will loop!
 */
u64 print_object(u32 obj) {
  u64 uVar1;
  ulong uVar2;
  
  uVar1 = (u64)(int)obj;
  uVar2 = uVar1 & 7;
  if (uVar2 == 0) {
    uVar1 = print_binteger((ulong)obj);
    uVar1 = (u64)(int)uVar1;
  }
  else if (((uVar1 < (ulong)(long)SymbolTable2) || (0x7ffffff < uVar1)) && (0x7bfff < obj - 0x84000)
          ) {
    cprintf("#<invalid object #x%x>",uVar1);
  }
  else {
    if (uVar2 == 2) {
      uVar1 = print_pair(obj);
      return uVar1;
    }
    if ((((uVar1 & 1) != 0) && ((ulong)(long)SymbolTable2 <= uVar1)) &&
       (uVar1 < (ulong)(long)LastSymbol)) {
      uVar1 = print_symbol(obj);
      return uVar1;
    }
    if (uVar2 == 4) {
      uVar1 = call_method_of_type(obj,*(Type **)(obj - 4),2);
      return uVar1;
    }
    cprintf("#<unknown type %d @ #x%x>",uVar2,uVar1);
  }
  return uVar1;
}

/*!
 * Default print method a basic.
 * Confirms basic is valid and prints the type name.
 */
u64 print_basic(u32 obj) {
  ulong uVar1;
  int unaff_s7_lo;
  undefined4 unaff_s7_hi;
  
  uVar1 = (ulong)(int)obj;
  if ((((uVar1 < (ulong)(long)SymbolTable2) || (0x7ffffff < uVar1)) && (0x7bfff < obj - 0x84000)) ||
     ((uVar1 & 7) != 4)) {
    if (uVar1 == CONCAT44(unaff_s7_hi,unaff_s7_lo)) {
      cprintf("#f");
    }
    else {
      cprintf("#<invalid basic #x%x>",uVar1);
    }
  }
  else {
    cprintf("#<%s @ #x%x>",*(int *)((**(int **)(obj - 4) - unaff_s7_lo) + SymbolString) + 4,
            (ulong)obj);
  }
  return uVar1;
}

/*!
 * Print a pair as a LISP list.  Don't try to print circular lists or it will get stuck
 * Can print improper lists
 */
u64 print_pair(u32 obj) {
  uint uVar1;
  char *format;
  ulong uVar2;
  u32 obj_00;
  ulong uVar3;
  int unaff_s7_lo;
  undefined4 unaff_s7_hi;
  
  uVar2 = (ulong)(int)obj;
  if (uVar2 == (long)(unaff_s7_lo + -7)) {
    format = "()";
  }
  else {
    if (((((long)*(int *)(CollapseQuote + -1) != CONCAT44(unaff_s7_hi,unaff_s7_lo)) &&
         ((uVar2 & 7) == 2)) && (*(int *)(obj - 2) == unaff_s7_lo + 0xe8)) &&
       ((uVar1 = *(uint *)(obj + 2), (uVar1 & 7) == 2 &&
        ((long)*(int *)(uVar1 + 2) == (long)(unaff_s7_lo + -7))))) {
      cprintf("\'");
      print_object(*(u32 *)(uVar1 - 2));
      return uVar2;
    }
    cprintf("(");
    uVar3 = uVar2;
    while (obj_00 = (u32)uVar3, (uVar3 & 7) == 2) {
      print_object(*(u32 *)(obj_00 - 2));
      uVar3 = (ulong)*(int *)(obj_00 + 2);
      if (uVar3 == (long)(unaff_s7_lo + -7)) goto LAB_0026ccc0;
      cprintf(" ");
    }
    cprintf(". ");
    print_object(obj_00);
LAB_0026ccc0:
    format = ")";
  }
  cprintf(format);
  return uVar2;
}

/*!
 * Print method for symbol.  Just prints the name without quotes or anything fancy.
 */
u64 print_symbol(u32 obj) {
  char *format;
  ulong uVar1;
  ulong uVar2;
  int unaff_s7_lo;
  
  uVar1 = (ulong)(int)obj;
  uVar2 = uVar1;
  if (((((ulong)(long)SymbolTable2 <= uVar1) && (uVar1 < 0x8000000)) || (obj - 0x84000 < 0x7c000))
     && (((uVar1 ^ 1) & 1) == 0)) {
    format = "#<invalid symbol #x%x>";
    if (uVar1 < (ulong)(long)SymbolTable2) goto LAB_0026cec0;
    if (uVar1 < (ulong)(long)LastSymbol) {
      format = "%s";
      uVar2 = (ulong)(*(int *)((obj - unaff_s7_lo) + SymbolString) + 4);
      goto LAB_0026cec0;
    }
  }
  format = "#<invalid symbol #x%x>";
LAB_0026cec0:
  cprintf(format,uVar2);
  return uVar1;
}

/*!
 * Print method for type.  Just prints the name without quotes
 */
u64 print_type(u32 obj) {) { ulong uVar1;
  ulong uVar2;
  int unaff_s7_lo;
  
  uVar1 = (ulong)(int)obj;
  if ((((uVar1 < (ulong)(long)SymbolTable2) || (0x7ffffff < uVar1)) && (0x7bfff < obj - 0x84000)) ||
     (((uVar1 & 7) != 4 || (*(int *)(obj - 4) != *(int *)(unaff_s7_lo + 0x17))))) {
    format = "#<invalid type #x%x>";
    uVar2 = uVar1;
  }
  else {
    format = "%s";
    uVar2 = (long)(*(int *)((*(int *)obj - unaff_s7_lo) + SymbolString) + 4);
  }
  cprintf(format,uVar2);
  return uVar1;
}

/*!
 * Print method for string.  Prints the string in quotes.
 */
u64 print_string(u32 obj) {
  char *format;
  ulong uVar1;
  ulong uVar2;
  int unaff_s7_lo;
  undefined4 unaff_s7_hi;
  
  uVar1 = (ulong)(int)obj;
  if ((((uVar1 < (ulong)(long)SymbolTable2) || (0x7ffffff < uVar1)) && (0x7bfff < obj - 0x84000)) ||
     (((uVar1 & 7) != 4 || (*(int *)(obj - 4) != *(int *)(unaff_s7_lo + 0xf))))) {
    if (uVar1 == CONCAT44(unaff_s7_hi,unaff_s7_lo)) {
      cprintf("#f",uVar1);
      return uVar1;
    }
    format = "#<invalid string #x%x>";
    uVar2 = uVar1;
  }
  else {
    uVar2 = (ulong)(int)(obj + 4);
    format = "\"%s\"";
  }
  cprintf(format,uVar2);
  return uVar1;
}

/*!
 * Print method for function. Just prints the address because functions can't identify themselves.
 */
u64 print_function(u32 obj) {
  int unaff_s7_lo;
  
  cprintf("#<compiled %s @ #x%x>",*(int *)((**(int **)(obj - 4) - unaff_s7_lo) + SymbolString) + 4,
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
u64 copy_basic(u32 obj,u32 heap,u32 unused,u32 pp) {
  u64 __n;
  u64 uVar1;
  void *__src;
  void *__dest;
  
  uVar1 = (u64)(int)heap;
  __n = call_method_of_type(obj,*(Type **)(obj - 4),5);
  __src = (void *)(obj - 4);
  __dest = (void *)(heap - 4);
  if ((uVar1 & 1) != 0) {
    uVar1 = alloc_heap_object(heap,*(u32 *)(obj - 4),(u32)__n,pp);
    __n = (u64)(int)((u32)__n - 4);
    __dest = (void *)uVar1;
    __src = (void *)obj;
  }
  memcpy(__dest,__src,__n);
  return uVar1;
}

u64 inspect_pair(u32 obj);
u64 inspect_symbol(u32 obj);
/*!
 * Highest level inspect method. Won't inspect 64-bit bintegers correctly.
 */
u64 inspect_object(u32 obj) {
  u64 uVar1;
  ulong uVar2;
  
  uVar1 = (u64)(int)obj;
  uVar2 = uVar1 & 7;
  if (uVar2 == 0) {
    uVar1 = inspect_binteger((ulong)obj);
    uVar1 = (u64)(int)uVar1;
  }
  else if (((uVar1 < (ulong)(long)SymbolTable2) || (0x7ffffff < uVar1)) && (0x7bfff < obj - 0x84000)
          ) {
    cprintf("#<invalid object #x%x>\n",uVar1);
  }
  else {
    if (uVar2 == 2) {
      uVar1 = inspect_pair(obj);
      return uVar1;
    }
    if ((((uVar1 & 1) != 0) && ((ulong)(long)SymbolTable2 <= uVar1)) &&
       (uVar1 < (ulong)(long)LastSymbol)) {
      uVar1 = inspect_symbol(obj);
      return uVar1;
    }
    if (uVar2 == 4) {
      uVar1 = call_method_of_type(obj,*(Type **)(obj - 4),3);
      return uVar1;
    }
    cprintf("#<unknown type %d @ #x%x>",uVar2,uVar1);
  }
  return uVar1;
}

/*!
 * Inspect a pair.
 */
u64 inspect_pair(u32 obj) {
  cprintf("[%8x] pair ",(long)(int)obj);
  print_pair(obj);
  cprintf("\n");
  return (long)(int)obj;
}

/*!
 * Inspect a string. There's a typo in allocated_length (has underscore instead of dash).
 * This typo is fixed in later games.
 */
u64 inspect_string(u32 obj) {
  ulong uVar1;
  int unaff_s7_lo;
  
  uVar1 = (ulong)(int)obj;
  if ((((uVar1 < (ulong)(long)SymbolTable2) || (0x7ffffff < uVar1)) && (0x7bfff < obj - 0x84000)) ||
     (((uVar1 & 7) != 4 || (*(int *)(obj - 4) != *(int *)(unaff_s7_lo + 0xf))))) {
    cprintf("#<invalid string #x%x>\n",uVar1);
  }
  else {
    cprintf("[%8x] string\n\tallocated-length: %d\n\tdata: \"%s\"\n",uVar1,*(undefined4 *)obj,
            obj + 4);
  }
  return uVar1;
}

/*!
 * Inspect a symbol.
 */
u64 inspect_symbol(u32 obj) {
  ulong uVar1;
  int unaff_s7_lo;
  
  uVar1 = (ulong)(int)obj;
  if ((((uVar1 < (ulong)(long)SymbolTable2) || (0x7ffffff < uVar1)) && (0x7bfff < obj - 0x84000)) ||
     (((((uVar1 ^ 1) & 1) != 0 || (uVar1 < (ulong)(long)SymbolTable2)) ||
      ((ulong)(long)LastSymbol <= uVar1)))) {
    cprintf("#<invalid symbol #x%x>\n",uVar1);
  }
  else {
    cprintf("[%8x] symbol\n\tname: %s\n\tvalue: ",uVar1,
            *(int *)((obj - unaff_s7_lo) + SymbolString) + 4);
    print_object(*(u32 *)(obj - 1));
    cprintf("\n");
  }
  return uVar1;
}

/*!
 * Inspect a type.
 */
u64 inspect_type(u32 obj) {
  ulong uVar1;
  int unaff_s7_lo;
  
  uVar1 = (ulong)(int)obj;
  if ((((uVar1 < (ulong)(long)SymbolTable2) || (0x7ffffff < uVar1)) && (0x7bfff < obj - 0x84000)) ||
     (((uVar1 & 7) != 4 || (*(int *)(obj - 4) != *(int *)(unaff_s7_lo + 0x17))))) {
    cprintf("#<invalid type #x%x>\n",uVar1);
  }
  else {
    cprintf("[%8x] type\n\tname: %s\n\tparent: ",uVar1,
            *(int *)((*(int *)obj - unaff_s7_lo) + SymbolString) + 4);
    print_object(*(u32 *)(obj + 4));
    cprintf("\n\tsize: %d/%d\n\theap-base: %d\n\tallocated-length: %d\n\tprint: ",
            (ulong)*(ushort *)(obj + 8),(ulong)*(ushort *)(obj + 10),(ulong)*(ushort *)(obj + 0xc),
            (ulong)*(ushort *)(obj + 0xe));
    print_object(*(u32 *)(obj + 0x18));
    cprintf("\n\tinspect: ");
    print_object(*(u32 *)(obj + 0x1c));
    cprintf("\n\tmem-usage: ");
    print_object(*(u32 *)(obj + 0x30));
    cprintf("\n");
  }
  return uVar1;
}

/*!
 * Inspect a basic. This is just a fallback for basics which don't know how to inspect themselves.
 * We just use print_object.
 */
u64 inspect_basic(u32 obj) {
  u64 uVar1;
  ulong uVar2;
  ulong unaff_s7;
  
  uVar2 = (ulong)(int)obj;
  if ((((uVar2 < (ulong)(long)SymbolTable2) || (0x7ffffff < uVar2)) && (0x7bfff < obj - 0x84000)) ||
     ((uVar2 & 7) != 4)) {
    if (uVar2 == unaff_s7) {
      uVar1 = inspect_symbol(obj);
      return uVar1;
    }
    cprintf("#<invalid basic #x%x>\n",uVar2);
  }
  else {
    cprintf("[%8x] ",uVar2);
    print_object(*(u32 *)(obj - 4));
    cprintf("\n");
  }
  return uVar2;
}

/*!
 * Inspect a link block. This link block doesn't seem to be used at all.
 */
u64 inspect_link_block(u32 ob) {
  cprintf("[%8x] link-block\n\tallocated-length: %d\n\tversion: %d\n\tfunction: ",(long)(int)ob,
          *(undefined4 *)ob,*(undefined2 *)(ob + 4));
  print_object(ob + *(int *)ob);
  cprintf("\n");
  return (long)(int)ob;
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
  int iVar1;
  int iVar2;
  uint uVar3;
  u8 *puVar4;
  u8 *puVar5;
  u32 uVar6;
  Function *pFVar7;
  Function *pFVar8;
  Function *pFVar9;
  Function *pFVar10;
  u32 *puVar11;
  int iVar12;
  undefined uVar13;
  undefined uVar14;
  u8 *value;
  
  puVar4 = kmalloc((kheapinfo *)&DAT_0025bb70,0x10000,0x1000,"symbol-table");
  puVar5 = kmalloc((kheapinfo *)&DAT_0025bb70,0x10000,0x1000,"string-table");
  SymbolTable2 = puVar4 + 5;
  SymbolString = puVar5 + 0x8000;
  LastSymbol = puVar4 + 0xff00;
  value = puVar4 + 0x8001;
  NumSymbols = 0;
  uVar14 = 0x20;
  reset_output();
  *(u8 **)(puVar4 + 0x7ff8) = puVar4 + 0x7ffa;
  *(undefined **)(puVar4 + 0x80a0) = &DAT_0025bb70;
  *(u8 **)(puVar4 + 0x7ffc) = puVar4 + 0x7ffa;
  UnknownName = make_string_from_c("*unknown-symbol-name*");
  alloc_and_init_type(puVar4 + 0x8019,9,true);
  alloc_and_init_type(puVar4 + 0x8015,9,true);
  alloc_and_init_type(puVar4 + 0x8011,9,true);
  alloc_and_init_type(puVar4 + 0x8009,9,true);
  set_fixed_symbol(FIX_SYM_FALSE,"#f",(u32)value);
  set_fixed_symbol(FIX_SYM_TRUE,"#t",(u32)(puVar4 + 0x8005));
  uVar6 = make_nothing_func();
  set_fixed_symbol(FIX_SYM_NOTHING_FUNC,"nothing",uVar6);
  uVar6 = make_zero_func();
  uVar13 = 0x60;
  set_fixed_symbol(FIX_SYM_ZERO_FUNC,"zero-func",uVar6);
  pFVar7 = make_function_from_c(asize_of_basic,(bool)uVar13);
  uVar13 = uVar14;
  set_fixed_symbol(FIX_SYM_ASIZE_OF_BASIC_FUNC,"asize-of-basic-func",(u32)pFVar7);
  pFVar7 = make_function_from_c(copy_basic,(bool)uVar13);
  set_fixed_symbol(FIX_SYM_COPY_BASIC_FUNC,"asize-of-basic-func",(u32)pFVar7);
  pFVar7 = make_function_from_c(delete_basic,(bool)uVar14);
  set_fixed_symbol(FIX_SYM_DELETE_BASIC,"delete-basic",(u32)pFVar7);
  set_fixed_symbol(FIX_SYM_GLOBAL_HEAP,"global",(u32)&DAT_0025bb70);
  set_fixed_symbol(FIX_SYM_DEBUG,"debug",(u32)kdebugheap);
  set_fixed_symbol(FIX_SYM_STATIC,"static",(u32)(puVar4 + 0x809d));
  set_fixed_symbol(FIX_SYM_LOADING_LEVEL,"loading-level",(u32)&DAT_0025bb70);
  set_fixed_symbol(FIX_SYM_LOADING_PACKAGE,"loading-package",(u32)&DAT_0025bb70);
  set_fixed_symbol(FIX_SYM_PROCESS_LEVEL_HEAP,"process-level-heap",(u32)&DAT_0025bb70);
  set_fixed_symbol(FIX_SYM_STACK,"stack",(u32)(puVar4 + 0x80b5));
  set_fixed_symbol(FIX_SYM_SCRATCH,"scratch",(u32)(puVar4 + 0x80b9));
  set_fixed_symbol(FIX_SYM_SCRATCH_TOP,"*scratch-top*",0x70000000);
  set_fixed_symbol(FIX_SYM_LEVEL,"level",0);
  set_fixed_symbol(FIX_SYM_ART_GROUP,"art-group",0);
  set_fixed_symbol(FIX_SYM_TEXTURE_PAGE_DIR,"texture-page-dir",0);
  set_fixed_symbol(FIX_SYM_TEXTURE_PAGE,"texture-page",0);
  set_fixed_symbol(FIX_SYM_SOUND,"sound",0);
  set_fixed_symbol(FIX_SYM_DGO,"dgo",0);
  set_fixed_symbol(FIX_SYM_TOP_LEVEL,"top-level",*(u32 *)(puVar4 + 0x8094));
  set_fixed_symbol(FIX_SYM_QUOTE,"quote",(u32)(puVar4 + 0x80e9));
  set_fixed_symbol(FIX_SYM_LISTENER_LINK_BLOCK,"*listener-link-block*",0);
  set_fixed_symbol(FIX_SYM_LISTENER_FUNCTION,"*listener-function*",0);
  set_fixed_symbol(FIX_SYM_STACK_TOP,"*stack-top*",0);
  set_fixed_symbol(FIX_SYM_STACK_BASE,"*stack-base*",0);
  set_fixed_symbol(FIX_SYM_STACK_SIZE,"*stack-size*",0);
  set_fixed_symbol(FIX_SYM_KERNEL_FUNCTION,"*kernel-function*",0);
  set_fixed_symbol(FIX_SYM_KERNEL_PACKAGES,"*kernel-packages*",0);
  set_fixed_symbol(FIX_SYM_KERNEL_BOOT_MESSAGE,"*kernel-boot-message*",0);
  set_fixed_symbol(FIX_SYM_KERNEL_BOOT_MODE,"*kernel-boot-mode*",0);
  set_fixed_symbol(FIX_SYM_KERNEL_BOOT_LEVEL,"*kernel-boot-level*",0);
  set_fixed_symbol(FIX_SYM_KERNEL_BOOT_ART_GROUP,"*kernel-boot-art-group*",0);
  set_fixed_symbol(FIX_SYM_KERNEL_DEBUG,"*kernel-debug*",0);
  set_fixed_symbol(FIX_SYM_KERNEL_VERSION,"*kernel-version*",0);
  set_fixed_symbol(FIX_SYM_KERNEL_DISPATCHER,"kernel-dispatcher",0);
  set_fixed_symbol(FIX_SYM_SYNC_DISPATCHER,"sync-dispatcher",0);
  set_fixed_symbol(FIX_SYM_PRINT_COLLUMN,"*print-column*",0);
  set_fixed_symbol(FIX_SYM_DEBUG_SEGMENT,"*debug-segment*",0);
  set_fixed_symbol(FIX_SYM_ENABLE_METHOD_SET,"*enable-method-set*",0);
  set_fixed_symbol(FIX_SYM_SQL_RESULT,"*sql-result*",0);
  set_fixed_symbol(FIX_SYM_COLLAPSE_QUOTE,"*collapse-quote*",0);
  set_fixed_symbol(FIX_SYM_LEVEL_TYPE_LIST,"*level-type-list*",0);
  set_fixed_symbol(FIX_SYM_DECI_COUNT,"*deci-count*",0);
  set_fixed_symbol(FIX_SYM_USER,"*user*",0);
  set_fixed_symbol(FIX_SYM_VIDEO_MODE,"*video-mode*",0);
  set_fixed_symbol(FIX_SYM_BOOT_VIDEO_MODE,"*boot-video-mode*",0);
  set_fixed_symbol(FIX_SYM_BOOT,"boot",0);
  set_fixed_symbol(FIX_SYM_DEMO,"demo",0);
  set_fixed_symbol(FIX_SYM_DEMO_SHARED,"demo-shared",0);
  set_fixed_symbol(FIX_SYM_PREVIEW,"preview",0);
  set_fixed_symbol(FIX_SYM_KIOSK,"kiosk",0);
  set_fixed_symbol(FIX_SYM_BETA,"beta",0);
  set_fixed_symbol(FIX_SYM_PLAY_BOOT,"play-boot",0);
  set_fixed_symbol(FIX_SYM_SIN,"sin",0);
  set_fixed_symbol(FIX_SYM_COS,"cos",0);
  set_fixed_symbol(FIX_SYM_PUT_DISPLAY_ENV,"put-display-env",0);
  set_fixed_symbol(FIX_SYM_SYNCV,"syncv",0);
  set_fixed_symbol(FIX_SYM_SYNC_PATH,"sync-path",0);
  set_fixed_symbol(FIX_SYM_RESET_PATH,"reset-path",0);
  set_fixed_symbol(FIX_SYM_RESET_GRAPH,"reset-graph",0);
  set_fixed_symbol(FIX_SYM_DMA_SYNC,"dma-sync",0);
  set_fixed_symbol(FIX_SYM_GS_PUT_IMR,"gs-put-imr",0);
  set_fixed_symbol(FIX_SYM_GS_GET_IMR,"gs-get-imr",0);
  set_fixed_symbol(FIX_SYM_GS_STORE_IMAGE,"gs-store-image",0);
  set_fixed_symbol(FIX_SYM_FLUSH_CACHE,"flush-cache",0);
  set_fixed_symbol(FIX_SYM_CPAD_OPEN,"cpad-open",0);
  set_fixed_symbol(FIX_SYM_CPAD_GET_DATA,"cpad-get-data",0);
  set_fixed_symbol(FIX_SYM_MOUSE_GET_DATA,"mouse-get-data",0);
  set_fixed_symbol(FIX_SYM_KEYBD_GET_DATA,"keybd-get-data",0);
  set_fixed_symbol(FIX_SYM_INSTALL_HANDLER,"install-handler",0);
  set_fixed_symbol(FIX_SYM_INSTALL_DEBUG_HANDLER,"install-debug-handler",0);
  set_fixed_symbol(FIX_SYM_FILE_STREAM_OPEN,"file-stream-open",0);
  set_fixed_symbol(FIX_SYM_FILE_STREAM_CLOSE,"file-stream-close",0);
  set_fixed_symbol(FIX_SYM_FILE_STREAM_LENGTH,"file-stream-length",0);
  set_fixed_symbol(FIX_SYM_FILE_STREAM_SEEK,"file-stream-seek",0);
  set_fixed_symbol(FIX_SYM_FILE_STREAM_READ,"file-stream-read",0);
  set_fixed_symbol(FIX_SYM_FILE_STREAM_WRITE,"file-stream-write",0);
  set_fixed_symbol(FIX_SYM_FILE_STREAM_WRITE,"file-stream-write",0);
  set_fixed_symbol(FIX_SYM_FILE_STREAM_MKDIR,"file-stream-mkdir",0);
  set_fixed_symbol(FIX_SYM_SCF_GET_LANGUAGE,"scf-get-language",0);
  set_fixed_symbol(FIX_SYM_SCF_GET_TIME,"scf-get-time",0);
  set_fixed_symbol(FIX_SYM_SCF_GET_ASPECT,"scf-get-aspect",0);
  set_fixed_symbol(FIX_SYM_SCF_GET_VOLUME,"scf-get-volume",0);
  set_fixed_symbol(FIX_SYM_SCF_GET_TERRITORY,"scf-get-territory",0);
  set_fixed_symbol(FIX_SYM_SCF_GET_TIMEOUT,"scf-get-timeout",0);
  set_fixed_symbol(FIX_SYM_SCF_GET_INACTIVE_TIMEOUT,"scf-get-inactive-timeout",0);
  set_fixed_symbol(FIX_SYM_DMA_TO_IOP,"dma-to-iop",0);
  set_fixed_symbol(FIX_SYM_KERNEL_SHUTDOWN,"kernel-shutdown",0);
  set_fixed_symbol(FIX_SYM_AYBABTU,"aybabtu",0);
  set_fixed_symbol(FIX_SYM_STRING_TO_SYMBOL,"string->symbol",0);
  set_fixed_symbol(FIX_SYM_SYMBOL_TO_STRING,"symbol->string",0);
  set_fixed_symbol(FIX_SYM_PRINT,"print",0);
  set_fixed_symbol(FIX_SYM_INSPECT,"inspect",0);
  set_fixed_symbol(FIX_SYM_LOAD,"load",0);
  set_fixed_symbol(FIX_SYM_LOADB,"loadb",0);
  set_fixed_symbol(FIX_SYM_LOADO,"loado",0);
  set_fixed_symbol(FIX_SYM_UNLOAD,"unload",0);
  set_fixed_symbol(FIX_SYM_FORMAT,"_format",0);
  set_fixed_symbol(FIX_SYM_MALLOC,"malloc",0);
  set_fixed_symbol(FIX_SYM_KMALLOC,"kmalloc",0);
  set_fixed_symbol(FIX_SYM_KMEMOPEN,"kmemopen",0);
  set_fixed_symbol(FIX_SYM_KMEMCLOSE,"kmemclose",0);
  set_fixed_symbol(FIX_SYM_NEW_DYNAMIC_STRUCTURE,"new-dynamic-structure",0);
  set_fixed_symbol(FIX_SYM_METHOD_SET,"method-set!",0);
  set_fixed_symbol(FIX_SYM_LINK,"link",0);
  set_fixed_symbol(FIX_SYM_LINK_BUSY,"link-busy?",0);
  set_fixed_symbol(FIX_SYM_LINK_RESET,"link-reset",0);
  set_fixed_symbol(FIX_SYM_LINK_BEGIN,"link-begin",0);
  set_fixed_symbol(FIX_SYM_LINK_RESUME,"link-resume",0);
  set_fixed_symbol(FIX_SYM_DGO_LOAD,"dgo-load",0);
  set_fixed_symbol(FIX_SYM_SQL_QUERY,"sql-query",0);
  set_fixed_symbol(FIX_SYM_MC_RUN,"mc-run",0);
  set_fixed_symbol(FIX_SYM_MC_FORMAT,"mc-format",0);
  set_fixed_symbol(FIX_SYM_MC_UNFORMAT,"mc-unformat",0);
  set_fixed_symbol(FIX_SYM_MC_CREATE_FILE,"mc-create-file",0);
  set_fixed_symbol(FIX_SYM_MC_SAVE,"mc-save",0);
  set_fixed_symbol(FIX_SYM_MC_LOAD,"mc-load",0);
  set_fixed_symbol(FIX_SYM_MC_CHECK_RESULT,"mc-check-result",0);
  set_fixed_symbol(FIX_SYM_MC_GET_SLOT_INFO,"mc-get-slot-info",0);
  set_fixed_symbol(FIX_SYM_MC_MAKEFILE,"mc-makefile",0);
  set_fixed_symbol(FIX_SYM_KSET_LANGUAGE,"kset-language",0);
  set_fixed_symbol(FIX_SYM_RPC_CALL,"rpc-call",0);
  set_fixed_symbol(FIX_SYM_RPC_BUSY,"rpc-busy?",0);
  set_fixed_symbol(FIX_SYM_TEST_LOAD_DGO_C,"test-load-dgo-c",0);
  set_fixed_symbol(FIX_SYM_SYMLINK2,"symlink2",0);
  set_fixed_symbol(FIX_SYM_SYMLINK3,"symlink3",0);
  set_fixed_symbol(FIX_SYM_ULTIMATE_MEMCPY,"ultimate-memcpy",0);
  set_fixed_symbol(FIX_SYM_PLAY,"play",0);
  set_fixed_symbol(FIX_SYM_SYMBOL_STRING,"*symbol-string*",(u32)SymbolString);
  set_fixed_symbol(FIX_SYM_KERNEL_SYMBOL_WARNINGS,"*kernel-symbol-warnings*",(u32)(puVar4 + 0x8005))
  ;
  uVar13 = 0x48;
  set_fixed_symbol(FIX_SYM_NETWORK_BOOTSTRAP,"network-bootstrap",0);
  pFVar7 = make_function_from_c(new_illegal,(bool)uVar13);
  pFVar8 = make_function_from_c(delete_illegal,(bool)uVar13);
  pFVar9 = make_function_from_c(print_object,(bool)uVar13);
  pFVar10 = make_function_from_c(inspect_object,(bool)uVar13);
  uVar13 = 0x60;
  set_fixed_type(FIX_SYM_OBJECT_TYPE,"object",(Symbol4 *)(puVar4 + 0x801d),0x900000004,(u32)pFVar9,
                 (u32)pFVar10);
  iVar12 = *(int *)(puVar4 + 0x801c);
  iVar1 = *(int *)(puVar4 + 0x801c);
  *(undefined4 *)(iVar12 + 0x10) = *(undefined4 *)(puVar4 + 0x8094);
  iVar2 = *(int *)(puVar4 + 0x801c);
  *(Function **)(iVar1 + 0x14) = pFVar8;
  *(undefined4 *)(iVar12 + 0x24) = *(undefined4 *)(puVar4 + 0x80c0);
  pFVar9 = make_function_from_c(copy_fixed,(bool)uVar13);
  *(Function **)(iVar2 + 0x28) = pFVar9;
  pFVar9 = make_function_from_c(print_structure,(bool)uVar13);
  pFVar10 = make_function_from_c(inspect_structure,(bool)uVar13);
  uVar13 = 0x68;
  set_fixed_type(FIX_SYM_STRUCTURE,"structure",(Symbol4 *)(puVar4 + 0x801d),0x900000004,(u32)pFVar9,
                 (u32)pFVar10);
  iVar12 = *(int *)(puVar4 + 0x806c);
  pFVar9 = make_function_from_c(new_structure,(bool)uVar13);
  *(Function **)(iVar12 + 0x10) = pFVar9;
  iVar12 = *(int *)(puVar4 + 0x806c);
  pFVar9 = make_function_from_c(delete_structure,(bool)uVar13);
  *(Function **)(iVar12 + 0x14) = pFVar9;
  pFVar9 = make_function_from_c(print_basic,(bool)uVar13);
  pFVar10 = make_function_from_c(inspect_basic,(bool)uVar13);
  uVar13 = 0x78;
  set_fixed_type(FIX_SYM_BASIC,"basic",(Symbol4 *)(puVar4 + 0x806d),0x900000004,(u32)pFVar9,
                 (u32)pFVar10);
  iVar12 = *(int *)(puVar4 + 0x800c);
  pFVar9 = make_function_from_c(new_basic,(bool)uVar13);
  iVar1 = *(int *)(puVar4 + 0x800c);
  *(Function **)(iVar12 + 0x10) = pFVar9;
  iVar12 = *(int *)(puVar4 + 0x800c);
  *(undefined4 *)(iVar1 + 0x14) = *(undefined4 *)(puVar4 + 0x8098);
  *(undefined4 *)(iVar12 + 0x24) = *(undefined4 *)(puVar4 + 0x80c4);
  *(undefined4 *)(iVar1 + 0x28) = *(undefined4 *)(puVar4 + 0x80c8);
  pFVar9 = make_function_from_c(print_symbol,(bool)uVar13);
  pFVar10 = make_function_from_c(inspect_symbol,(bool)uVar13);
  uVar13 = 0x80;
  set_fixed_type(FIX_SYM_SYMBOL_TYPE,"symbol",(Symbol4 *)(puVar4 + 0x801d),0x900000004,(u32)pFVar9,
                 (u32)pFVar10);
  iVar12 = *(int *)(puVar4 + 0x8014);
  *(Function **)(*(int *)(puVar4 + 0x8014) + 0x10) = pFVar7;
  *(Function **)(iVar12 + 0x14) = pFVar8;
  pFVar9 = make_function_from_c(print_type,(bool)uVar13);
  pFVar10 = make_function_from_c(inspect_type,(bool)uVar13);
  uVar13 = 0x88;
  set_fixed_type(FIX_SYM_TYPE_TYPE,"type",(Symbol4 *)(puVar4 + 0x800d),0x900000038,(u32)pFVar9,
                 (u32)pFVar10);
  iVar12 = *(int *)(puVar4 + 0x8018);
  pFVar9 = make_function_from_c(new_type,(bool)uVar13);
  iVar1 = *(int *)(puVar4 + 0x8018);
  *(Function **)(iVar12 + 0x10) = pFVar9;
  *(Function **)(iVar1 + 0x14) = pFVar8;
  pFVar9 = make_function_from_c(print_string,(bool)uVar13);
  pFVar10 = make_function_from_c(inspect_string,(bool)uVar13);
  uVar13 = 0x90;
  set_fixed_type(FIX_SYM_STRING_TYPE,"string",(Symbol4 *)(puVar4 + 0x800d),0x900000008,(u32)pFVar9,
                 (u32)pFVar10);
  pFVar9 = make_function_from_c(print_function,(bool)uVar13);
  uVar13 = 0x98;
  set_fixed_type(FIX_SYM_FUNCTION_TYPE,"function",(Symbol4 *)(puVar4 + 0x800d),0x900000004,
                 (u32)pFVar9,0);
  iVar12 = *(int *)(puVar4 + 0x8008);
  *(Function **)(*(int *)(puVar4 + 0x8008) + 0x10) = pFVar7;
  *(Function **)(iVar12 + 0x14) = pFVar8;
  pFVar9 = make_function_from_c(print_vu_function,(bool)uVar13);
  pFVar10 = make_function_from_c(inspect_vu_function,(bool)uVar13);
  uVar13 = 0xa8;
  set_fixed_type(FIX_SYM_VU_FUNCTION,"vu-function",(Symbol4 *)(puVar4 + 0x806d),0x900000010,
                 (u32)pFVar9,(u32)pFVar10);
  *(Function **)(*(int *)(puVar4 + 0x8080) + 0x14) = pFVar8;
  pFVar9 = make_function_from_c(inspect_link_block,(bool)uVar13);
  uVar13 = 0xb8;
  set_fixed_type(FIX_SYM_LINK_BLOCK,"link-block",(Symbol4 *)(puVar4 + 0x800d),0x90000000c,0,
                 (u32)pFVar9);
  iVar12 = *(int *)(puVar4 + 0x8020);
  *(Function **)(*(int *)(puVar4 + 0x8020) + 0x10) = pFVar7;
  *(Function **)(iVar12 + 0x14) = pFVar8;
  pFVar8 = make_function_from_c(kheapstatus,(bool)uVar13);
  set_fixed_type(FIX_SYM_HEAP,"kheap",(Symbol4 *)(puVar4 + 0x806d),0x900000010,0,(u32)pFVar8);
  uVar13 = 0xd0;
  set_fixed_type(FIX_SYM_ARRAY,"array",(Symbol4 *)(puVar4 + 0x800d),0x900000010,0,0);
  pFVar8 = make_function_from_c(print_pair,(bool)uVar13);
  pFVar9 = make_function_from_c(inspect_pair,(bool)uVar13);
  uVar13 = 0xd8;
  set_fixed_type(FIX_SYM_PAIR_TYPE,"pair",(Symbol4 *)(puVar4 + 0x801d),0x900000008,(u32)pFVar8,
                 (u32)pFVar9);
  iVar12 = *(int *)(puVar4 + 0x8070);
  pFVar8 = make_function_from_c(new_pair,(bool)uVar13);
  *(Function **)(iVar12 + 0x10) = pFVar8;
  iVar12 = *(int *)(puVar4 + 0x8070);
  pFVar8 = make_function_from_c(delete_pair,(bool)uVar13);
  *(Function **)(iVar12 + 0x14) = pFVar8;
  set_fixed_type(FIX_SYM_PROCESS_TREE,"process-tree",(Symbol4 *)(puVar4 + 0x800d),0xf0000002c,0,0);
  set_fixed_type(FIX_SYM_PROCESS_TYPE,"process",(Symbol4 *)(puVar4 + 0x8061),0xf00000090,0,0);
  set_fixed_type(FIX_SYM_THREAD,"thread",(Symbol4 *)(puVar4 + 0x800d),0xc00000028,0,0);
  set_fixed_type(FIX_SYM_CONNECTABLE,"connectable",(Symbol4 *)(puVar4 + 0x806d),0x900000010,0,0);
  set_fixed_type(FIX_SYM_STACK_FRAME,"stack-frame",(Symbol4 *)(puVar4 + 0x800d),0x90000000c,0,0);
  set_fixed_type(FIX_SYM_FILE_STREAM,"file-stream",(Symbol4 *)(puVar4 + 0x800d),0x900000014,0,0);
  uVar13 = 0x30;
  set_fixed_type(FIX_SYM_POINTER,"pointer",(Symbol4 *)(puVar4 + 0x801d),0x900000004,0,0);
  *(Function **)(*(int *)(puVar4 + 0x8074) + 0x10) = pFVar7;
  pFVar8 = make_function_from_c(print_integer,(bool)uVar13);
  pFVar9 = make_function_from_c(inspect_integer,(bool)uVar13);
  uVar13 = 0x38;
  set_fixed_type(FIX_SYM_NUMBER,"number",(Symbol4 *)(puVar4 + 0x801d),0x900000008,(u32)pFVar8,
                 (u32)pFVar9);
  *(Function **)(*(int *)(puVar4 + 0x8078) + 0x10) = pFVar7;
  pFVar7 = make_function_from_c(print_float,(bool)uVar13);
  pFVar8 = make_function_from_c(inspect_float,(bool)uVar13);
  set_fixed_type(FIX_SYM_FLOAT,"float",(Symbol4 *)(puVar4 + 0x8079),0x900000004,(u32)pFVar7,
                 (u32)pFVar8);
  uVar13 = 0x48;
  set_fixed_type(FIX_SYM_INTEGER,"integer",(Symbol4 *)(puVar4 + 0x8079),0x900000008,0,0);
  pFVar7 = make_function_from_c(print_binteger,(bool)uVar13);
  pFVar8 = make_function_from_c(inspect_binteger,(bool)uVar13);
  set_fixed_type(FIX_SYM_BINTEGER,"binteger",(Symbol4 *)(puVar4 + 0x8025),0x900000008,(u32)pFVar7,
                 (u32)pFVar8);
  set_fixed_type(FIX_SYM_SINTEGER,"sinteger",(Symbol4 *)(puVar4 + 0x8025),0x900000008,0,0);
  set_fixed_type(FIX_SYM_INT8,"int8",(Symbol4 *)(puVar4 + 0x8029),0x900000001,0,0);
  set_fixed_type(FIX_SYM_INT16,"int16",(Symbol4 *)(puVar4 + 0x8029),0x900000002,0,0);
  set_fixed_type(FIX_SYM_INT32,"int32",(Symbol4 *)(puVar4 + 0x8029),0x900000004,0,0);
  set_fixed_type(FIX_SYM_INT64,"int64",(Symbol4 *)(puVar4 + 0x8029),0x900000008,0,0);
  set_fixed_type(FIX_SYM_INT128,"int128",(Symbol4 *)(puVar4 + 0x8029),0x900000010,0,0);
  set_fixed_type(FIX_SYM_UINTEGER,"uinteger",(Symbol4 *)(puVar4 + 0x8025),0x900000008,0,0);
  set_fixed_type(FIX_SYM_UINT8,"uint8",(Symbol4 *)(puVar4 + 0x802d),0x900000001,0,0);
  set_fixed_type(FIX_SYM_UINT16,"uint16",(Symbol4 *)(puVar4 + 0x802d),0x900000002,0,0);
  set_fixed_type(FIX_SYM_UINT32,"uint32",(Symbol4 *)(puVar4 + 0x802d),0x900000004,0,0);
  set_fixed_type(FIX_SYM_UINT64,"uint64",(Symbol4 *)(puVar4 + 0x802d),0x900000008,0,0);
  uVar14 = 0;
  uVar13 = 200;
  set_fixed_type(FIX_SYM_UINT128,"uint128",(Symbol4 *)(puVar4 + 0x802d),0x900000010,0,0);
  iVar12 = *(int *)(puVar4 + 0x801c);
  pFVar7 = make_function_from_c(alloc_heap_object,(bool)uVar13);
  *(Function **)(iVar12 + 0x10) = pFVar7;
  make_function_symbol_from_c("string->symbol",intern);
  make_function_symbol_from_c("symbol->string",symbol_to_string_from_c);
  make_function_symbol_from_c("print",sprint);
  make_function_symbol_from_c("inspect",inspect_object);
  make_function_symbol_from_c("load",load);
  make_function_symbol_from_c("loadb",loadb);
  make_function_symbol_from_c("loado",loado);
  make_function_symbol_from_c("unload",unload);
  make_function_symbol_from_c("_format",format_impl_jak3);
  make_function_symbol_from_c("malloc",alloc_heap_memory);
  make_function_symbol_from_c("kmalloc",goal_malloc);
  make_function_symbol_from_c("kmemopen",kmemopen);
  make_function_symbol_from_c("kmemclose",kmemclose);
  make_function_symbol_from_c("new-dynamic-structure",new_dynamic_structure);
  make_function_symbol_from_c("method-set!",method_set);
  make_function_symbol_from_c("link",link_and_exec);
  make_function_symbol_from_c("link-busy?",link_busy);
  make_function_symbol_from_c("link-reset",link_reset);
  make_function_symbol_from_c("dgo-load",load_and_link_dgo);
  make_raw_function_symbol_from_c("ultimate-memcpy",0);
  make_raw_function_symbol_from_c("symlink2",0);
  make_raw_function_symbol_from_c("symlink3",0);
  make_function_symbol_from_c("link-begin",link_begin);
  make_function_symbol_from_c("link-resume",link_resume);
  make_function_symbol_from_c("sql-query",sql_query_sync);
  make_function_symbol_from_c("mc-run",MC_run);
  make_function_symbol_from_c("mc-format",MC_format);
  make_function_symbol_from_c("mc-unformat",MC_unformat);
  make_function_symbol_from_c("mc-create-file",MC_createfile);
  make_function_symbol_from_c("mc-save",MC_save);
  make_function_symbol_from_c("mc-load",MC_load);
  make_function_symbol_from_c("mc-check-result",MC_check_result);
  make_function_symbol_from_c("mc-get-slot-info",MC_get_status);
  make_function_symbol_from_c("mc-makefile",MC_makefile);
  make_function_symbol_from_c("kset-language",MC_set_language);
  make_function_symbol_from_c("network-bootstrap",network_bootstrapProxy);
  puVar11 = intern_from_c(-1,0,"*debug-segment*");
  puVar5 = puVar4 + 0x8005;
  if (DebugSegment == 0) {
    puVar5 = value;
  }
  *(u8 **)((int)puVar11 + -1) = puVar5;
  puVar11 = intern_from_c(-1,0,"*enable-method-set*");
  EnableMethodSet = (int *)((int)puVar11 + -1);
  *(undefined4 *)((int)puVar11 + -1) = 0;
  puVar11 = intern_from_c(-1,0,"*kernel-debug*");
  DAT_002836f0 = (int)puVar11 + -1;
  *(undefined4 *)((int)puVar11 + -1) = 0;
  puVar11 = intern_from_c(-1,0,"*boot-video-mode*");
  *(undefined4 *)((int)puVar11 + -1) = 1;
  puVar11 = intern_from_c(-1,0,"*video-mode*");
  *(undefined4 *)((int)puVar11 + -1) = 1;
  SqlResult = intern_from_c(-1,0,"*sql-result*");
  *(u8 **)((int)SqlResult + -1) = value;
  CollapseQuote = intern_from_c(-1,0,"*collapse-quote*");
  *(u8 **)((int)CollapseQuote + -1) = puVar4 + 0x8005;
  LevelTypeList = intern_from_c(-1,0,"*level-type-list*");
  *EnableMethodSet = *EnableMethodSet + 1;
  load_and_link_dgo_from_c("kernel",(kheapinfo *)&DAT_0025bb70,0xd,0x400000,(bool)uVar14);
  *EnableMethodSet = *EnableMethodSet + -1;
  puVar11 = intern_from_c(-1,0,"*kernel-version*");
  uVar3 = *(uint *)((int)puVar11 + -1);
  if ((uVar3 == 0) || (uVar3 >> 0x13 != 0x16)) {
    MsgErr("\n");
    MsgErr("dkernel: compiled C kernel version is %d.%d but the goal kernel is %d.%d!\n\tfrom the goal> prompt (:mch) then mkee your kernel in linux.\n"
           ,0x16,0,uVar3 >> 0x13,uVar3 >> 3 & 0xffff);
    iVar12 = -1;
  }
  else {
    protoBlock.deci2count = (s32)intern_from_c(-1,0,"*deci-count*");
    InitListener();
    InitMachineScheme();
    kmemclose();
    iVar12 = 0;
  }
  return iVar12;
}

u64 load(u32 file_name_in,u32 heap_in) {
  undefined4 uVar1;
  char *__src;
  u64 uVar2;
  int unaff_s7_lo;
  undefined4 unaff_s7_hi;
  char acStack_120 [256];
  
  uVar1 = *(undefined4 *)(unaff_s7_lo + 0xab);
  *(u32 *)(unaff_s7_lo + 0xab) = heap_in;
  __src = DecodeFileName((const_char *)(file_name_in + 4));
  strcpy(acStack_120,__src);
  uVar2 = load_and_link((const_char *)(file_name_in + 4),acStack_120,(kheapinfo *)heap_in,0xf);
  *(undefined4 *)(unaff_s7_lo + 0xab) = uVar1;
  if ((uVar2 & 0xfffffffffff00000) == 0xfffffffffff00000) {
    uVar2 = CONCAT44(unaff_s7_hi,unaff_s7_lo);
  }
  return uVar2;
}

u64 loadb(u32 file_name_in,u32 heap_in,u32 param3) {
  char *__src;
  u8 *puVar1;
  ulong uVar2;
  u64 unaff_s7;
  char acStack_120 [256];
  
  __src = DecodeFileName((const_char *)(file_name_in + 4));
  strcpy(acStack_120,__src);
  puVar1 = FileLoad(acStack_120,(kheapinfo *)heap_in,(u8 *)0x0,0x40,(s32 *)param3);
  uVar2 = (long)(int)puVar1;
  if (((long)(int)puVar1 & 0xfffffffffff00000U) == 0xfffffffffff00000) {
    uVar2 = unaff_s7;
  }
  return uVar2;
}

u64 loadc(const_char *file_name,kheapinfo *heap,u32 flags) {
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

u64 loado(u32 file_name_in,u32 heap_in) {
  char *__src;
  ulong uVar1;
  const_char *name;
  u64 unaff_s7;
  char acStack_120 [256];
  
  name = (const_char *)(file_name_in + 4);
  printf("****** CALL TO loado(%s) ******\n",name);
  __src = MakeFileName(0x20,name,0);
  strcpy(acStack_120,__src);
  uVar1 = load_and_link(name,acStack_120,(kheapinfo *)heap_in,8);
  if ((uVar1 & 0xfffffffffff00000) == 0xfffffffffff00000) {
    uVar1 = unaff_s7;
  }
  return uVar1;
}

/*!
 * "Unload". Doesn't free memory, just informs listener we unloaded.
 */
u64 unload(u32 name) {
  u64 in_v0;
  
  output_unload((const_char *)(name + 4));
  return in_v0;
}

s64 load_and_link(const_char *filename,char *decode_name,kheapinfo *heap,u32 flags) {
  u8 *data;
  uint8_t *puVar1;
  undefined in_t1_lo;
  int32_t local_30 [4];
  ulong uVar2;
  
  data = FileLoad(decode_name,heap,(u8 *)0x0,0x40,local_30);
  uVar2 = (ulong)(int)data;
  if ((uVar2 & 0xfffffffffff00000) != 0xfffffffffff00000) {
    puVar1 = link_and_exec(data,decode_name,local_30[0],heap,flags,(bool)in_t1_lo);
    uVar2 = (ulong)(int)puVar1;
  }
  return uVar2;
}

}  // namespace jak3
