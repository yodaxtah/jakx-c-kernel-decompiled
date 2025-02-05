#include "kmachine.h"

#include <random>

#include "common/global_profiler/GlobalProfiler.h"
#include "common/log/log.h"
#include "common/symbols.h"
#include "common/util/FileUtil.h"
#include "common/util/FontUtils.h"
#include "common/util/Timer.h"
#include "common/util/string_util.h"

#include "game/external/discord.h"
#include "game/graphics/display.h"
#include "game/graphics/gfx.h"
#include "game/graphics/screenshot.h"
#include "game/kernel/common/Ptr.h"
#include "game/kernel/common/kernel_types.h"
#include "game/kernel/common/kprint.h"
#include "game/kernel/common/kscheme.h"
#include "game/mips2c/mips2c_table.h"
#include "game/sce/libcdvd_ee.h"
#include "game/sce/libpad.h"
#include "game/sce/libscf.h"
#include "game/sce/sif_ee.h"

/*!
 * Where does OVERLORD load its data from?
 */
OverlordDataSource isodrv;

// Get IOP modules from DVD or from dsefilesv
u32 modsrc;

// Reboot IOP with IOP kernel from DVD/CD on boot
u32 reboot_iop;

const char* init_types[] = {"fakeiso", "deviso", "iso_cd"};
u8 pad_dma_buf[2 * SCE_PAD_DMA_BUFFER_SIZE];

// added
u32 vif1_interrupt_handler = 0;
u32 vblank_interrupt_handler = 0;

Timer ee_clock_timer;

void kmachine_init_globals_common() {
  memset(pad_dma_buf, 0, sizeof(pad_dma_buf));
  isodrv = fakeiso;  // changed. fakeiso is the only one that works in opengoal.
  modsrc = 1;
  reboot_iop = 1;
  vif1_interrupt_handler = 0;
  vblank_interrupt_handler = 0;
  ee_clock_timer = Timer();
}

/*!
 * Initialize the CD Drive
 * DONE, EXACT
 */
void InitCD() {
  if (cd_S_INITIALIZE_CD_W != '\0') {
    s32 result;
    while (true) {
      strlen("dkernel: Initializing DVD drive...\n");
      printf("dkernel: Initializing DVD drive...\n");
      result = sceCdInit(0);
      if (result != 0) {
        break;
      }
      printf("dkernel: DVD drive initialization failed, retrying...\n");
    }
    printf("dkernel: DVD drive initialized; result=%d\n", result);
  }
}

/*!
 * Initialize the GS and display the splash screen.
 * Not yet implemented. TODO
 * TBD
 */
void InitVideo() {
  bool bVar1;
  int iVar2;
  undefined auStack_b0 [96];
  DisplayEnv display_W;
  
  sceGsResetGraph(0,1,3,0);
  sceGsSetDefLoadImage(auStack_b0,0x2c00,8,0,0,0,0x200,0xe0);
  FlushCache(0);
  sceGsExecLoadImage(auStack_b0,0x1000000);
  sceGsSetDefLoadImage(auStack_b0,0x2c00,8,0,0,0xe0,0x200,0xe0);
  FlushCache(0);
  sceGsExecLoadImage(auStack_b0,0x1070000);
  memset(&display_W,0,0x28);
  display_W.gs_pmode2 = display_W.gs_pmode2 & 0xfffffffffffffffd | 1;
  display_W.gs_pmode = display_W.gs_pmode & 0xfffffffffffffffd | 0x60;
  display_W.gs_display_fb = display_W.gs_display_fb & 0xffc00000fff00000 | 0x1160;
  if (false) {
    trap(7);
  }
  display_W.gs_display = display_W.gs_display & 0xff800000e0000000 | 0x1bf9ff0204a28c;
  display_W.gs_bgcolor._0_1_ = 0;
  display_W.gs_bgcolor._1_1_ = 0;
  display_W.gs_bgcolor._2_1_ = 0;
  sceGsSyncV(0);
  sceGsPutDispEnv(&display_W);
  iVar2 = 4;
  do {
    sceGsSyncV(0);
    bVar1 = -1 < iVar2;
    iVar2 = iVar2 + -1;
  } while (bVar1);
  display_W.gs_pmode = display_W.gs_pmode | 2;
  sceGsPutDispEnv(&display_W);
  return;
}

/*!
 * Flush caches.  Does all the memory, regardless of what you specify
 */
void CacheFlush(void* mem, int size) {
  // FlushCache(0);
  // FlushCache(2);
}

/*!
 * Open a new controller pad.
 * Set the new_pad flag to 1 and state to 0.
 * Prints an error if it fails to open.
 */
u64 CPadOpen(u64 cpad_info, s32 pad_number) {
  CPadInfo* pad = (CPadInfo*)cpad_info;
  if (cpad_info == 0) {
    MsgErr("dkernel: error; NULL pad info\n");
    cpad_info = 0;
  } else if (((uint)pad_number < 2) && pad->cpad_file == 0) {
    cpad->new_pad = 1;
    cpad->state = 0;
    cpad->cpad_file = 1;
  }
  return cpad_info;
}

/*!
 * Different in Jak X, uses scePad2 instead of scePad.
 * TBD
 */
u64 CPadGetData(u64 cpad_info) {
  byte bVar1;
  int iVar3;
  char *format;
  CPadInfo *cpad;
  long lVar4;
  undefined4 uVar5;
  undefined local_70;
  char local_6f;
  undefined local_60 [16];
  byte local_50;
  byte local_4f;
  byte local_40 [16];
  
  if (cpad_info == 0) {
    MsgErr("dkernel: error; NULL pad info\n");
  }
  else {
    cpad = (CPadInfo *)cpad_info;
    uint portIndex = cpad->number;
    if (1 < portIndex) {
      MsgErr("dkernel: error; invalid controller port index %d\n",portIndex);
      return cpad_info;
    }
    iVar3 = controllerPortIndexes_SW[portIndex];
    if (-1 < iVar3) {
      lVar4 = scePad2GetState(iVar3);
      if (lVar4 == 0) {
        cpad->state = 0;
      }
      int cpad_state = cpad->state;
      cpad->valid = (byte)lVar4 | 0x80;
      if (cpad_state == 0x46) {
        lVar4 = sceVibGetProfile(iVar3,local_40);
        if (lVar4 < 0) {
          return cpad_info;
        }
        if ((lVar4 < 1) || (uVar5 = 1, (local_40[0] & 3) == 0)) {
          uVar5 = 0;
        }
        *(undefined4 *)cpad[1].abutton = uVar5;
        cpad->state = 99;
        return cpad_info;
      }
      if (0x46 < cpad_state) {
        if (cpad_state != 99) {
          return cpad_info;
        }
        if (lVar4 != 1) {
          return cpad_info;
        }
        lVar4 = scePad2Read(iVar3,&cpad->button0);
        if (-1 < lVar4) {
          cpad_state = (int)lVar4 + 1 >> 1;
          if (0xf < cpad_state) {
            cpad_state = 0xf;
          }
          cpad->button0 = ~cpad->button0;
          cpad->status = (byte)cpad_state | 0x70;
        }
        cpad->valid = '\x01';
        if (*(int *)cpad[1].abutton == 0) {
          return cpad_info;
        }
        local_60[0] = 3;
        local_50 = 0;
        local_4f = 0;
        if (*(byte *)cpad->buzz_time < 6) {
          local_50 = *(byte *)((int)cpad->buzz_time + *(byte *)cpad->buzz_time + 6) & 1;
        }
        bVar1 = *(byte *)((int)cpad->buzz_time + 1);
        if (bVar1 < 6) {
          bVar1 = *(byte *)((int)cpad->buzz_time + bVar1 + 6);
          local_4f = bVar1 >> 7;
          local_50 = local_50 | (byte)((bVar1 & 0x7f) << 1);
        }
        sceVibSetActParam(iVar3,1,local_60,2,&local_50);
        return cpad_info;
      }
      if (cpad_state != 0) {
        return cpad_info;
      }
      if (lVar4 != 1) {
        return cpad_info;
      }
      lVar4 = scePad2GetButtonProfile(iVar3,&local_70);
      cpad->state = 90;
      if (lVar4 < 4) {
        return cpad_info;
      }
      if (local_6f != -1) {
        return cpad_info;
      }
      cpad->state = 70;
      return cpad_info;
    }
    MsgErr("dkernel: error; invalid pad socket\n");
  }
  return 0;
}

// should make sure this works the same way in jak 2
void InstallHandler(u32 handler_idx, u32 handler_func) {
  DisableIntc(handler_idx);
  AddIntcHandler(handler_idx,(void *)handler_func,0);
  EnableIntc(handler_idx);
}

// nothing used this in jak1, hopefully same for 2
void InstallDebugHandler() {
  SetDebugHandler();
}

/*!
 * Get length of a file.
 */
s32 klength(u64 fs) {
  FileStream* file_stream = (FileStream*)fs;
  if (((*(byte *)&file_stream->flags ^ 1) & 1) != 0) {
    int end_seek = sceLseek(file_stream->file, 0, 2);
    int reset_seek = sceLseek(file_stream->file, 0, 0);
    if (end_seek < 0 || !(-1 < reset_seek)) { // matches jak3's condition
      file_stream->flags |= 1;
    }
    return end_seek;
  } else {
    return 0;
  }
}

/*!
 * Seek a file stream.
 */
s32 kseek(u64 fs, s32 offset, s32 where) {
  s32 result = -1;
  FileStream* file_stream = (FileStream*)fs;
  if (((*(byte *)&file_stream->flags ^ 1) & 1) != 0) {
    result = sceLseek(file_stream->file, offset, where);
    if (result < 0) {
      file_stream->flags |= 1;
    }
  }
  return result;
}

/*!
 * Read from a file stream.
 */
s32 kread(u64 fs, u64 buffer, s32 size) {
  s32 result = -1;
  FileStream* file_stream = (FileStream*)fs;
  if (((*(byte *)&file_stream->flags ^ 1) & 1) != 0) {
    result = sceRead(file_stream->file, (void *)buffer, size)
    if (result < 0) {
      file_stream->flags |= 1;
    }
  }
  return result;
}

/*!
 * Write to a file stream.
 */
s32 kwrite(u64 fs, u64 buffer, s32 size) {
  s32 result = -1;
  FileStream* file_stream = (FileStream*)fs;
  if (((*(byte *)&file_stream->flags ^ 1) & 1) != 0) {
    result = sceWrite(file_stream->file, (const void *)buffer, size);
    if (result < 0) {
      file_stream->flags |= 1;
    }
  }
  return result;
}

/*!
 * Close a file stream.
 */
u64 kclose(u64 fs) {
  FileStream* file_stream = (FileStream*)fs;
  if (((*(byte *)&file_stream->flags ^ 1) & 1) != 0) {
    sceClose(file_stream->file);
    file_stream->file = -1;
  }
  file_stream->flags = 0;
  return fs;
}

// TODO dma_to_iop
bool dma_to_iop(void* src_G, int size_G, void* dest_G) {
  SifDmaTransfer_t transfer_W;
  transfer_W.attr = 0;
  transfer_W.src = src_G;
  transfer_W.dest = dest_G;
  transfer_W.size = size_G;
  u32 id = sceSifSetDma(&transfer_W, 1);
  if (id != 0) {
    s32 sVar1;
    do {
      sVar1 = sceSifDmaStat(id);
    } while (-1 < sVar1);
  }
  return id == 0;
}

u64 DecodeLanguage() {
  return (ulong)masterConfig.language;
}

u64 DecodeAspect() {
  return (ulong)masterConfig.aspect;
}

u64 DecodeVolume() {
  return (ulong)masterConfig.volume;
}

// NOTE: this is originally hardcoded, and returns different values depending on the disc region.
// it returns 0 for NTSC-U, 1 for PAL and 2 for NTSC-J
u64 DecodeTerritory() {
  return 1;
}

u64 DecodeTimeout() {
  return (ulong)masterConfig.timeout;
}

u64 DecodeInactiveTimeout() {
  return (ulong)masterConfig.inactive_timeout;
}

void DecodeTime(u32 ptr) {
  if (ptr != 0 && FUN_0027476c_called_in_DecodeTime_implicit_dkernel() != 0) {
    sceScfGetLocalTimefromRTC(ptr);
  }
}

// void vif_interrupt_callback(int bucket_id) {
//   // added for the PC port for faking VIF interrupts from the graphics system.
//   if (vif1_interrupt_handler && MasterExit == RuntimeExitStatus::RUNNING) {
//     call_goal(Ptr<Function>(vif1_interrupt_handler), bucket_id, 0, 0, s7.offset, g_ee_main_mem);
//   }
// }

/// PC PORT FUNCTIONS BEGIN

u32 offset_of_s7() {
  return s7.offset;
}

inline bool symbol_to_bool(const u32 symptr) {
  return symptr != s7.offset;
}

inline u64 bool_to_symbol(const bool val) {
  return val ? static_cast<u64>(s7.offset) + true_symbol_offset(g_game_version) : s7.offset;
}

u64 pc_filter_debug_string(u32 str_ptr, u32 dist_ptr) {
  auto str = std::string(Ptr<String>(str_ptr).c()->data());
  float dist;
  memcpy(&dist, &dist_ptr, 4);

  // Check distance first
  if (Gfx::g_debug_settings.text_check_range) {
    if (dist / 4096.F > Gfx::g_debug_settings.text_max_range) {
      return bool_to_symbol(true);
    }
  }

  // Get the current filters
  const auto& filters = Gfx::g_debug_settings.text_filters;
  if (filters.empty()) {
    // there are no filters, exit early
    return bool_to_symbol(false);
  }

  // Currently very dumb contains check
  for (const auto& filter : filters) {
    if (filter.type == DebugTextFilter::Type::CONTAINS) {
      if (!str.empty() && !filter.content.empty() && !str_util::contains(str, filter.content)) {
        return bool_to_symbol(true);
      }
    } else if (filter.type == DebugTextFilter::Type::NOT_CONTAINS) {
      if (!str.empty() && !filter.content.empty() && str_util::contains(str, filter.content)) {
        return bool_to_symbol(true);
      }
    } else if (filter.type == DebugTextFilter::Type::REGEX) {
      if (str_util::valid_regex(filter.content) &&
          std::regex_match(str, std::regex(filter.content))) {
        return bool_to_symbol(true);
      }
    }
  }
  return bool_to_symbol(false);
}

CommonPCPortFunctionWrappers g_pc_port_funcs;

u64 read_ee_timer() {
  u64 ns = ee_clock_timer.getNs();
  return (ns * 3) / 10;
}

void pc_memmove(u32 dst, u32 src, u32 size) {
  memmove(Ptr<u8>(dst).c(), Ptr<u8>(src).c(), size);
}

void send_gfx_dma_chain(u32 /*bank*/, u32 chain) {
  if (Gfx::GetCurrentRenderer()) {
    Gfx::GetCurrentRenderer()->send_chain(g_ee_main_mem, chain);
  }
}

void pc_texture_upload_now(u32 page, u32 mode) {
  if (Gfx::GetCurrentRenderer()) {
    Gfx::GetCurrentRenderer()->texture_upload_now(Ptr<u8>(page).c(), mode, s7.offset);
  }
}

void pc_texture_relocate(u32 dst, u32 src, u32 format) {
  if (Gfx::GetCurrentRenderer()) {
    Gfx::GetCurrentRenderer()->texture_relocate(dst, src, format);
  }
}

u64 pc_get_mips2c(u32 name) {
  const char* n = Ptr<String>(name).c()->data();
  return Mips2C::gLinkedFunctionTable.get(n);
}

u64 pc_get_display_id() {
  if (Display::GetMainDisplay()) {
    return Display::GetMainDisplay()->get_display_manager()->get_active_display_id();
  }
  return 0;
}

void pc_set_display_id(u64 display_id) {
  if (Display::GetMainDisplay()) {
    Display::GetMainDisplay()->get_display_manager()->enqueue_set_display_id(display_id);
  }
}

u64 pc_get_display_name(u32 id, u32 str_dest_ptr) {
  std::string name = "";
  if (Display::GetMainDisplay()) {
    name = Display::GetMainDisplay()->get_display_manager()->get_connected_display_name(id);
  }
  if (name.empty()) {
    return bool_to_symbol(false);
  }
  if (g_game_version == GameVersion::Jak1) {
    // The Jak 1 font has only caps
    name = str_util::to_upper(name).c_str();
  }
  // Encode the string to the game font
  const auto encoded_name = get_font_bank_from_game_version(g_game_version)
                                ->convert_utf8_to_game(str_util::titlize(name).c_str());
  strcpy(Ptr<String>(str_dest_ptr).c()->data(), encoded_name.c_str());
  strcpy(Ptr<String>(str_dest_ptr).c()->data(), str_util::titlize(encoded_name).c_str());
  return bool_to_symbol(true);
}

u32 pc_get_display_mode() {
  auto display_mode = game_settings::DisplaySettings::DisplayMode::Windowed;
  if (Display::GetMainDisplay()) {
    display_mode = Display::GetMainDisplay()->get_display_manager()->get_display_mode();
  }
  switch (display_mode) {
    case game_settings::DisplaySettings::DisplayMode::Borderless:
      return g_pc_port_funcs.intern_from_c("borderless").offset;
    case game_settings::DisplaySettings::DisplayMode::Fullscreen:
      return g_pc_port_funcs.intern_from_c("fullscreen").offset;
    default:
      return g_pc_port_funcs.intern_from_c("windowed").offset;
  }
}

void pc_set_display_mode(u32 symptr) {
  if (!Display::GetMainDisplay()) {
    return;
  }
  if (symptr == g_pc_port_funcs.intern_from_c("windowed").offset || symptr == s7.offset) {
    Display::GetMainDisplay()->get_display_manager()->enqueue_set_window_display_mode(
        game_settings::DisplaySettings::DisplayMode::Windowed);
  } else if (symptr == g_pc_port_funcs.intern_from_c("borderless").offset) {
    Display::GetMainDisplay()->get_display_manager()->enqueue_set_window_display_mode(
        game_settings::DisplaySettings::DisplayMode::Borderless);
  } else if (symptr == g_pc_port_funcs.intern_from_c("fullscreen").offset) {
    Display::GetMainDisplay()->get_display_manager()->enqueue_set_window_display_mode(
        game_settings::DisplaySettings::DisplayMode::Fullscreen);
  }
}

u64 pc_get_display_count() {
  if (Display::GetMainDisplay()) {
    return Display::GetMainDisplay()->get_display_manager()->num_connected_displays();
  }
  return 0;
}

void pc_get_active_display_size(u32 w_ptr, u32 h_ptr) {
  if (!Display::GetMainDisplay()) {
    return;
  }
  if (w_ptr) {
    auto w_out = Ptr<s64>(w_ptr).c();
    if (w_out) {
      *w_out = Display::GetMainDisplay()->get_display_manager()->get_screen_width();
    }
  }
  if (h_ptr) {
    auto h_out = Ptr<s64>(h_ptr).c();
    if (h_out) {
      *h_out = Display::GetMainDisplay()->get_display_manager()->get_screen_height();
    }
  }
}

s64 pc_get_active_display_refresh_rate() {
  if (Display::GetMainDisplay()) {
    return Display::GetMainDisplay()->get_display_manager()->get_active_display_refresh_rate();
  }
  return 0;
}

void pc_get_window_size(u32 w_ptr, u32 h_ptr) {
  if (!Display::GetMainDisplay()) {
    return;
  }
  if (w_ptr) {
    auto w = Ptr<s64>(w_ptr).c();
    if (w) {
      *w = Display::GetMainDisplay()->get_display_manager()->get_window_width();
    }
  }
  if (h_ptr) {
    auto h = Ptr<s64>(h_ptr).c();
    if (h) {
      *h = Display::GetMainDisplay()->get_display_manager()->get_window_height();
    }
  }
}

void pc_get_window_scale(u32 x_ptr, u32 y_ptr) {
  if (!Display::GetMainDisplay()) {
    return;
  }
  if (x_ptr) {
    auto x = Ptr<float>(x_ptr).c();
    if (x) {
      *x = Display::GetMainDisplay()->get_display_manager()->get_window_scale_x();
    }
  }
  if (y_ptr) {
    auto y = Ptr<float>(y_ptr).c();
    if (y) {
      *y = Display::GetMainDisplay()->get_display_manager()->get_window_scale_y();
    }
  }
}

void pc_set_window_size(u64 width, u64 height) {
  if (Display::GetMainDisplay()) {
    Display::GetMainDisplay()->get_display_manager()->enqueue_set_window_size(width, height);
  }
}

s64 pc_get_num_resolutions() {
  if (Display::GetMainDisplay()) {
    return Display::GetMainDisplay()->get_display_manager()->get_num_resolutions();
  }
  return 0;
}

void pc_get_resolution(u32 id, u32 w_ptr, u32 h_ptr) {
  if (Display::GetMainDisplay()) {
    auto res = Display::GetMainDisplay()->get_display_manager()->get_resolution(id);
    auto w = Ptr<s64>(w_ptr).c();
    if (w) {
      *w = res.width;
    }
    auto h = Ptr<s64>(h_ptr).c();
    if (h) {
      *h = res.height;
    }
  }
}

u64 pc_is_supported_resolution(u64 width, u64 height) {
  if (Display::GetMainDisplay()) {
    return bool_to_symbol(
        Display::GetMainDisplay()->get_display_manager()->is_supported_resolution(width, height));
  }
  return bool_to_symbol(false);
}

u64 pc_get_controller_name(u32 id, u32 str_dest_ptr) {
  std::string name = "";
  if (Display::GetMainDisplay()) {
    name = Display::GetMainDisplay()->get_input_manager()->get_controller_name(id);
  }
  if (name.empty()) {
    return bool_to_symbol(false);
  }

  if (g_game_version == GameVersion::Jak1) {
    // The Jak 1 font has only caps
    name = str_util::to_upper(name).c_str();
  }
  // Encode the string to the game font
  const auto encoded_name = get_font_bank_from_game_version(g_game_version)
                                ->convert_utf8_to_game(str_util::titlize(name).c_str());
  strcpy(Ptr<String>(str_dest_ptr).c()->data(), encoded_name.c_str());
  strcpy(Ptr<String>(str_dest_ptr).c()->data(), str_util::titlize(encoded_name).c_str());
  return bool_to_symbol(true);
}

u64 pc_get_current_bind(s32 bind_assignment_info, u32 str_dest_ptr) {
  if (!Display::GetMainDisplay()) {
    // TODO - return something that lets the runtime use a translatable string if unknown
    strcpy(Ptr<String>(str_dest_ptr).c()->data(), str_util::to_upper("unknown").c_str());
    return bool_to_symbol(true);
  }

  auto info = bind_assignment_info ? Ptr<BindAssignmentInfo>(bind_assignment_info).c() : NULL;
  auto port = (int)info->port;
  auto device_type = (int)info->device_type;
  auto for_button = info->buttons != s7.offset;
  auto input_idx = (int)info->input_idx;
  auto analog_min_range = info->analog_min_range != s7.offset;

  if (Display::GetMainDisplay()) {
    auto name = Display::GetMainDisplay()->get_input_manager()->get_current_bind(
        port, (InputDeviceType)device_type, for_button, input_idx, analog_min_range);
    if (name.empty()) {
      return bool_to_symbol(false);
    }
    if (g_game_version == GameVersion::Jak1) {
      // The Jak 1 font has only caps
      name = str_util::to_upper(name).c_str();
    }
    // Encode the string to the game font
    const auto encoded_name = get_font_bank_from_game_version(g_game_version)
                                  ->convert_utf8_to_game(str_util::titlize(name).c_str());
    strcpy(Ptr<String>(str_dest_ptr).c()->data(), encoded_name.c_str());
    return bool_to_symbol(true);
  }
  // TODO - return something that lets the runtime use a translatable string if unknown
  strcpy(Ptr<String>(str_dest_ptr).c()->data(), str_util::to_upper("unknown").c_str());
  return bool_to_symbol(true);
}

u64 pc_get_controller_count() {
  if (Display::GetMainDisplay()) {
    return Display::GetMainDisplay()->get_input_manager()->get_num_controllers();
  }
  return 0;
}

u64 pc_get_controller_index(u32 port) {
  if (Display::GetMainDisplay()) {
    return Display::GetMainDisplay()->get_input_manager()->get_controller_index(port);
  }
  return 0;
}

void pc_set_controller(u32 controller_id, u32 port) {
  if (Display::GetMainDisplay()) {
    Display::GetMainDisplay()->get_input_manager()->set_controller_for_port(controller_id, port);
  }
}

u32 pc_get_keyboard_enabled() {
  if (Display::GetMainDisplay()) {
    return bool_to_symbol(Display::GetMainDisplay()->get_input_manager()->is_keyboard_enabled());
  }
  return bool_to_symbol(false);
}

void pc_set_keyboard_enabled(u32 sym_val) {
  if (Display::GetMainDisplay()) {
    Display::GetMainDisplay()->get_input_manager()->enable_keyboard(symbol_to_bool(sym_val));
  }
}

void pc_set_mouse_options(u32 enabled, u32 control_camera, u32 control_movement) {
  if (Display::GetMainDisplay()) {
    Display::GetMainDisplay()->get_input_manager()->enqueue_update_mouse_options(
        symbol_to_bool(enabled), symbol_to_bool(control_camera), symbol_to_bool(control_movement));
  }
}

void pc_set_mouse_camera_sens(u32 xsens, u32 ysens) {
  float xsens_val;
  memcpy(&xsens_val, &xsens, 4);
  float ysens_val;
  memcpy(&ysens_val, &ysens, 4);
  if (Display::GetMainDisplay()) {
    Display::GetMainDisplay()->get_input_manager()->set_camera_sens(xsens_val, ysens_val);
  }
}

void pc_ignore_background_controller_events(u32 sym_val) {
  if (Display::GetMainDisplay()) {
    Display::GetMainDisplay()->get_input_manager()->enqueue_ignore_background_controller_events(
        symbol_to_bool(sym_val));
  }
}

u64 pc_current_controller_has_led() {
  if (Display::GetMainDisplay()) {
    return bool_to_symbol(Display::GetMainDisplay()->get_input_manager()->controller_has_led(0));
  }
  return bool_to_symbol(false);
}

u64 pc_current_controller_has_rumble() {
  if (Display::GetMainDisplay()) {
    return bool_to_symbol(Display::GetMainDisplay()->get_input_manager()->controller_has_rumble(0));
  }
  return bool_to_symbol(false);
}

void pc_set_controller_led(const int port, const u8 red, const u8 green, const u8 blue) {
  if (Display::GetMainDisplay()) {
    Display::GetMainDisplay()->get_input_manager()->enqueue_set_controller_led(port, red, green,
                                                                               blue);
  }
}

u64 pc_waiting_for_bind() {
  if (Display::GetMainDisplay()) {
    return bool_to_symbol(Display::GetMainDisplay()->get_input_manager()->get_waiting_for_bind());
  }
  return bool_to_symbol(false);
}

void pc_set_waiting_for_bind(InputDeviceType device_type,
                             u32 for_analog,
                             u32 for_minimum_analog,
                             s32 input_idx) {
  if (Display::GetMainDisplay()) {
    Display::GetMainDisplay()->get_input_manager()->set_wait_for_bind(
        device_type, symbol_to_bool(for_analog), symbol_to_bool(for_minimum_analog), input_idx);
  }
}

void pc_stop_waiting_for_bind() {
  if (Display::GetMainDisplay()) {
    return Display::GetMainDisplay()->get_input_manager()->stop_waiting_for_bind();
  }
}

void pc_reset_bindings_to_defaults(const int port, const InputDeviceType device_type) {
  if (Display::GetMainDisplay()) {
    Display::GetMainDisplay()->get_input_manager()->reset_input_bindings_to_defaults(port,
                                                                                     device_type);
  }
}

void pc_set_auto_hide_cursor(u32 val) {
  if (Display::GetMainDisplay()) {
    Display::GetMainDisplay()->get_input_manager()->enqueue_set_auto_hide_mouse(
        symbol_to_bool(val));
  }
}

void pc_set_vsync(u32 sym_val) {
  Gfx::g_global_settings.vsync = symbol_to_bool(sym_val);
}

void pc_set_msaa(int samples) {
  Gfx::g_global_settings.msaa_samples = samples;
}

void pc_set_frame_rate(int rate) {
  Gfx::g_global_settings.target_fps = rate;
}

void pc_set_game_resolution(int w, int h) {
  Gfx::g_global_settings.game_res_w = w;
  Gfx::g_global_settings.game_res_h = h;
}

void pc_set_letterbox(int w, int h) {
  Gfx::g_global_settings.lbox_w = w;
  Gfx::g_global_settings.lbox_h = h;
}

void pc_renderer_tree_set_lod(Gfx::RendererTreeType tree, int lod) {
  switch (tree) {
    case Gfx::RendererTreeType::TFRAG3:
      Gfx::g_global_settings.lod_tfrag = lod;
      break;
    case Gfx::RendererTreeType::TIE3:
      Gfx::g_global_settings.lod_tie = lod;
      break;
    default:
      lg::error("Invalid tree {} specified for SetLod ({})", fmt::underlying(tree), lod);
      break;
  }
}

void pc_set_collision_mask(GfxGlobalSettings::CollisionRendererMode mode, s64 mask, u32 symptr) {
  if (symbol_to_bool(symptr)) {
    Gfx::CollisionRendererSetMask(mode, mask);
  } else {
    Gfx::CollisionRendererClearMask(mode, mask);
  }
}

u32 pc_get_collision_mask(GfxGlobalSettings::CollisionRendererMode mode, s64 mask) {
  return Gfx::CollisionRendererGetMask(mode, mask) ? s7.offset + true_symbol_offset(g_game_version)
                                                   : s7.offset;
}

void pc_set_collision_wireframe(u32 symptr) {
  Gfx::g_global_settings.collision_wireframe = symbol_to_bool(symptr);
}

void pc_set_collision(u32 symptr) {
  Gfx::g_global_settings.collision_enable = symbol_to_bool(symptr);
}

void pc_set_gfx_hack(u64 which, u32 symptr) {
  switch (which) {
    case 0:  // no tex
      Gfx::g_global_settings.hack_no_tex = symbol_to_bool(symptr);
      break;
  }
}

u32 pc_get_os() {
#ifdef _WIN32
  return g_pc_port_funcs.intern_from_c("windows").offset;
#elif __linux__
  return g_pc_port_funcs.intern_from_c("linux").offset;
#elif __APPLE__
  return g_pc_port_funcs.intern_from_c("darwin").offset;
#else
  return s7.offset;
#endif
}

time_t pc_get_unix_timestamp() {
  return std::time(nullptr);
}

u64 pc_filepath_exists(u32 filepath) {
  auto filepath_str = std::string(Ptr<String>(filepath).c()->data());
  return bool_to_symbol(fs::exists(filepath_str));
}

u64 pc_mkdir_filepath(u32 filepath) {
  auto filepath_str = std::string(Ptr<String>(filepath).c()->data());
  return bool_to_symbol(file_util::create_dir_if_needed_for_file(filepath_str));
}

void pc_prof(u32 name, ProfNode::Kind kind) {
  prof().event(Ptr<String>(name).c()->data(), kind);
}

std::mt19937 extra_random_generator;
u32 pc_rand() {
  return (u32)extra_random_generator();
}

void pc_treat_pad0_as_pad1(u32 symptr) {
  Gfx::g_debug_settings.treat_pad0_as_pad1 = symbol_to_bool(symptr);
}

u32 pc_is_imgui_visible() {
  return bool_to_symbol(Gfx::g_debug_settings.show_imgui);
}

void pc_screen_shot() {
  g_want_screenshot = true;
}

void pc_register_screen_shot_settings(u32 ptr) {
  register_screen_shot_settings(Ptr<ScreenShotSettings>(ptr).c());
}

/// Initializes all functions that are common across all game versions
/// These functions have the same implementation and do not use any game specific functions (other
/// than the one to create a function in the first place)
void init_common_pc_port_functions(
    std::function<Ptr<Function>(const char*, void*)> make_func_symbol_func,
    std::function<InternFromCInfo(const char*)> intern_from_c_func,
    std::function<u64(const char*)> make_string_from_c_func) {
  g_pc_port_funcs.intern_from_c = intern_from_c_func;
  g_pc_port_funcs.make_string_from_c = make_string_from_c_func;
  // Get a 300MHz timer value. Called from EE thread
  make_func_symbol_func("__read-ee-timer", (void*)read_ee_timer);
  // Do a fast memory copy.
  make_func_symbol_func("__mem-move", (void*)pc_memmove);
  // Called from game thread to submit rendering DMA chain.
  make_func_symbol_func("__send-gfx-dma-chain", (void*)send_gfx_dma_chain);
  // Called from game thread to upload a texture outside of the main DMA chain.
  make_func_symbol_func("__pc-texture-upload-now", (void*)pc_texture_upload_now);
  make_func_symbol_func("__pc-texture-relocate", (void*)pc_texture_relocate);
  // Called from the game thread at initialization. The game thread is the only one to touch the
  // mips2c function table (through the linker and ugh this function), so no locking is needed.
  make_func_symbol_func("__pc-get-mips2c", (void*)pc_get_mips2c);

  // -- DISPLAY RELATED --
  // Returns the name of the display with the given id or #f if not found / empty
  make_func_symbol_func("pc-get-display-id", (void*)pc_get_display_id);
  make_func_symbol_func("pc-set-display-id!", (void*)pc_set_display_id);
  make_func_symbol_func("pc-get-display-name", (void*)pc_get_display_name);
  make_func_symbol_func("pc-get-display-mode", (void*)pc_get_display_mode);
  make_func_symbol_func("pc-set-display-mode!", (void*)pc_set_display_mode);
  make_func_symbol_func("pc-get-display-count", (void*)pc_get_display_count);
  // Returns resolution of the monitor's current display mode
  make_func_symbol_func("pc-get-active-display-size", (void*)pc_get_active_display_size);
  // Returns the current refresh rate of the currently selected monitor's display mode.
  make_func_symbol_func("pc-get-active-display-refresh-rate",
                        (void*)pc_get_active_display_refresh_rate);
  // Returns size of window. Called from game thread
  make_func_symbol_func("pc-get-window-size", (void*)pc_get_window_size);
  // Returns scale of window. This is for DPI stuff.
  make_func_symbol_func("pc-get-window-scale", (void*)pc_get_window_scale);
  make_func_symbol_func("pc-set-window-size!", (void*)pc_set_window_size);
  make_func_symbol_func("pc-get-num-resolutions", (void*)pc_get_num_resolutions);
  make_func_symbol_func("pc-get-resolution", (void*)pc_get_resolution);
  make_func_symbol_func("pc-is-supported-resolution?", (void*)pc_is_supported_resolution);

  // -- INPUT RELATED --
  // Returns the name of the display with the given id or #f if not found / empty
  make_func_symbol_func("pc-get-controller-name", (void*)pc_get_controller_name);
  make_func_symbol_func("pc-get-current-bind", (void*)pc_get_current_bind);
  make_func_symbol_func("pc-get-controller-count", (void*)pc_get_controller_count);
  make_func_symbol_func("pc-get-controller-index", (void*)pc_get_controller_index);
  make_func_symbol_func("pc-set-controller!", (void*)pc_set_controller);
  make_func_symbol_func("pc-get-keyboard-enabled?", (void*)pc_get_keyboard_enabled);
  make_func_symbol_func("pc-set-keyboard-enabled!", (void*)pc_set_keyboard_enabled);
  make_func_symbol_func("pc-set-mouse-options!", (void*)pc_set_mouse_options);
  make_func_symbol_func("pc-set-mouse-camera-sens!", (void*)pc_set_mouse_camera_sens);
  make_func_symbol_func("pc-ignore-background-controller-events!",
                        (void*)pc_ignore_background_controller_events);
  make_func_symbol_func("pc-current-controller-has-led?", (void*)pc_current_controller_has_led);
  make_func_symbol_func("pc-current-controller-has-rumble?",
                        (void*)pc_current_controller_has_rumble);
  make_func_symbol_func("pc-set-controller-led!", (void*)pc_set_controller_led);
  make_func_symbol_func("pc-waiting-for-bind?", (void*)pc_waiting_for_bind);
  make_func_symbol_func("pc-set-waiting-for-bind!", (void*)pc_set_waiting_for_bind);
  make_func_symbol_func("pc-stop-waiting-for-bind!", (void*)pc_stop_waiting_for_bind);
  make_func_symbol_func("pc-reset-bindings-to-defaults!", (void*)pc_reset_bindings_to_defaults);
  make_func_symbol_func("pc-set-auto-hide-cursor!", (void*)pc_set_auto_hide_cursor);

  // graphics things
  make_func_symbol_func("pc-set-vsync", (void*)pc_set_vsync);
  make_func_symbol_func("pc-set-msaa", (void*)pc_set_msaa);
  make_func_symbol_func("pc-set-frame-rate", (void*)pc_set_frame_rate);
  make_func_symbol_func("pc-set-game-resolution", (void*)pc_set_game_resolution);
  make_func_symbol_func("pc-set-letterbox", (void*)pc_set_letterbox);
  make_func_symbol_func("pc-renderer-tree-set-lod", (void*)pc_renderer_tree_set_lod);
  make_func_symbol_func("pc-set-collision-mode", (void*)Gfx::CollisionRendererSetMode);
  make_func_symbol_func("pc-set-collision-mask", (void*)pc_set_collision_mask);
  make_func_symbol_func("pc-get-collision-mask", (void*)pc_get_collision_mask);
  make_func_symbol_func("pc-set-collision-wireframe", (void*)pc_set_collision_wireframe);
  make_func_symbol_func("pc-set-collision", (void*)pc_set_collision);
  make_func_symbol_func("pc-set-gfx-hack", (void*)pc_set_gfx_hack);

  // -- OTHER --
  // Return the current OS as a symbol. Actually returns what it was compiled for!
  make_func_symbol_func("pc-get-os", (void*)pc_get_os);
  make_func_symbol_func("pc-get-unix-timestamp", (void*)pc_get_unix_timestamp);
  make_func_symbol_func("pc-treat-pad0-as-pad1", (void*)pc_treat_pad0_as_pad1);
  make_func_symbol_func("pc-is-imgui-visible?", (void*)pc_is_imgui_visible);

  // file related functions
  make_func_symbol_func("pc-filepath-exists?", (void*)pc_filepath_exists);
  make_func_symbol_func("pc-mkdir-file-path", (void*)pc_mkdir_filepath);

  // discord rich presence
  make_func_symbol_func("pc-discord-rpc-set", (void*)set_discord_rpc);

  // profiler
  make_func_symbol_func("pc-prof", (void*)pc_prof);

  // RNG
  make_func_symbol_func("pc-rand", (void*)pc_rand);

  // debugging tools
  make_func_symbol_func("pc-filter-debug-string?", (void*)pc_filter_debug_string);
  make_func_symbol_func("pc-screen-shot", (void*)pc_screen_shot);
  make_func_symbol_func("pc-register-screen-shot-settings",
                        (void*)pc_register_screen_shot_settings);
}
