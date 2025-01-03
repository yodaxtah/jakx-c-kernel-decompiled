/*!
 * @file kmemcard.cpp
 * Memory card interface. Very messy code. Most of it is commented out now, as we've switched away
 * from memory cards to just raw saves.
 *
 * Not checked carefully for differences in jak 2.
 */

#include "kmemcard.h"

#include <array>
#include <cstdio>
#include <cstring>

#include "common/util/Assert.h"
#include "common/util/FileUtil.h"
#include "common/util/Timer.h"

#include "game/sce/sif_ee.h"
#include "game/sce/sif_ee_memcard.h"

#include "fmt/core.h"

static constexpr bool memcard_debug = false;

using McCallbackFunc = void (*)(s32);

McCallbackFunc callback;

static s32 language;
static MemoryCardOperation op;
// instead of two memory cards we just simulate the 4 save files (8 banks).
static MemoryCardFile mc_files[4];
// keep track of latest file selected. this is only used in an auto-save mode thats not used
static int mc_last_file = -1;

// a random value we will use as the memory card "handle" for the pc port, which has no memcards.
constexpr u32 PC_MEM_CARD_HANDLE = 0x6C616F67;

constexpr u32 MEM_CARD_MAGIC = 0x12345678;

struct McHeader {
  u32 save_count;
  u32 checksum;
  u32 magic;
  u8 preview_data[64];
  u8 data[944];
  u32 save_count2;
};
static_assert(sizeof(McHeader) == 0x400, "McHeader size");

static McHeader header;

// these are the return value for sceMcGetInfo.
static s32 p1, p2, p3, p4;
using namespace ee;

template <typename... Args>
void mc_print(const std::string& str, Args&&... args) {
  if (memcard_debug) {
    fmt::print("[MC] ");
    if (!str.empty() && str.back() == '\n') {
      fmt::print(fmt::runtime(str), std::forward<Args>(args)...);
    } else {
      fmt::print(fmt::runtime(str + '\n'), std::forward<Args>(args)...);
    }
  }
}

const char* filename_jak1[12] = {
    "BASCUS-97124AYBABTU!",           "BASCUS-97124AYBABTU!/icon.sys",
    "BASCUS-97124AYBABTU!/icon.ico",  "BASCUS-97124AYBABTU!/BASCUS-97124AYBABTU!",
    "BASCUS-97124AYBABTU!/bank0.bin", "BASCUS-97124AYBABTU!/bank1.bin",
    "BASCUS-97124AYBABTU!/bank2.bin", "BASCUS-97124AYBABTU!/bank3.bin",
    "BASCUS-97124AYBABTU!/bank4.bin", "BASCUS-97124AYBABTU!/bank5.bin",
    "BASCUS-97124AYBABTU!/bank6.bin", "BASCUS-97124AYBABTU!/bank7.bin"};

const char* filename_jak2[12] = {
    "BASCUS-97265AYBABTU!",           "BASCUS-97265AYBABTU!/icon.sys",
    "BASCUS-97265AYBABTU!/icon.ico",  "BASCUS-97265AYBABTU!/BASCUS-97265AYBABTU!",
    "BASCUS-97265AYBABTU!/bank0.bin", "BASCUS-97265AYBABTU!/bank1.bin",
    "BASCUS-97265AYBABTU!/bank2.bin", "BASCUS-97265AYBABTU!/bank3.bin",
    "BASCUS-97265AYBABTU!/bank4.bin", "BASCUS-97265AYBABTU!/bank5.bin",
    "BASCUS-97265AYBABTU!/bank6.bin", "BASCUS-97265AYBABTU!/bank7.bin"};

const char* filename_jak3[12] = {
    "BASCUS-97330AYBABTU!",           "BASCUS-97330AYBABTU!/icon.sys",
    "BASCUS-97330AYBABTU!/icon.ico",  "BASCUS-97330AYBABTU!/BASCUS-97330AYBABTU!",
    "BASCUS-97330AYBABTU!/bank0.bin", "BASCUS-97330AYBABTU!/bank1.bin",
    "BASCUS-97330AYBABTU!/bank2.bin", "BASCUS-97330AYBABTU!/bank3.bin",
    "BASCUS-97330AYBABTU!/bank4.bin", "BASCUS-97330AYBABTU!/bank5.bin",
    "BASCUS-97330AYBABTU!/bank6.bin", "BASCUS-97330AYBABTU!/bank7.bin"};

const char* filename_jakx[12] = {
    "BASCUS-97429AYBABTU!",           "BASCUS-97429AYBABTU!/icon.sys",
    "BASCUS-97429AYBABTU!/icon.ico",  "BASCUS-97429AYBABTU!/BASCUS-97429AYBABTU!",
    "BASCUS-97429AYBABTU!/bank0.bin", "BASCUS-97429AYBABTU!/bank1.bin",
    "BASCUS-97429AYBABTU!/bank2.bin", "BASCUS-97429AYBABTU!/bank3.bin",
    "BASCUS-97429AYBABTU!/bank4.bin", "BASCUS-97429AYBABTU!/bank5.bin",
    "BASCUS-97429AYBABTU!/bank6.bin", "BASCUS-97429AYBABTU!/bank7.bin"};

const char* mc_get_filename_no_dir(GameVersion version, int ndx) {
  const char** filenames = nullptr;
  switch (version) {
    case GameVersion::Jak1:
      filenames = filename_jak1;
      break;
    case GameVersion::Jak2:
      filenames = filename_jak2;
      break;
    case GameVersion::Jak3:
      filenames = filename_jak3;
      break;
    case GameVersion::JakX:
      filenames = filename_jakx;
      break;
  }
  return filenames[ndx];
}

inline fs::path mc_get_filename(GameVersion version, int ndx) {
  return file_util::get_user_memcard_dir(version) / mc_get_filename_no_dir(version, ndx);
}

int mc_get_total_bank_size(GameVersion) {
  return BANK_SIZE[g_game_version] + sizeof(McHeader) * 2;
}

void kmemcard_init_globals() {
  // next = 0;
  language = 0;
  op = {};
  // mc[0] = {};
  // mc[1] = {};
  mc_files[0] = {};
  mc_files[1] = {};
  mc_files[2] = {};
  mc_files[3] = {};
  callback = nullptr;
  p1 = 0;
  p2 = 0;
  p3 = 0;
  p4 = 0;
  // memset(&dirent, 0, sizeof(sceMcTblGetDir));
  memset(&header, 0, sizeof(McHeader));
}

/*!
 * A questionable checksum used on memory card data.
 */
u32 mc_checksum(Ptr<u8> data, s32 size) {
  if (size < 0) {
    size += 3;
  }

  u32 result = 0;
  u32* data_u32 = (u32*)data.c();
  for (s32 i = 0; i < size / 4; i++) {
    result = result << 1 ^ (s32)result >> 0x1f ^ data_u32[i] ^ MEM_CARD_MAGIC;
  }

  return result ^ 0xedd1e666;
}

/*!
 * PC port function that returns whether a given bank ID's file exists or not.
 */
bool file_is_present(int id, int bank = 0) {
  auto bankname = mc_get_filename(g_game_version, 4 + id * 2 + bank);
  if (!fs::exists(bankname) ||
      int(fs::file_size(bankname)) < mc_get_total_bank_size(g_game_version)) {
    // file doesn't exist, or size is bad. we do not want to open files that will crash on read!
    return false;
  }
  // avoid file check here tbh. there shouldn't be any saves with a save count of zero anyway.
  // the file check is quite slow and ultimately not very useful.
  return true;

  /*
  // file exists. but let's see if it's an empty one.
  // this prevents the game from reading a bank but classifying it as corrupt data.
  // which a file full of zeros logically is.
  auto fp = file_util::open_file(bankname.c_str(), "rb");

  // we can actually just check if the save count is over zero...
  u32 savecount = 0;
  fread(&savecount, sizeof(u32), 1, fp);
  fclose(fp);
  return savecount > 0;
  */
}

/*!
 * PC port function to set memcard info. We don't use a memory card, instead just the raw savefiles.
 */
void pc_update_card() {
  // int highest_save_count = 0;
  mc_last_file = -1;
  for (s32 file = 0; file < 4; file++) {
    auto bankname = mc_get_filename(g_game_version, 4 + file * 2);
    mc_files[file].present = file_is_present(file);
    if (mc_files[file].present) {
      auto bankdata = file_util::read_binary_file(bankname.string());
      auto header1 = reinterpret_cast<McHeader*>(bankdata.data());
      if (file_is_present(file, 1)) {
        auto bankname2 = mc_get_filename(g_game_version, 1 + 4 + file * 2);
        auto bankdata2 = file_util::read_binary_file(bankname2.string());
        auto header2 = reinterpret_cast<McHeader*>(bankdata2.data());

        if (header2->save_count > header1->save_count) {
          // use most recent bank here.
          header1 = header2;
        }

        // banks chosen and checked. copy data and set info.
        mc_files[file].last_saved_bank = header1 == header2;
        mc_files[file].most_recent_save_count = header1->save_count;

        memcpy(mc_files[file].data, header1->preview_data, 64);
      } else {
        // banks chosen and checked. copy data and set info.
        mc_files[file].last_saved_bank = 0;
        mc_files[file].most_recent_save_count = header1->save_count;

        memcpy(mc_files[file].data, header1->preview_data, 64);
      }

      // if (mc_files[file].most_recent_save_count > highest_save_count) {
      //  mc_last_file = file;
      //  highest_save_count = mc_files[file].most_recent_save_count;
      // }
    }
  }
}

/*!
 * PC port function to save a file. This does the whole saving at once, synchronously.
 */
void pc_game_save_synch() {
  Timer mc_timer;
  mc_timer.start();
  pc_update_card();
  auto path = mc_get_filename(g_game_version, 0);
  file_util::create_dir_if_needed_for_file(path.string());

  // cd_reprobe_save //
  if (!file_is_present(op.param2)) {
    mc_print("reprobe save: first time!");
    // first time saving!
    p2 = 0;  // save count 0
    p4 = 0;  // first bank for file
  } else {
    p2 = mc_files[op.param2].most_recent_save_count + 1;  // increment save count
    p4 = mc_files[op.param2].last_saved_bank ^ 1;         // use the other bank
  }

  // reserve 0 as "I never saved" and use 1 instead.
  if (p2 == 0) {
    p2 = 1;
  }

  // file*2 + p4 is the bank (2 banks per file, p4 is 0 or 1 to select the bank)
  // 4 is the first bank file
  mc_print("open {} for saving", mc_get_filename_no_dir(g_game_version, op.param2 * 2 + 4 + p4));
  auto save_path = mc_get_filename(g_game_version, op.param2 * 2 + 4 + p4);
  file_util::create_dir_if_needed_for_file(save_path.string());
  auto fd = file_util::open_file(save_path.string().c_str(), "wb");
  mc_print("synchronous save file open took {:.2f}ms\n", mc_timer.getMs());
  if (fd) {
    // cb_openedsave //
    mc_print("save file opened, writing header...");
    memset(&header, 0, sizeof(McHeader));
    header.save_count = p2;
    header.checksum = mc_checksum(op.data_ptr, BANK_SIZE[g_game_version]);
    header.magic = MEM_CARD_MAGIC;
    header.save_count2 = p2;
    memcpy(header.preview_data, op.data_ptr2.c(), 64);
    if (fwrite(&header, sizeof(McHeader), 1, fd) == 1) {
      // cb_savedheader //
      mc_print("save file writing main data");
      if (fwrite(op.data_ptr.c(), BANK_SIZE[g_game_version], 1, fd) == 1) {
        // cb_saveddata //
        mc_print("save file writing footer");
        if (fwrite(&header, sizeof(McHeader), 1, fd) == 1) {
          // cb_savedfooter //
          if (fclose(fd) == 0) {
            // cb_closedsave //
            mc_print("All done with saving!!");
            op.operation = MemoryCardOperationKind::NO_OP;
            op.result = McStatusCode::OK;
            mc_files[op.param2].present = 1;
            mc_files[op.param2].most_recent_save_count = p2;
            mc_files[op.param2].last_saved_bank = p4;
            memcpy(mc_files[op.param2].data, op.data_ptr2.c(), 64);
            mc_last_file = op.param2;
          } else {
            op.operation = MemoryCardOperationKind::NO_OP;
            op.result = McStatusCode::INTERNAL_ERROR;
          }
        } else {
          fclose(fd);
          op.operation = MemoryCardOperationKind::NO_OP;
          op.result = McStatusCode::INTERNAL_ERROR;
        }
      } else {
        fclose(fd);
        op.operation = MemoryCardOperationKind::NO_OP;
        op.result = McStatusCode::INTERNAL_ERROR;
      }
    } else {
      fclose(fd);
      op.operation = MemoryCardOperationKind::NO_OP;
      op.result = McStatusCode::INTERNAL_ERROR;
    }
  } else {
    fmt::print("[MC] Error opening file, errno - {}", errno);
    op.operation = MemoryCardOperationKind::NO_OP;
    op.result = McStatusCode::INTERNAL_ERROR;
  }

  mc_print("[MC] synchronous save took {:.2f}ms\n", mc_timer.getMs());
}

void pc_game_load_open_file(FILE* fd) {
  if (fd) {
    // cb_openedload //
    size_t read_size = mc_get_total_bank_size(g_game_version);
    mc_print("reading save file...");
    if (fread(op.data_ptr.c() + p2 * read_size, read_size, 1, fd) == 1) {
      // cb_readload //
      mc_print("closing save file..");
      if (fclose(fd) == 0) {
        // cb_closedload //
        // added : check if aux bank exists
        if (p2 < 1 && fs::exists(mc_get_filename(g_game_version, op.param2 * 2 + 4 + p2 + 1))) {
          p2++;
          mc_print("reading next save bank {}",
                   mc_get_filename_no_dir(g_game_version, op.param2 * 2 + 4 + p2));
          auto new_bankname = mc_get_filename(g_game_version, op.param2 * 2 + 4 + p2);
          auto new_fd = file_util::open_file(new_bankname.string().c_str(), "rb");
          pc_game_load_open_file(new_fd);
        } else {
          // let's verify the data.
          McHeader* headers[2];
          McHeader* footers[2];
          bool ok[2];

          headers[0] = (McHeader*)(op.data_ptr.c());
          footers[0] = (McHeader*)(op.data_ptr.c() + sizeof(McHeader) + BANK_SIZE[g_game_version]);
          headers[1] = (McHeader*)(op.data_ptr.c() + mc_get_total_bank_size(g_game_version));
          footers[1] = (McHeader*)(op.data_ptr.c() + mc_get_total_bank_size(g_game_version) +
                                   sizeof(McHeader) + BANK_SIZE[g_game_version]);
          // static_assert(mc_get_total_bank_size(g_game_version) * 2 == 0x21000, "save layout");
          ok[0] = true;
          ok[1] = p2 == 1;

          for (int idx = 0; idx < 2; idx++) {
            u32 expected_save_count = headers[idx]->save_count;
            if (headers[idx]->save_count2 == expected_save_count &&
                footers[idx]->save_count == expected_save_count &&
                footers[idx]->save_count2 == expected_save_count) {
              // save count is okay!
              if (headers[idx]->magic == MEM_CARD_MAGIC && footers[idx]->magic == MEM_CARD_MAGIC) {
                // magic numbers okay!
                if (headers[idx]->checksum == footers[idx]->checksum) {
                  // checksum
                  auto expected_checksum = headers[idx]->checksum;
                  if (mc_checksum(make_u8_ptr(headers[idx] + 1), BANK_SIZE[g_game_version]) !=
                      expected_checksum) {
                    mc_print("failed checksum");
                    ok[idx] = false;
                  }
                } else {
                  mc_print("corrupted checksum");
                  ok[idx] = false;
                }
              } else {
                mc_print("bad magic");
                ok[idx] = false;
              }
            } else {
              mc_print("bad save count");
              ok[idx] = false;
            }
          }

          mc_print("checking loaded banks");

          //
          if (!ok[0] && !ok[1]) {
            // no good data.
            if (headers[0]->save_count == 0 && headers[0]->checksum == 0 &&
                headers[0]->magic == 0 && headers[0]->save_count2 == 0 &&
                headers[1]->save_count == 0 && headers[1]->checksum == 0 &&
                headers[1]->magic == 0 && headers[1]->save_count2 == 0) {
              // this is a fresh file that you tried to load from...
              mc_print("new game result");
              op.operation = MemoryCardOperationKind::NO_OP;
              op.result = McStatusCode::NEW_GAME;
              mc_last_file = op.param2;
            } else {
              mc_print("corrupted data");
              op.operation = MemoryCardOperationKind::NO_OP;
              op.result = McStatusCode::READ_ERROR;
            }
          } else {
            // pick the bank
            int bank = 0;

            if (!ok[0] || !ok[1]) {
              if (ok[1]) {
                bank = 1;
              }
            } else {
              bank = headers[0]->save_count <= headers[1]->save_count;
            }

            mc_print(fmt::format("loading bank {}", bank));
            u32 current_save_count = headers[bank]->save_count;
            memmove(
                op.data_ptr.c(),
                op.data_ptr.c() + bank * mc_get_total_bank_size(g_game_version) + sizeof(McHeader),
                BANK_SIZE[g_game_version]);
            mc_last_file = op.param2;
            mc_files[op.param2].most_recent_save_count = current_save_count;
            mc_files[op.param2].last_saved_bank = bank;
            op.operation = MemoryCardOperationKind::NO_OP;
            op.result = McStatusCode::OK;
            mc_print("load succeeded");
          }
        }
      } else {
        op.operation = MemoryCardOperationKind::NO_OP;
        op.result = McStatusCode::INTERNAL_ERROR;
      }
    } else {
      fclose(fd);
      op.operation = MemoryCardOperationKind::NO_OP;
      op.result = McStatusCode::INTERNAL_ERROR;
    }
  } else {
    op.operation = MemoryCardOperationKind::NO_OP;
    op.result = McStatusCode::INTERNAL_ERROR;
  }
}

/*!
 * PC port function to load a file. This does the whole loading at once, synchronously.
 */
void pc_game_load_synch() {
  Timer mc_timer;
  mc_timer.start();
  pc_update_card();

  // cb_reprobe_load //
  p2 = 0;
  mc_print("opening save file {}", mc_get_filename_no_dir(g_game_version, op.param2 * 2 + 4));

  auto path = mc_get_filename(g_game_version, op.param2 * 2 + 4);
  auto fd = file_util::open_file(path.string().c_str(), "rb");
  pc_game_load_open_file(fd);

  mc_print("synchronous load took {:.2f}ms\n", mc_timer.getMs());
}

/*!
 * Run the Memory Card state machine.  This is called once per frame in GOAL.
 * It:
 *  - does nothing if there is an in-progress memory card operation
 *  - if async memory card functions are done, runs their callbacks
 *  - if there is a requested operation, starts running sony functions.
 *  - if there is none of the above, and unknown cards, finds out about them.
 *  - every now and then, recheck cards.
 */
void MC_run() {
  s32 sema_id;
  
  sema_id = DAT_002d3908_mc_sema_id;
  WaitSema(DAT_002d3908_mc_sema_id);
  FUN_002730e4();
  FUN_002732e4();
  SignalSema(sema_id);
  return;
}

/////////////////////////
// Memory Card Functions
/////////////////////////

// These functions are called from GOAL to start memory card operations.

/*!
 * Set the language or something.
 * Why is this a memory card func?
 */
int MC_set_language(s32 l) {
  s32 sema_id;
  int iVar1;
  
  sema_id = DAT_002d3908_mc_sema_id;
  WaitSema(DAT_002d3908_mc_sema_id);
  language = l;
  iVar1 = SignalSema(sema_id);
  return iVar1;
}

/*!
 * Set the current memory card operation to FORMAT the given card.
 * Doesn't do anything in the port because we don't use memory cards.
 */
u64 MC_format(s32 card_idx) {
  s32 sema_id;
  u64 uVar1;
  
  sema_id = DAT_002d3908_mc_sema_id;
  WaitSema(DAT_002d3908_mc_sema_id);
  if ((op.operation == 0) && (op.unknown_field_W < 1)) {
    op.result = 0;
    op.operation = 1;
    op.param2 = 0;
    op.retry_count = 100;
    op.data_ptr = (u8 *)0x0;
    op.data_ptr2 = (u8 *)0x0;
    op.unknown_field_W = 0;
    op.param = card_idx;
    SignalSema(sema_id);
    uVar1 = 1;
  }
  else {
    SignalSema(sema_id);
    uVar1 = 0;
  }
  return uVar1;
}


/*!
 * Set the current memory card operation to UNFORMAT the given card.
 * You get the idea.
 */
u64 MC_unformat(s32 card_idx) {
  s32 sema_id;
  u64 uVar1;
  
  sema_id = DAT_002d3908_mc_sema_id;
  WaitSema(DAT_002d3908_mc_sema_id);
  if ((op.operation == 0) && (op.unknown_field_W < 1)) {
    op.result = 0;
    op.operation = 2;
    op.param2 = 0;
    op.retry_count = 100;
    op.data_ptr = (u8 *)0x0;
    op.data_ptr2 = (u8 *)0x0;
    op.unknown_field_W = 0;
    op.param = card_idx;
    SignalSema(sema_id);
    uVar1 = 1;
  }
  else {
    SignalSema(sema_id);
    uVar1 = 0;
  }
  return uVar1;
}

/*!
 * Set the current memory card operation to create the save file.
 * The data I believe is just an empty buffer used as temporary storage.
 */
u64 MC_createfile(s32 param,u8* data) {
  s32 sema_id;
  u64 uVar1;
  
  sema_id = DAT_002d3908_mc_sema_id;
  WaitSema(DAT_002d3908_mc_sema_id);
  if ((op.operation == 0) && (op.unknown_field_W < 1)) {
    op.result = 0;
    op.operation = 3;
    op.param2 = 0;
    op.retry_count = 100;
    op.data_ptr2 = (u8 *)0x0;
    op.unknown_field_W = 0;
    op.param = param;
    op.data_ptr = data;
    SignalSema(sema_id);
    uVar1 = 1;
  }
  else {
    SignalSema(sema_id);
    uVar1 = 0;
  }
  return uVar1;
}

/*!
 * Set the current operation to SAVE.
 * The "summary data" is data that will be used when previewing save files (number of orbs etc)
 * TODO put synchronous call here
 */
u64 MC_save(s32 card_idx,s32 file_idx,u8* save_data,u8* save_summary_data) {
  s32 sema_id;
  u64 uVar1;
  
  sema_id = DAT_002d3908_mc_sema_id;
  WaitSema(DAT_002d3908_mc_sema_id);
  if ((op.operation == 0) && (op.unknown_field_W < 1)) {
    op.result = 0;
    op.operation = 4;
    op.retry_count = 100;
    op.unknown_field_W = 0;
    op.param = card_idx;
    op.param2 = file_idx;
    op.data_ptr = save_data;
    op.data_ptr2 = save_summary_data;
    SignalSema(sema_id);
    uVar1 = 1;
  }
  else {
    SignalSema(sema_id);
    uVar1 = 0;
  }
  return uVar1;
}

undefined4 mc_save_common_S(uint32_t param_1,u8* param_2) {
  s32 sema_id;
  undefined4 uVar1;
  
  sema_id = DAT_002d3908_mc_sema_id;
  WaitSema(DAT_002d3908_mc_sema_id);
  if ((op.operation == 0) && (op.unknown_field_W < 1)) {
    op.result = 0;
    op.operation = 5;
    op.param2 = 0;
    op.retry_count = 100;
    op.data_ptr2 = (u8 *)0x0;
    op.unknown_field_W = 0;
    op.param = param_1;
    op.data_ptr = param_2;
    SignalSema(sema_id);
    uVar1 = 1;
  }
  else {
    SignalSema(sema_id);
    uVar1 = 0;
  }
  return uVar1;
}

undefined4 mc_save_patch_S(uint32_t param_1,u8* param_2) {
  s32 sema_id;
  undefined4 uVar1;
  
  sema_id = DAT_002d3908_mc_sema_id;
  WaitSema(DAT_002d3908_mc_sema_id);
  if ((op.operation == 0) && (op.unknown_field_W < 1)) {
    op.result = 0;
    op.operation = 6;
    op.param2 = 0;
    op.retry_count = 100;
    op.data_ptr2 = (u8 *)0x0;
    op.unknown_field_W = 0;
    op.param = param_1;
    op.data_ptr = param_2;
    SignalSema(sema_id);
    uVar1 = 1;
  }
  else {
    SignalSema(sema_id);
    uVar1 = 0;
  }
  return uVar1;
}

undefined4 mc_save_ghost_S(uint32_t param_1,uint32_t param_2,u8* param_3) {
  s32 sema_id;
  undefined4 uVar1;
  
  sema_id = DAT_002d3908_mc_sema_id;
  WaitSema(DAT_002d3908_mc_sema_id);
  if ((op.operation == 0) && (op.unknown_field_W < 1)) {
    op.result = 0;
    op.operation = 7;
    op.retry_count = 100;
    op.data_ptr2 = (u8 *)0x0;
    op.unknown_field_W = 0;
    op.param = param_1;
    op.param2 = param_2;
    op.data_ptr = param_3;
    SignalSema(sema_id);
    uVar1 = 1;
  }
  else {
    SignalSema(sema_id);
    uVar1 = 0;
  }
  return uVar1;
}


/*!
 * Set the current operation to LOAD.
 * TODO put synchronous call here
 */
u64 MC_load(s32 card_idx,s32 file_idx,u8* data) {
  s32 sema_id;
  u64 uVar1;
  
  sema_id = DAT_002d3908_mc_sema_id;
  WaitSema(DAT_002d3908_mc_sema_id);
  if ((op.operation == 0) && (op.unknown_field_W < 1)) {
    op.result = 0;
    op.operation = 8;
    op.retry_count = 100;
    op.data_ptr2 = (u8 *)0x0;
    op.unknown_field_W = 0;
    op.param = card_idx;
    op.param2 = file_idx;
    op.data_ptr = data;
    SignalSema(sema_id);
    uVar1 = 1;
  }
  else {
    SignalSema(sema_id);
    uVar1 = 0;
  }
  return uVar1;
}

undefined4 mc_load_common_S(uint32_t param_1,u8* param_2) {
  s32 sema_id;
  undefined4 uVar1;
  
  sema_id = DAT_002d3908_mc_sema_id;
  WaitSema(DAT_002d3908_mc_sema_id);
  if ((op.operation == 0) && (op.unknown_field_W < 1)) {
    op.result = 0;
    op.operation = 9;
    op.param2 = 0;
    op.retry_count = 100;
    op.data_ptr2 = (u8 *)0x0;
    op.unknown_field_W = 0;
    op.param = param_1;
    op.data_ptr = param_2;
    SignalSema(sema_id);
    uVar1 = 1;
  }
  else {
    SignalSema(sema_id);
    uVar1 = 0;
  }
  return uVar1;
}

undefined4 mc_load_patch_S(uint32_t param_1,u8* param_2) {
  s32 sema_id;
  undefined4 uVar1;
  
  sema_id = DAT_002d3908_mc_sema_id;
  WaitSema(DAT_002d3908_mc_sema_id);
  if ((op.operation == 0) && (op.unknown_field_W < 1)) {
    op.result = 0;
    op.operation = 10;
    op.param2 = 0;
    op.retry_count = 100;
    op.data_ptr2 = (u8 *)0x0;
    op.unknown_field_W = 0;
    op.param = param_1;
    op.data_ptr = param_2;
    SignalSema(sema_id);
    uVar1 = 1;
  }
  else {
    SignalSema(sema_id);
    uVar1 = 0;
  }
  return uVar1;
}

undefined4 mc_load_ghost_S(uint32_t param_1,uint32_t param_2,u8* param_3) {
  s32 sema_id;
  undefined4 uVar1;
  
  sema_id = DAT_002d3908_mc_sema_id;
  WaitSema(DAT_002d3908_mc_sema_id);
  if ((op.operation == 0) && (op.unknown_field_W < 1)) {
    op.result = 0;
    op.operation = 0xb;
    op.retry_count = 100;
    op.data_ptr2 = (u8 *)0x0;
    op.unknown_field_W = 0;
    op.param = param_1;
    op.param2 = param_2;
    op.data_ptr = param_3;
    SignalSema(sema_id);
    uVar1 = 1;
  }
  else {
    SignalSema(sema_id);
    uVar1 = 0;
  }
  return uVar1;
}

/*!
 * Some sort of test function for memory card stuff.
 * This is exported as a GOAL function, but nothing calls it.
 */
void MC_makefile(s32 port,s32 size) {
  return;
}

u32 MC_check_result() {
  s32 sema_id;
  u32 uVar1;
  
  sema_id = DAT_002d3908_mc_sema_id;
  WaitSema(DAT_002d3908_mc_sema_id);
  uVar1 = op.result;
  SignalSema(sema_id);
  return uVar1;
}


/*!
 * Update the info for the given slot.
 * You can call this at any time.
 * The slot includes the four save slots (8 banks), and a few other files.
 */
void MC_get_status(s32 slot,mc_slot_info *info) {
  s32 sema_id;
  
  sema_id = DAT_002d3908_mc_sema_id;
  WaitSema(DAT_002d3908_mc_sema_id);
  if (((uint)slot < 2) && (info != (mc_slot_info *)0x0)) {
    FUN_00271098(&DAT_00283740 + slot * 0x8c0,info);
  }
  SignalSema(sema_id);
  return;
}

uint mc_get_secrets_S() {
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  uVar1 = 0;
  iVar3 = 0;
  do {
    uVar2 = 0;
    iVar4 = iVar3 + 1;
    if ((&DAT_00283864)[iVar3 * 0x230] == 3) {
      uVar2 = (&DAT_00283fe0)[iVar3 * 0x230];
    }
    uVar1 = uVar1 | uVar2;
    iVar3 = iVar4;
  } while (iVar4 < 2);
  return uVar1;
}