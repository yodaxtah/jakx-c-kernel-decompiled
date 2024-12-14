# `game`

## `kernel`

### `common`

#### `fileio`

- [ ] fileio_init_globals
- [x] strend
- [x] ReadHufWord ~~(not found in both)~~
- [x] kstrcpy
- [x] kstrcpyup
- [x] kstrcat ~~(in jak 3, but replaced by standard, `MyStrcat`?)~~
- [x] kstrncat ~~(in jak 3, but replaced by standard `MyStrncat`?)~~
- [x] kstrinsert
- [x] basename_goal
- [x] FileExists ~~(not found in both)~~
- [x] FileDelete ~~(not found in both)~~
- [x] FileCopy ~~(not found in both)~~
- [x] FileLength
- [x] FileLoad
- [x] FileSave ~~(unreferenced string at `0025b6f8`)~~

#### `kboot`

- [ ] kboot_init_globals_common

#### `kdgo`

- [ ] kdgo_init_globals
- [x] RpcCall (`sceSifCallRpc`?)
- [x] RpcCall_wrapper (`RpcCall`?)
- [x] RpcBusy
- [x] RpcSync
- [x] RpcBind
- [x] InitRPC
- [x] StopIOP
- [x] LoadDGOTest

#### `kdsnetm`

- [ ] kdsnetm_init_globals_common
- [x] InitGoalProto
- [x] ShutdownGoalProto
- [x] GoalProtoHandler
- [x] SendFromBufferD
- [x] GoalProtoStatus ~~(unreferenced string at `0027d408`)~~

#### `klink`

- [ ] ~~is_opengoal_object~~ (not visible in `jak3_begin`, exclusive to PC port?)
- [ ] klink_init_globals
- [ ] ~~jak1_jak2_begin~~ (exclusive to PC port?)
- [x] c_symlink2 ~~(in `jak3_work_v2_v4` or `jak3_work_v5`, but not sure which I have)~~

#### `klisten`

- [ ] klisten_init_globals
- [x] ClearPending
- [x] SendAck

#### `kmachine_extras`

/

#### `kmachine`

- [ ] kmachine_init_globals_common
- [x] InitCD
- [x] InitVideo
- [x] CacheFlush
- [x] CPadOpen
- [x] CPadGetData
- [x] InstallHandler
- [x] InstallDebugHandler
- [x] klength
- [x] kseek
- [x] kread
- [x] kwrite
- [x] kclose
- [x] dma_to_iop
- [x] DecodeLanguage
- [x] DecodeAspect
- [x] DecodeVolume
- [x] DecodeTerritory
- [x] DecodeTimeout
- [x] DecodeInactiveTimeout
- [x] DecodeTime (suspicious shallow definition, no `sceCdReadClock` call in either jakx or jak3)
- [ ] ~~vif_interrupt_callback~~ (exclusive to PC port?)

#### `kmalloc`

- [ ] kmalloc_init_globals_common
- [x] ksmalloc ~~(`printf` string not found)~~
- [x] kheapstatus
- [x] kinitheap
- [x] kheapused ~~(not visible yet in `load_and_link_dgo_from_c`)~~
- [x] kmalloc
- [x] kfree ~~(not visible yet in `delete_structure`, `delete_basic`, `delete_pair`)~~

#### `kmemcard`

- [ ] mc_print
- [ ] mc_get_filename_no_dir
- [ ] mc_get_filename
- [ ] mc_get_total_bank_size
- [ ] kmemcard_init_globals
- [ ] mc_checksum
- [ ] file_is_present
- [ ] pc_update_card
- [ ] pc_game_save_synch
- [ ] pc_game_load_open_file
- [ ] pc_game_load_synch
- [x] MC_run (does not correspond with jak3, looks suspicious)
- [x] MC_set_language (does not correspond with jak3, looks suspicious, `lgprint` string not found)
- [x] MC_format (does not correspond with jak3, looks suspicious)
- [x] MC_unformat (does not correspond with jak3, looks suspicious)
- [x] MC_createfile (does not correspond with jak3, looks suspicious)
- [x] MC_save (does not correspond with jak3, looks suspicious)
- [x] MC_load (does not correspond with jak3, looks suspicious)
- [x] MC_makefile (does not correspond with jak3, looks suspicious)
- [x] MC_check_result (does not correspond with jak3, looks suspicious)
- [x] MC_get_status (does not correspond with jak3, looks suspicious)

#### `kprint`

- [ ] kprint_init_globals_common
- [x] init_output
- [x] clear_output
- [x] clear_print
- [x] reset_output
- [x] output_unload
- [x] output_segment_load
- [x] cprintf
- [x] Msg
- [x] MsgWarn
- [x] MsgErr
- [x] reverse
- [x] round
- [x] cvt_float
- [x] ftoa
- [x] kitoa
- [x] kqtoa (G)

#### `kscheme`

- [ ] kscheme_init_globals_common
- [ ] init_crc
- [ ] crc32 (not found in both)
- [x] delete_illegal
- [x] goal_malloc
- [ ] ~~call_goal~~ (not yet visible as function in `jak3_finish`, `call_method_of_type`, `call_method_of_type_arg2`)
- [ ] ~~call_goal_on_stack~~ (not yet visible as function in `KernelDispatch`)
- [x] call_goal_function ~~(not yet visible as function in `call_goal_function_by_name`)~~
- [x] print_structure
- [x] print_integer
- [x] print_binteger
- [x] print_float
- [x] print_vu_function
- [x] copy_fixed
- [x] copy_structure (not found in both)
- [x] inspect_integer
- [x] inspect_binteger
- [x] inspect_float
- [x] inspect_structure
- [x] inspect_vu_function
- [ ] ~~inspect_kheap~~ (points directly to kheapstatus in `InitHeapAndSymbol`)

#### `ksocket`

- [x] ReceiveToBuffer
- [x] SendFromBuffer
- [x] InitListenerConnect
- [x] InitCheckListener
- [x] WaitForMessageAndAck
- [x] CloseListener

#### `ksound`

- [ ] ~~InitSound~~ (no longer called in `InitMachine`, between `InitGoalProto` and `InitRPC`)
- [ ] ~~ShutdownSound~~ (hard to find in `ShutdownMachine`, if present)
- [ ] ~~set_flava_hack~~ (PC port exclusive?)
- [ ] ~~set_fade_hack~~ (PC port exclusive?)



### `jak3`

#### `fileio`

- [x] DecodeFileName
- [x] MakeFileName

#### `kboot`

- [ ] kboot_init_globals
- [x] goal_main
- [x] KernelDispatch
- [x] KernelShutdown
- [x] KernelCheckAndDispatch

#### `kdgo`

- [ ] kdgo_init_globals
- [x] BeginLoadingDGO
- [x] GetNextDGO
- [x] ContinueLoadingDGO
- [x] load_and_link_dgo
- [x] load_and_link_dgo_from_c

#### `klink`

- [ ] is_opengoal_object (similar to previous)
- [x] jak3_begin
- [x] jak3_work
- [ ] ~~jak3_work_v5~~ (Not sure what version I have)
- [ ] ~~cross_seg_dist_link_v3~~ (not yet visible in `jak3_work_opengoal`)
- [ ] ~~ptr_link_v3~~ (not yet visible in `jak3_work_opengoal`)
- [ ] ~~typelink_v3~~ (not yet visible in `jak3_work_opengoal`)
- [ ] ~~symlink_v3~~ (not yet visible in `jak3_work_opengoal`)
- [x] jak3_work_opengoal
- [x] jak3_finish
- [x] link_and_exec
- [ ] ~~link_and_exec_wrapper~~ (`link_and_exex` is directly used in `InitHeapAndSymbol`)
- [x] link_busy
- [x] link_reset
- [x] link_begin
- [x] link_resume
- [x] ultimate_memcpy (PC port exclusive?)
- [ ] ~~jak3_work_v2_v4~~ (Not sure what version I have)

#### `klisten`

- [ ] klisten_init_globals
- [x] InitListener
- [x] ProcessListenerMessage
- [x] sql_query_sync

#### `kmachine_extras` (PC Port exclusives?)

- [ ] ~~update_discord_rpc~~
- [ ] ~~pc_set_levels~~
- [ ] ~~pc_set_active_levels~~
- [ ] ~~bool_to_symbol~~
- [ ] ~~symbol_to_bool~~
- [ ] ~~encode_utf8_string~~

#### `kmachine`

- [x] InitParms
- [x] InitIOP
- [x] InitMachine
- [x] ShutdownMachine
- [x] KeybdGetData
- [x] MouseGetData -- below Keyb, or above kopen, not found in jak3 due to undefined functions
- [x] kopen
- [x] PutDisplayEnv
- [ ] ~~aybabtu~~ (function removed in `InitHeapAndSymbol`)
- [ ] ~~InitMachine_PCPort~~ (PC port exclusive?)
- [x] InitMachineScheme

#### `kmalloc`

- [x] kmemopen_from_c
- [x] kmemopen
- [x] kmemclose

#### `kprint`

- [x] format_impl_jak3

#### `kscheme`

- [ ] kscheme_init_globals
- [ ] ~~u32_in_fixed_sym~~ (not found in demo, not yet visible in functions)
- [ ] ~~fixed_sym_set~~ (not found in demo, not yet visible in `InitHeapAndSymbol`)
- [x] new_illegal
- [x] alloc_from_heap
- [x] alloc_heap_memory
- [x] alloc_heap_object
- [x] new_structure
- [x] new_dynamic_structure
- [x] delete_structure
- [x] new_basic
- [x] delete_basic
- [x] new_pair
- [x] delete_pair
- [x] make_string
- [x] make_string_from_c
- [x] make_debug_string_from_c
- [ ] ~~make_function_from_c_systemv~~
- [ ] ~~make_function_from_c_win32~~
- [ ] ~~make_stack_arg_function_from_c_systemv~~
- [ ] ~~make_stack_arg_function_from_c_win32~~
- [x] make_function_from_c
- [ ] ~~make_stack_arg_function_from_c~~ (requires finding `make_stack_arg_function_symbol_from_c`)
- [x] make_nothing_func
- [x] make_zero_func
- [x] symbol_to_string_from_c
- [x] make_function_symbol_from_c
- [ ] ~~make_stack_arg_function_symbol_from_c~~ (not found in demo, is currently visible as `make_function_symbol_from_c` in `InitHeapAndSymbol`)
- [x] make_raw_function_symbol_from_c
- [x] set_fixed_symbol
- [x] find_symbol_in_area
- [ ] ~~find_symbol_from_c_ht~~ (hidden by `JAK3_HASH_TABLE`)
- [ ] ~~find_slot_in_area~~ (used in `intern_from_c_ht` hidden by `JAK3_HASH_TABLE`)
- [ ] ~~intern_from_c_ht~~ (hidden by `JAK3_HASH_TABLE`)
- [x] find_symbol_from_c
- [x] intern_from_c
- [x] intern
- [x] set_type_values
- [ ] ~~in_valid_memory_for_new_type~~ (not yet visible yet in `new_type`, `method_set`)
- [ ] ~~size_of_type~~ (not yet visible yet in `alloc_and_init_type`, `intern_type_from_c`)
- [ ] ~~is_valid_type~~ (not yet visible yet in `intern_type_from_c`)
- [x] alloc_and_init_type
- [x] intern_type_from_c
- [x] intern_type (manually decompiled, initially not a reference of `intern_type_from_c`)
- [x] set_fixed_type
- [x] new_type
- [x] type_typep
- [x] method_set
- [x] call_method_of_type
- [x] call_goal_function_arg2
- [x] call_goal_function_by_name
- [x] sprint (probably undefined function at `0026c958`)
- [x] call_method_of_type_arg2
- [x] print_object
- [x] print_basic
- [x] print_pair
- [x] print_symbol
- [x] print_type
- [x] print_string
- [x] print_function
- [x] asize_of_basic
- [x] copy_basic
- [x] inspect_object
- [x] inspect_pair
- [x] inspect_string
- [x] inspect_symbol
- [x] inspect_type
- [x] inspect_basic
- [x] inspect_link_block
- [ ] get_fixed_type_symbol (not yet visible)
- [ ] pack_type_flag (not yet visible)
- [x] InitHeapAndSymbol
- [x] load
- [x] loadb
- [x] loadc
- [x] loado
- [x] unload
- [x] load_and_link

#### `ksound`

- [ ] ~~InitSoundScheme~~ (inlined in `InitMachineScheme`)