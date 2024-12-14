# `game`

## `kernel`

### `common`

#### `fileio`

- [ ] fileio_init_globals
- [ ] strend
- [ ] ReadHufWord (not found in both)
- [ ] kstrcpy
- [ ] kstrcpyup
- [ ] kstrcat (in jak 3, but replaced by standard, `MyStrcat`?)
- [ ] kstrncat (in jak 3, but replaced by standard `MyStrncat`?)
- [ ] kstrinsert
- [ ] basename_goal
- [ ] FileExists (not found in both)
- [ ] FileDelete (not found in both)
- [ ] FileCopy (not found in both)
- [ ] FileLength
- [ ] FileLoad
- [ ] ~~FileSave~~ (unreferenced string at `0025b6f8`)

#### `kboot`

- [ ] kboot_init_globals_common

#### `kdgo`

- [ ] kdgo_init_globals
- [ ] RpcCall (`sceSifCallRpc`?)
- [ ] RpcCall_wrapper (`RpcCall`?)
- [ ] RpcBusy
- [ ] RpcSync
- [ ] RpcBind
- [ ] InitRPC
- [ ] StopIOP
- [ ] LoadDGOTest

#### `kdsnetm`

- [ ] kdsnetm_init_globals_common
- [ ] InitGoalProto
- [ ] ShutdownGoalProto
- [ ] GoalProtoHandler
- [ ] SendFromBufferD
- [ ] ~~GoalProtoStatus~~ (unreferenced string at `0027d408`)

#### `klink`

- [ ] ~~is_opengoal_object~~ (not visible in `jak3_begin`, exclusive to PC port?)
- [ ] klink_init_globals
- [ ] ~~jak1_jak2_begin~~ (exclusive to PC port?)
- [ ] ~~c_symlink2~~ (in `jak3_work_v2_v4` or `jak3_work_v5`, but not sure which I have)

#### `klisten`

- [ ] klisten_init_globals
- [ ] ClearPending
- [ ] SendAck

#### `kmachine_extras`

/

#### `kmachine`

- [ ] kmachine_init_globals_common
- [ ] InitCD
- [ ] InitVideo
- [ ] CacheFlush
- [ ] CPadOpen
- [ ] CPadGetData
- [ ] InstallHandler
- [ ] InstallDebugHandler
- [ ] klength
- [ ] kseek
- [ ] kread
- [ ] kwrite
- [ ] kclose
- [ ] dma_to_iop
- [ ] DecodeLanguage
- [ ] DecodeAspect
- [ ] DecodeVolume
- [ ] DecodeTerritory
- [ ] DecodeTimeout
- [ ] DecodeInactiveTimeout
- [ ] DecodeTime (suspicious shallow definition, no `sceCdReadClock` call in either jakx or jak3)
- [ ] ~~vif_interrupt_callback~~ (exclusive to PC port?)

#### `kmalloc`

- [ ] kmalloc_init_globals_common
- [ ] ~~ksmalloc~~ (`printf` string not found)
- [ ] kheapstatus
- [ ] kinitheap
- [ ] ~~kheapused~~ (not visible yet in `load_and_link_dgo_from_c`)
- [ ] kmalloc
- [ ] ~~kfree~~ (not visible yet in `delete_structure`, `delete_basic`, `delete_pair`)

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
- [ ] MC_run (does not correspond with jak3, looks suspicious)
- [ ] MC_set_language (does not correspond with jak3, looks suspicious, `lgprint` string not found)
- [ ] MC_format (does not correspond with jak3, looks suspicious)
- [ ] MC_unformat (does not correspond with jak3, looks suspicious)
- [ ] MC_createfile (does not correspond with jak3, looks suspicious)
- [ ] MC_save (does not correspond with jak3, looks suspicious)
- [ ] MC_load (does not correspond with jak3, looks suspicious)
- [ ] MC_makefile (does not correspond with jak3, looks suspicious)
- [ ] MC_check_result (does not correspond with jak3, looks suspicious)
- [ ] MC_get_status (does not correspond with jak3, looks suspicious)

#### `kprint`

- [ ] kprint_init_globals_common
- [ ] init_output
- [ ] clear_output
- [ ] clear_print
- [ ] reset_output
- [ ] output_unload
- [ ] output_segment_load
- [ ] cprintf
- [ ] Msg
- [ ] MsgWarn
- [ ] MsgErr
- [ ] reverse
- [ ] round
- [ ] cvt_float
- [ ] ftoa
- [ ] kitoa
- [ ] kqtoa (G)

#### `kscheme`

- [ ] kscheme_init_globals_common
- [ ] init_crc
- [ ] crc32 (not found in both)
- [ ] delete_illegal
- [ ] goal_malloc
- [ ] ~~call_goal~~ (not yet visible as function in `jak3_finish`, `call_method_of_type`, `call_method_of_type_arg2`)
- [ ] ~~call_goal_on_stack~~ (not yet visible as function in `KernelDispatch`)
- [ ] ~~call_goal_function~~ (not yet visible as function in `call_goal_function_by_name`)
- [ ] print_structure
- [ ] print_integer
- [ ] print_binteger
- [ ] print_float
- [ ] print_vu_function
- [ ] copy_fixed
- [ ] copy_structure (not found in both)
- [ ] inspect_integer
- [ ] inspect_binteger
- [ ] inspect_float
- [ ] inspect_structure
- [ ] inspect_vu_function
- [ ] ~~inspect_kheap~~ (points directly to kheapstatus in `InitHeapAndSymbol`)

#### `ksocket`

- [ ] ReceiveToBuffer
- [ ] SendFromBuffer
- [ ] InitListenerConnect
- [ ] InitCheckListener
- [ ] WaitForMessageAndAck
- [ ] CloseListener

#### `ksound`

- [ ] ~~InitSound~~ (no longer called in `InitMachine`, between `InitGoalProto` and `InitRPC`)
- [ ] ~~ShutdownSound~~ (hard to find in `ShutdownMachine`, if present)
- [ ] ~~set_flava_hack~~ (PC port exclusive?)
- [ ] ~~set_fade_hack~~ (PC port exclusive?)



### `jak3`

#### `fileio`

- [ ] DecodeFileName
- [ ] MakeFileName

#### `kboot`

- [ ] kboot_init_globals
- [ ] goal_main
- [ ] KernelDispatch
- [ ] KernelShutdown
- [ ] KernelCheckAndDispatch

#### `kdgo`

- [ ] kdgo_init_globals
- [ ] BeginLoadingDGO
- [ ] GetNextDGO
- [ ] ContinueLoadingDGO
- [ ] load_and_link_dgo
- [ ] load_and_link_dgo_from_c

#### `klink`

- [ ] is_opengoal_object (similar to previous)
- [ ] jak3_begin
- [ ] jak3_work
- [ ] ~~jak3_work_v5~~ (Not sure what version I have)
- [ ] ~~cross_seg_dist_link_v3~~ (not yet visible in `jak3_work_opengoal`)
- [ ] ~~ptr_link_v3~~ (not yet visible in `jak3_work_opengoal`)
- [ ] ~~typelink_v3~~ (not yet visible in `jak3_work_opengoal`)
- [ ] ~~symlink_v3~~ (not yet visible in `jak3_work_opengoal`)
- [ ] jak3_work_opengoal
- [ ] jak3_finish
- [ ] link_and_exec
- [ ] ~~link_and_exec_wrapper~~ (`link_and_exex` is directly used in `InitHeapAndSymbol`)
- [ ] link_busy
- [ ] link_reset
- [ ] link_begin
- [ ] link_resume
- [ ] ultimate_memcpy (PC port exclusive?)
- [ ] ~~jak3_work_v2_v4~~ (Not sure what version I have)

#### `klisten`

- [ ] klisten_init_globals
- [ ] InitListener
- [ ] ProcessListenerMessage
- [ ] sql_query_sync

#### `kmachine_extras` (PC Port exclusives?)

- [ ] ~~update_discord_rpc~~
- [ ] ~~pc_set_levels~~
- [ ] ~~pc_set_active_levels~~
- [ ] ~~bool_to_symbol~~
- [ ] ~~symbol_to_bool~~
- [ ] ~~encode_utf8_string~~

#### `kmachine`

- [ ] InitParms
- [ ] InitIOP
- [ ] InitMachine
- [ ] ShutdownMachine
- [ ] KeybdGetData
- [ ] MouseGetData -- below Keyb, or above kopen, not found in jak3 due to undefined functions
- [ ] kopen
- [ ] PutDisplayEnv
- [ ] ~~aybabtu~~ (function removed in `InitHeapAndSymbol`)
- [ ] ~~InitMachine_PCPort~~ (PC port exclusive?)
- [ ] InitMachineScheme

#### `kmalloc`

- [ ] kmemopen_from_c
- [ ] kmemopen
- [ ] kmemclose

#### `kprint`

- [ ] format_impl_jak3

#### `kscheme`

- [ ] kscheme_init_globals
- [ ] ~~u32_in_fixed_sym~~ (not yet visible in functions)
- [ ] ~~fixed_sym_set~~ (not yet visible in `InitHeapAndSymbol`)
- [ ] new_illegal
- [ ] alloc_from_heap
- [ ] alloc_heap_memory
- [ ] alloc_heap_object
- [ ] new_structure
- [ ] new_dynamic_structure
- [ ] delete_structure
- [ ] new_basic
- [ ] delete_basic
- [ ] new_pair
- [ ] delete_pair
- [ ] make_string
- [ ] make_string_from_c
- [ ] make_debug_string_from_c
- [ ] ~~make_function_from_c_systemv~~
- [ ] ~~make_function_from_c_win32~~
- [ ] ~~make_stack_arg_function_from_c_systemv~~
- [ ] ~~make_stack_arg_function_from_c_win32~~
- [ ] make_function_from_c
- [ ] ~~make_stack_arg_function_from_c~~ (requires finding `make_stack_arg_function_symbol_from_c`)
- [ ] make_nothing_func
- [ ] make_zero_func
- [ ] symbol_to_string_from_c
- [ ] make_function_symbol_from_c
- [ ] ~~make_stack_arg_function_symbol_from_c~~ (is currently visible as `make_function_symbol_from_c` in `InitHeapAndSymbol`)
- [ ] make_raw_function_symbol_from_c
- [ ] set_fixed_symbol
- [ ] find_symbol_in_area
- [ ] ~~find_symbol_from_c_ht~~ (hidden by `JAK3_HASH_TABLE`)
- [ ] ~~find_slot_in_area~~ (used in `intern_from_c_ht` hidden by `JAK3_HASH_TABLE`)
- [ ] ~~intern_from_c_ht~~ (hidden by `JAK3_HASH_TABLE`)
- [ ] find_symbol_from_c
- [ ] intern_from_c
- [ ] intern
- [ ] set_type_values
- [ ] ~~in_valid_memory_for_new_type~~ (not yet visible yet in `new_type`, `method_set`)
- [ ] ~~size_of_type~~ (not yet visible yet in `alloc_and_init_type`, `intern_type_from_c`)
- [ ] ~~is_valid_type~~ (not yet visible yet in `intern_type_from_c`)
- [ ] alloc_and_init_type
- [ ] intern_type_from_c
- [ ] intern_type (not a reference of `intern_type_from_c`)
- [ ] set_fixed_type
- [ ] new_type
- [ ] type_typep
- [ ] method_set
- [ ] call_method_of_type
- [ ] call_goal_function_arg2
- [ ] call_goal_function_by_name
- [ ] sprint (probably undefined function at `0026c958`)
- [ ] call_method_of_type_arg2
- [ ] print_object
- [ ] print_basic
- [ ] print_pair
- [ ] print_symbol
- [ ] print_type
- [ ] print_string
- [ ] print_function
- [ ] asize_of_basic
- [ ] copy_basic
- [ ] inspect_object
- [ ] inspect_pair
- [ ] inspect_string
- [ ] inspect_symbol
- [ ] inspect_type
- [ ] inspect_basic
- [ ] inspect_link_block
- [ ] get_fixed_type_symbol (not yet visible)
- [ ] pack_type_flag (not yet visible)
- [ ] InitHeapAndSymbol
- [ ] load
- [ ] loadb
- [ ] loadc
- [ ] loado
- [ ] unload
- [ ] load_and_link

#### `ksound`

- [ ] ~~InitSoundScheme~~ (ommitted from `InitMachineScheme`)