#define 16 0x10
#define 964 0x3c4
#define 0x54 0x54
#define 11 0xb
#define 12 0xc
#define 0x23 0x23
#define 0x1E 0x1e
#define 1 0x3f800000
#define 64 0x40
#define 3200 0xc80
#define 160 0xa0
#define -145 -0x91
#define 5120 0x1400
#define 1024 0x400
#define 2048 0x800
#define 544 0x220
#define 257 0x101
#define -11 -0xb
#define -13 -0xd
#define 0x28 0x28

typedef unsigned char   undefined;

typedef unsigned char    bool;
typedef unsigned char    byte;
typedef unsigned int    dword;
typedef long long    longlong;
typedef unsigned char    uchar;
typedef unsigned int    uint;
typedef unsigned long    ulong;
typedef unsigned long long    ulonglong;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned int    undefined4;
typedef unsigned long    undefined8;
typedef unsigned short    ushort;
typedef unsigned short    word;
#define unkbyte9   unsigned long long
#define unkbyte10   unsigned long long
#define unkbyte11   unsigned long long
#define unkbyte12   unsigned long long
#define unkbyte13   unsigned long long
#define unkbyte14   unsigned long long
#define unkbyte15   unsigned long long
#define unkbyte16   unsigned long long

#define unkuint9   unsigned long long
#define unkuint10   unsigned long long
#define unkuint11   unsigned long long
#define unkuint12   unsigned long long
#define unkuint13   unsigned long long
#define unkuint14   unsigned long long
#define unkuint15   unsigned long long
#define unkuint16   unsigned long long

#define unkint9   long long
#define unkint10   long long
#define unkint11   long long
#define unkint12   long long
#define unkint13   long long
#define unkint14   long long
#define unkint15   long long
#define unkint16   long long

#define unkfloat1   float
#define unkfloat2   float
#define unkfloat3   float
#define unkfloat5   double
#define unkfloat6   double
#define unkfloat7   double
#define unkfloat9   long double
#define unkfloat11   long double
#define unkfloat12   long double
#define unkfloat13   long double
#define unkfloat14   long double
#define unkfloat15   long double
#define unkfloat16   long double

#define BADSPACEBASE   void
#define code   void

typedef struct LinkedListNodeLintPrime_W LinkedListNodeLintPrime_W, *PLinkedListNodeLintPrime_W;

struct LinkedListNodeLintPrime_W {
    pointer forward_W;
    pointer forward_double_W;
    int field2_0x8;
};

typedef struct IpInitStructIdk_W IpInitStructIdk_W, *PIpInitStructIdk_W;

struct IpInitStructIdk_W {
    int field0_0x0;
    pointer field1_0x4;
    int field2_0x8;
    pointer field3_0xc;
    pointer field4_0x10;
    pointer field5_0x14;
    pointer field6_0x18;
    pointer field7_0x1c;
    pointer field8_0x20;
    pointer field9_0x24;
    undefined *field10_0x28;
    undefined *field11_0x2c;
    undefined *field12_0x30;
};

typedef uchar uint8_t;

typedef uint8_t u8;

typedef unsigned short    wchar16;
typedef enum Elf32_GPRMask_MIPS {
    gpr_zero=1,
    gpr_at=2,
    gpr_v0=4,
    gpr_v1=8,
    gpr_a0=16,
    gpr_a1=32,
    gpr_a2=64,
    gpr_a3=128,
    gpr_t0=256,
    gpr_t1=512,
    gpr_t2=1024,
    gpr_t3=2048,
    gpr_t4=4096,
    gpr_t5=8192,
    gpr_t6=16384,
    gpr_t7=32768,
    gpr_s0=65536,
    gpr_s1=131072,
    gpr_s2=262144,
    gpr_s3=524288,
    gpr_s4=1048576,
    gpr_s5=2097152,
    gpr_s6=4194304,
    gpr_s7=8388608,
    gpr_t8=16777216,
    gpr_t9=33554432,
    gpr_k0=67108864,
    gpr_k1=134217728,
    gpr_gp=268435456,
    gpr_sp=536870912,
    gpr_fp=1073741824,
    gpr_ra=2147483648
} Elf32_GPRMask_MIPS;

typedef struct tcpInitData_W tcpInitData_W, *PtcpInitData_W;

struct tcpInitData_W {
    undefined4 field0_0x0;
    undefined4 field1_0x4;
    undefined field2_0x8;
    undefined field3_0x9;
    undefined field4_0xa;
    undefined field5_0xb;
    undefined2 field6_0xc;
    undefined field7_0xe;
    undefined field8_0xf;
    undefined4 field9_0x10;
    undefined4 field10_0x14;
    undefined4 field11_0x18;
    undefined4 field12_0x1c;
    undefined4 field13_0x20;
    undefined4 field14_0x24;
    undefined4 field15_0x28;
    undefined4 field16_0x2c;
    undefined4 field17_0x30;
    undefined4 field18_0x34;
    undefined4 field19_0x38;
    undefined4 field20_0x3c;
    undefined field21_0x40;
    undefined field22_0x41;
    undefined field23_0x42;
    undefined field24_0x43;
    undefined4 field25_0x44;
    undefined field26_0x48;
    undefined field27_0x49;
    undefined field28_0x4a;
    undefined field29_0x4b;
    undefined field30_0x4c;
    undefined field31_0x4d;
    undefined field32_0x4e;
    undefined field33_0x4f;
    undefined field34_0x50;
    undefined field35_0x51;
    undefined field36_0x52;
    undefined field37_0x53;
    undefined field38_0x54;
    undefined field39_0x55;
    undefined field40_0x56;
    undefined field41_0x57;
    undefined field42_0x58;
    undefined field43_0x59;
    undefined field44_0x5a;
    undefined field45_0x5b;
    undefined field46_0x5c;
    undefined field47_0x5d;
    undefined field48_0x5e;
    undefined field49_0x5f;
    undefined field50_0x60;
    undefined field51_0x61;
    undefined field52_0x62;
    undefined field53_0x63;
    undefined field54_0x64;
    undefined field55_0x65;
    undefined field56_0x66;
    undefined field57_0x67;
    undefined field58_0x68;
    undefined field59_0x69;
    undefined field60_0x6a;
    undefined field61_0x6b;
    undefined8 field62_0x6c;
};

typedef struct EzNetMessageEntry2_W EzNetMessageEntry2_W, *PEzNetMessageEntry2_W;

struct EzNetMessageEntry2_W {
    int field0_0x0;
    int field1_0x4;
    char *messageString;
    void *function;
};

typedef struct MediusErrorPair MediusErrorPair, *PMediusErrorPair;

struct MediusErrorPair {
    int code_W;
    char *field1_0x4;
};

typedef struct Type Type, *PType;

typedef ushort uint16_t;

typedef uint16_t u16;

typedef struct Function Function, *PFunction;

struct Function {
};

struct Type {
    struct Type **symbol;
    struct Type *parent;
    u16 allocated_size;
    u16 padded_size;
    u16 heap_base;
    u16 num_methods;
    struct Function *new_method;
    struct Function *delete_method;
    struct Function *print_method;
    struct Function *inpsect_method;
    struct Function *length_method;
    struct Function *asize_of_method;
    struct Function *copy_method;
    struct Function *relocate_method;
    struct Function *memusage_method;
};

typedef struct SomeBaseT,TX,FDX_W SomeBaseT,TX,FDX_W, *PSomeBaseT,TX,FDX_W;

struct SomeBaseT,TX,FDX_W {
    pointer field0_0x0;
    undefined4 field1_0x4;
    undefined4 field2_0x8;
};

typedef struct SomeDataTypeIdk_W SomeDataTypeIdk_W, *PSomeDataTypeIdk_W;

struct SomeDataTypeIdk_W {
    int usually_zero_W;
    int some_flag_W;
    pointer some_data_W;
};

typedef struct SegmentInfoV5 SegmentInfoV5, *PSegmentInfoV5;

typedef uint uint32_t;

struct SegmentInfoV5 {
    uint32_t relocs; // offset of relocation table
    uint32_t data; // offset of segment data
    uint32_t size; // segment data size (0 if segment doesn't exist)
    uint32_t magic; // always 0
};

typedef struct DmaTag DmaTag, *PDmaTag;

struct DmaTag {
    short field0_0x0;
    undefined field1_0x2;
    undefined field2_0x3;
    undefined field3_0x4;
    undefined field4_0x5;
    undefined field5_0x6;
    undefined field6_0x7;
    undefined field7_0x8;
    undefined field8_0x9;
    undefined field9_0xa;
    undefined field10_0xb;
    undefined field11_0xc;
    undefined field12_0xd;
    undefined field13_0xe;
    undefined field14_0xf;
    undefined8 field15_0x10;
    undefined8 field16_0x18;
    undefined8 field17_0x20;
    undefined8 field18_0x28;
    undefined8 field19_0x30;
    undefined8 field20_0x38;
    undefined8 field21_0x40;
    undefined8 field22_0x48;
    undefined8 field23_0x50;
    undefined8 field24_0x58;
    undefined8 field25_0x60;
    undefined8 field26_0x68;
    undefined2 field27_0x70;
    undefined field28_0x72;
    undefined field29_0x73;
    void *field30_0x74;
    undefined field31_0x78;
    undefined field32_0x79;
    undefined field33_0x7a;
    undefined field34_0x7b;
    undefined field35_0x7c;
    undefined field36_0x7d;
    undefined field37_0x7e;
    undefined field38_0x7f;
    undefined2 field39_0x80;
    undefined field40_0x82;
    undefined field41_0x83;
};

typedef uint32_t u32;

typedef struct UnreliableDataType5_W UnreliableDataType5_W, *PUnreliableDataType5_W;

struct UnreliableDataType5_W {
    undefined field0_0x0;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    undefined field4_0x4;
    undefined field5_0x5;
    undefined field6_0x6;
    undefined field7_0x7;
    pointer field8_0x8;
    undefined field9_0xc;
    undefined field10_0xd;
    undefined field11_0xe;
    undefined field12_0xf;
    pointer field13_0x10;
    pointer field14_0x14;
};

typedef struct SomeModuleIdk_W SomeModuleIdk_W, *PSomeModuleIdk_W;

struct SomeModuleIdk_W {
    undefined2 idk_data_1_W;
    undefined2 idk_data_2_W;
    char **name_W;
    void *func1;
    void *func2;
    void *func3;
    void *func4;
    void *func5;
    void *func6;
    void *func7;
    void *func8;
    void *func9;
    void *func10;
    void *func11;
    void *func12;
    void *func13;
};

typedef ulonglong uint64_t;

typedef uint64_t u64;

typedef struct mc_file_info mc_file_info, *Pmc_file_info;

struct mc_file_info {
    u32 present;
    u8 data[64];
};

typedef int int32_t;

typedef int32_t s32;

typedef struct  SifRpcHeader_t_G  SifRpcHeader_t_G, *P SifRpcHeader_t_G;

struct  SifRpcHeader_t_G {
    void *pkt_addr;
    u32 rpc_id;
    int sema_id;
    u32 mode;
};

typedef longlong int64_t;

typedef int64_t s64;

typedef struct MemoryCardFile MemoryCardFile, *PMemoryCardFile;

struct MemoryCardFile {
    u32 present;
    u32 most_recent_save_count;
    u32 last_saved_bank;
    u8 data[64];
};

typedef void _IO_lock_t;

typedef struct _IO_marker _IO_marker, *P_IO_marker;

typedef struct _IO_FILE _IO_FILE, *P_IO_FILE;

typedef long __off_t;

typedef long __off64_t;

typedef ulong size_t;

struct _IO_FILE {
    int _flags;
    char *_IO_read_ptr;
    char *_IO_read_end;
    char *_IO_read_base;
    char *_IO_write_base;
    char *_IO_write_ptr;
    char *_IO_write_end;
    char *_IO_buf_base;
    char *_IO_buf_end;
    char *_IO_save_base;
    char *_IO_backup_base;
    char *_IO_save_end;
    struct _IO_marker *_markers;
    struct _IO_FILE *_chain;
    int _fileno;
    int _flags2;
    __off_t _old_offset;
    ushort _cur_column;
    char _vtable_offset;
    char _shortbuf[1];
    _IO_lock_t *_lock;
    __off64_t _offset;
    void *__pad1;
    void *__pad2;
    void *__pad3;
    void *__pad4;
    size_t __pad5;
    int _mode;
    char _unused2[20];
};

struct _IO_marker {
    struct _IO_marker *_next;
    struct _IO_FILE *_sbuf;
    int _pos;
};

typedef struct stat stat, *Pstat;

typedef ulong __dev_t;

typedef ulong __ino_t;

typedef ulong __nlink_t;

typedef uint __mode_t;

typedef uint __uid_t;

typedef uint __gid_t;

typedef long __blksize_t;

typedef long __blkcnt_t;

typedef struct timespec timespec, *Ptimespec;

typedef long __time_t;

struct timespec {
    __time_t tv_sec;
    long tv_nsec;
};

struct stat {
    __dev_t st_dev;
    __ino_t st_ino;
    __nlink_t st_nlink;
    __mode_t st_mode;
    __uid_t st_uid;
    __gid_t st_gid;
    int __pad0;
    __dev_t st_rdev;
    __off_t st_size;
    __blksize_t st_blksize;
    __blkcnt_t st_blocks;
    struct timespec st_atim;
    struct timespec st_mtim;
    struct timespec st_ctim;
    long __unused[3];
};

typedef struct sceExecData sceExecData, *PsceExecData;

struct sceExecData {
    uint epc;
    uint gp;
    uint sp;
    uint dummy;
};

typedef struct FileStream FileStream, *PFileStream;

struct FileStream {
    u32 flags;
    u32 mode; // basic
    u32 name; // basic
    s32 file; // int32
};

typedef struct String String, *PString;

struct String {
    u32 len;
};

typedef struct ca_pkt ca_pkt, *Pca_pkt;

typedef struct SifCmdHeader_t SifCmdHeader_t, *PSifCmdHeader_t;

struct SifCmdHeader_t { // Removed: /** Can be freely used. */     u32 opt;
    u32 psize; // Packet size. Min: 1x16 (header only), max: 7*16
    u32 dsize; // Payload size
    void *dest; // Destination address for payload. Can be NULL if there is no payload.
    int cid; // Function number of function to call.
};

struct ca_pkt {
    struct SifCmdHeader_t header;
    undefined field1_0x10;
    undefined field2_0x11;
    undefined field3_0x12;
    undefined field4_0x13;
    void *buf;
};

typedef struct SifRpcPktHeader_t SifRpcPktHeader_t, *PSifRpcPktHeader_t;

struct SifRpcPktHeader_t {
    struct SifCmdHeader_t sifcmd;
    int rec_id;
    int rpc_id; // at 0x18
    void *pkt_addr;
};

typedef struct ee_sema_t ee_sema_t, *Pee_sema_t;

struct ee_sema_t {
    int count; // used by WaitSema and SignalSema
    int max_count;
    int init_count; // initial value for count
    int wait_threads; // number of threads associated with this semaphore
    u32 attr; // not used by kernel
    string *option; // u32;not used by kernel
};

typedef struct SifRpcOtherDataPkt_t SifRpcOtherDataPkt_t, *PSifRpcOtherDataPkt_t;

typedef struct SifRpcReceiveData_t SifRpcReceiveData_t, *PSifRpcReceiveData_t;

typedef struct SifRpcHeader_t SifRpcHeader_t, *PSifRpcHeader_t;

struct SifRpcOtherDataPkt_t {
    struct SifCmdHeader_t sifcmd;
    undefined field1_0x10;
    undefined field2_0x11;
    undefined field3_0x12;
    undefined field4_0x13;
    void *pkt_addr;
    int rpc_id; // at 0x18
    struct SifRpcReceiveData_t *receive; // at 0x1c
    void *src; // at 0x20
    void *dest; // at 0x24
    int size; // at 0x28
    int rec_id;
};

struct SifRpcHeader_t {
    void *pkt_addr;
    u32 rpc_id;
    int sema_id;
    u32 mode;
};

struct SifRpcReceiveData_t {
    struct SifRpcHeader_t hdr;
    void *src;
    void *dest;
    int size;
};

typedef char int8_t;

typedef int8_t s8;

typedef struct SifRpcDataQueue_t SifRpcDataQueue_t, *PSifRpcDataQueue_t;

typedef struct SifRpcServerData_t SifRpcServerData_t, *PSifRpcServerData_t;

typedef struct SifRpcClientData_t SifRpcClientData_t, *PSifRpcClientData_t;

struct SifRpcDataQueue_t {
    int thread_id;
    int active;
    struct SifRpcServerData_t *link; // at 0x8
    struct SifRpcServerData_t *start;
    struct SifRpcServerData_t *end;
    struct SifRpcDataQueue_t *next;
};

struct SifRpcClientData_t {
    struct  SifRpcHeader_t_G hdr;
    u32 command;
    void *buff;
    void *cbuff;
    void *end_function;
    void *end_param;
    struct SifRpcServerData_t *server;
};

struct SifRpcServerData_t {
    int sid; // at 0x0
    void *func; // at 0x4
    void *buff; // at 0x8
    int size;
    void *cfunc; // at 0x10
    void *cbuff; // at 0x14
    int size2;
    struct SifRpcClientData_t *client;
    void *pkt_addr;
    int rpc_number;
    void *receive;
    int rsize;
    int rmode;
    int rid;
    struct SifRpcServerData_t *link;
    struct SifRpcServerData_t *next;
    struct SifRpcDataQueue_t *base;
};

typedef struct SifRpcBindPkt_t SifRpcBindPkt_t, *PSifRpcBindPkt_t;

struct SifRpcBindPkt_t {
    struct SifCmdHeader_t sifcmd;
    undefined field1_0x10;
    undefined field2_0x11;
    undefined field3_0x12;
    undefined field4_0x13;
    void *pkt_addr; // at 0x14
    int rec_id;
    struct SifRpcClientData_t *client; // at 0x1c
    int sid; // at 0x20
    int rpc_id;
};

typedef struct sceEENetDriverIdk_W sceEENetDriverIdk_W, *PsceEENetDriverIdk_W;

struct sceEENetDriverIdk_W {
    undefined4 field0_0x0;
    undefined4 field1_0x4;
    undefined4 field2_0x8;
    undefined4 field3_0xc;
    undefined4 field4_0x10;
    undefined4 field5_0x14;
    undefined4 field6_0x18;
    undefined4 field7_0x1c;
};

typedef struct kheapinfo kheapinfo, *Pkheapinfo;

struct kheapinfo {
    u8 *base; // ! beginning of heap
    u8 *top; // ! current location of bottom of top allocations
    u8 *current; // ! current location of top of bottom allocations
    u8 *top_base; // ! end of heap
};

typedef uchar const_uchar;

typedef struct SifCmdHandlerData_t SifCmdHandlerData_t, *PSifCmdHandlerData_t;

struct SifCmdHandlerData_t {
    void *handler;
    void *harg;
};

typedef struct Symbol4 Symbol4, *PSymbol4;

struct Symbol4 {
    float foo;
};

typedef struct link_control link_control, *Plink_control;

struct link_control {
    uint8_t *m_object_data;
    uint8_t *m_entry;
    char m_object_name[64];
    int32_t m_object_size;
    undefined *m_heap;
    uint32_t m_flags;
    uint8_t *m_heap_top;
    bool m_keep_debug;
    uint8_t *m_link_block_ptr;
    uint32_t m_code_size;
    uint8_t *m_code_start;
    uint32_t m_state;
    uint32_t m_segment_process;
    uint32_t m_version;
    int heap_gap;
    uint8_t *m_original_object_location;
    u8 *m_reloc_ptr;
    u8 *m_base_ptr;
    u8 *m_loc_ptr;
    int m_table_toggle;
    bool m_opengoal;
    bool m_busy;
    bool m_on_global_heap;
    undefined *m_link_hdr;
    bool m_moved_link_block;
    int m_n_segments;
    struct SegmentInfoV5 *m_link_segments_table;
};

typedef struct mc_slot_info mc_slot_info, *Pmc_slot_info;

struct mc_slot_info {
    u32 handle;
    u32 known;
    u32 formatted;
    u32 initted;
    u32 last_file;
    u32 mem_required;
    u32 mem_actual;
    struct mc_file_info files[4];
};

typedef struct PaddedString_W PaddedString_W, *PPaddedString_W;

struct PaddedString_W {
    undefined4 padding;
    char string[1];
};

typedef struct InternFromCInfo InternFromCInfo, *PInternFromCInfo;

struct InternFromCInfo {
    u32 offset;
    u32 value;
};

typedef struct KnetFunctionPair_W KnetFunctionPair_W, *PKnetFunctionPair_W;

struct KnetFunctionPair_W {
    char **name;
    void *address;
};

typedef struct SifRpcRendPkt_t SifRpcRendPkt_t, *PSifRpcRendPkt_t;

struct SifRpcRendPkt_t {
    struct SifCmdHeader_t sifcmd;
    undefined field1_0x10;
    undefined field2_0x11;
    undefined field3_0x12;
    undefined field4_0x13;
    void *pkt_addr;
    int rec_id;
    struct SifRpcClientData_t *client;
    u32 cid;
    struct SifRpcServerData_t *server; // at 0x24
    void *buff; // at 0x28
    void *cbuff;
    int rpc_id;
};

typedef struct ee_thread_t ee_thread_t, *Pee_thread_t;

struct ee_thread_t {
    int status;
    void *func;
    void *stack;
    int stack_size;
    void *gp_reg;
    int initial_priority;
    int current_priority;
    u32 attr;
    char *option; // u32; Do not use - officially documented to not work.
};

typedef void *SifCmdHandler_t;

typedef struct ee_thread_status_t ee_thread_status_t, *Pee_thread_status_t;

struct ee_thread_status_t {
    int status;
    void *func;
    void *stack;
    int stack_size;
    void *gp_reg;
    int initial_priority;
    int current_priority;
    u32 attr;
    u32 option;
    u32 waitType;
    u32 waitId;
    u32 wakeupCount;
};

typedef struct MasterConfig MasterConfig, *PMasterConfig;

struct MasterConfig {
    u16 language; // ! GOAL language
    u16 aspect; // ! SCE_ASPECT
    u16 disable_game;
    u16 inactive_timeout;
    u16 timeout;
    u16 jak2_only_unused; // seems unused
    u16 volume;
};

typedef struct topArg topArg, *PtopArg;

typedef struct request request, *Prequest;

struct request {
    u8 mode;
    u8 data;
};

struct topArg {
    int requestOut;
    int requestIn;
    struct request request[512];
};

typedef struct RpcCallEndFunctionArg_W RpcCallEndFunctionArg_W, *PRpcCallEndFunctionArg_W;

struct RpcCallEndFunctionArg_W {
    int sema_id;
    void *callback;
    int third;
    int fourth;
};

typedef struct RpcChannelIdPair_W RpcChannelIdPair_W, *PRpcChannelIdPair_W;

struct RpcChannelIdPair_W {
    undefined4 channel;
    undefined4 id;
};

typedef struct kheapinfo_duplicate kheapinfo_duplicate, *Pkheapinfo_duplicate;

struct kheapinfo_duplicate {
    u8 *! beginning of heap;
    u8 *! current location of bottom of top allocation;
    u8 *! current location of top of bottom allocation;
    u8 *! end of heap;
};

typedef struct format_struct format_struct, *Pformat_struct;

struct format_struct {
    char data[64];
};

typedef struct rpc_data rpc_data, *Prpc_data;

struct rpc_data {
    int pid;
    void *pkt_table;
    int pkt_table_len;
    int unused1;
    int unused2;
    u8 *rdata_table;
    int rdata_table_len;
    u8 *client_table;
    int client_table_len;
    int rdata_table_idx;
    void *active_queue;
};

typedef struct GoalProtoBlock GoalProtoBlock, *PGoalProtoBlock;

struct GoalProtoBlock {
    s32 socket;
    s32 receive_progress;
    s32 send_remaining;
    undefined field3_0xc;
    undefined field4_0xd;
    undefined field5_0xe;
    undefined field6_0xf;
    undefined field7_0x10;
    undefined field8_0x11;
    undefined field9_0x12;
    undefined field10_0x13;
    undefined field11_0x14;
    undefined field12_0x15;
    undefined field13_0x16;
    undefined field14_0x17;
    undefined field15_0x18;
    undefined field16_0x19;
    undefined field17_0x1a;
    undefined field18_0x1b;
    undefined field19_0x1c;
    undefined field20_0x1d;
    undefined field21_0x1e;
    undefined field22_0x1f;
    undefined field23_0x20;
    undefined field24_0x21;
    undefined field25_0x22;
    undefined field26_0x23;
    undefined field27_0x24;
    undefined field28_0x25;
    undefined field29_0x26;
    undefined field30_0x27;
    undefined field31_0x28;
    undefined field32_0x29;
    undefined field33_0x2a;
    undefined field34_0x2b;
    undefined field35_0x2c;
    undefined field36_0x2d;
    undefined field37_0x2e;
    undefined field38_0x2f;
    undefined field39_0x30;
    undefined field40_0x31;
    undefined field41_0x32;
    undefined field42_0x33;
    undefined field43_0x34;
    undefined field44_0x35;
    undefined field45_0x36;
    undefined field46_0x37;
    undefined field47_0x38;
    undefined field48_0x39;
    undefined field49_0x3a;
    undefined field50_0x3b;
    undefined field51_0x3c;
    undefined field52_0x3d;
    undefined field53_0x3e;
    undefined field54_0x3f;
    int some_event;
    int some_param;
    undefined4 field57_0x48;
    undefined field58_0x4c;
    undefined field59_0x4d;
    undefined field60_0x4e;
    undefined field61_0x4f;
    undefined8 msg_id;
    int *send_buffer;
    void *receive_buffer;
    void *send_ptr;
    s32 last_receive_size;
    s32 send_status;
    undefined1 idk_var;
    undefined field69_0x6d;
    undefined field70_0x6e;
    undefined field71_0x6f;
    s32 deci2count;
    undefined field73_0x74;
    undefined field74_0x75;
    undefined field75_0x76;
    undefined field76_0x77;
};

typedef byte const_void;

typedef struct SifCmdSysHandlerData_t SifCmdSysHandlerData_t, *PSifCmdSysHandlerData_t;

struct SifCmdSysHandlerData_t {
    void *handler;
    void *harg;
    void *unknown08;
};

typedef struct sce_stat sce_stat, *Psce_stat;

struct sce_stat {
    uint st_mode;
    uint st_attr;
    uint st_size;
    char st_ctime[8];
    char st_atime[8];
    char st_mtime[8];
    int st_hisize;
    int st_private[6];
};

typedef struct MemoryCard MemoryCard, *PMemoryCard;

struct MemoryCard {
    undefined field0_0x0;
    u32 handle;
    u32 countdown_to_check;
    u32 inited;
    u32 last_file;
    u32 mem_size;
    struct MemoryCardFile files[4];
};

typedef enum _ListOf125Values {
    New_Name=0,
    New_Name_(1)=4,
    New_Name_(2)=8,
    New_Name_(3)=16,
    New_Name_(4)=20,
    New_Name_(5)=24,
    New_Name_(6)=28,
    New_Name_(7)=32,
    FIX_SYM_INTEGER=36,
    FIX_SYM_SINTEGER=40,
    FIX_SYM_UINTEGER=44,
    FIX_SYM_BINTEGER=48,
    FIX_SYM_INT8=52,
    FIX_SYM_INT16=56,
    FIX_SYM_INT32=60,
    FIX_SYM_INT64=64,
    FIX_SYM_INT128=68,
    FIX_SYM_UINT8=72,
    FIX_SYM_UINT16=76,
    FIX_SYM_UINT32=80,
    FIX_SYM_UINT64=84,
    New_Name_(8)=88,
    New_Name_(9)=92,
    New_Name_(10)=96,
    New_Name_(11)=100,
    New_Name_(12)=104,
    New_Name_(13)=108,
    New_Name_(14)=112,
    New_Name_(15)=116,
    New_Name_(16)=120,
    New_Name_(17)=124,
    New_Name_(18)=128,
    New_Name_(19)=132,
    New_Name_(20)=136,
    New_Name_(21)=140,
    New_Name_(22)=144,
    New_Name_(23)=148,
    New_Name_(24)=152,
    New_Name_(26)=156,
    New_Name_(25)=160,
    New_Name_(27)=164,
    New_Name_(28)=168,
    New_Name_(29)=172,
    New_Name_(30)=176,
    New_Name_(31)=180,
    New_Name_(32)=184,
    New_Name_(33)=188,
    New_Name_(34)=192,
    New_Name_(35)=196,
    New_Name_(36)=200,
    New_Name_(37)=204,
    New_Name_(38)=208,
    New_Name_(39)=212,
    New_Name_(40)=216,
    220=220,
    New_Name_(41)=224,
    New_Name_(42)=228,
    New_Name_(43)=232,
    New_Name_(44)=236,
    New_Name_(45)=240,
    New_Name_(46)=244,
    New_Name_(47)=248,
    New_Name_(48)=252,
    New_Name_(49)=256,
    New_Name_(50)=260,
    New_Name_(50.2)=264,
    NN:268=268,
    New_Name_(51)=272,
    New_Name_(52)=276,
    New_Name_(53)=280,
    New_Name_(54)=284,
    New_Name_(55)=288,
    New_Name_(56)=292,
    New_Name_(57)=296,
    New_Name_(58)=300,
    New_Name_(59)=304,
    New_Name_(60)=308,
    New_Name_(61)=312,
    New_Name_(62)=316,
    New_Name_(63)=320,
    New_Name_(64)=324,
    New_Name_(65)=328,
    New_Name_(66)=332,
    New_Name_(67)=336,
    New_Name_(68)=340,
    New_Name_(69)=344,
    New_Name_(70)=348,
    New_Name_(71)=352,
    New_Name_(73)=356,
    New_Name_(72)=360,
    New_Name_(74)=364,
    New_Name_(75)=368,
    New_Name_(76)=372,
    New_Name_(77)=376,
    New_Name_(78)=380,
    New_Name_(79)=384,
    NN:388=388,
    New_Name_(80)=392,
    New_Name_(81)=396,
    New_Name_(82)=400,
    New_Name_(83)=404,
    New_Name_(84)=408,
    New_Name_(85)=412,
    New_Name_(86)=416,
    New_Name_(87)=420,
    New_Name_(88)=424,
    New_Name_(89)=428,
    New_Name_(90)=432,
    New_Name_(91)=436,
    New_Name_(92)=440,
    New_Name_(93)=448,
    New_Name_(94)=452,
    New_Name_(95)=456,
    New_Name_(96)=460,
    New_Name_(97)=464,
    New_Name_(98)=468,
    New_Name_(99)=472,
    New_Name_(100)=476,
    New_Name_(101)=480,
    New_Name_(102)=484,
    New_Name_(103)=488,
    New_Name_(104)=492,
    New_Name_(105)=496,
    New_Name_(106)=500,
    New_Name_(107)=504,
    New_Name_(108)=508,
    New_Name_(109)=512,
    New_Name_(110)=516,
    New_Name_(111)=520,
    New_Name_(112)=524,
    New_Name_(113)=528,
    New_Name_(114)=532,
    New_Name_(115)=536,
    New_Name_(116)=540,
    New_Name_(117)=544,
    New_Name_(118)=548,
    New_Name_(119)=552,
    New_Name_(120)=556,
    New_Name_(121)=560,
    New_Name_(122)=564,
    New_Name_(123)=568,
    New_Name_(124)=572,
    New_Name_(125)=576,
    New_Name_(126)=580,
    New_Name_(127)=584,
    New_Name_(128)=588,
    New_Name_(129)=592,
    New_Name_(130)=596,
    New_Name_(131)=600
} _ListOf125Values;

typedef struct UnreliableInitData_W UnreliableInitData_W, *PUnreliableInitData_W;

struct UnreliableInitData_W {
    int data;
    pointer function_pointer1;
    pointer initSceFunctions_callback;
    pointer function_pointer3;
};

typedef char const_char;

typedef struct SifDmaTransfer_t SifDmaTransfer_t, *PSifDmaTransfer_t;

struct SifDmaTransfer_t {
    void *src;
    void *dest;
    int size;
    int attr;
};

typedef struct MediusHashTable_W MediusHashTable_W, *PMediusHashTable_W;

struct MediusHashTable_W {
    void *field0_0x0;
    void *field1_0x4;
    void *field2_0x8;
    void *function_0xc;
    void *function_compare_0x10;
    void *function_copy_0x14;
    undefined4 field6_0x18;
    undefined4 field7_0x1c;
};

typedef struct sce_dirent sce_dirent, *Psce_dirent;

struct sce_dirent {
    struct sce_stat d_stat;
    char d_name[256];
    void *d_private;
};

typedef struct MemoryCardOperation MemoryCardOperation, *PMemoryCardOperation;

struct MemoryCardOperation {
    undefined field0_0x0;
    uint32_t param;
    uint32_t param2;
    undefined field3_0x9;
    uint32_t retry_count;
    u8 *data_ptr;
    u8 *data_ptr2;
};

typedef struct CPadInfo CPadInfo, *PCPadInfo;

struct CPadInfo {
    u8 valid;
    u8 status;
    u16 button0;
    u8 rightx;
    u8 righty;
    u8 leftx;
    u8 lefty;
    u8 abutton[12];
    u8 dummy[12];
    s32 number;
    s32 cpad_file;
    u32 button0_abs;
    u32 button0_shadow_abs;
    u32 button0_rel;
    float stick0_dir;
    float stick0_speed;
    s32 new_pad;
    s32 state;
    u8 align[6];
    u8 direct[6];
    u8 buzz_val[2];
    u8 buzz_pause_val[1];
    u8 buzz_pause_time;
    u64 buzz_time[2];
    u32 buzz;
    s32 buzz_act;
    s64 change_time;
};

typedef struct RpcCallEndFunctionArg_copy_W RpcCallEndFunctionArg_copy_W, *PRpcCallEndFunctionArg_copy_W;

struct RpcCallEndFunctionArg_copy_W {
    s32 sema_id;
    void *callback;
    s32 field2_0x8;
    s32 field3_0xc;
};

typedef struct sceMpeg sceMpeg, *PsceMpeg;

struct sceMpeg {
    undefined field0_0x0;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    undefined field4_0x4;
    undefined field5_0x5;
    undefined field6_0x6;
    undefined field7_0x7;
    undefined field8_0x8;
    undefined field9_0x9;
    undefined field10_0xa;
    undefined field11_0xb;
    undefined field12_0xc;
    undefined field13_0xd;
    undefined field14_0xe;
    undefined field15_0xf;
    undefined field16_0x10;
    undefined field17_0x11;
    undefined field18_0x12;
    undefined field19_0x13;
    undefined field20_0x14;
    undefined field21_0x15;
    undefined field22_0x16;
    undefined field23_0x17;
    undefined field24_0x18;
    undefined field25_0x19;
    undefined field26_0x1a;
    undefined field27_0x1b;
    undefined field28_0x1c;
    undefined field29_0x1d;
    undefined field30_0x1e;
    undefined field31_0x1f;
    undefined field32_0x20;
    undefined field33_0x21;
    undefined field34_0x22;
    undefined field35_0x23;
    undefined field36_0x24;
    undefined field37_0x25;
    undefined field38_0x26;
    undefined field39_0x27;
    undefined field40_0x28;
    undefined field41_0x29;
    undefined field42_0x2a;
    undefined field43_0x2b;
    undefined field44_0x2c;
    undefined field45_0x2d;
    undefined field46_0x2e;
    undefined field47_0x2f;
    undefined field48_0x30;
    undefined field49_0x31;
    undefined field50_0x32;
    undefined field51_0x33;
    undefined field52_0x34;
    undefined field53_0x35;
    undefined field54_0x36;
    undefined field55_0x37;
    undefined field56_0x38;
    undefined field57_0x39;
    undefined field58_0x3a;
    undefined field59_0x3b;
    undefined field60_0x3c;
    undefined field61_0x3d;
    undefined field62_0x3e;
    undefined field63_0x3f;
    undefined field64_0x40;
    undefined field65_0x41;
    undefined field66_0x42;
    undefined field67_0x43;
    undefined field68_0x44;
    undefined field69_0x45;
    undefined field70_0x46;
    undefined field71_0x47;
    void *field72_0x48;
    int field73_0x4c;
    undefined field74_0x50;
    undefined field75_0x51;
    undefined field76_0x52;
    undefined field77_0x53;
    undefined field78_0x54;
    undefined field79_0x55;
    undefined field80_0x56;
    undefined field81_0x57;
    undefined field82_0x58;
    undefined field83_0x59;
    undefined field84_0x5a;
    undefined field85_0x5b;
    undefined field86_0x5c;
    undefined field87_0x5d;
    undefined field88_0x5e;
    undefined field89_0x5f;
    undefined *field90_0x60;
    undefined field91_0x64;
    undefined field92_0x65;
    undefined field93_0x66;
    undefined field94_0x67;
    undefined4 field95_0x68;
    undefined field96_0x6c;
    undefined field97_0x6d;
    undefined field98_0x6e;
    undefined field99_0x6f;
    undefined field100_0x70;
    undefined field101_0x71;
    undefined field102_0x72;
    undefined field103_0x73;
    undefined field104_0x74;
    undefined field105_0x75;
    undefined field106_0x76;
    undefined field107_0x77;
    undefined field108_0x78;
    undefined field109_0x79;
    undefined field110_0x7a;
    undefined field111_0x7b;
    undefined field112_0x7c;
    undefined field113_0x7d;
    undefined field114_0x7e;
    undefined field115_0x7f;
    undefined field116_0x80;
    undefined field117_0x81;
    undefined field118_0x82;
    undefined field119_0x83;
    undefined field120_0x84;
    undefined field121_0x85;
    undefined field122_0x86;
    undefined field123_0x87;
    undefined field124_0x88;
    undefined field125_0x89;
    undefined field126_0x8a;
    undefined field127_0x8b;
    undefined field128_0x8c;
    undefined field129_0x8d;
    undefined field130_0x8e;
    undefined field131_0x8f;
    undefined field132_0x90;
    undefined field133_0x91;
    undefined field134_0x92;
    undefined field135_0x93;
    undefined field136_0x94;
    undefined field137_0x95;
    undefined field138_0x96;
    undefined field139_0x97;
    undefined field140_0x98;
    undefined field141_0x99;
    undefined field142_0x9a;
    undefined field143_0x9b;
    undefined field144_0x9c;
    undefined field145_0x9d;
    undefined field146_0x9e;
    undefined field147_0x9f;
    undefined field148_0xa0;
    undefined field149_0xa1;
    undefined field150_0xa2;
    undefined field151_0xa3;
    undefined field152_0xa4;
    undefined field153_0xa5;
    undefined field154_0xa6;
    undefined field155_0xa7;
    undefined field156_0xa8;
    undefined field157_0xa9;
    undefined field158_0xaa;
    undefined field159_0xab;
    undefined field160_0xac;
    undefined field161_0xad;
    undefined field162_0xae;
    undefined field163_0xaf;
    undefined field164_0xb0;
    undefined field165_0xb1;
    undefined field166_0xb2;
    undefined field167_0xb3;
    undefined field168_0xb4;
    undefined field169_0xb5;
    undefined field170_0xb6;
    undefined field171_0xb7;
    undefined field172_0xb8;
    undefined field173_0xb9;
    undefined field174_0xba;
    undefined field175_0xbb;
    undefined field176_0xbc;
    undefined field177_0xbd;
    undefined field178_0xbe;
    undefined field179_0xbf;
    undefined field180_0xc0;
    undefined field181_0xc1;
    undefined field182_0xc2;
    undefined field183_0xc3;
    undefined field184_0xc4;
    undefined field185_0xc5;
    undefined field186_0xc6;
    undefined field187_0xc7;
    undefined field188_0xc8;
    undefined field189_0xc9;
    undefined field190_0xca;
    undefined field191_0xcb;
    undefined4 field192_0xcc;
};

typedef struct sceMpegCbData sceMpegCbData, *PsceMpegCbData;

struct sceMpegCbData {
};

typedef struct SifRpcCallPkt_t SifRpcCallPkt_t, *PSifRpcCallPkt_t;

struct SifRpcCallPkt_t {
    struct SifCmdHeader_t sifcmd;
    undefined field1_0x10;
    undefined field2_0x11;
    undefined field3_0x12;
    undefined field4_0x13;
    void *pkt_addr; // probably at 0x14
    int rpc_id; // probably at 0x18
    struct SifRpcClientData_t *client; // at x1c
    int rpc_number; // probably at 0x20
    int send_size; // probably at 0x24
    void *receive; // probably at 0x28
    int recv_size; // probably at 0x2c
    int rmode;
    struct SifRpcServerData_t *server; // at 0x34
    int rec_id;
};

typedef struct BindAssignmentInfo BindAssignmentInfo, *PBindAssignmentInfo;

struct BindAssignmentInfo {
    u32 port;
    u32 device_type;
    u32 buttons;
    u32 input_idx;
    u32 analog_min_range;
};

typedef struct LinkBlock LinkBlock, *PLinkBlock;

struct LinkBlock {
    u32 length;
    u32 version;
};

typedef struct cmd_data cmd_data, *Pcmd_data;

struct cmd_data {
    void *pktbuf;
    void *unused;
    void *iopbuf;
    struct SifCmdSysHandlerData_t *sys_cmd_handlers;
    u32 nr_sys_handlers;
    struct SifCmdHandlerData_t *usr_cmd_handlers;
    u32 nr_usr_handlers;
    int *sregs;
};

typedef struct McHeader McHeader, *PMcHeader;

struct McHeader {
    u32 save_count;
    u32 checksum;
    u32 magic;
    u8 preview_data[64];
    u8 data[944];
    u32 save_count2;
};

typedef struct VuFunction VuFunction, *PVuFunction;

struct VuFunction {
    u32 length;
    u32 origin;
    u32 qlength;
};

typedef short int16_t;

typedef int16_t s16;

typedef enum FixedSymbolTypeOffset {
    New_Name=0,
    New_Name_(1)=4,
    FIX_SYM_FUNCTION_TYPE=8,
    FIX_SYM_BASIC=12,
    FIX_SYM_STRING_TYPE=16,
    FIX_SYM_SYMBOL_TYPE=20,
    FIX_SYM_TYPE_TYPE=24,
    FIX_SYM_OBJECT_TYPE=28,
    FIX_SYM_LINK_BLOCK=32,
    FIX_SYM_INTEGER=36,
    FIX_SYM_SINTEGER=40,
    FIX_SYM_UINTEGER=44,
    FIX_SYM_BINTEGER=48,
    FIX_SYM_INT8=52,
    FIX_SYM_INT16=56,
    FIX_SYM_INT32=60,
    FIX_SYM_INT64=64,
    FIX_SYM_INT128=68,
    FIX_SYM_UINT8=72,
    FIX_SYM_UINT16=76,
    FIX_SYM_UINT32=80,
    FIX_SYM_UINT64=84,
    FIX_SYM_UINT128=88,
    FIX_SYM_FLOAT=92,
    FIX_SYM_PROCESS_TREE=96,
    FIX_SYM_PROCESS_TYPE=100,
    FIX_SYM_THREAD=104,
    FIX_SYM_STRUCTURE=108,
    FIX_SYM_PAIR_TYPE=112,
    FIX_SYM_POINTER=116,
    FIX_SYM_NUMBER=120,
    FIX_SYM_ARRAY=124,
    FIX_SYM_VU_FUNCTION=128,
    FIX_SYM_CONNECTABLE=132,
    FIX_SYM_STACK_FRAME=136,
    FIX_SYM_FILE_STREAM=140,
    FIX_SYM_HEAP=144,
    New_Name_(23)=148,
    New_Name_(24)=152,
    New_Name_(26)=156,
    New_Name_(25)=160,
    New_Name_(27)=164,
    New_Name_(28)=168,
    New_Name_(29)=172,
    New_Name_(30)=176,
    New_Name_(31)=180,
    New_Name_(32)=184,
    New_Name_(33)=188,
    New_Name_(34)=192,
    New_Name_(35)=196,
    New_Name_(36)=200,
    New_Name_(37)=204,
    New_Name_(38)=208,
    New_Name_(39)=212,
    New_Name_(40)=216,
    220=220,
    New_Name_(41)=224,
    New_Name_(42)=228,
    New_Name_(43)=232,
    New_Name_(44)=236,
    New_Name_(45)=240,
    New_Name_(46)=244,
    New_Name_(47)=248,
    New_Name_(48)=252,
    New_Name_(49)=256,
    New_Name_(50)=260,
    268=268,
    New_Name_(51)=272,
    New_Name_(52)=276,
    New_Name_(53)=280,
    New_Name_(54)=284,
    New_Name_(55)=288,
    New_Name_(56)=292,
    New_Name_(57)=296,
    New_Name_(58)=300,
    New_Name_(59)=304,
    New_Name_(60)=308,
    New_Name_(61)=312,
    New_Name_(62)=316,
    New_Name_(63)=320,
    New_Name_(64)=324,
    New_Name_(65)=328,
    New_Name_(66)=332,
    New_Name_(67)=336,
    New_Name_(68)=340,
    New_Name_(69)=344,
    New_Name_(70)=348,
    New_Name_(71)=352,
    New_Name_(73)=356,
    New_Name_(72)=360,
    New_Name_(74)=364,
    New_Name_(75)=368,
    New_Name_(76)=372,
    New_Name_(77)=376,
    New_Name_(78)=380,
    New_Name_(79)=384,
    388=388,
    New_Name_(80)=392,
    New_Name_(81)=396,
    New_Name_(82)=400,
    New_Name_(83)=404,
    New_Name_(84)=408,
    New_Name_(85)=412,
    New_Name_(86)=416,
    New_Name_(87)=420,
    New_Name_(88)=424,
    New_Name_(89)=428,
    New_Name_(90)=432,
    New_Name_(91)=436,
    New_Name_(92)=440,
    New_Name_(93)=448,
    New_Name_(94)=452,
    New_Name_(95)=456,
    New_Name_(96)=460,
    New_Name_(97)=464,
    New_Name_(98)=468,
    New_Name_(99)=472,
    New_Name_(100)=476,
    New_Name_(101)=480,
    New_Name_(102)=484,
    New_Name_(103)=488,
    New_Name_(104)=492,
    New_Name_(105)=496,
    New_Name_(106)=500,
    New_Name_(107)=504,
    New_Name_(108)=508,
    New_Name_(109)=512,
    New_Name_(110)=516,
    New_Name_(111)=520,
    New_Name_(112)=524,
    New_Name_(113)=528,
    New_Name_(114)=532,
    New_Name_(115)=536,
    New_Name_(116)=540,
    New_Name_(117)=544,
    New_Name_(118)=548,
    New_Name_(119)=552,
    New_Name_(120)=556,
    New_Name_(121)=560,
    New_Name_(122)=564,
    New_Name_(123)=568,
    New_Name_(124)=572,
    New_Name_(125)=576,
    New_Name_(126)=580,
    New_Name_(127)=584,
    New_Name_(128)=588,
    New_Name_(129)=592,
    New_Name_(130)=596,
    New_Name_(131)=600
} FixedSymbolTypeOffset;

typedef enum FixedSymbolOffset {
    FIX_SYM_FALSE=0,
    FIX_SYM_TRUE=4,
    VVV=8,
    New_Name_(3)=16,
    New_Name_(4)=20,
    New_Name_(5)=24,
    New_Name_(6)=28,
    New_Name_(7)=32,
    FIX_SYM_INTEGER=36,
    FIX_SYM_SINTEGER=40,
    FIX_SYM_UINTEGER=44,
    FIX_SYM_BINTEGER=48,
    FIX_SYM_INT8=52,
    FIX_SYM_INT16=56,
    FIX_SYM_INT32=60,
    FIX_SYM_INT64=64,
    FIX_SYM_INT128=68,
    FIX_SYM_UINT8=72,
    FIX_SYM_UINT16=76,
    FIX_SYM_UINT32=80,
    FIX_SYM_UINT64=84,
    New_Name_(8)=88,
    New_Name_(9)=92,
    New_Name_(10)=96,
    New_Name_(11)=100,
    New_Name_(12)=104,
    New_Name_(13)=108,
    New_Name_(14)=112,
    New_Name_(15)=116,
    New_Name_(16)=120,
    New_Name_(17)=124,
    New_Name_(18)=128,
    New_Name_(19)=132,
    New_Name_(20)=136,
    New_Name_(21)=140,
    New_Name_(22)=144,
    FIX_SYM_NOTHING_FUNC=148,
    FIX_SYM_DELETE_BASIC=152,
    FIX_SYM_STATIC=156,
    FIX_SYM_GLOBAL_HEAP=160,
    FIX_SYM_DEBUG=164,
    FIX_SYM_LOADING_LEVEL=168,
    FIX_SYM_LOADING_PACKAGE=172,
    FIX_SYM_PROCESS_LEVEL_HEAP=176,
    FIX_SYM_STACK=180,
    FIX_SYM_SCRATCH=184,
    FIX_SYM_SCRATCH_TOP=188,
    FIX_SYM_ZERO_FUNC=192,
    FIX_SYM_ASIZE_OF_BASIC_FUNC=196,
    FIX_SYM_COPY_BASIC_FUNC=200,
    FIX_SYM_LEVEL=204,
    FIX_SYM_ART_GROUP=208,
    FIX_SYM_TEXTURE_PAGE_DIR=212,
    FIX_SYM_TEXTURE_PAGE=216,
    FIX_SYM_SOUND=220,
    FIX_SYM_DGO=224,
    FIX_SYM_TOP_LEVEL=228,
    FIX_SYM_QUOTE=232,
    FIX_SYM_LISTENER_LINK_BLOCK=236,
    FIX_SYM_LISTENER_FUNCTION=240,
    FIX_SYM_STACK_TOP=244,
    FIX_SYM_STACK_BASE=248,
    FIX_SYM_STACK_SIZE=252,
    FIX_SYM_KERNEL_FUNCTION=256,
    FIX_SYM_KERNEL_PACKAGES=260,
    FIX_SYM_KERNEL_BOOT_MESSAGE=264,
    FIX_SYM_KERNEL_BOOT_MODE=268,
    FIX_SYM_KERNEL_BOOT_LEVEL=272,
    FIX_SYM_KERNEL_BOOT_ART_GROUP=276,
    FIX_SYM_KERNEL_DEBUG=280,
    FIX_SYM_KERNEL_VERSION=284,
    FIX_SYM_KERNEL_DISPATCHER=288,
    FIX_SYM_SYNC_DISPATCHER=292,
    FIX_SYM_PRINT_COLLUMN=296,
    FIX_SYM_DEBUG_SEGMENT=300,
    FIX_SYM_ENABLE_METHOD_SET=304,
    FIX_SYM_SQL_RESULT=308,
    FIX_SYM_COLLAPSE_QUOTE=312,
    FIX_SYM_LEVEL_TYPE_LIST=316,
    FIX_SYM_DECI_COUNT=320,
    FIX_SYM_USER=324,
    FIX_SYM_VIDEO_MODE=328,
    FIX_SYM_BOOT_VIDEO_MODE=332,
    FIX_SYM_BOOT=336,
    FIX_SYM_DEMO=340,
    FIX_SYM_DEMO_SHARED=344,
    FIX_SYM_PREVIEW=348,
    FIX_SYM_KIOSK=352,
    FIX_SYM_PLAY_BOOT=356,
    FIX_SYM_SIN=360,
    FIX_SYM_COS=364,
    FIX_SYM_PUT_DISPLAY_ENV=368,
    FIX_SYM_SYNCV=372,
    FIX_SYM_SYNC_PATH=376,
    FIX_SYM_RESET_PATH=380,
    FIX_SYM_RESET_GRAPH=384,
    FIX_SYM_DMA_SYNC=388,
    FIX_SYM_GS_PUT_IMR=392,
    FIX_SYM_GS_GET_IMR=396,
    FIX_SYM_GS_STORE_IMAGE=400,
    FIX_SYM_FLUSH_CACHE=404,
    FIX_SYM_CPAD_OPEN=408,
    FIX_SYM_CPAD_GET_DATA=412,
    FIX_SYM_MOUSE_GET_DATA=416,
    FIX_SYM_KEYBD_GET_DATA=420,
    FIX_SYM_INSTALL_HANDLER=424,
    FIX_SYM_INSTALL_DEBUG_HANDLER=428,
    FIX_SYM_FILE_STREAM_OPEN=432,
    FIX_SYM_FILE_STREAM_CLOSE=436,
    FIX_SYM_FILE_STREAM_LENGTH=440,
    FIX_SYM_FILE_STREAM_SEEK=444,
    FIX_SYM_FILE_STREAM_READ=448,
    FIX_SYM_FILE_STREAM_WRITE=452,
    FIX_SYM_SCF_GET_LANGUAGE=456,
    FIX_SYM_SCF_GET_TIME=460,
    FIX_SYM_SCF_GET_ASPECT=464,
    FIX_SYM_SCF_GET_VOLUME=468,
    FIX_SYM_SCF_GET_TERRITORY=472,
    FIX_SYM_SCF_GET_TIMEOUT=476,
    FIX_SYM_SCF_GET_INACTIVE_TIMEOUT=480,
    FIX_SYM_DMA_TO_IOP=484,
    FIX_SYM_KERNEL_SHUTDOWN=488,
    FIX_SYM_AYBABTU=492,
    FIX_SYM_STRING_TO_SYMBOL=496,
    FIX_SYM_SYMBOL_TO_STRING=500,
    FIX_SYM_PRINT=504,
    FIX_SYM_INSPECT=508,
    FIX_SYM_LOAD=512,
    FIX_SYM_LOADB=516,
    FIX_SYM_LOADO=520,
    FIX_SYM_UNLOAD=524,
    FIX_SYM_FORMAT=528,
    FIX_SYM_MALLOC=532,
    FIX_SYM_KMALLOC=536,
    FIX_SYM_KMEMOPEN=540,
    FIX_SYM_KMEMCLOSE=544,
    FIX_SYM_NEW_DYNAMIC_STRUCTURE=548,
    FIX_SYM_METHOD_SET=552,
    FIX_SYM_LINK=556,
    FIX_SYM_LINK_BUSY=560,
    FIX_SYM_LINK_RESET=564,
    FIX_SYM_LINK_BEGIN=568,
    FIX_SYM_LINK_RESUME=572,
    FIX_SYM_DGO_LOAD=576,
    FIX_SYM_SQL_QUERY=580,
    FIX_SYM_MC_RUN=584,
    FIX_SYM_MC_FORMAT=588,
    FIX_SYM_MC_UNFORMAT=592,
    FIX_SYM_MC_CREATE_FILE=596,
    FIX_SYM_MC_SAVE=600,
    FIX_SYM_MC_LOAD=604,
    FIX_SYM_MC_CHECK_RESULT=608,
    FIX_SYM_MC_GET_SLOT_INFO=612,
    FIX_SYM_MC_MAKEFILE=616,
    FIX_SYM_KSET_LANGUAGE=620,
    FIX_SYM_RPC_CALL=624,
    FIX_SYM_RPC_BUSY=628,
    FIX_SYM_TEST_LOAD_DGO_C=632,
    FIX_SYM_SYMLINK2=636,
    FIX_SYM_SYMLINK3=640,
    FIX_SYM_ULTIMATE_MEMCPY=644,
    FIX_SYM_PLAY=648,
    FIX_SYM_SYMBOL_STRING=652,
    FIX_SYM_KERNEL_SYMBOL_WARNINGS=656,
    FIX_SYM_NETWORK_BOOTSTRAP=660,
    FIX_SYM_FILE_STREAM_MKDIR=664,
    FIX_SYM_BETA=668
} FixedSymbolOffset;

typedef undefined **SymbolTable;

typedef struct RPC_Dgo_Cmd RPC_Dgo_Cmd, *PRPC_Dgo_Cmd;

struct RPC_Dgo_Cmd {
    uint16_t rsvd;
    uint16_t result;
    uint32_t buffer1;
    uint32_t buffer2;
    uint32_t buffer_heap_top;
    char name[16];
    int32_t cgo_id;
    char padding[28];
};

typedef struct GoalStackArgs GoalStackArgs, *PGoalStackArgs;

struct GoalStackArgs {
    u64 field0_0x0[8];
};

typedef struct _IO_FILE FILE;

typedef long __ssize_t;

typedef __ssize_t ssize_t;

typedef int __pid_t;

typedef struct DisplayParams_TG DisplayParams_TG, *PDisplayParams_TG;

struct DisplayParams_TG {
    undefined8 field0_0x0;
    undefined8 field1_0x8;
    undefined field2_0x10;
    undefined field3_0x11;
    undefined field4_0x12;
    undefined field5_0x13;
    undefined field6_0x14;
    undefined field7_0x15;
    undefined field8_0x16;
    undefined field9_0x17;
    undefined field10_0x18;
    undefined field11_0x19;
    undefined field12_0x1a;
    undefined field13_0x1b;
    undefined field14_0x1c;
    undefined field15_0x1d;
    undefined field16_0x1e;
    undefined field17_0x1f;
    undefined field18_0x20;
    undefined field19_0x21;
    undefined field20_0x22;
    undefined field21_0x23;
    undefined field22_0x24;
    undefined field23_0x25;
    undefined field24_0x26;
    undefined field25_0x27;
    undefined field26_0x28;
    undefined field27_0x29;
    undefined field28_0x2a;
    undefined field29_0x2b;
    undefined field30_0x2c;
    undefined field31_0x2d;
    undefined field32_0x2e;
    undefined field33_0x2f;
};

typedef struct sceMpegCbDataStr sceMpegCbDataStr, *PsceMpegCbDataStr;

struct sceMpegCbDataStr {
    undefined field0_0x0;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    undefined field4_0x4;
    undefined field5_0x5;
    undefined field6_0x6;
    undefined field7_0x7;
    void *field8_0x8;
    int field9_0xc;
};

typedef struct smap_rpc_server_struct_W smap_rpc_server_struct_W, *Psmap_rpc_server_struct_W;

struct smap_rpc_server_struct_W {
    undefined field0_0x0;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    undefined field4_0x4;
    undefined field5_0x5;
    undefined field6_0x6;
    undefined field7_0x7;
    undefined field8_0x8;
    undefined field9_0x9;
    undefined field10_0xa;
    undefined field11_0xb;
    undefined field12_0xc;
    undefined field13_0xd;
    undefined field14_0xe;
    undefined field15_0xf;
    undefined field16_0x10;
    undefined field17_0x11;
    undefined field18_0x12;
    undefined field19_0x13;
    undefined field20_0x14;
    undefined field21_0x15;
    undefined field22_0x16;
    undefined field23_0x17;
    undefined field24_0x18;
    undefined field25_0x19;
    undefined field26_0x1a;
    undefined field27_0x1b;
    undefined field28_0x1c;
    undefined field29_0x1d;
    undefined field30_0x1e;
    undefined field31_0x1f;
    undefined field32_0x20;
    undefined field33_0x21;
    undefined field34_0x22;
    undefined field35_0x23;
    undefined field36_0x24;
    undefined field37_0x25;
    undefined field38_0x26;
    undefined field39_0x27;
    undefined field40_0x28;
    undefined field41_0x29;
    undefined field42_0x2a;
    undefined field43_0x2b;
    undefined field44_0x2c;
    undefined field45_0x2d;
    undefined field46_0x2e;
    undefined field47_0x2f;
    undefined field48_0x30;
    undefined field49_0x31;
    undefined field50_0x32;
    undefined field51_0x33;
    undefined field52_0x34;
    undefined field53_0x35;
    undefined field54_0x36;
    undefined field55_0x37;
    int field56_0x38;
    undefined field57_0x3c;
    undefined field58_0x3d;
    undefined field59_0x3e;
    undefined field60_0x3f;
    struct SifRpcDataQueue_t field61_0x40;
    struct SifRpcServerData_t field62_0x58;
    undefined field63_0x9c;
    undefined field64_0x9d;
    undefined field65_0x9e;
    undefined field66_0x9f;
    undefined field67_0xa0;
    undefined field68_0xa1;
    undefined field69_0xa2;
    undefined field70_0xa3;
    undefined field71_0xa4;
    undefined field72_0xa5;
    undefined field73_0xa6;
    undefined field74_0xa7;
    undefined field75_0xa8;
    undefined field76_0xa9;
    undefined field77_0xaa;
    undefined field78_0xab;
    int field79_0xac;
    undefined field80_0xb0;
    undefined field81_0xb1;
    undefined field82_0xb2;
    undefined field83_0xb3;
    undefined field84_0xb4;
    undefined field85_0xb5;
    undefined field86_0xb6;
    undefined field87_0xb7;
    undefined field88_0xb8;
    undefined field89_0xb9;
    undefined field90_0xba;
    undefined field91_0xbb;
    undefined field92_0xbc;
    undefined field93_0xbd;
    undefined field94_0xbe;
    undefined field95_0xbf;
    struct SifRpcServerData_t *field96_0xc0;
};

typedef struct UnreliablePacket_W UnreliablePacket_W, *PUnreliablePacket_W;

struct UnreliablePacket_W {
    undefined field0_0x0;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    undefined4 field4_0x4;
    byte *field5_0x8;
    int field6_0xc;
    undefined field7_0x10;
    undefined field8_0x11;
    undefined1 someFlags_2_W; // Created by retype action
    undefined field10_0x13;
    undefined4 field11_0x14;
    int numberOfBytes_W;
};

typedef struct ProductsAndPurchasesData_W ProductsAndPurchasesData_W, *PProductsAndPurchasesData_W;

struct ProductsAndPurchasesData_W {
    int field0_0x0;
    int field1_0x4;
    int free_able_x2;
    int field3_0xc;
    int field4_0x10;
    int field5_0x14;
    int field6_0x18;
    int field7_0x1c;
    int free_able_x20;
    int field9_0x24;
    int field10_0x28;
    int field11_0x2c;
    int field12_0x30;
    int free_able_x34;
    int field14_0x38;
    int field15_0x3c;
    int field16_0x40;
    int field17_0x44;
    int field18_0x48;
    int freeable_x4c;
    int field20_0x50;
    int field21_0x54;
    int field22_0x58;
    int field23_0x5c;
    int field24_0x60;
    int field25_0x64;
    int field26_0x68;
    int field27_0x6c;
    int field28_0x70;
};

typedef struct rt_mutex_data rt_mutex_data, *Prt_mutex_data;

struct rt_mutex_data {
    int field0_0x0;
    int field1_0x4;
    int field2_0x8;
};

typedef struct UnreliableDataType3_W UnreliableDataType3_W, *PUnreliableDataType3_W;

struct UnreliableDataType3_W {
    undefined field0_0x0;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    int field4_0x4;
    int field5_0x8;
    int field6_0xc;
    int field7_0x10;
    char *field8_0x14;
    int field9_0x18;
    int field10_0x1c;
    undefined field11_0x20;
    undefined field12_0x21;
    undefined field13_0x22;
    undefined field14_0x23;
    undefined field15_0x24;
    undefined field16_0x25;
    undefined field17_0x26;
    undefined field18_0x27;
    undefined field19_0x28;
    undefined field20_0x29;
    undefined field21_0x2a;
    undefined field22_0x2b;
    undefined field23_0x2c;
    undefined field24_0x2d;
    undefined field25_0x2e;
    undefined field26_0x2f;
    undefined2 field27_0x30;
    undefined field28_0x32;
    undefined field29_0x33;
    undefined field30_0x34;
    undefined field31_0x35;
    undefined field32_0x36;
    undefined field33_0x37;
    undefined field34_0x38;
    undefined field35_0x39;
    undefined field36_0x3a;
    undefined field37_0x3b;
    undefined field38_0x3c;
    undefined field39_0x3d;
    undefined field40_0x3e;
    undefined field41_0x3f;
    undefined8 field42_0x40;
    undefined field43_0x48;
    undefined field44_0x49;
    undefined field45_0x4a;
    undefined field46_0x4b;
    undefined field47_0x4c;
    undefined field48_0x4d;
    undefined field49_0x4e;
    undefined field50_0x4f;
    undefined field51_0x50;
    undefined field52_0x51;
    undefined field53_0x52;
    undefined field54_0x53;
    undefined field55_0x54;
    undefined field56_0x55;
    undefined field57_0x56;
    undefined field58_0x57;
    undefined field59_0x58;
    undefined field60_0x59;
    undefined field61_0x5a;
    undefined field62_0x5b;
    undefined field63_0x5c;
    undefined field64_0x5d;
    undefined field65_0x5e;
    undefined field66_0x5f;
    undefined field67_0x60;
    undefined field68_0x61;
    undefined field69_0x62;
    undefined field70_0x63;
    undefined field71_0x64;
    undefined field72_0x65;
    undefined field73_0x66;
    undefined field74_0x67;
    undefined field75_0x68;
    undefined field76_0x69;
    undefined field77_0x6a;
    undefined field78_0x6b;
    undefined field79_0x6c;
    undefined field80_0x6d;
    undefined field81_0x6e;
    undefined field82_0x6f;
    undefined field83_0x70;
    undefined field84_0x71;
    undefined field85_0x72;
    undefined field86_0x73;
    undefined field87_0x74;
    undefined field88_0x75;
    undefined field89_0x76;
    undefined field90_0x77;
    undefined field91_0x78;
    undefined field92_0x79;
    undefined field93_0x7a;
    undefined field94_0x7b;
    undefined field95_0x7c;
    undefined field96_0x7d;
    undefined field97_0x7e;
    undefined field98_0x7f;
    undefined field99_0x80;
    undefined field100_0x81;
    undefined field101_0x82;
    undefined field102_0x83;
    undefined field103_0x84;
    undefined field104_0x85;
    undefined field105_0x86;
    undefined field106_0x87;
    undefined field107_0x88;
    undefined field108_0x89;
    undefined field109_0x8a;
    undefined field110_0x8b;
    undefined field111_0x8c;
    undefined field112_0x8d;
    undefined field113_0x8e;
    undefined field114_0x8f;
    undefined field115_0x90;
    undefined field116_0x91;
    undefined field117_0x92;
    undefined field118_0x93;
    undefined field119_0x94;
    undefined field120_0x95;
    undefined field121_0x96;
    undefined field122_0x97;
    undefined field123_0x98;
    undefined field124_0x99;
    undefined field125_0x9a;
    undefined field126_0x9b;
    undefined field127_0x9c;
    undefined field128_0x9d;
    undefined field129_0x9e;
    undefined field130_0x9f;
    undefined field131_0xa0;
    undefined field132_0xa1;
    undefined field133_0xa2;
    undefined field134_0xa3;
    undefined field135_0xa4;
    undefined field136_0xa5;
    undefined field137_0xa6;
    undefined field138_0xa7;
    undefined field139_0xa8;
    undefined field140_0xa9;
    undefined field141_0xaa;
    undefined field142_0xab;
    undefined field143_0xac;
    undefined field144_0xad;
    undefined field145_0xae;
    undefined field146_0xaf;
    undefined field147_0xb0;
    undefined field148_0xb1;
    undefined field149_0xb2;
    undefined field150_0xb3;
    undefined field151_0xb4;
    undefined field152_0xb5;
    undefined field153_0xb6;
    undefined field154_0xb7;
    undefined field155_0xb8;
    undefined field156_0xb9;
    undefined field157_0xba;
    undefined field158_0xbb;
    undefined field159_0xbc;
    undefined field160_0xbd;
    undefined field161_0xbe;
    undefined field162_0xbf;
    undefined field163_0xc0;
    undefined field164_0xc1;
    undefined field165_0xc2;
    undefined field166_0xc3;
    undefined field167_0xc4;
    undefined field168_0xc5;
    undefined field169_0xc6;
    undefined field170_0xc7;
    undefined *field171_0xc8;
    undefined *field172_0xcc;
    undefined field173_0xd0;
    undefined field174_0xd1;
    undefined field175_0xd2;
    undefined field176_0xd3;
    undefined field177_0xd4;
    undefined field178_0xd5;
    undefined field179_0xd6;
    undefined field180_0xd7;
    undefined field181_0xd8;
    undefined field182_0xd9;
    undefined field183_0xda;
    undefined field184_0xdb;
    undefined field185_0xdc;
    undefined field186_0xdd;
    undefined field187_0xde;
    undefined field188_0xdf;
    undefined field189_0xe0;
    undefined field190_0xe1;
    undefined field191_0xe2;
    undefined field192_0xe3;
    undefined field193_0xe4;
    undefined field194_0xe5;
    undefined field195_0xe6;
    undefined field196_0xe7;
    undefined4 field197_0xe8;
    undefined field198_0xec;
    undefined field199_0xed;
    undefined field200_0xee;
    undefined field201_0xef;
    undefined field202_0xf0;
    undefined field203_0xf1;
    undefined field204_0xf2;
    undefined field205_0xf3;
    undefined field206_0xf4;
    undefined field207_0xf5;
    undefined field208_0xf6;
    undefined field209_0xf7;
    undefined field210_0xf8;
    undefined field211_0xf9;
    undefined field212_0xfa;
    undefined field213_0xfb;
    undefined field214_0xfc;
    undefined field215_0xfd;
    undefined field216_0xfe;
    undefined field217_0xff;
    undefined field218_0x100;
    undefined field219_0x101;
    undefined field220_0x102;
    undefined field221_0x103;
    undefined field222_0x104;
    undefined field223_0x105;
    undefined field224_0x106;
    undefined field225_0x107;
    undefined field226_0x108;
    undefined field227_0x109;
    undefined field228_0x10a;
    undefined field229_0x10b;
    undefined field230_0x10c;
    undefined field231_0x10d;
    undefined field232_0x10e;
    undefined field233_0x10f;
    undefined field234_0x110;
    undefined field235_0x111;
    undefined field236_0x112;
    undefined field237_0x113;
    undefined field238_0x114;
    undefined field239_0x115;
    undefined field240_0x116;
    undefined field241_0x117;
    undefined field242_0x118;
    undefined field243_0x119;
    undefined field244_0x11a;
    undefined field245_0x11b;
    void *field246_0x11c;
    void *field247_0x120;
    undefined field248_0x124;
    undefined field249_0x125;
    undefined field250_0x126;
    undefined field251_0x127;
    undefined field252_0x128;
    undefined field253_0x129;
    undefined field254_0x12a;
    undefined field255_0x12b;
    uint field256_0x12c;
    undefined4 field257_0x130;
};

typedef struct SomeBuffersAndStuff1_W SomeBuffersAndStuff1_W, *PSomeBuffersAndStuff1_W;

struct SomeBuffersAndStuff1_W {
    undefined field0_0x0;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    undefined field4_0x4;
    undefined field5_0x5;
    undefined field6_0x6;
    undefined field7_0x7;
    undefined field8_0x8;
    undefined field9_0x9;
    undefined field10_0xa;
    undefined field11_0xb;
    undefined field12_0xc;
    undefined field13_0xd;
    undefined field14_0xe;
    undefined field15_0xf;
    undefined4 field16_0x10;
    int field17_0x14;
    undefined4 field18_0x18;
    undefined4 field19_0x1c;
    int field20_0x20;
    undefined4 field21_0x24;
    undefined4 field22_0x28;
    int field23_0x2c;
    undefined4 field24_0x30;
    undefined2 field25_0x34;
    undefined2 field26_0x36;
    char field27_0x38[256];
    char field28_0x138[256];
    undefined2 field29_0x238;
    undefined2 field30_0x23a;
    char field31_0x23c[256];
    char field32_0x33c[256];
    undefined field33_0x43c;
    undefined field34_0x43d;
    undefined field35_0x43e;
    undefined field36_0x43f;
    undefined field37_0x440;
    undefined field38_0x441;
    undefined field39_0x442;
    undefined field40_0x443;
    undefined field41_0x444;
    undefined field42_0x445;
    undefined field43_0x446;
    undefined field44_0x447;
    undefined field45_0x448;
    undefined field46_0x449;
    undefined field47_0x44a;
    undefined field48_0x44b;
    undefined field49_0x44c;
    undefined field50_0x44d;
    undefined field51_0x44e;
    undefined field52_0x44f;
    undefined field53_0x450;
    undefined field54_0x451;
    undefined field55_0x452;
    undefined field56_0x453;
    undefined field57_0x454;
    undefined field58_0x455;
    undefined field59_0x456;
    undefined field60_0x457;
    undefined field61_0x458;
    undefined field62_0x459;
    undefined field63_0x45a;
    undefined field64_0x45b;
    undefined field65_0x45c;
    undefined field66_0x45d;
    undefined field67_0x45e;
    undefined field68_0x45f;
    undefined field69_0x460;
    undefined field70_0x461;
    undefined field71_0x462;
    undefined field72_0x463;
    undefined field73_0x464;
    undefined field74_0x465;
    undefined field75_0x466;
    undefined field76_0x467;
    undefined field77_0x468;
    undefined field78_0x469;
    undefined field79_0x46a;
    undefined field80_0x46b;
    undefined field81_0x46c;
    undefined field82_0x46d;
    undefined field83_0x46e;
    undefined field84_0x46f;
    undefined field85_0x470;
    undefined field86_0x471;
    undefined field87_0x472;
    undefined field88_0x473;
    undefined field89_0x474;
    undefined field90_0x475;
    undefined field91_0x476;
    undefined field92_0x477;
    undefined field93_0x478;
    undefined field94_0x479;
    undefined field95_0x47a;
    undefined field96_0x47b;
    undefined field97_0x47c;
    undefined field98_0x47d;
    undefined field99_0x47e;
    undefined field100_0x47f;
    undefined field101_0x480;
    undefined field102_0x481;
    undefined field103_0x482;
    undefined field104_0x483;
    undefined field105_0x484;
    undefined field106_0x485;
    undefined field107_0x486;
    undefined field108_0x487;
    undefined field109_0x488;
    undefined field110_0x489;
    undefined field111_0x48a;
    undefined field112_0x48b;
    undefined field113_0x48c;
    undefined field114_0x48d;
    undefined field115_0x48e;
    undefined field116_0x48f;
    undefined field117_0x490;
    undefined field118_0x491;
    undefined field119_0x492;
    undefined field120_0x493;
    undefined field121_0x494;
    undefined field122_0x495;
    undefined field123_0x496;
    undefined field124_0x497;
    undefined field125_0x498;
    undefined field126_0x499;
    undefined field127_0x49a;
    undefined field128_0x49b;
    undefined field129_0x49c;
    undefined field130_0x49d;
    undefined field131_0x49e;
    undefined field132_0x49f;
    undefined field133_0x4a0;
    undefined field134_0x4a1;
    undefined field135_0x4a2;
    undefined field136_0x4a3;
    undefined field137_0x4a4;
    undefined field138_0x4a5;
    undefined field139_0x4a6;
    undefined field140_0x4a7;
    undefined field141_0x4a8;
    undefined field142_0x4a9;
    undefined field143_0x4aa;
    undefined field144_0x4ab;
    undefined field145_0x4ac;
    undefined field146_0x4ad;
    undefined field147_0x4ae;
    undefined field148_0x4af;
    undefined field149_0x4b0;
    undefined field150_0x4b1;
    undefined field151_0x4b2;
    undefined field152_0x4b3;
    undefined field153_0x4b4;
    undefined field154_0x4b5;
    undefined field155_0x4b6;
    undefined field156_0x4b7;
    undefined field157_0x4b8;
    undefined field158_0x4b9;
    undefined field159_0x4ba;
    undefined field160_0x4bb;
    undefined field161_0x4bc;
    undefined field162_0x4bd;
    undefined field163_0x4be;
    undefined field164_0x4bf;
    undefined field165_0x4c0;
    undefined field166_0x4c1;
    undefined field167_0x4c2;
    undefined field168_0x4c3;
    undefined field169_0x4c4;
    undefined field170_0x4c5;
    undefined field171_0x4c6;
    undefined field172_0x4c7;
    undefined field173_0x4c8;
    undefined field174_0x4c9;
    undefined field175_0x4ca;
    undefined field176_0x4cb;
    undefined field177_0x4cc;
    undefined field178_0x4cd;
    undefined field179_0x4ce;
    undefined field180_0x4cf;
    undefined field181_0x4d0;
    undefined field182_0x4d1;
    undefined field183_0x4d2;
    undefined field184_0x4d3;
    undefined field185_0x4d4;
    undefined field186_0x4d5;
    undefined field187_0x4d6;
    undefined field188_0x4d7;
    undefined field189_0x4d8;
    undefined field190_0x4d9;
    undefined field191_0x4da;
    undefined field192_0x4db;
    undefined field193_0x4dc;
    undefined field194_0x4dd;
    undefined field195_0x4de;
    undefined field196_0x4df;
    undefined field197_0x4e0;
    undefined field198_0x4e1;
    undefined field199_0x4e2;
    undefined field200_0x4e3;
    undefined field201_0x4e4;
    undefined field202_0x4e5;
    undefined field203_0x4e6;
    undefined field204_0x4e7;
    undefined field205_0x4e8;
    undefined field206_0x4e9;
    undefined field207_0x4ea;
    undefined field208_0x4eb;
    undefined field209_0x4ec;
    undefined field210_0x4ed;
    undefined field211_0x4ee;
    undefined field212_0x4ef;
    undefined field213_0x4f0;
    undefined field214_0x4f1;
    undefined field215_0x4f2;
    undefined field216_0x4f3;
    undefined field217_0x4f4;
    undefined field218_0x4f5;
    undefined field219_0x4f6;
    undefined field220_0x4f7;
    undefined field221_0x4f8;
    undefined field222_0x4f9;
    undefined field223_0x4fa;
    undefined field224_0x4fb;
    undefined field225_0x4fc;
    undefined field226_0x4fd;
    undefined field227_0x4fe;
    undefined field228_0x4ff;
    undefined field229_0x500;
    undefined field230_0x501;
    undefined field231_0x502;
    undefined field232_0x503;
    undefined field233_0x504;
    undefined field234_0x505;
    undefined field235_0x506;
    undefined field236_0x507;
    undefined field237_0x508;
    undefined field238_0x509;
    undefined field239_0x50a;
    undefined field240_0x50b;
    undefined field241_0x50c;
    undefined field242_0x50d;
    undefined field243_0x50e;
    undefined field244_0x50f;
    undefined field245_0x510;
    undefined field246_0x511;
    undefined field247_0x512;
    undefined field248_0x513;
    undefined field249_0x514;
    undefined field250_0x515;
    undefined field251_0x516;
    undefined field252_0x517;
    undefined field253_0x518;
    undefined field254_0x519;
    undefined field255_0x51a;
    undefined field256_0x51b;
    undefined field257_0x51c;
    undefined field258_0x51d;
    undefined field259_0x51e;
    undefined field260_0x51f;
    undefined field261_0x520;
    undefined field262_0x521;
    undefined field263_0x522;
    undefined field264_0x523;
    undefined field265_0x524;
    undefined field266_0x525;
    undefined field267_0x526;
    undefined field268_0x527;
    undefined field269_0x528;
    undefined field270_0x529;
    undefined field271_0x52a;
    undefined field272_0x52b;
    undefined field273_0x52c;
    undefined field274_0x52d;
    undefined field275_0x52e;
    undefined field276_0x52f;
    undefined field277_0x530;
    undefined field278_0x531;
    undefined field279_0x532;
    undefined field280_0x533;
    undefined field281_0x534;
    undefined field282_0x535;
    undefined field283_0x536;
    undefined field284_0x537;
    undefined field285_0x538;
    undefined field286_0x539;
    undefined field287_0x53a;
    undefined field288_0x53b;
    undefined field289_0x53c;
    undefined field290_0x53d;
    undefined field291_0x53e;
    undefined field292_0x53f;
    undefined field293_0x540;
    undefined field294_0x541;
    undefined field295_0x542;
    undefined field296_0x543;
    undefined field297_0x544;
    undefined field298_0x545;
    undefined field299_0x546;
    undefined field300_0x547;
    undefined field301_0x548;
    undefined field302_0x549;
    undefined field303_0x54a;
    undefined field304_0x54b;
    undefined field305_0x54c;
    undefined field306_0x54d;
    undefined field307_0x54e;
    undefined field308_0x54f;
    undefined field309_0x550;
    undefined field310_0x551;
    undefined field311_0x552;
    undefined field312_0x553;
    undefined field313_0x554;
    undefined field314_0x555;
    undefined field315_0x556;
    undefined field316_0x557;
    undefined field317_0x558;
    undefined field318_0x559;
    undefined field319_0x55a;
    undefined field320_0x55b;
    undefined field321_0x55c;
    undefined field322_0x55d;
    undefined field323_0x55e;
    undefined field324_0x55f;
    undefined field325_0x560;
    undefined field326_0x561;
    undefined field327_0x562;
    undefined field328_0x563;
    undefined field329_0x564;
    undefined field330_0x565;
    undefined field331_0x566;
    undefined field332_0x567;
    undefined field333_0x568;
    undefined field334_0x569;
    undefined field335_0x56a;
    undefined field336_0x56b;
    undefined field337_0x56c;
    undefined field338_0x56d;
    undefined field339_0x56e;
    undefined field340_0x56f;
    undefined field341_0x570;
    undefined field342_0x571;
    undefined field343_0x572;
    undefined field344_0x573;
    undefined field345_0x574;
    undefined field346_0x575;
    undefined field347_0x576;
    undefined field348_0x577;
    undefined field349_0x578;
    undefined field350_0x579;
    undefined field351_0x57a;
    undefined field352_0x57b;
    undefined field353_0x57c;
    undefined field354_0x57d;
    undefined field355_0x57e;
    undefined field356_0x57f;
    undefined field357_0x580;
    undefined field358_0x581;
    undefined field359_0x582;
    undefined field360_0x583;
    undefined field361_0x584;
    undefined field362_0x585;
    undefined field363_0x586;
    undefined field364_0x587;
    undefined field365_0x588;
    undefined field366_0x589;
    undefined field367_0x58a;
    undefined field368_0x58b;
    undefined field369_0x58c;
    undefined field370_0x58d;
    undefined field371_0x58e;
    undefined field372_0x58f;
    undefined field373_0x590;
    undefined field374_0x591;
    undefined field375_0x592;
    undefined field376_0x593;
    undefined field377_0x594;
    undefined field378_0x595;
    undefined field379_0x596;
    undefined field380_0x597;
    undefined field381_0x598;
    undefined field382_0x599;
    undefined field383_0x59a;
    undefined field384_0x59b;
    undefined field385_0x59c;
    undefined field386_0x59d;
    undefined field387_0x59e;
    undefined field388_0x59f;
    undefined field389_0x5a0;
    undefined field390_0x5a1;
    undefined field391_0x5a2;
    undefined field392_0x5a3;
    undefined field393_0x5a4;
    undefined field394_0x5a5;
    undefined field395_0x5a6;
    undefined field396_0x5a7;
    undefined field397_0x5a8;
    undefined field398_0x5a9;
    undefined field399_0x5aa;
    undefined field400_0x5ab;
    undefined field401_0x5ac;
    undefined field402_0x5ad;
    undefined field403_0x5ae;
    undefined field404_0x5af;
    undefined field405_0x5b0;
    undefined field406_0x5b1;
    undefined field407_0x5b2;
    undefined field408_0x5b3;
    undefined field409_0x5b4;
    undefined field410_0x5b5;
    undefined field411_0x5b6;
    undefined field412_0x5b7;
    undefined field413_0x5b8;
    undefined field414_0x5b9;
    undefined field415_0x5ba;
    undefined field416_0x5bb;
    undefined field417_0x5bc;
    undefined field418_0x5bd;
    undefined field419_0x5be;
    undefined field420_0x5bf;
    undefined field421_0x5c0;
    undefined field422_0x5c1;
    undefined field423_0x5c2;
    undefined field424_0x5c3;
    undefined field425_0x5c4;
    undefined field426_0x5c5;
    undefined field427_0x5c6;
    undefined field428_0x5c7;
    undefined field429_0x5c8;
    undefined field430_0x5c9;
    undefined field431_0x5ca;
    undefined field432_0x5cb;
    undefined field433_0x5cc;
    undefined field434_0x5cd;
    undefined field435_0x5ce;
    undefined field436_0x5cf;
    undefined field437_0x5d0;
    undefined field438_0x5d1;
    undefined field439_0x5d2;
    undefined field440_0x5d3;
    undefined field441_0x5d4;
    undefined field442_0x5d5;
    undefined field443_0x5d6;
    undefined field444_0x5d7;
    undefined field445_0x5d8;
    undefined field446_0x5d9;
    undefined field447_0x5da;
    undefined field448_0x5db;
    undefined field449_0x5dc;
    undefined field450_0x5dd;
    undefined field451_0x5de;
    undefined field452_0x5df;
    undefined field453_0x5e0;
    undefined field454_0x5e1;
    undefined field455_0x5e2;
    undefined field456_0x5e3;
    undefined field457_0x5e4;
    undefined field458_0x5e5;
    undefined field459_0x5e6;
    undefined field460_0x5e7;
    undefined field461_0x5e8;
    undefined field462_0x5e9;
    undefined field463_0x5ea;
    undefined field464_0x5eb;
    undefined field465_0x5ec;
    undefined field466_0x5ed;
    undefined field467_0x5ee;
    undefined field468_0x5ef;
    undefined field469_0x5f0;
    undefined field470_0x5f1;
    undefined field471_0x5f2;
    undefined field472_0x5f3;
    undefined field473_0x5f4;
    undefined field474_0x5f5;
    undefined field475_0x5f6;
    undefined field476_0x5f7;
    undefined field477_0x5f8;
    undefined field478_0x5f9;
    undefined field479_0x5fa;
    undefined field480_0x5fb;
    undefined field481_0x5fc;
    undefined field482_0x5fd;
    undefined field483_0x5fe;
    undefined field484_0x5ff;
    undefined field485_0x600;
    undefined field486_0x601;
    undefined field487_0x602;
    undefined field488_0x603;
    undefined field489_0x604;
    undefined field490_0x605;
    undefined field491_0x606;
    undefined field492_0x607;
    undefined field493_0x608;
    undefined field494_0x609;
    undefined field495_0x60a;
    undefined field496_0x60b;
    undefined field497_0x60c;
    undefined field498_0x60d;
    undefined field499_0x60e;
    undefined field500_0x60f;
    undefined field501_0x610;
    undefined field502_0x611;
    undefined field503_0x612;
    undefined field504_0x613;
    undefined field505_0x614;
    undefined field506_0x615;
    undefined field507_0x616;
    undefined field508_0x617;
    undefined field509_0x618;
    undefined field510_0x619;
    undefined field511_0x61a;
    undefined field512_0x61b;
    undefined field513_0x61c;
    undefined field514_0x61d;
    undefined field515_0x61e;
    undefined field516_0x61f;
    undefined field517_0x620;
    undefined field518_0x621;
    undefined field519_0x622;
    undefined field520_0x623;
    undefined field521_0x624;
    undefined field522_0x625;
    undefined field523_0x626;
    undefined field524_0x627;
    undefined field525_0x628;
    undefined field526_0x629;
    undefined field527_0x62a;
    undefined field528_0x62b;
    undefined field529_0x62c;
    undefined field530_0x62d;
    undefined field531_0x62e;
    undefined field532_0x62f;
    undefined field533_0x630;
    undefined field534_0x631;
    undefined field535_0x632;
    undefined field536_0x633;
    undefined field537_0x634;
    undefined field538_0x635;
    undefined field539_0x636;
    undefined field540_0x637;
    undefined field541_0x638;
    undefined field542_0x639;
    undefined field543_0x63a;
    undefined field544_0x63b;
    undefined field545_0x63c;
    undefined field546_0x63d;
    undefined field547_0x63e;
    undefined field548_0x63f;
    undefined field549_0x640;
    undefined field550_0x641;
    undefined field551_0x642;
    undefined field552_0x643;
    undefined field553_0x644;
    undefined field554_0x645;
    undefined field555_0x646;
    undefined field556_0x647;
    undefined field557_0x648;
    undefined field558_0x649;
    undefined field559_0x64a;
    undefined field560_0x64b;
    undefined field561_0x64c;
    undefined field562_0x64d;
    undefined field563_0x64e;
    undefined field564_0x64f;
    undefined field565_0x650;
    undefined field566_0x651;
    undefined field567_0x652;
    undefined field568_0x653;
    undefined field569_0x654;
    undefined field570_0x655;
    undefined field571_0x656;
    undefined field572_0x657;
    undefined field573_0x658;
    undefined field574_0x659;
    undefined field575_0x65a;
    undefined field576_0x65b;
    undefined field577_0x65c;
    undefined field578_0x65d;
    undefined field579_0x65e;
    undefined field580_0x65f;
    undefined field581_0x660;
    undefined field582_0x661;
    undefined field583_0x662;
    undefined field584_0x663;
    undefined field585_0x664;
    undefined field586_0x665;
    undefined field587_0x666;
    undefined field588_0x667;
    undefined field589_0x668;
    undefined field590_0x669;
    undefined field591_0x66a;
    undefined field592_0x66b;
    undefined field593_0x66c;
    undefined field594_0x66d;
    undefined field595_0x66e;
    undefined field596_0x66f;
    undefined field597_0x670;
    undefined field598_0x671;
    undefined field599_0x672;
    undefined field600_0x673;
    undefined field601_0x674;
    undefined field602_0x675;
    undefined field603_0x676;
    undefined field604_0x677;
    undefined field605_0x678;
    undefined field606_0x679;
    undefined field607_0x67a;
    undefined field608_0x67b;
    undefined field609_0x67c;
    undefined field610_0x67d;
    undefined field611_0x67e;
    undefined field612_0x67f;
    undefined field613_0x680;
    undefined field614_0x681;
    undefined field615_0x682;
    undefined field616_0x683;
    undefined field617_0x684;
    undefined field618_0x685;
    undefined field619_0x686;
    undefined field620_0x687;
    undefined field621_0x688;
    undefined field622_0x689;
    undefined field623_0x68a;
    undefined field624_0x68b;
    undefined field625_0x68c;
    undefined field626_0x68d;
    undefined field627_0x68e;
    undefined field628_0x68f;
    undefined field629_0x690;
    undefined field630_0x691;
    undefined field631_0x692;
    undefined field632_0x693;
    undefined field633_0x694;
    undefined field634_0x695;
    undefined field635_0x696;
    undefined field636_0x697;
    undefined field637_0x698;
    undefined field638_0x699;
    undefined field639_0x69a;
    undefined field640_0x69b;
    undefined field641_0x69c;
    undefined field642_0x69d;
    undefined field643_0x69e;
    undefined field644_0x69f;
    undefined field645_0x6a0;
    undefined field646_0x6a1;
    undefined field647_0x6a2;
    undefined field648_0x6a3;
    undefined field649_0x6a4;
    undefined field650_0x6a5;
    undefined field651_0x6a6;
    undefined field652_0x6a7;
    undefined field653_0x6a8;
    undefined field654_0x6a9;
    undefined field655_0x6aa;
    undefined field656_0x6ab;
    undefined field657_0x6ac;
    undefined field658_0x6ad;
    undefined field659_0x6ae;
    undefined field660_0x6af;
    undefined field661_0x6b0;
    undefined field662_0x6b1;
    undefined field663_0x6b2;
    undefined field664_0x6b3;
    undefined field665_0x6b4;
    undefined field666_0x6b5;
    undefined field667_0x6b6;
    undefined field668_0x6b7;
    undefined field669_0x6b8;
    undefined field670_0x6b9;
    undefined field671_0x6ba;
    undefined field672_0x6bb;
    undefined field673_0x6bc;
    undefined field674_0x6bd;
    undefined field675_0x6be;
    undefined field676_0x6bf;
    undefined field677_0x6c0;
    undefined field678_0x6c1;
    undefined field679_0x6c2;
    undefined field680_0x6c3;
    undefined field681_0x6c4;
    undefined field682_0x6c5;
    undefined field683_0x6c6;
    undefined field684_0x6c7;
    undefined field685_0x6c8;
    undefined field686_0x6c9;
    undefined field687_0x6ca;
    undefined field688_0x6cb;
    undefined field689_0x6cc;
    undefined field690_0x6cd;
    undefined field691_0x6ce;
    undefined field692_0x6cf;
    undefined field693_0x6d0;
    undefined field694_0x6d1;
    undefined field695_0x6d2;
    undefined field696_0x6d3;
    undefined field697_0x6d4;
    undefined field698_0x6d5;
    undefined field699_0x6d6;
    undefined field700_0x6d7;
    undefined field701_0x6d8;
    undefined field702_0x6d9;
    undefined field703_0x6da;
    undefined field704_0x6db;
    undefined field705_0x6dc;
    undefined field706_0x6dd;
    undefined field707_0x6de;
    undefined field708_0x6df;
    undefined field709_0x6e0;
    undefined field710_0x6e1;
    undefined field711_0x6e2;
    undefined field712_0x6e3;
    undefined field713_0x6e4;
    undefined field714_0x6e5;
    undefined field715_0x6e6;
    undefined field716_0x6e7;
    undefined field717_0x6e8;
    undefined field718_0x6e9;
    undefined field719_0x6ea;
    undefined field720_0x6eb;
    undefined field721_0x6ec;
    undefined field722_0x6ed;
    undefined field723_0x6ee;
    undefined field724_0x6ef;
    undefined field725_0x6f0;
    undefined field726_0x6f1;
    undefined field727_0x6f2;
    undefined field728_0x6f3;
    undefined field729_0x6f4;
    undefined field730_0x6f5;
    undefined field731_0x6f6;
    undefined field732_0x6f7;
    undefined field733_0x6f8;
    undefined field734_0x6f9;
    undefined field735_0x6fa;
    undefined field736_0x6fb;
    undefined field737_0x6fc;
    undefined field738_0x6fd;
    undefined field739_0x6fe;
    undefined field740_0x6ff;
    undefined field741_0x700;
    undefined field742_0x701;
    undefined field743_0x702;
    undefined field744_0x703;
    undefined field745_0x704;
    undefined field746_0x705;
    undefined field747_0x706;
    undefined field748_0x707;
    undefined field749_0x708;
    undefined field750_0x709;
    undefined field751_0x70a;
    undefined field752_0x70b;
    undefined field753_0x70c;
    undefined field754_0x70d;
    undefined field755_0x70e;
    undefined field756_0x70f;
    undefined field757_0x710;
    undefined field758_0x711;
    undefined field759_0x712;
    undefined field760_0x713;
    undefined field761_0x714;
    undefined field762_0x715;
    undefined field763_0x716;
    undefined field764_0x717;
    undefined field765_0x718;
    undefined field766_0x719;
    undefined field767_0x71a;
    undefined field768_0x71b;
    undefined field769_0x71c;
    undefined field770_0x71d;
    undefined field771_0x71e;
    undefined field772_0x71f;
    undefined field773_0x720;
    undefined field774_0x721;
    undefined field775_0x722;
    undefined field776_0x723;
    undefined field777_0x724;
    undefined field778_0x725;
    undefined field779_0x726;
    undefined field780_0x727;
    undefined field781_0x728;
    undefined field782_0x729;
    undefined field783_0x72a;
    undefined field784_0x72b;
    undefined field785_0x72c;
    undefined field786_0x72d;
    undefined field787_0x72e;
    undefined field788_0x72f;
    undefined field789_0x730;
    undefined field790_0x731;
    undefined field791_0x732;
    undefined field792_0x733;
    undefined field793_0x734;
    undefined field794_0x735;
    undefined field795_0x736;
    undefined field796_0x737;
    undefined field797_0x738;
    undefined field798_0x739;
    undefined field799_0x73a;
    undefined field800_0x73b;
    undefined field801_0x73c;
    undefined field802_0x73d;
    undefined field803_0x73e;
    undefined field804_0x73f;
    undefined field805_0x740;
    undefined field806_0x741;
    undefined field807_0x742;
    undefined field808_0x743;
    undefined field809_0x744;
    undefined field810_0x745;
    undefined field811_0x746;
    undefined field812_0x747;
    undefined field813_0x748;
    undefined field814_0x749;
    undefined field815_0x74a;
    undefined field816_0x74b;
    undefined field817_0x74c;
    undefined field818_0x74d;
    undefined field819_0x74e;
    undefined field820_0x74f;
    undefined field821_0x750;
    undefined field822_0x751;
    undefined field823_0x752;
    undefined field824_0x753;
    undefined field825_0x754;
    undefined field826_0x755;
    undefined field827_0x756;
    undefined field828_0x757;
    undefined field829_0x758;
    undefined field830_0x759;
    undefined field831_0x75a;
    undefined field832_0x75b;
    undefined field833_0x75c;
    undefined field834_0x75d;
    undefined field835_0x75e;
    undefined field836_0x75f;
    undefined field837_0x760;
    undefined field838_0x761;
    undefined field839_0x762;
    undefined field840_0x763;
    undefined field841_0x764;
    undefined field842_0x765;
    undefined field843_0x766;
    undefined field844_0x767;
    undefined field845_0x768;
    undefined field846_0x769;
    undefined field847_0x76a;
    undefined field848_0x76b;
    undefined field849_0x76c;
    undefined field850_0x76d;
    undefined field851_0x76e;
    undefined field852_0x76f;
    undefined field853_0x770;
    undefined field854_0x771;
    undefined field855_0x772;
    undefined field856_0x773;
    undefined field857_0x774;
    undefined field858_0x775;
    undefined field859_0x776;
    undefined field860_0x777;
    undefined field861_0x778;
    undefined field862_0x779;
    undefined field863_0x77a;
    undefined field864_0x77b;
    undefined field865_0x77c;
    undefined field866_0x77d;
    undefined field867_0x77e;
    undefined field868_0x77f;
    undefined field869_0x780;
    undefined field870_0x781;
    undefined field871_0x782;
    undefined field872_0x783;
    undefined field873_0x784;
    undefined field874_0x785;
    undefined field875_0x786;
    undefined field876_0x787;
    undefined field877_0x788;
    undefined field878_0x789;
    undefined field879_0x78a;
    undefined field880_0x78b;
    undefined field881_0x78c;
    undefined field882_0x78d;
    undefined field883_0x78e;
    undefined field884_0x78f;
    undefined field885_0x790;
    undefined field886_0x791;
    undefined field887_0x792;
    undefined field888_0x793;
    undefined field889_0x794;
    undefined field890_0x795;
    undefined field891_0x796;
    undefined field892_0x797;
    undefined field893_0x798;
    undefined field894_0x799;
    undefined field895_0x79a;
    undefined field896_0x79b;
    undefined field897_0x79c;
    undefined field898_0x79d;
    undefined field899_0x79e;
    undefined field900_0x79f;
    undefined field901_0x7a0;
    undefined field902_0x7a1;
    undefined field903_0x7a2;
    undefined field904_0x7a3;
    undefined field905_0x7a4;
    undefined field906_0x7a5;
    undefined field907_0x7a6;
    undefined field908_0x7a7;
    undefined field909_0x7a8;
    undefined field910_0x7a9;
    undefined field911_0x7aa;
    undefined field912_0x7ab;
    undefined field913_0x7ac;
    undefined field914_0x7ad;
    undefined field915_0x7ae;
    undefined field916_0x7af;
    undefined field917_0x7b0;
    undefined field918_0x7b1;
    undefined field919_0x7b2;
    undefined field920_0x7b3;
    undefined field921_0x7b4;
    undefined field922_0x7b5;
    undefined field923_0x7b6;
    undefined field924_0x7b7;
    undefined field925_0x7b8;
    undefined field926_0x7b9;
    undefined field927_0x7ba;
    undefined field928_0x7bb;
    undefined field929_0x7bc;
    undefined field930_0x7bd;
    undefined field931_0x7be;
    undefined field932_0x7bf;
    undefined field933_0x7c0;
    undefined field934_0x7c1;
    undefined field935_0x7c2;
    undefined field936_0x7c3;
    undefined field937_0x7c4;
    undefined field938_0x7c5;
    undefined field939_0x7c6;
    undefined field940_0x7c7;
    undefined field941_0x7c8;
    undefined field942_0x7c9;
    undefined field943_0x7ca;
    undefined field944_0x7cb;
    undefined field945_0x7cc;
    undefined field946_0x7cd;
    undefined field947_0x7ce;
    undefined field948_0x7cf;
    undefined field949_0x7d0;
    undefined field950_0x7d1;
    undefined field951_0x7d2;
    undefined field952_0x7d3;
    undefined field953_0x7d4;
    undefined field954_0x7d5;
    undefined field955_0x7d6;
    undefined field956_0x7d7;
    undefined field957_0x7d8;
    undefined field958_0x7d9;
    undefined field959_0x7da;
    undefined field960_0x7db;
    undefined field961_0x7dc;
    undefined field962_0x7dd;
    undefined field963_0x7de;
    undefined field964_0x7df;
    undefined field965_0x7e0;
    undefined field966_0x7e1;
    undefined field967_0x7e2;
    undefined field968_0x7e3;
    undefined field969_0x7e4;
    undefined field970_0x7e5;
    undefined field971_0x7e6;
    undefined field972_0x7e7;
    undefined field973_0x7e8;
    undefined field974_0x7e9;
    undefined field975_0x7ea;
    undefined field976_0x7eb;
    undefined field977_0x7ec;
    undefined field978_0x7ed;
    undefined field979_0x7ee;
    undefined field980_0x7ef;
    undefined field981_0x7f0;
    undefined field982_0x7f1;
    undefined field983_0x7f2;
    undefined field984_0x7f3;
    undefined field985_0x7f4;
    undefined field986_0x7f5;
    undefined field987_0x7f6;
    undefined field988_0x7f7;
    undefined field989_0x7f8;
    undefined field990_0x7f9;
    undefined field991_0x7fa;
    undefined field992_0x7fb;
    undefined field993_0x7fc;
    undefined field994_0x7fd;
    undefined field995_0x7fe;
    undefined field996_0x7ff;
    undefined field997_0x800;
    undefined field998_0x801;
    undefined field999_0x802;
    undefined field1000_0x803;
    undefined field1001_0x804;
    undefined field1002_0x805;
    undefined field1003_0x806;
    undefined field1004_0x807;
    undefined field1005_0x808;
    undefined field1006_0x809;
    undefined field1007_0x80a;
    undefined field1008_0x80b;
    undefined field1009_0x80c;
    undefined field1010_0x80d;
    undefined field1011_0x80e;
    undefined field1012_0x80f;
    undefined field1013_0x810;
    undefined field1014_0x811;
    undefined field1015_0x812;
    undefined field1016_0x813;
    undefined field1017_0x814;
    undefined field1018_0x815;
    undefined field1019_0x816;
    undefined field1020_0x817;
    undefined field1021_0x818;
    undefined field1022_0x819;
    undefined field1023_0x81a;
    undefined field1024_0x81b;
    undefined field1025_0x81c;
    undefined field1026_0x81d;
    undefined field1027_0x81e;
    undefined field1028_0x81f;
    undefined field1029_0x820;
    undefined field1030_0x821;
    undefined field1031_0x822;
    undefined field1032_0x823;
    undefined field1033_0x824;
    undefined field1034_0x825;
    undefined field1035_0x826;
    undefined field1036_0x827;
    undefined field1037_0x828;
    undefined field1038_0x829;
    undefined field1039_0x82a;
    undefined field1040_0x82b;
    undefined field1041_0x82c;
    undefined field1042_0x82d;
    undefined field1043_0x82e;
    undefined field1044_0x82f;
    undefined field1045_0x830;
    undefined field1046_0x831;
    undefined field1047_0x832;
    undefined field1048_0x833;
    undefined field1049_0x834;
    undefined field1050_0x835;
    undefined field1051_0x836;
    undefined field1052_0x837;
    undefined field1053_0x838;
    undefined field1054_0x839;
    undefined field1055_0x83a;
    undefined field1056_0x83b;
    undefined field1057_0x83c;
    undefined field1058_0x83d;
    undefined field1059_0x83e;
    undefined field1060_0x83f;
    undefined field1061_0x840;
    undefined field1062_0x841;
    undefined field1063_0x842;
    undefined field1064_0x843;
    undefined field1065_0x844;
    undefined field1066_0x845;
    undefined field1067_0x846;
    undefined field1068_0x847;
    undefined field1069_0x848;
    undefined field1070_0x849;
    undefined field1071_0x84a;
    undefined field1072_0x84b;
    undefined field1073_0x84c;
    undefined field1074_0x84d;
    undefined field1075_0x84e;
    undefined field1076_0x84f;
    undefined field1077_0x850;
    undefined field1078_0x851;
    undefined field1079_0x852;
    undefined field1080_0x853;
    undefined field1081_0x854;
};

typedef struct PlayerParams PlayerParams, *PPlayerParams;

struct PlayerParams {
    undefined4 field0_0x0;
    undefined field1_0x4;
    undefined field2_0x5;
    undefined field3_0x6;
    undefined field4_0x7;
    undefined8 field5_0x8;
    undefined field6_0x10;
    undefined field7_0x11;
    undefined field8_0x12;
    undefined field9_0x13;
    undefined field10_0x14;
    undefined field11_0x15;
    undefined field12_0x16;
    undefined field13_0x17;
    undefined field14_0x18;
    undefined field15_0x19;
    undefined field16_0x1a;
    undefined field17_0x1b;
    undefined field18_0x1c;
    undefined field19_0x1d;
    undefined field20_0x1e;
    undefined field21_0x1f;
    undefined field22_0x20;
    undefined field23_0x21;
    undefined field24_0x22;
    undefined field25_0x23;
    undefined field26_0x24;
    undefined field27_0x25;
    undefined field28_0x26;
    undefined field29_0x27;
    undefined field30_0x28;
    undefined field31_0x29;
    undefined field32_0x2a;
    undefined field33_0x2b;
    undefined field34_0x2c;
    undefined field35_0x2d;
    undefined field36_0x2e;
    undefined field37_0x2f;
    int field38_0x30;
    int field39_0x34;
    undefined field40_0x38;
    undefined field41_0x39;
    undefined field42_0x3a;
    undefined field43_0x3b;
    undefined field44_0x3c;
    undefined field45_0x3d;
    undefined field46_0x3e;
    undefined field47_0x3f;
    undefined field48_0x40;
    undefined field49_0x41;
    undefined field50_0x42;
    undefined field51_0x43;
    undefined field52_0x44;
    undefined field53_0x45;
    undefined field54_0x46;
    undefined field55_0x47;
    undefined field56_0x48;
    undefined field57_0x49;
    undefined field58_0x4a;
    undefined field59_0x4b;
    int field60_0x4c;
    int field61_0x50;
};

typedef struct nciCodecInfo_W nciCodecInfo_W, *PnciCodecInfo_W;

struct nciCodecInfo_W {
    undefined2 field0_0x0;
    char codec_version_S[12];
    undefined field2_0xe;
    undefined field3_0xf;
    undefined field4_0x10;
    undefined field5_0x11;
    undefined field6_0x12;
    undefined field7_0x13;
    undefined field8_0x14;
    undefined field9_0x15;
    undefined field10_0x16;
    undefined field11_0x17;
    undefined field12_0x18;
    undefined field13_0x19;
    undefined field14_0x1a;
    undefined field15_0x1b;
    undefined field16_0x1c;
    undefined field17_0x1d;
    undefined field18_0x1e;
    undefined field19_0x1f;
    undefined field20_0x20;
    undefined field21_0x21;
    undefined field22_0x22;
    undefined field23_0x23;
    undefined field24_0x24;
    undefined field25_0x25;
    undefined field26_0x26;
    undefined field27_0x27;
    undefined8 field28_0x28;
    undefined8 field29_0x30;
    undefined2 sampling_rate_S;
    undefined2 bits_per_sample_S;
    undefined2 samples_per_frame_S;
    undefined2 field33_0x3e_set_to_1;
    undefined2 field34_0x40_set_to_1_too;
    undefined field35_0x42;
    undefined field36_0x43;
    undefined field37_0x44;
    undefined field38_0x45;
    undefined field39_0x46;
    undefined field40_0x47;
    undefined8 bit_rate_S;
    undefined8 min_packet_bits_S;
    undefined8 avg_packet_bits_S;
    undefined8 max_packet_bits_S;
    short field45_0x68_ceilf_of_0.90625_without_some_delta;
    short field46_0x6a_in_relation_to_samples_per_frame;
};

typedef struct UnreliableDataType4_W UnreliableDataType4_W, *PUnreliableDataType4_W;

struct UnreliableDataType4_W {
    undefined4 *field0_0x0;
    undefined4 field1_0x4;
    undefined4 *field2_0x8;
    undefined4 field3_0xc;
    uint field4_0x10;
    undefined4 field5_0x14;
};

typedef struct MpegStream MpegStream, *PMpegStream;

struct MpegStream {
    undefined field0_0x0;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    undefined field4_0x4;
    undefined field5_0x5;
    undefined field6_0x6;
    undefined field7_0x7;
    undefined4 field8_0x8;
    undefined field9_0xc;
    undefined field10_0xd;
    undefined field11_0xe;
    undefined field12_0xf;
    undefined field13_0x10;
    undefined field14_0x11;
    undefined field15_0x12;
    undefined field16_0x13;
    undefined field17_0x14;
    undefined field18_0x15;
    undefined field19_0x16;
    undefined field20_0x17;
    undefined field21_0x18;
    undefined field22_0x19;
    undefined field23_0x1a;
    undefined field24_0x1b;
    undefined field25_0x1c;
    undefined field26_0x1d;
    undefined field27_0x1e;
    undefined field28_0x1f;
    undefined field29_0x20;
    undefined field30_0x21;
    undefined field31_0x22;
    undefined field32_0x23;
    undefined field33_0x24;
    undefined field34_0x25;
    undefined field35_0x26;
    undefined field36_0x27;
    undefined field37_0x28;
    undefined field38_0x29;
    undefined field39_0x2a;
    undefined field40_0x2b;
    undefined field41_0x2c;
    undefined field42_0x2d;
    undefined field43_0x2e;
    undefined field44_0x2f;
    undefined field45_0x30;
    undefined field46_0x31;
    undefined field47_0x32;
    undefined field48_0x33;
    undefined field49_0x34;
    undefined field50_0x35;
    undefined field51_0x36;
    undefined field52_0x37;
    undefined field53_0x38;
    undefined field54_0x39;
    undefined field55_0x3a;
    undefined field56_0x3b;
    undefined field57_0x3c;
    undefined field58_0x3d;
    undefined field59_0x3e;
    undefined field60_0x3f;
    undefined4 *field61_0x40;
    undefined field62_0x44;
    undefined field63_0x45;
    undefined field64_0x46;
    undefined field65_0x47;
    uint field66_0x48;
    undefined4 field67_0x4c;
    undefined4 field68_0x50;
    undefined4 field69_0x54;
    uint field70_0x58;
    uint field71_0x5c;
    undefined4 field72_0x60;
    undefined *field73_0x64;
    int field74_0x68;
    undefined4 field75_0x6c;
    undefined field76_0x70;
    undefined field77_0x71;
    undefined field78_0x72;
    undefined field79_0x73;
    undefined field80_0x74;
    undefined field81_0x75;
    undefined field82_0x76;
    undefined field83_0x77;
    undefined field84_0x78;
    undefined field85_0x79;
    undefined field86_0x7a;
    undefined field87_0x7b;
    undefined field88_0x7c;
    undefined field89_0x7d;
    undefined field90_0x7e;
    undefined field91_0x7f;
    undefined field92_0x80;
    undefined field93_0x81;
    undefined field94_0x82;
    undefined field95_0x83;
    undefined field96_0x84;
    undefined field97_0x85;
    undefined field98_0x86;
    undefined field99_0x87;
    undefined field100_0x88;
    undefined field101_0x89;
    undefined field102_0x8a;
    undefined field103_0x8b;
    undefined field104_0x8c;
    undefined field105_0x8d;
    undefined field106_0x8e;
    undefined field107_0x8f;
    undefined field108_0x90;
    undefined field109_0x91;
    undefined field110_0x92;
    undefined field111_0x93;
    struct DmaTag *field112_0x94;
    undefined field113_0x98;
    undefined field114_0x99;
    undefined field115_0x9a;
    undefined field116_0x9b;
    undefined field117_0x9c;
    undefined field118_0x9d;
    undefined field119_0x9e;
    undefined field120_0x9f;
    void *field121_0xa0;
    undefined field122_0xa4;
    undefined field123_0xa5;
    undefined field124_0xa6;
    undefined field125_0xa7;
    undefined field126_0xa8;
    undefined field127_0xa9;
    undefined field128_0xaa;
    undefined field129_0xab;
    uint field130_0xac;
    uint field131_0xb0;
    undefined4 field132_0xb4;
    int field133_0xb8;
    int field134_0xbc;
    int field135_0xc0;
    uint field136_0xc4;
    int field137_0xc8;
    undefined4 field138_0xcc;
};

typedef struct ezNetConfigData_W ezNetConfigData_W, *PezNetConfigData_W;

struct ezNetConfigData_W {
    char attach_ifc_S[256];
    char attach_dev_S[256];
    char dhcp_host_name_S[256];
    char address_S[256];
    char netmask_S[256];
    char gateway_S[256];
    char dns1_address_S[256];
    char dns2_address_S[256];
    char phone_numbers1_S[256];
    char phone_numbers2_S[256];
    char phone_numbers3_S[256];
    char auth_name_S[256];
    char auth_key_S[256];
    char peer_name_S[256];
    char vendor_S[256];
    char product_S[256];
    char chat_additional_S[256];
    char outside_number_S[256];
    char outside_delay_S[256];
    int ifc_type_S;
    int mtu_S;
    int ifc_idle_timeout_S;
    int dev_type_S;
    int phy_config_S;
    int dialing_type_S;
    int dev_idle_timeout;
    undefined4 field26_0x131c;
    byte dhcp_S;
    byte dns1_nego_S;
    byte dns2_nego_S;
    byte f_auth_S;
    byte auth_S;
    byte pppoe_S;
    byte prc_nego_S;
    byte acc_nego_S;
    byte accm_nego_S;
};

typedef struct UnreliableLargeData_W UnreliableLargeData_W, *PUnreliableLargeData_W;

struct UnreliableLargeData_W {
    undefined field0_0x0;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    undefined field4_0x4;
    undefined field5_0x5;
    undefined field6_0x6;
    undefined field7_0x7;
    undefined field8_0x8;
    undefined field9_0x9;
    undefined field10_0xa;
    undefined field11_0xb;
    undefined field12_0xc;
    undefined field13_0xd;
    undefined field14_0xe;
    undefined field15_0xf;
    undefined field16_0x10;
    undefined field17_0x11;
    undefined field18_0x12;
    undefined field19_0x13;
    char name[28]; // Created by retype action
    ushort field21_0x30;
    undefined field22_0x32;
    undefined field23_0x33;
    undefined field24_0x34;
    undefined field25_0x35;
    undefined field26_0x36;
    undefined field27_0x37;
    undefined field28_0x38;
    undefined field29_0x39;
    undefined field30_0x3a;
    undefined field31_0x3b;
    undefined field32_0x3c;
    undefined field33_0x3d;
    undefined field34_0x3e;
    undefined field35_0x3f;
    undefined field36_0x40;
    undefined field37_0x41;
    undefined field38_0x42;
    undefined field39_0x43;
    undefined field40_0x44;
    undefined field41_0x45;
    undefined field42_0x46;
    undefined field43_0x47;
    undefined field44_0x48;
    undefined field45_0x49;
    undefined field46_0x4a;
    undefined field47_0x4b;
    undefined field48_0x4c;
    undefined field49_0x4d;
    undefined field50_0x4e;
    undefined field51_0x4f;
    undefined field52_0x50;
    undefined field53_0x51;
    undefined field54_0x52;
    undefined field55_0x53;
    undefined field56_0x54;
    undefined field57_0x55;
    undefined field58_0x56;
    undefined field59_0x57;
    undefined field60_0x58;
    undefined field61_0x59;
    undefined field62_0x5a;
    undefined field63_0x5b;
    undefined field64_0x5c;
    undefined field65_0x5d;
    undefined field66_0x5e;
    undefined field67_0x5f;
    long field68_0x60;
    undefined field69_0x68;
    undefined field70_0x69;
    undefined field71_0x6a;
    undefined field72_0x6b;
    undefined field73_0x6c;
    undefined field74_0x6d;
    undefined field75_0x6e;
    undefined field76_0x6f;
    long field77_0x70;
    undefined field78_0x78;
    undefined field79_0x79;
    undefined field80_0x7a;
    undefined field81_0x7b;
    undefined field82_0x7c;
    undefined field83_0x7d;
    undefined field84_0x7e;
    undefined field85_0x7f;
    long field86_0x80;
    long field87_0x88;
    undefined field88_0x90;
    undefined field89_0x91;
    undefined field90_0x92;
    undefined field91_0x93;
    undefined field92_0x94;
    undefined field93_0x95;
    undefined field94_0x96;
    undefined field95_0x97;
    undefined field96_0x98;
    undefined field97_0x99;
    undefined field98_0x9a;
    undefined field99_0x9b;
    undefined field100_0x9c;
    undefined field101_0x9d;
    undefined field102_0x9e;
    undefined field103_0x9f;
    undefined field104_0xa0;
    undefined field105_0xa1;
    undefined field106_0xa2;
    undefined field107_0xa3;
    undefined field108_0xa4;
    undefined field109_0xa5;
    undefined field110_0xa6;
    undefined field111_0xa7;
    undefined field112_0xa8;
    undefined field113_0xa9;
    undefined field114_0xaa;
    undefined field115_0xab;
    undefined field116_0xac;
    undefined field117_0xad;
    undefined field118_0xae;
    undefined field119_0xaf;
    undefined field120_0xb0;
    undefined field121_0xb1;
    undefined field122_0xb2;
    undefined field123_0xb3;
    undefined field124_0xb4;
    undefined field125_0xb5;
    undefined field126_0xb6;
    undefined field127_0xb7;
    undefined field128_0xb8;
    undefined field129_0xb9;
    undefined field130_0xba;
    undefined field131_0xbb;
    undefined field132_0xbc;
    undefined field133_0xbd;
    undefined field134_0xbe;
    undefined field135_0xbf;
    undefined field136_0xc0;
    undefined field137_0xc1;
    undefined field138_0xc2;
    undefined field139_0xc3;
    undefined field140_0xc4;
    undefined field141_0xc5;
    undefined field142_0xc6;
    undefined field143_0xc7;
    undefined field144_0xc8;
    undefined field145_0xc9;
    undefined field146_0xca;
    undefined field147_0xcb;
    undefined field148_0xcc;
    undefined field149_0xcd;
    undefined field150_0xce;
    undefined field151_0xcf;
    undefined field152_0xd0;
    undefined field153_0xd1;
    undefined field154_0xd2;
    undefined field155_0xd3;
    undefined field156_0xd4;
    undefined field157_0xd5;
    undefined field158_0xd6;
    undefined field159_0xd7;
    undefined field160_0xd8;
    undefined field161_0xd9;
    undefined field162_0xda;
    undefined field163_0xdb;
    undefined field164_0xdc;
    undefined field165_0xdd;
    undefined field166_0xde;
    undefined field167_0xdf;
    undefined field168_0xe0;
    undefined field169_0xe1;
    undefined field170_0xe2;
    undefined field171_0xe3;
    undefined field172_0xe4;
    undefined field173_0xe5;
    undefined field174_0xe6;
    undefined field175_0xe7;
    undefined field176_0xe8;
    undefined field177_0xe9;
    undefined field178_0xea;
    undefined field179_0xeb;
    int field180_0xec;
    undefined field181_0xf0;
    undefined field182_0xf1;
    undefined field183_0xf2;
    undefined field184_0xf3;
    undefined field185_0xf4;
    undefined field186_0xf5;
    undefined field187_0xf6;
    undefined field188_0xf7;
    undefined field189_0xf8;
    undefined field190_0xf9;
    undefined field191_0xfa;
    undefined field192_0xfb;
    undefined field193_0xfc;
    undefined field194_0xfd;
    undefined field195_0xfe;
    undefined field196_0xff;
    undefined field197_0x100;
    undefined field198_0x101;
    undefined field199_0x102;
    undefined field200_0x103;
    undefined field201_0x104;
    undefined field202_0x105;
    undefined field203_0x106;
    undefined field204_0x107;
    undefined field205_0x108;
    undefined field206_0x109;
    undefined field207_0x10a;
    undefined field208_0x10b;
    undefined field209_0x10c;
    undefined field210_0x10d;
    undefined field211_0x10e;
    undefined field212_0x10f;
    int field213_0x110;
    struct UnreliablePacket_W *field214_0x114;
    struct UnreliablePacket_W *field215_0x118;
    int field216_0x11c;
    int field217_0x120;
    undefined field218_0x124;
    undefined field219_0x125;
    undefined field220_0x126;
    undefined field221_0x127;
    struct UnreliableLargeData_W *other_random_data;
    uint someFlagsAgain_W;
    undefined field224_0x130;
    undefined field225_0x131;
    undefined field226_0x132;
    undefined field227_0x133;
    ushort field228_0x134;
    undefined field229_0x136;
    undefined field230_0x137;
    uint field231_0x138;
    undefined field232_0x13c;
    undefined field233_0x13d;
    undefined field234_0x13e;
    undefined field235_0x13f;
    undefined field236_0x140;
    undefined field237_0x141;
    undefined field238_0x142;
    undefined field239_0x143;
    undefined field240_0x144;
    undefined field241_0x145;
    undefined field242_0x146;
    undefined field243_0x147;
    undefined field244_0x148;
    undefined field245_0x149;
    undefined field246_0x14a;
    undefined field247_0x14b;
    undefined field248_0x14c;
    undefined field249_0x14d;
    undefined field250_0x14e;
    undefined field251_0x14f;
    undefined field252_0x150;
    undefined field253_0x151;
    undefined field254_0x152;
    undefined field255_0x153;
    undefined field256_0x154;
    undefined field257_0x155;
    undefined field258_0x156;
    undefined field259_0x157;
    undefined field260_0x158;
    undefined field261_0x159;
    undefined field262_0x15a;
    undefined field263_0x15b;
    undefined field264_0x15c;
    undefined field265_0x15d;
    undefined field266_0x15e;
    undefined field267_0x15f;
    uint field268_0x160;
    undefined1 flagsToState_W; // Created by retype action
    undefined field270_0x165;
    undefined field271_0x166;
    undefined field272_0x167;
    undefined field273_0x168;
    undefined field274_0x169;
    undefined field275_0x16a;
    undefined field276_0x16b;
    undefined field277_0x16c;
    undefined field278_0x16d;
    undefined field279_0x16e;
    undefined field280_0x16f;
    undefined1 stateId_W_2; // Created by retype action
    undefined field282_0x171;
    undefined field283_0x172;
    undefined field284_0x173;
    undefined1 stateId_W; // Created by retype action
    undefined field286_0x175;
    undefined field287_0x176;
    undefined field288_0x177;
    undefined field289_0x178;
    undefined field290_0x179;
    undefined field291_0x17a;
    undefined field292_0x17b;
    undefined field293_0x17c;
    undefined field294_0x17d;
    undefined field295_0x17e;
    undefined field296_0x17f;
    undefined field297_0x180;
    undefined field298_0x181;
    undefined field299_0x182;
    undefined field300_0x183;
    undefined field301_0x184;
    undefined field302_0x185;
    undefined field303_0x186;
    undefined field304_0x187;
    undefined field305_0x188;
    undefined field306_0x189;
    undefined field307_0x18a;
    undefined field308_0x18b;
    int rst_counter_S_2; // Created by retype action
    int rst_counter_S; // Created by retype action
    undefined field311_0x194;
    undefined field312_0x195;
    undefined field313_0x196;
    undefined field314_0x197;
    undefined field315_0x198;
    undefined field316_0x199;
    undefined field317_0x19a;
    undefined field318_0x19b;
    undefined field319_0x19c;
    undefined field320_0x19d;
    undefined field321_0x19e;
    undefined field322_0x19f;
    undefined field323_0x1a0;
    undefined field324_0x1a1;
    undefined field325_0x1a2;
    undefined field326_0x1a3;
    undefined field327_0x1a4;
    undefined field328_0x1a5;
    undefined field329_0x1a6;
    undefined field330_0x1a7;
    undefined field331_0x1a8;
    undefined field332_0x1a9;
    undefined field333_0x1aa;
    undefined field334_0x1ab;
    undefined field335_0x1ac;
    undefined field336_0x1ad;
    undefined field337_0x1ae;
    undefined field338_0x1af;
    undefined field339_0x1b0;
    undefined field340_0x1b1;
    undefined field341_0x1b2;
    undefined field342_0x1b3;
    undefined field343_0x1b4;
    undefined field344_0x1b5;
    undefined field345_0x1b6;
    undefined field346_0x1b7;
    undefined field347_0x1b8;
    undefined field348_0x1b9;
    undefined field349_0x1ba;
    undefined field350_0x1bb;
    undefined field351_0x1bc;
    undefined field352_0x1bd;
    undefined field353_0x1be;
    undefined field354_0x1bf;
    undefined field355_0x1c0;
    undefined field356_0x1c1;
    undefined field357_0x1c2;
    undefined field358_0x1c3;
    undefined field359_0x1c4;
    undefined field360_0x1c5;
    undefined field361_0x1c6;
    undefined field362_0x1c7;
    undefined field363_0x1c8;
    undefined field364_0x1c9;
    undefined field365_0x1ca;
    undefined field366_0x1cb;
    undefined field367_0x1cc;
    undefined field368_0x1cd;
    undefined field369_0x1ce;
    undefined field370_0x1cf;
    undefined field371_0x1d0;
    undefined field372_0x1d1;
    undefined field373_0x1d2;
    undefined field374_0x1d3;
    undefined field375_0x1d4;
    undefined field376_0x1d5;
    undefined field377_0x1d6;
    undefined field378_0x1d7;
    undefined field379_0x1d8;
    undefined field380_0x1d9;
    undefined field381_0x1da;
    undefined field382_0x1db;
    undefined field383_0x1dc;
    undefined field384_0x1dd;
    undefined field385_0x1de;
    undefined field386_0x1df;
    undefined field387_0x1e0;
    undefined field388_0x1e1;
    undefined field389_0x1e2;
    undefined field390_0x1e3;
    undefined field391_0x1e4;
    undefined field392_0x1e5;
    undefined field393_0x1e6;
    undefined field394_0x1e7;
    undefined field395_0x1e8;
    undefined field396_0x1e9;
    undefined field397_0x1ea;
    undefined field398_0x1eb;
    undefined field399_0x1ec;
    undefined field400_0x1ed;
    undefined field401_0x1ee;
    undefined field402_0x1ef;
    undefined field403_0x1f0;
    undefined field404_0x1f1;
    undefined field405_0x1f2;
    undefined field406_0x1f3;
    undefined field407_0x1f4;
    undefined field408_0x1f5;
    undefined field409_0x1f6;
    undefined field410_0x1f7;
    undefined field411_0x1f8;
    undefined field412_0x1f9;
    undefined field413_0x1fa;
    undefined field414_0x1fb;
    undefined field415_0x1fc;
    undefined field416_0x1fd;
    undefined field417_0x1fe;
    undefined field418_0x1ff;
    undefined field419_0x200;
    undefined field420_0x201;
    undefined field421_0x202;
    undefined field422_0x203;
    undefined field423_0x204;
    undefined field424_0x205;
    undefined field425_0x206;
    undefined field426_0x207;
    undefined field427_0x208;
    undefined field428_0x209;
    undefined field429_0x20a;
    undefined field430_0x20b;
    undefined field431_0x20c;
    undefined field432_0x20d;
    undefined field433_0x20e;
    undefined field434_0x20f;
    undefined field435_0x210;
    undefined field436_0x211;
    undefined field437_0x212;
    undefined field438_0x213;
    undefined field439_0x214;
    undefined field440_0x215;
    undefined field441_0x216;
    undefined field442_0x217;
    undefined field443_0x218;
    undefined field444_0x219;
    undefined field445_0x21a;
    undefined field446_0x21b;
    undefined field447_0x21c;
    undefined field448_0x21d;
    undefined field449_0x21e;
    undefined field450_0x21f;
    undefined field451_0x220;
    undefined field452_0x221;
    undefined field453_0x222;
    undefined field454_0x223;
    undefined field455_0x224;
    undefined field456_0x225;
    undefined field457_0x226;
    undefined field458_0x227;
    undefined field459_0x228;
    undefined field460_0x229;
    undefined field461_0x22a;
    undefined field462_0x22b;
    undefined field463_0x22c;
    undefined field464_0x22d;
    undefined field465_0x22e;
    undefined field466_0x22f;
    undefined field467_0x230;
    undefined field468_0x231;
    undefined field469_0x232;
    undefined field470_0x233;
    undefined field471_0x234;
    undefined field472_0x235;
    undefined field473_0x236;
    undefined field474_0x237;
    undefined field475_0x238;
    undefined field476_0x239;
    undefined field477_0x23a;
    undefined field478_0x23b;
    undefined field479_0x23c;
    undefined field480_0x23d;
    undefined field481_0x23e;
    undefined field482_0x23f;
    undefined field483_0x240;
    undefined field484_0x241;
    undefined field485_0x242;
    undefined field486_0x243;
    undefined field487_0x244;
    undefined field488_0x245;
    undefined field489_0x246;
    undefined field490_0x247;
    undefined field491_0x248;
    undefined field492_0x249;
    undefined field493_0x24a;
    undefined field494_0x24b;
    undefined field495_0x24c;
    undefined field496_0x24d;
    undefined field497_0x24e;
    undefined field498_0x24f;
    undefined field499_0x250;
    undefined field500_0x251;
    undefined field501_0x252;
    undefined field502_0x253;
    undefined field503_0x254;
    undefined field504_0x255;
    undefined field505_0x256;
    undefined field506_0x257;
    undefined field507_0x258;
    undefined field508_0x259;
    undefined field509_0x25a;
    undefined field510_0x25b;
    undefined field511_0x25c;
    undefined field512_0x25d;
    undefined field513_0x25e;
    undefined field514_0x25f;
    undefined field515_0x260;
    undefined field516_0x261;
    undefined field517_0x262;
    undefined field518_0x263;
    undefined field519_0x264;
    undefined field520_0x265;
    undefined field521_0x266;
    undefined field522_0x267;
    undefined field523_0x268;
    undefined field524_0x269;
    undefined field525_0x26a;
    undefined field526_0x26b;
    undefined field527_0x26c;
    undefined field528_0x26d;
    undefined field529_0x26e;
    undefined field530_0x26f;
    undefined field531_0x270;
    undefined field532_0x271;
    undefined field533_0x272;
    undefined field534_0x273;
    undefined4 field535_0x274;
    undefined field536_0x278;
    undefined field537_0x279;
    undefined field538_0x27a;
    undefined field539_0x27b;
    undefined field540_0x27c;
    undefined field541_0x27d;
    undefined field542_0x27e;
    undefined field543_0x27f;
    undefined field544_0x280;
    undefined field545_0x281;
    undefined field546_0x282;
    undefined field547_0x283;
    undefined field548_0x284;
    undefined field549_0x285;
    undefined field550_0x286;
    undefined field551_0x287;
    undefined field552_0x288;
    undefined field553_0x289;
    undefined field554_0x28a;
    undefined field555_0x28b;
    undefined field556_0x28c;
    undefined field557_0x28d;
    undefined field558_0x28e;
    undefined field559_0x28f;
    undefined field560_0x290;
    undefined field561_0x291;
    undefined field562_0x292;
    undefined field563_0x293;
    undefined field564_0x294;
    undefined field565_0x295;
    undefined field566_0x296;
    undefined field567_0x297;
    undefined field568_0x298;
    undefined field569_0x299;
    undefined field570_0x29a;
    undefined field571_0x29b;
    uint field572_0x29c;
    char field573_0x2a0;
    undefined field574_0x2a1;
    undefined field575_0x2a2;
    undefined field576_0x2a3;
    int field577_0x2a4;
    undefined field578_0x2a8;
    undefined field579_0x2a9;
    undefined field580_0x2aa;
    undefined field581_0x2ab;
    undefined field582_0x2ac;
    undefined field583_0x2ad;
    undefined field584_0x2ae;
    undefined field585_0x2af;
    undefined field586_0x2b0;
    undefined field587_0x2b1;
    undefined field588_0x2b2;
    undefined field589_0x2b3;
    undefined field590_0x2b4;
    undefined field591_0x2b5;
    undefined field592_0x2b6;
    undefined field593_0x2b7;
    undefined field594_0x2b8;
    undefined field595_0x2b9;
    undefined field596_0x2ba;
    undefined field597_0x2bb;
    undefined field598_0x2bc;
    undefined field599_0x2bd;
    undefined field600_0x2be;
    undefined field601_0x2bf;
    undefined field602_0x2c0;
    undefined field603_0x2c1;
    undefined field604_0x2c2;
    undefined field605_0x2c3;
    undefined field606_0x2c4;
    undefined field607_0x2c5;
    undefined field608_0x2c6;
    undefined field609_0x2c7;
    undefined field610_0x2c8;
    undefined field611_0x2c9;
    undefined field612_0x2ca;
    undefined field613_0x2cb;
    undefined field614_0x2cc;
    undefined field615_0x2cd;
    undefined field616_0x2ce;
    undefined field617_0x2cf;
    int field618_0x2d0;
};

typedef struct rpcPacketData_W rpcPacketData_W, *PrpcPacketData_W;

struct rpcPacketData_W {
    undefined field0_0x0;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    undefined field4_0x4;
    undefined field5_0x5;
    undefined field6_0x6;
    undefined field7_0x7;
    undefined field8_0x8;
    undefined field9_0x9;
    undefined field10_0xa;
    undefined field11_0xb;
    undefined field12_0xc;
    undefined field13_0xd;
    undefined field14_0xe;
    undefined field15_0xf;
    undefined field16_0x10;
    undefined field17_0x11;
    undefined field18_0x12;
    undefined field19_0x13;
    undefined4 field20_0x14;
    undefined field21_0x18;
    undefined field22_0x19;
    undefined field23_0x1a;
    undefined field24_0x1b;
    undefined4 field25_0x1c;
    undefined4 field26_0x20;
    undefined4 field27_0x24;
    undefined4 field28_0x28;
    undefined4 field29_0x2c;
};

typedef struct lconv lconv, *Plconv;

struct lconv {
    char *decimal_point;
    char *thousands_sep;
    char *grouping;
    char *int_curr_symbol;
    char *currency_symbol;
    char *mon_decimal_point;
    char *mon_thousands_sep;
    char *mon_grouping;
    char *positive_sign;
    char *negative_sign;
    char int_frac_digits;
    char frac_digits;
    char p_cs_precedes;
    char p_sep_by_space;
    char n_cs_precedes;
    char n_sep_by_space;
    char p_sign_posn;
    char n_sign_posn;
    char int_p_cs_precedes;
    char int_p_sep_by_space;
    char int_n_cs_precedes;
    char int_n_sep_by_space;
    char int_p_sign_posn;
    char int_n_sign_posn;
};

typedef void *__gnuc_va_list;

typedef void (*__sighandler_t)(int);

typedef int (*__compar_fn_t)(void *, void *);

typedef struct Elf32_RegInfo_MIPS Elf32_RegInfo_MIPS, *PElf32_RegInfo_MIPS;

struct Elf32_RegInfo_MIPS {
    enum Elf32_GPRMask_MIPS ri_gprmask;
    dword field1_0x4[4];
    dword ri_gp_value;
};

typedef struct Elf32_Shdr Elf32_Shdr, *PElf32_Shdr;

typedef enum Elf_SectionHeaderType_MIPS {
    SHT_NULL=0,
    SHT_PROGBITS=1,
    SHT_SYMTAB=2,
    SHT_STRTAB=3,
    SHT_RELA=4,
    SHT_HASH=5,
    SHT_DYNAMIC=6,
    SHT_NOTE=7,
    SHT_NOBITS=8,
    SHT_REL=9,
    SHT_SHLIB=10,
    SHT_DYNSYM=11,
    SHT_INIT_ARRAY=14,
    SHT_FINI_ARRAY=15,
    SHT_PREINIT_ARRAY=16,
    SHT_GROUP=17,
    SHT_SYMTAB_SHNDX=18,
    SHT_ANDROID_REL=1610612737,
    SHT_ANDROID_RELA=1610612738,
    SHT_GNU_ATTRIBUTES=1879048181,
    SHT_GNU_HASH=1879048182,
    SHT_GNU_LIBLIST=1879048183,
    SHT_CHECKSUM=1879048184,
    SHT_SUNW_move=1879048186,
    SHT_SUNW_COMDAT=1879048187,
    SHT_SUNW_syminfo=1879048188,
    SHT_GNU_verdef=1879048189,
    SHT_GNU_verneed=1879048190,
    SHT_GNU_versym=1879048191,
    SHT_MIPS_LIBLIST=1879048192,
    SHT_MIPS_MSYM=1879048193,
    SHT_MIPS_CONFLICT=1879048194,
    SHT_MIPS_GPTAB=1879048195,
    SHT_MIPS_UCODE=1879048196,
    SHT_MIPS_DEBUG=1879048197,
    SHT_MIPS_REGINFO=1879048198,
    SHT_MIPS_PACKAGE=1879048199,
    SHT_MIPS_PACKSYM=1879048200,
    SHT_MIPS_RELD=1879048201,
    =1879048203,
    SHT_MIPS_CONTENT=1879048204,
    SHT_MIPS_OPTIONS=1879048205,
    SHT_MIPS_SHDR=1879048208,
    SHT_MIPS_FDESC=1879048209,
    SHT_MIPS_EXTSYM=1879048210,
    SHT_MIPS_DENSE=1879048211,
    SHT_MIPS_PDESC=1879048212,
    SHT_MIPS_LOCSYM=1879048213,
    SHT_MIPS_AUXSYM=1879048214,
    SHT_MIPS_OPTSYM=1879048215,
    SHT_MIPS_LOCSTR=1879048216,
    SHT_MIPS_LINE=1879048217,
    SHT_MIPS_RFDESC=1879048218,
    SHT_MIPS_DELTASYM=1879048219,
    SHT_MIPS_DELTAINST=1879048220,
    SHT_MIPS_DELTACLASS=1879048221,
    SHT_MIPS_DWARF=1879048222,
    SHT_MIPS_DELTADECL=1879048223,
    SHT_MIPS_SYMBOL_LIB=1879048224,
    SHT_MIPS_EVENTS=1879048225,
    SHT_MIPS_TRANSLATE=1879048226,
    SHT_MIPS_PIXIE=1879048227,
    SHT_MIPS_XLATE=1879048228,
    SHT_MIPS_XLATE_DEBUG=1879048229,
    SHT_MIPS_WHIRL=1879048230,
    SHT_MIPS_EH_REGION=1879048231,
    SHT_MIPS_XLATE_OLD=1879048232,
    SHT_MIPS_PDR_EXCEPTION=1879048233,
    SHT_MIPS_ABIFLAGS=1879048234,
    SHT_MIPS_PSPREL=1879048352
} Elf_SectionHeaderType_MIPS;

struct Elf32_Shdr {
    dword sh_name;
    enum Elf_SectionHeaderType_MIPS sh_type;
    dword sh_flags;
    dword sh_addr;
    dword sh_offset;
    dword sh_size;
    dword sh_link;
    dword sh_info;
    dword sh_addralign;
    dword sh_entsize;
};

typedef struct Elf32_Phdr Elf32_Phdr, *PElf32_Phdr;

typedef enum Elf_ProgramHeaderType_MIPS {
    PT_NULL=0,
    PT_LOAD=1,
    PT_DYNAMIC=2,
    PT_INTERP=3,
    PT_NOTE=4,
    PT_SHLIB=5,
    PT_PHDR=6,
    PT_TLS=7,
    PT_GNU_EH_FRAME=1685382480,
    PT_GNU_STACK=1685382481,
    PT_GNU_RELRO=1685382482,
    PT_MIPS_REGINFO=1879048192,
    PT_MIPS_RTPROC=1879048193,
    PT_MIPS_OPTIONS=1879048194,
    PT_MIPS_ABIFLAGS=1879048195,
    PT_MIPS_PSPREL1=1879048352,
    PT_MIPS_PSPREL2=1879048353
} Elf_ProgramHeaderType_MIPS;

struct Elf32_Phdr {
    enum Elf_ProgramHeaderType_MIPS p_type;
    dword p_offset;
    dword p_vaddr;
    dword p_paddr;
    dword p_filesz;
    dword p_memsz;
    dword p_flags;
    dword p_align;
};

typedef struct Elf32_Ehdr Elf32_Ehdr, *PElf32_Ehdr;

struct Elf32_Ehdr {
    byte e_ident_magic_num;
    char e_ident_magic_str[3];
    byte e_ident_class;
    byte e_ident_data;
    byte e_ident_version;
    byte e_ident_osabi;
    byte e_ident_abiversion;
    byte e_ident_pad[7];
    word e_type;
    word e_machine;
    dword e_version;
    dword e_entry;
    dword e_phoff;
    dword e_shoff;
    dword e_flags;
    word e_ehsize;
    word e_phentsize;
    word e_phnum;
    word e_shentsize;
    word e_shnum;
    word e_shstrndx;
};

typedef long intptr_t;




ulong __muldi3(undefined8 param_1,undefined8 param_2);
void __floatdidf_WG(long param_1);
void FUN_00100168(ulong param_1);
long __fixunsdfdi_G(undefined8 param_1);
long FUN_00100330(undefined8 param_1);
long FUN_001003a0(void);
undefined8 FUN_001004a8_called_instead_of__divdi3(long param_1,long param_2);
ulong __udivdi3_similar(long param_1,long param_2,long param_3);
undefined8 FUN_00100c80_called_instead_of__moddi3(long param_1,long param_2);
ulong __udivdi3_similar_2(long param_1,long param_2,long param_3);
void __udivdi3_Proxy_G(undefined8 param_1,undefined8 param_2);
ulong __udivdi3(long param_1,long param_2,long param_3);
undefined8 __umoddi3_Proxy_G(undefined8 param_1,undefined8 param_2);
ulong __umoddi3(long param_1,long param_2,long param_3);
uint __pack_f_G(uint *param_1);
void __unpack_f(uint *param_1,undefined4 *param_2);
void __make_fp(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void fptodp(undefined4 param_1);
uint fptoui(undefined4 param_1);
ulong __pack_d(uint *param_1);
void __unpack_d(ulong *param_1,undefined4 *param_2);
undefined8 _fpadd_parts(undefined8 param_1,undefined8 param_2,undefined8 param_3);
void dpadd(undefined8 param_1,undefined8 param_2);
void dpsub(undefined8 param_1,undefined8 param_2);
void dpadd(undefined8 param_1,undefined8 param_2);
undefined8 _fpadd_parts(undefined8 param_1,undefined8 param_2,undefined8 param_3);
void FUN_00102aa0(undefined8 param_1,undefined8 param_2);
undefined8 FUN_00102af8(undefined8 param_1,undefined8 param_2);
int __fpcmp_parts_d(uint *param_1,uint *param_2);
void dpcmp(undefined8 param_1,undefined8 param_2);
undefined8 litodp(ulong param_1);
int dptoli(undefined8 param_1);
void __make_dp(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined8 param_4);
void dptofp(undefined8 param_1);
undefined4 dptoul(undefined8 param_1);
undefined4 FUN_00102fb8(byte param_1);
void FUN_00103020(byte *param_1,ulong *param_2);
void FUN_00103058(byte *param_1,ulong *param_2);
undefined8 * FUN_001030b0(byte param_1,int param_2,undefined8 param_3,undefined4 *param_4);
void FUN_00103270(UnreliableInitData_W *param_1,undefined4 *param_2);
void FUN_00103290(UnreliableInitData_W *param_1);
int FUN_001032e0(undefined4 param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4);
void FUN_00103350(undefined8 param_1,undefined8 param_2);
void FUN_00103370(undefined8 param_1);
int FUN_001033a0(int **param_1);
void FUN_001034b0(UnreliableInitData_W *param_1);
void FUN_001034c8(UnreliableInitData_W *param_1);
undefined4 FUN_00103500(byte param_1,int param_2);
byte FUN_00103580(int param_1);
undefined4 FUN_00103650(undefined8 param_1,int param_2,int param_3);
undefined4 FUN_00103678(undefined8 param_1,int param_2,int param_3);
undefined4 FUN_00103740(undefined8 param_1,int param_2,int param_3);
void FUN_00103810(undefined4 param_1,code *param_2,int param_3);
int FUN_00103a98(undefined8 param_1,int *param_2);
void FUN_00103c18(undefined8 param_1,int *param_2,int *param_3);
int * FUN_00103da0(undefined8 param_1,int *param_2,int param_3);
int FUN_00103f48(undefined8 param_1,uint param_2);
long FUN_00104258(uint param_1,uint *param_2);
void FUN_00104408(undefined8 param_1);
void FUN_00104758(undefined8 param_1,code *param_2,int param_3,int param_4);
float __ieee754_acosf_similar(float param_1);
float __ieee754_expf_G(float param_1);
undefined * __ieee754_logf_G(float param_1);
undefined * __ieee754_log10f_G(float param_1);
float __ieee754_powf_G(float param_1,float param_2);
int __ieee754_rem_pio2f(float param_1,float *param_2);
float __ieee754_sqrtf(float param_1);
float __kernel_cosf(float param_1,float param_2);
uint __kernel_rem_pio2f(float *param_1,float *param_2,int param_3,int param_4,int param_5,void *param_6);
float __kernel_sinf(float param_1,float param_2,long param_3);
float ceilf(float __x);
float copysignf(float __x,float __y);
float cosf(float __x);
float fabsf(float __x);
float floorf(float __x);
double modf(double __x,double *__iptr);
float scalbnf(float __x,int __n);
float sinf_G(uint param_1);
float asinf(float __x);
float expf(float __x);
float logf(float __x);
float log10f(float __x);
float powf(float __x,float __y);
float sqrtf(float __x);
void abort(void);
void __assert(char *__assertion,char *__file,int __line);
int atexit(__func *__func);
int atoi(char *__nptr);
int FUN_00106f28(void *param_1,void *param_2,size_t param_3);
void * bsearch(void *__key,void *__base,size_t __nmemb,size_t __size,__compar_fn_t __compar);
void FUN_00107008(undefined *param_1,int param_2);
void * calloc(size_t __nmemb,size_t __size);
long _calloc_r(undefined8 param_1,int param_2,int param_3);
void _close_r(int *param_1,int param_2);
int quorem(undefined8 param_1,int param_2);
char * _dtoa_r(undefined8 param_1,ulong param_2,uint param_3,uint param_4,int *param_5,undefined4 *param_6,char **param_7);
void FUN_00108568(void);
void FUN_00108570(void);
undefined * __errno(void);
int probablyCustomExit_W(long param_1);
int fflush(FILE *__stream);
undefined * FUN_00108820(undefined *param_1,long param_2,undefined8 param_3);
void std(undefined4 *param_1,undefined2 param_2,undefined2 param_3,undefined4 param_4);
long __sfmoreglue(undefined8 param_1,int param_2);
undefined4 * FUN_00108a18(undefined8 param_1);
void _cleanup_r(undefined4 param_1);
void FUN_00108b10(void);
void __sinit(undefined8 param_1);
void fiprintf(undefined8 param_1,char *param_2,...);
undefined4 FUN_00108be8(undefined4 *param_1,char *param_2,uint *param_3);
long FUN_00108c80(undefined8 param_1,undefined8 param_2,undefined8 param_3);
void FUN_00108d68(undefined8 param_1,undefined8 param_2);
int fiprintf(FILE *param_1,char *param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8);
int FUN_00108dc8(void *param_1,long param_2,int param_3,undefined8 param_4);
void _free_r(undefined8 param_1,long param_2);
undefined4 _malloc_trim_r(undefined8 param_1,ulong param_2);
undefined4 FUN_00109318(undefined8 param_1,ulong param_2,long param_3);
void _fstat_r(int *param_1,int param_2,stat *param_3);
long ftell(FILE *__stream);
undefined4 __sfvwrite(FILE *param_1,int **param_2);
ulong _fwalk(int param_1,void *param_2);
size_t fwrite(void *__ptr,size_t __size,size_t __n,FILE *__s);
void FUN_00109dc8(undefined8 param_1,undefined8 param_2);
void FUN_00109df0(undefined8 param_1);
char * FUN_00109e18(undefined8 param_1,char *param_2,int *param_3);
void FUN_00109f48(undefined8 param_1,undefined8 param_2);
char * _setlocale_r(int param_1,undefined4 param_2,long param_3);
undefined ** _localeconv_r(void);
char * setlocale(int __category,char *__locale);
lconv * localeconv(void);
void _lseek_r(int *param_1,int param_2,__off_t param_3,int param_4);
void __smakebuf(int *param_1);
void memalign(undefined8 param_1,undefined8 param_2);
int _memalign_r(undefined8 param_1,ulong param_2,undefined8 param_3);
void FUN_0010a3e0(void);
undefined8 * FUN_0010a480(undefined8 *param_1,undefined8 param_2);
void * malloc(size_t __size);
void free(void *__ptr);
void malloc_extend_top(undefined8 param_1,int param_2);
undefined4 * _malloc_r(undefined8 param_1,int param_2);
bool FUN_0010aee0(undefined8 param_1,long param_2,long param_3);
void FUN_0010af90(undefined8 param_1);
uint _mbtowc_r(undefined8 param_1,uint *param_2,long param_3,long param_4);
void * memchr(void *__s,int __c,size_t __n);
int memcmp(void *__s1,void *__s2,size_t __n);
void * memcpy(void *__dest,void *__src,size_t __n);
void * memmove(void *__dest,void *__src,size_t __n);
void * memset(void *__s,int __c,size_t __n);
void __malloc_lock_Q(void);
int __malloc_unlock(void);
int _Balloc(undefined8 param_1,uint param_2);
void _Bfree(int param_1,long param_2);
undefined8 _multadd(undefined8 param_1,undefined8 param_2,int param_3,uint param_4);
void FUN_0010b718(undefined8 param_1,int param_2,int param_3,int param_4,undefined4 param_5);
int _hi0bits(uint param_1);
int _lo0bits(uint *param_1);
void _i2b(undefined8 param_1,undefined4 param_2);
void _multiply(undefined8 param_1,int param_2,int param_3);
undefined8 _pow5mult(undefined8 param_1,undefined8 param_2,uint param_3);
undefined8 _lshift(undefined8 param_1,undefined8 param_2,uint param_3);
int __mcmp(int param_1,int param_2);
void FUN_0010be98(undefined8 param_1,undefined8 param_2,undefined8 param_3);
ulong _ulp(undefined8 param_1);
ulong _b2d(int param_1,int *param_2);
undefined8 _d2b(undefined8 param_1,long param_2,int *param_3,int *param_4);
void _ratio(undefined8 param_1,undefined8 param_2);
undefined8 FUN_0010c490(int param_1);
undefined8 FUN_0010c500(undefined8 param_1);
void FUN_0010c530(void);
void FUN_0010c550(undefined8 param_1,undefined8 param_2);
void FUN_0010c578(undefined8 param_1,undefined8 param_2);
void FUN_0010c5b0(undefined8 param_1);
void _open_r(int *param_1,char *param_2,int param_3,undefined8 param_4);
void _printf_r(int param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8);
int printf(char *__format,...);
ulong FUN_0010c6b8(int param_1,undefined8 param_2);
void FUN_0010c758(undefined8 param_1);
undefined4 FUN_0010c778(int param_1,char *param_2);
void printf_2(const_char *param_1);
void qsort(void *__base,size_t __nmemb,size_t __size,__compar_fn_t __compar);
ssize_t _read_r(int *param_1,int param_2,void *param_3,size_t param_4);
void * realloc_G(void *__ptr,size_t __size);
int * _realloc_r(undefined8 param_1,long param_2,undefined8 param_3);
int lflush(FILE *param_1);
undefined4 __srefill(undefined8 param_1);
int isinf(double __value);
int isnan(double __value);
void _sbrk_r(int *param_1,intptr_t param_2);
undefined4 _init_signal_r(int param_1);
undefined4 _signal_r(undefined4 *param_1,ulong param_2,undefined4 param_3);
undefined4 _raise_r(undefined8 param_1,ulong param_2);
undefined4 __sigtramp_r(int param_1,ulong param_2);
int raise(int __sig);
__sighandler_t signal(int __sig,__sighandler_t __handler);
void _init_signal(void);
void __sigtramp(undefined8 param_1);
void _kill_r(int *param_1,__pid_t param_2,int param_3);
__pid_t _getpid_r(void);
int some_printf_G_1(char *__s,char *__format,...);
int some_printf_G_2(char *__s,char *__format,...);
int some_printf_G_3(char *__s,char *__format,...);
int sprintf(char *__s,char *__format,...);
int some_printf_G_5(char *__s,char *__format,...);
int some_printf_G_6(char *__s,char *__format,...);
void __sread(int param_1,undefined8 param_2,undefined8 param_3);
void __sseek(int param_1,undefined8 param_2,undefined8 param_3);
int FUN_0010e198(byte *param_1,byte *param_2);
char * strcat(char *__dest,char *__src);
char * strchr(char *__s,int __c);
int strcmp(char *__s1,char *__s2);
char * strcpy(char *__dest,char *__src);
int strcspn_W(char *param_1,char *param_2);
size_t strlen(char *__s);
char * strncat(char *__dest,char *__src,size_t __n);
int strncmp(char *__s1,char *__s2,size_t __n);
char * strncpy(char *__dest,char *__src,size_t __n);
char * strrchr(char *__s,int __c);
char * strstr(char *__haystack,char *__needle);
ulong FUN_0010eee0(undefined8 param_1,char *param_2,char **param_3);
void FUN_0010fd08(undefined8 param_1,undefined8 param_2);
void FUN_0010fd30(undefined8 param_1,undefined8 param_2);
ulong _strtol_r(undefined4 *param_1,char *param_2,char **param_3,long param_4);
long strtol(char *__nptr,char **__endptr,int __base);
ulong _strtoul_r(undefined4 *param_1,char *param_2,char **param_3,long param_4);
ulong strtoul(char *__nptr,char **__endptr,int __base);
undefined8 FUN_00110220(undefined8 param_1);
undefined4 __submore_G(void **param_1);
int ungetc(int __c,FILE *__stream);
undefined8 __sprint_1(undefined8 param_1,int param_2);
long __sbprintf(int param_1);
char * _vfprintf_r(int param_1,char *param_2,ulong *param_3);
undefined8 __sprint_2(undefined8 param_1,int param_2);
int __sbprintf(int param_1,char *param_2,__gnuc_va_list param_3);
int vfprintf(FILE *__s,char *__format,__gnuc_va_list __arg);
char * _vfiprintf_r(undefined4 param_1,int param_2,char *param_3,double *param_4);
undefined8 cvt(undefined8 param_1,long param_2,int param_3,ulong param_4,undefined *param_5,undefined8 param_6,long param_7,int *param_8);
int exponent(undefined *param_1,int param_2,undefined param_3);
void FUN_00112b80(undefined8 param_1,undefined8 param_2,undefined8 param_3);
void FUN_00112bf8(undefined8 param_1,undefined8 param_2,undefined8 param_3);
void FUN_00112c28(void);
int FUN_00112c40(undefined4 param_1,undefined8 param_2,byte *param_3,long **param_4);
char * FUN_001138d0(int param_1,char *param_2);
int vprintf(char *param_1,__gnuc_va_list param_2);
void FUN_001139e8(int param_1,undefined8 param_2,undefined8 param_3);
int vsprintf(char *param_1,char *param_2,__gnuc_va_list param_3);
void FUN_00113a68(undefined4 param_1,undefined *param_2);
uint FUN_00113ab8(byte param_1,undefined8 param_2);
ssize_t _write_r(int *param_1,int param_2,void *param_3,size_t param_4);
undefined4 __swsetup(undefined8 param_1);
void FullReset(void);
void ResetEE(u32 init_bitfield);
void SetGsCrt(s16 interlace,s16 pal_ntsc,s16 field);
void RFU003(void);
void KExit(s32 exit_code);
void ResumeIntrDispatch(void);
void _LoadExecPS2(const_char *filename,s32 num_args,char **args);
void ExecPS2(void);
void ResumeT3IntrDispatch(void);
void RFU009(void);
void AddSbusIntcHandler(void);
void RemoveSbusIntcHandler(void);
void Interrupt2Iop(void);
void SetVTLBRefillHandler(s32 handler_num,void *handler_func);
void SetVCommonHandler(s32 handler_num,void *handler_func);
void SetVInterruptHandler(s32 handler_num,void *handler_func);
s32 AddIntcHandler(s32 cause,void *handler_func,s32 next);
s32 AddIntcHandler2(s32 cause,void *handler_func,s32 next,void *arg);
s32 RemoveIntcHandler(s32 cause,s32 handler_id);
s32 AddDmacHandler(s32 channel,void *handler,s32 next);
s32 AddDmacHandler2(s32 channel,void *handler,s32 next,void *arg);
s32 RemoveDmacHandler(s32 channel,s32 handler_id);
s32 _EnableIntc(s32 cause);
s32 _DisableIntc(s32 cause);
s32 _EnableDmac(s32 channel);
s32 _DisableDmac(s32 channel);
s32 SetAlarm(u16 time,void *callback,void *common);
s32 ReleaseAlarm(s32 alarm_id);
s32 _iEnableIntc(s32 cause);
s32 _iDisableIntc(s32 cause);
s32 _iEnableDmac(s32 channel);
s32 _iDisableDmac(s32 channel);
s32 iSetAlarm(u16 time,void *callback,void *common);
s32 iReleaseAlarm(s32 alarm_id);
s32 CreateThread(ee_thread_t *thread);
s32 DeleteThread(s32 thread_id);
s32 _StartThread(s32 thread_id,void *args);
void ExitThread(void);
void ExitDeleteThread(void);
s32 TerminateThread(s32 thread_id);
s32 iTerminateThread(s32 thread_id);
void DisableDispatchThread(void);
void EnableDispatchThread(void);
s32 ChangeThreadPriority(s32 thread_id,s32 priority);
s32 iChangeThreadPriority(s32 thread_id,s32 priority);
s32 RotateThreadReadyQueue(s32 priority);
s32 _iRotateThreadReadyQueue(s32 priority);
s32 ReleaseWaitThread(s32 thread_id);
s32 iReleaseWaitThread(s32 thread_id);
s32 GetThreadId(void);
s32 ReferThreadStatus(s32 thread_id,ee_thread_status_t *info);
s32 iReferThreadStatus(s32 thread_id,ee_thread_status_t *info);
s32 SleepThread(void);
s32 WakeupThread(s32 thread_id);
s32 _iWakeupThread(s32 thread_id);
s32 CancelWakeupThread(s32 thread_id);
s32 iCancelWakeupThread(s32 thread_id);
s32 SuspendThread(s32 thread_id);
s32 _iSuspendThread(s32 thread_id);
s32 ResumeThread(s32 thread_id);
s32 iResumeThread(s32 thread_id);
void JoinThread(void);
void SetupThread(void);
void SetupHeap(void);
void EndOfHeap(void);
void RFU063(void);
int CreateSema(ee_sema_t *s);
int DeleteSema(int sema_id);
int SignalSema(int sema_id);
int iSignalSema(int sema_id);
s32 WaitSema(s32 sema_id);
int PollSema(int sema_id);
int iPollSema(int sema_id);
s32 ReferSemaStatus(s32 sema_id,ee_sema_t *sema);
s32 iReferSemaStatus(s32 sema_id,ee_sema_t *sema);
void RFU073(void);
void SetOsdConfigParam(void *addr);
void GetOsdConfigParam(void *addr);
void GetGsHParam(void *addr1,void *addr2,void *addr3);
s32 GetGsVParam(void);
void SetGsHParam(void *addr1,void *addr2,void *addr3,void *addr4);
void SetGsVParam(s32 arg1);
void CreateEventFlag(void);
void DeleteEventFlag(void);
void SetEventFlag(void);
void iSetEventFlag_G(void);
void ClearEventFlag(void);
int iPutTLBEntry(uint PageMask,uint EntryHi,uint EntryLo0,uint EntryLo1);
int SetTLBEntry(uint index,uint PageMask,uint EntryHi,uint EntryLo0,uint EntryLo1);
int GetTLBEntry(uint index,uint *PageMask,uint *EntryHi,uint *EntryLo0,uint *EntryLo1);
int iProbeTLBEntry(uint EntryHi,uint *PageMask,uint *EntryLo0,uint *EntryLo1);
int ExpandScratchPad(uint page);
void RFU090_iReferEventFlagStatus(void);
void RFU091(void);
void EnableIntcHandler(u32 cause);
void iEnableIntcHandler(u32 cause);
void DisableIntcHandler(u32 cause);
void iDisableIntcHandler(u32 cause);
void EnableDmacHandler(u32 channel);
void iEnableDmacHandler(u32 channel);
void DisableDmacHandler(u32 channel);
void iDisableDmacHandler(u32 channel);
void KSeg0(s32 arg1);
s32 EnableCache(s32 cache);
s32 DisableCache(s32 cache);
u32 GetCop0(s32 reg_id);
void FlushCache(s32 operation);
u32 CpuConfig(u32 config);
u32 iGetCop0(s32 reg_id);
void iFlushCache(s32 operation);
u32 iCpuConfig(u32 config);
void sceSifStopDma(void);
void SetCPUTimerHandler(void *handler);
void SetCPUTimer(s32 compval);
void SetOsdConfigParam2(void *config,s32 size,s32 offset);
void GetOsdConfigParam2(void *config,s32 size,s32 offset);
u64 GsGetIMR(void);
u64 iGsGetIMR(void);
u64 GsPutIMR(u64 imr);
u64 iGsPutIMR(u64 imr);
void SetPgifHandler(void *handler);
void SetVSyncFlag(u32 *param_1,u64 *param_2);
void SetSyscall(s32 syscall_num,void *handler);
void _print(const_char *fmt,...);
s32 sceSifDmaStat(u32 id);
s32 isceSifDmaStat(u32 id);
u32 sceSifSetDma(SifDmaTransfer_t *sdd,s32 len);
u32 isceSifSetDma(SifDmaTransfer_t *sdd,s32 len);
void sceSifSetDChain(void);
void isceSifSetDChain(void);
int sceSifSetReg(u32 register_num,int register_value);
int sceSifGetReg(u32 register_num);
void _ExecOSD(int num_args,char **args);
s32 Deci2Call(s32 param_1,u32 *param_2);
void PSMode(void);
s32 MachineType(void);
s32 GetMemorySize(void);
void InitTLB(void);
void sceResetttyinit(void);
int VSync(void);
undefined8 VSync2(void);
ssize_t write(int __fd,void *__buf,size_t __n);
ssize_t read(int __fd,void *__buf,size_t __nbytes);
int open(char *__file,int __oflag,...);
int close(int __fd);
int ioctl(int __fd,ulong __request,...);
__off_t lseek(int __fd,__off_t __offset,int __whence);
void * sbrk(intptr_t __delta);
int isatty(int __fd);
int fstat(int __fd,stat *__buf);
__pid_t getpid(void);
int kill(__pid_t __pid,int __sig);
int stat(char *__file,stat *__buf);
int unlink(char *__name);
void _sceIDC(uint param_1,uint param_2);
void SyncDCache(void *start,void *end);
void iSyncDCache(ulong param_1,ulong param_2);
void _sceIDC(uint param_1,uint param_2);
void InvalidDCache(void *start,void *end);
void iInvalidCache_WG(ulong param_1,ulong param_2);
uint QueryIntrContext(void);
int DisableIntc(int intc);
int EnableIntc(int intc);
int DisableDmac(int dmac);
int EnableDmac(int dmac);
s32 iEnableIntc(s32 param_1);
s32 iDisableIntc(s32 param_1);
s32 iEnableDmac(s32 param_1);
s32 iDisableDmac(s32 param_1);
void topThread(uint *param_1);
s32 InitThread(void);
void iWakeupThread(ulong param_1);
uint iRotateThreadReadyQueue(uint param_1);
void iSuspendThread(ulong param_1);
s32 sceKernelDelayThread_G(undefined8 param_1);
s32 StartThread(s32 thread_id,void *args);
undefined8 CB_DelayTh(void);
s32 sceDeci2Open(u16 protocol,void *opt,void *handler);
s32 sceDeci2Close(s32 s);
s32 sceDeci2ReqSend(u32 param_1,char param_2);
s32 sceDeci2Poll(u32 param_1);
s32 FUN_00115548(uint param_1,undefined4 param_2,undefined4 param_3);
s32 FUN_00115578(u32 param_1);
s32 sceDeci2ExRecv(s32 s,void *buf,u16 len);
s32 sceDeci2ExSend(s32 s,void *buf,u16 len);
s32 sceDeci2ExReqSend(u32 param_1,int param_2);
s32 sceDeci2ExLock(u32 param_1);
s32 sceDeci2ExUnLock(u32 param_1);
s32 kputs(u32 param_1);
undefined4 * QueueInit(undefined4 param_1);
void QueuePeekWriteDone(int *param_1);
void QueuePeekReadDone(int *param_1);
void sceTtyHandler(int param_1,long param_2,s32 *param_3);
int sceTtyWrite(char *param_1,int param_2);
int sceTtyRead(int param_1,int param_2);
bool sceTtyInit(void);
undefined8 kputchar(undefined8 param_1);
void deci2Putchar(int param_1);
void serialPutchar(long param_1);
int ftoi(ulong param_1);
int printfloat(code *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4);
int _sceSnprintf(void *printchar_W,undefined4 param_2,int some_code_W,char *format_W,...);
undefined4 snprintf_char(int *param_1,int *param_2,long param_3);
undefined4 printf_char(undefined8 param_1,undefined8 param_2,long param_3);
undefined4 kprintf_char(undefined8 param_1,undefined8 param_2,long param_3);
void _sceSnprintf_pf(void *printchar_W,undefined4 param_2,int *some_code_W,char *format_W,...);
void MyPrintf4(void *func_W,int code_W,char *format_W,...);
int sceSnprintf(char *buffer_W,int param_2,char *format_W,...);
void some_print_function_W(char *param_1,...);
void scePrintf(char *format_W,...);
void kprintf(char *param_1,...);
void _set_sreg(int param_1,int param_2);
void _change_addr(int param_1,int param_2);
int SifGetSreg(int index);
undefined8 SifGetSreg(int param_1,undefined8 param_2);
cmd_data * sceSifGetDataTable(void);
void sceSifInitCmd(void);
void sceSifExitCmd(void);
void sceSifSetCmdBuffer(SifCmdHandlerData_t *cmdBuffer,int size);
void sceSifSetSysCmdBuffer(SifCmdSysHandlerData_t *sysCmdBuffer,int size);
void SifAddCmdHandler(int pos,SifCmdHandler_t handler,void *harg);
void sceSifRemoveCmdHandler(int cid);
uint _SifSendCmd(int cid,int mode,void *pkt,int pktsize,void *src,void *dest,int size);
uint SifSendCmd(int cmd,void *packet,int packet_size,void *src_extra,void *dest_extra,int size_extra);
uint isceSifSendCmd(int cmd,void *packet,int packet_size,void *src_extra,void *dest_extra,int size_extra);
int _SifCmdIntHandler(int channel);
void sceSifWriteBackDCache(void *ptr,int size);
void SifInitRpc(int mode);
void SifExitRpc(void);
void * _sceRpcGetPacket(rpc_data *rpc_data);
void rpc_packet_free(void *packet);
void * _rpc_get_fpacket(rpc_data *rpc_data);
void * _rpc_get_fpacket2(rpc_data *rpc_data,int rid);
void _request_end(SifRpcRendPkt_t *request,void *data);
undefined4 _alarm_rdata(void);
void _request_rdata(SifRpcOtherDataPkt_t *rdata,void *data);
int SifRpcGetOtherData(SifRpcReceiveData_t *rd,void *src,void *dest,int size,int mode);
void * search_svdata(u32 sid,rpc_data *rpc_data);
undefined4 _alarm_bind(void);
void _request_bind(SifRpcBindPkt_t *bind,void *data);
int SifBindRpc(SifRpcClientData_t *client,int rpc_number,int mode);
void _request_call(SifRpcCallPkt_t *request,void *data);
int SifCallRpc(SifRpcClientData_t *cd,int rpc_number,int mode,void *sendbuf,int ssize,void *recvbuf,int rsize,void *endfunc,void *efarg);
int SifCheckStatRpc(SifRpcClientData_t *cd);
SifRpcDataQueue_t * SifSetRpcQueue(SifRpcDataQueue_t *qd,int thread_id);
SifRpcServerData_t *SifRegisterRpc(SifRpcServerData_t *sd,int sid,void *func,void *buff,void *cfunc,void *cbuff,SifRpcDataQueue_t *qd);
SifRpcServerData_t * SifRemoveRpc(SifRpcServerData_t *sd,SifRpcDataQueue_t *queue);
SifRpcDataQueue_t * SifRemoveRpcQueue(SifRpcDataQueue_t *qd);
SifRpcServerData_t * SifGetNextRequest(SifRpcDataQueue_t *qd);
void SifExecRequest(SifRpcServerData_t *sd);
void sceSifRpcLoopProxy_G(SifRpcDataQueue_t *cd_W);
void _sceFsIobSemaMK(void);
int new_iob_similar(void);
undefined * new_iob(void);
int sceSifCallRpc(SifRpcClientData_t *cd,int rpc_number,int mode,void *sendbuf,int ssize,void *recvbuf,int rsize,void *endfunc,void *efarg);
undefined * get_iob(ulong param_1);
undefined4 * _sceFs_Rcv_Intr(int param_1);
void _sceFsSemInit(void);
undefined8 _sceFsWaitS(void);
int _sceFsSigSema(void);
int * scePowerOffHandler(void *func,void *addr);
void _sceFs_Poff_Intr(undefined8 param_1,code **param_2);
int sceFsInit(void);
bool _fs_version(void);
int sceFsReset(void);
undefined4 sceOpen_G(uint param_1,ulong param_2);
undefined4 sceClose_G(undefined4 param_1);
s32 sceOpen(const_char *filename,s32 flag);
int sceClose(int fd);
int sceLseek(int fd,int offset,int where);
int sceRead(int fd,void *buf,int nbyte);
int sceWrite(int fd,const_void *buf,int nbyte);
int sceIoctl(int fd,int req,void *param_3);
undefined4 sceIoctl2(undefined8 param_1,undefined4 param_2,long param_3,ulong param_4,undefined4 param_5,ulong param_6);
undefined4 _sceCallCode(char *param_1,undefined8 param_2);
void sceRemove_duplicate(undefined8 param_1);
int sceRemove(const_char *filename);
int sceMkdir(const_char *dirname,int flag);
int sceRmdir(const_char *dirname);
int sceFormat(const_char *path,const_char *blkdevname,void *arg,int arglen);
undefined4 sceAddDrv(undefined4 param_1);
void sceDelDrv(undefined8 param_1);
int sceDopen(const_char *dirname);
int sceDclose(int fd);
int sceDread(int fd,sce_dirent *buf);
int sceGetstat(const_char *name,sce_stat *buf);
int sceChstat(const_char *name,sce_stat *buf,uint cbit);
int sceRename(const_char *oldname,const_char *newname);
int sceChdir(const_char *name);
int sceSync(const_char *path,int flag);
int sceMount(const_char *fsdevname,const_char *blkdevname,int flag,void *arg,int arglen);
int sceUmount(const_char *name);
long sceLseek64(int fd,long offset,int whence);
int sceDevctl(const_char *devname,int cmd,const_void *arg,uint arglen,void *bufp,uint buflen);
int sceSymlink(const_char *existing,const_char *newname);
int sceReadlink(const_char *path,char *buf,uint bufsize);
int sceSifInitIopHeap(void);
void * sceSifAllocIopHeap(uint param_1);
void * sceSifAllocSysMemory(int param_1,uint param_2,void *param_3);
int sceSifFreeSysMemory(void *param_1);
int sceSifFreeIopHeap(void *param_1);
int sceSifLoadIopHeap(const_char *param_1,void *param_2);
uint sceSifQueryMemSize(void);
uint sceSifQueryMaxFreeMemSize(void);
uint sceSifQueryTotalFreeMemSize(void);
void * sceSifQueryBlockTopAddress(void *param_1);
uint sceSifQueryBlockSize(void *param_1);
undefined4 _lf_bind(void);
bool _lf_version(void);
int sceSifLoadFileReset(void);
int _sceSifLoadModuleBuffer(const_void *addr,int args,const_char *argp);
int sceSifStopModule(int modid,int args,const_char *argp,int *result);
int sceSifUnloadModule(int modid);
int sceSifSearchModuleByName(const_char *modulename);
int sceSifSearchModuleByAddress(const_void *addr);
int sceSifLoadModuleBuffer(void *addr,int args,const_char *argp);
int sceSifLoadStartModuleBuffer(const_void *addr,int args,const_char *argp,int *result);
int _sceSifLoadStartModule(const_char *filename,int args,const_char *argp,int *result);
int sceSifLoadModule(const_char *filename,int args,const_char *argp);
int sceSifLoadStartModule(const_char *filename,int args,const_char *argp,int *result);
int _sceSifLoadElfPart(const_char *name,const_char *secname,sceExecData *data);
int sceSifLoadElfPart(const_char *param_1,const_char *param_2,sceExecData *param_3);
int sceSifLoadElf(const_char *name,sceExecData *data);
undefined4 sceSifGetIopAddr(undefined4 param_1,undefined4 *param_2,ulong param_3);
undefined4 sceSifSetIopAddr(undefined4 param_1,undefined4 *param_2,long param_3);
int SifIopReset(const_char *arg,int mode);
bool sceSifIsAliveIop(void);
int sceSifSyncIop(void);
int SifIopReboot(const_char *arg);
undefined8 SetTLBHandler(undefined8 param_1);
undefined4 SetDebugHandler(int param_1,undefined4 param_2);
int Copy(void *dest,void *src,int size);
int kCopy(void *dest,void *src,int size);
void * RFU091(int syscall);
void SetSyscall(int syscall_num,void *handler);
void InitTLBFunctions(void);
void PutTLBEntry(void);
void iPutTLBEntry(void);
void _SetTLBEntry(void);
undefined8 SetTLBEntry(int param_1);
void iSetTLBEntry(void);
void GetTLBEntry(void);
void iGetTLBEntry(void);
void ProbeTLBEntry(void);
void iProbeTLBEntry(void);
void ExpandScratchPad(void);
void InitTLB_not_TerminateLibrary(void);
long InitTLB32MB(void);
void _kTLBException(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8);
undefined8 _kExitTLBHandler(void);
void _kDebugException(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8);
bool FUN_0011e23c_before_Dintr(undefined8 param_1,uint param_2);
int DIntr(void);
int EIntr(void);
void supplement_crt0(void);
undefined4 getSceEhSemaId_W(void);
int Copy(void *dest,void *src,int size);
int kCopy(void *dest,void *src,int size);
int * kFindAddress(int *param_1,int *param_2,int param_3);
void FindAddress(undefined8 param_1,undefined8 param_2,void *func_W);
undefined4 GetSystemCallEntry(int param_1);
void InitSystemCallTableAddress(void);
void SetSyscall(int syscall_num,void *handler);
void _InitSys(void);
void SetSyscall(int syscall_num,void *handler);
int Copy(void *dest,void *src,int size);
int kCopy(void *dest,void *src,int size);
void * RFU091(int syscall);
bool PatchIsNeeded(void);
void InitExecPS2(void);
int Copy(void *dest,void *src,int size);
int kCopy(void *dest,void *src,int size);
void SetSyscall(int syscall_num,void *handler);
const_char * SetArg(const_char *filename,int argc,char **argv);
void InitTLB_not_TerminateLibrary(void);
void ExecPS2(undefined8 param_1,undefined8 param_2,undefined8 param_3,char **param_4);
void LoadExecPS2(const_char *filename,s32 num_args,char **args);
void Exit(s32 exit_code);
void ExecOSD(int num_args,char **args);
void SetSyscall(int syscall_num,void *handler);
int Copy(void *dest,void *src,int size);
int kCopy(void *dest,void *src,int size);
void * RFU091(int syscall);
void InitAlarm(void);
void SetT2(undefined4 *param_1,undefined4 param_2);
void SetT2_COUNT(undefined8 param_1);
void SetT2_MODE(undefined8 param_1);
void SetT2_COMP(undefined8 param_1);
undefined4 InitTimer(uint param_1);
undefined4 FUN_0011ecc8(void);
uint FUN_0011ed80(void);
undefined4 StartTimerSystemTime(void);
undefined4 StartTimerSystemTime_similar_G(void);
void SetNextComp(long param_1);
void InsertAlarm(undefined4 *param_1);
int UnlinkAlarm(int *param_1);
undefined8 cbTimerHandler(undefined8 param_1,undefined8 param_2,undefined8 param_3);
u64 iGetTimerSystemTime(void);
u64 GetTimerSystemTime(void);
s32 iAllocTimerCounter(void);
s32 AllocTimerCounter(void);
s32 iFreeTimerCounter(s32 id);
s32 FreeTimerCounter(s32 id);
undefined4 FUN_0011f630(long param_1,long param_2);
undefined8 FUN_0011f680(undefined8 param_1,undefined8 param_2);
s32 iStartTimerCounter(s32 id);
s32 StartTimerCounter(s32 id);
undefined4 FUN_0011f7e0_similar_to_iStartTimerCounter(uint param_1);
undefined8 FUN_0011f8a8(undefined8 param_1);
long FUN_0011f8f8(uint param_1,undefined8 param_2);
long FUN_0011f9c8(uint param_1);
undefined8 FUN_0011fa10(undefined8 param_1);
long iStartTimerCounter_similar(uint param_1);
undefined8 StartTimerCounter_similar(undefined8 param_1);
s32 iSetTimerHandler(s32 id,u64 scheduled_time,void *callback_handler,void *arg);
s32 SetTimerHandler(s32 id,u64 scheduled_time,void *callback_handler,void *arg);
void FUN_0011fc98(long param_1,long param_2,long param_3);
long TimerUSec2BusClock(int param_1,ulong param_2);
float FUN_0011fdb0(ulong param_1);
void FUN_0011fe08(float param_1);
undefined8 _InitAlarm(void);
s64 AlarmHandler(s32 alarm_id,u64 scheduled_time,u64 actual_time,void *arg,void *last_pc);
s32 SetTimerAlarm(u64 clock_cycles,void *callback_handler,void *arg);
uint iSetTimerAlarm(u64 some_code_W,void *func_W,undefined4 param_3);
undefined4 ReleaseTimerAlarm(uint param_1);
long FUN_001201b8(uint param_1);
void * sceSifInitRebootNotify(void);
undefined4 FUN_00120258(void *param_1,int param_2);
int sceSifAddRebootNotifyHandler(uint pos,void *pFunc,void *data);
int sceSifRemoveRebootNotifyHandler(uint pos);
undefined * sceSifExecNotifyHandler(long param_1,undefined8 param_2);
void sceGsResetGraph(short param_1,ushort param_2,ushort param_3,ushort param_4);
undefined4 * sceGsGetGParam(void);
void sceGsResetPath(void);
void sceGsPutDispEnv(undefined8 *param_1);
uint sceGsSyncV(void);
uint sceGsSyncPath(long param_1);
undefined4 sceGsSetDefLoadImage(ulong *param_1,short param_2,short param_3,short param_4,short param_5,short param_6,short param_7,short param_8);
undefined4 sceGsExecLoadImage(uint param_1,uint param_2);
undefined4 sceGsExecStoreImage(uint param_1,uint param_2);
int sceGsSyncVCallback(void *callback);
u64 sceGsPutIMR(u64 param_1);
void sceGsGetIMR(void);
void WaitDma(undefined8 param_1);
void WatchDma(undefined8 param_1,uint param_2,int param_3);
uint CheckAddress(uint param_1);
void memclr(undefined *param_1,long param_2);
undefined * sceDmaGetChan(ulong param_1);
uint sceDmaReset(int param_1);
undefined4 sceDmaPutEnv(undefined8 *param_1);
undefined8 sceDmaGetEnv(undefined8 param_1);
undefined4 sceDmaPutStallAddr(undefined4 param_1);
void sceDmaSend(undefined8 param_1,undefined8 param_2);
void sceDmaSendN(undefined8 param_1,undefined8 param_2,uint param_3);
void sceDmaSendI(undefined8 param_1,undefined8 param_2,uint param_3);
void sceDmaRecv(uint *param_1);
void sceDmaRecvN(undefined8 param_1,undefined8 param_2,uint param_3);
void sceDmaRecvI(undefined8 param_1,undefined8 param_2,uint param_3);
uint sceDmaSync(uint *param_1,long param_2);
bool sceDmaWatch(int param_1,uint param_2,int param_3,undefined8 param_4);
uint sceDmaPause(uint *param_1);
uint sceDmaRestart(uint *param_1,uint param_2);
undefined4 FUN_00121e48(undefined4 param_1);
int _sceCd_cd_callback(int *param_1);
void _Cdvd_cbLoop(void);
bool sceCdInitEeCB(int initial_priority,void *stack,int stack_size);
void cmd_sem_init(void);
long cdvd_exit(void);
undefined4 sceCdPOffCallback(undefined4 param_1,undefined4 param_2);
void _sceCd_Poff_Intr(void);
undefined4 PowerOffCB(void);
int sceCdLayerSearchFile(undefined8 *fp,const_char *path,int layer);
int sceCdSearchFile(undefined8 *param_1,const_char *param_2);
int _CdCheckNCmd(int cmd);
int sceCdNCmdDiskReady(void);
undefined4 sceCdSync(long param_1);
int _CdSyncS(long param_1);
int _CdCheckSCmd(int cur_cmd);
undefined4 _sceCdSC(long param_1,SifRpcClientData_t **param_2);
s32 sceCdInit(s32 mode);
s32 sceCdDiskReady_old(s32 mode);
s32 sceCdDiskReady(s32 mode);
undefined8 FUN_00123398_sceCd(int param_1,undefined8 param_2);
int FUN_00123460_sceCd(byte *param_1);
undefined4 FUN_001234c0_sceCd(void);
int sceCdReadChain(undefined *readChain,undefined *mode);
int sceCdRead(u32 lbn,u32 sectors,void *buf,undefined *mode);
int sceCdReadIOPMem(u32 lbn,u32 sectors,void *buf,undefined *mode);
undefined4 FUN_00123b40_sceCd(undefined4 param_1,int param_2,void *param_3,undefined *param_4,long param_5);
void FUN_00123d30_sceCd(void);
int sceCdGetToc(u8 *toc);
int sceCdSeek(u32 lbn);
int sceCdStandby(void);
int sceCdStop(void);
int sceCdPause(void);
int sceCdGetDiskType(void);
int FUN_00124358_sceCd(void);
int sceCdGetError(void);
int sceCdStatus(void);
int sceCdBreak(void);
int sceCdChangeThreadPriority(int priority);
undefined4 sceCdBlueLedCtrl_G_based_on_callrpc_params_but_probably_wrong!(undefined4 param_1,undefined4 param_2);
undefined4 sceCdReadDvdDualInfo_G_from_GoW(undefined4 *param_1,undefined4 *param_2);
undefined4 FUN_001247f8_sceCd(undefined4 param_1);
int sceCdPowerOff(u32 *result);
int sceCdMmode(int media);
int sceCdChgSys(u32 arg1);
int sceCdCtrlADout(int arg1,u32 *result);
int sceCdReadClock(undefined8 *clock);
int sceCdTrayReq(int param,u32 *traychk);
char * GetRomNameWithIODriver_G(char *romname,undefined *driver);
bool IsT10KWithIODriver_G(char *param_1,undefined *param_2);
uint sceScfGetLanguage(void);
void sceScfSetT10kConfig(undefined8 *param_1);
uint sceScfGetAspect(void);
uint sceScfGetSpdif(void);
long sceScfGetTimeZone(void);
byte sceScfGetDateNotation(void);
byte sceScfGetSummerTime(void);
byte sceScfGetTimeNotation(void);
uint tobcd(uint param_1);
uint frombcd(uint param_1);
void convertfrombcd(int param_1);
void converttobcd(int param_1);
void adddate(int param_1);
void subdate(int param_1);
void addhour(undefined8 param_1);
void subhour(int param_1);
void AdjustTime(undefined8 param_1,int param_2);
void FUN_00125330(undefined8 param_1);
void sceScfGetLocalTimefromRTC(undefined8 param_1);
void FUN_00125380_functions_saved(void);
void FUN_00125398_functions_saved_2(void);
undefined4 * FUN_001253b0_saved_functions_also_rt_comm(void);
undefined4 FUN_00125500(int *param_1);
void * FUN_00125548(void *param_1);
bool FUN_00125568(int param_1);
bool rt_comm_platform_linkaddress_isequal(int param_1,int param_2);
undefined8 rt_comm_platform_linkaddress_tostr(undefined8 param_1,undefined4 param_2);
undefined8 rt_comm_platform_linkaddress_toext(undefined8 param_1,undefined4 param_2);
undefined8 rt_comm_platform_linkaddress_toint(undefined4 *param_1,undefined8 param_2);
long FUN_00125630(void);
void FUN_001256a8(void);
undefined8 FUN_00125728(void);
long FUN_00125730(long param_1,int param_2,undefined8 param_3,long param_4,long param_5);
void FUN_00125a38(long param_1);
long FUN_00125b30(int param_1,long param_2,undefined8 param_3,long param_4);
long FUN_00125bf0(long param_1,undefined4 param_2,long param_3,long param_4,long param_5,long param_6);
long FUN_00125c88(long param_1,undefined4 *param_2,long param_3);
long FUN_00125d88(long param_1,undefined4 param_2,long param_3,void **param_4,long param_5);
long FUN_00125eb8(long param_1,undefined8 param_2,undefined4 param_3);
long FUN_00125f18(int param_1,long param_2,undefined8 param_3,long param_4);
long FUN_00126068(long param_1,undefined8 param_2,long param_3,long param_4,undefined8 param_5,long param_6);
long FUN_00126110(long param_1,undefined8 param_2,undefined8 param_3);
long FUN_00126170(int param_1,long param_2);
undefined8 FUN_00126288(long param_1);
undefined4 FUN_001262c0(undefined4 *param_1);
undefined8 FUN_001262e8(long param_1,undefined8 param_2);
long FUN_00126328(long param_1,undefined4 *param_2);
undefined8 FUN_001263b0(void);
undefined8 FUN_001263b8(undefined8 param_1,long param_2);
undefined4 FUN_001263e0(long param_1,long param_2,long param_3);
undefined * rt_comm_get_version_string_ptr_G(void);
undefined4 rt_comm_get_build_timestamp(long param_1,size_t param_2);
void FUN_00126558(void);
undefined8 FUN_00126570(void);
void FUN_00126588(undefined8 param_1);
void FUN_001265b0(void);
undefined8 FUN_001265c8(undefined8 param_1,long param_2);
void FUN_00126628(void);
undefined8 FUN_00126640(undefined8 param_1,long param_2);
void FUN_00126688(void);
undefined8 FUN_001266a0(undefined8 param_1,ulong param_2);
undefined8 FUN_001266e8(undefined8 param_1,ulong param_2);
undefined8 FUN_00126730(undefined8 param_1,ulong param_2);
undefined8 FUN_00126778(undefined8 param_1,undefined4 *param_2);
undefined8 FUN_001267d0(undefined8 param_1,undefined4 *param_2);
undefined8 FUN_00126828(undefined8 param_1,undefined2 param_2);
undefined8 FUN_001268a8(undefined8 param_1,undefined4 param_2,undefined2 param_3);
undefined8 FUN_00126930(undefined8 param_1,int *param_2);
undefined8 FUN_00126a00(undefined8 param_1,undefined4 param_2,undefined2 param_3);
void FUN_00126a88(void);
void FUN_00126aa0(void);
void FUN_00126ab8(void);
undefined8 FUN_00126ad0(undefined4 *param_1,long param_2);
undefined8 FUN_00126b38(void *param_1);
void FUN_00126b90(void);
void FUN_00126ba8(void);
undefined8 FUN_00126bd0(undefined8 param_1,long param_2);
undefined8 FUN_00126c40(undefined8 param_1,long param_2,long param_3,long param_4);
undefined8 FUN_00126cc0(undefined8 param_1,long param_2,long param_3,long param_4);
undefined8 FUN_00126d40(undefined8 param_1,long param_2,long param_3,long param_4);
undefined8 FUN_00126dc0(undefined4 *param_1);
undefined8 FUN_00126e18(undefined8 param_1,int param_2);
undefined8 FUN_00126e90(undefined8 param_1,long param_2,long param_3,long param_4,long param_5,long param_6);
undefined8 FUN_00126f50(undefined8 param_1,void *buffer_W,long param_3,undefined4 param_4,undefined2 param_5,long param_6);
undefined8 FUN_00127010(undefined8 param_1,long param_2,long param_3,long param_4);
undefined8 FUN_00127090(undefined8 param_1,long param_2,long param_3,long param_4);
uint FUN_00127110(ushort *param_1,int param_2);
undefined8 FUN_00127180(long param_1);
undefined8 FUN_001271e0(undefined8 param_1,long param_2,long param_3,undefined2 param_4);
undefined8 FUN_001272c0(undefined8 param_1,undefined4 *param_2,long param_3,long param_4);
void FUN_001273d8(void);
undefined8 FUN_001273f0(void);
long FUN_00127588(void);
void FUN_00127600(void);
undefined8 FUN_00127628(undefined8 param_1,undefined4 param_2);
undefined8 FUN_00127668(undefined8 param_1,undefined4 param_2);
undefined8 FUN_001276a8(undefined8 param_1,int *param_2);
undefined8 FUN_00127798(int param_1,ulong param_2,undefined8 param_3,undefined4 *param_4);
long FUN_00127820(long param_1,undefined8 param_2,undefined8 param_3,long param_4);
long FUN_00127880(undefined4 *param_1,uint param_2,undefined8 param_3,long param_4);
undefined8 FUN_00127988(undefined4 *param_1);
undefined8 FUN_00127b30(long param_1);
undefined8 FUN_00127cc0(undefined8 param_1,long param_2);
undefined4 FUN_00127e20(int param_1,int param_2);
undefined8 MediusBillingClientVersion(char *param_1,size_t param_2);
undefined8 MediusBillingServerVersion_G(char *param_1,size_t param_2);
undefined4 getGState_W(void);
void FUN_00127f08(void);
undefined4 MediusBillingUpdate|MediusBillingIsLoaded_Q(void);
undefined8 MediusBillingLockMutex_W(void);
void MediusBillingUnlockMutex_W(void);
undefined8 FUN_00127f80(void *param_1,ulong param_2);
undefined8 FUN_00128090(int param_1);
undefined4 MediusBillingUpdate|MediusBillingIsLoaded_Q2(void);
int FUN_00128130_cachePurchaseCreate(void);
undefined8 FUN_001282a8(void);
undefined8 FUN_00128308_reset_products_and_purchases_W(void);
int FUN_001283c0(undefined8 *param_1,undefined4 param_2,undefined4 param_3);
void FUN_00128528(void);
void FUN_00128788(void);
undefined4 MediusBillingAccountLogin_G(undefined4 *param_1,undefined4 param_2,undefined4 param_3);
char * MediusBillingLogInCallback(void);
undefined8 MediusBillingAccountLogout(undefined4 param_1,undefined4 param_2);
void FUN_001289f8(void);
undefined4 FUN_00128a48(undefined8 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void MediusBillingResponse_WS(void);
undefined4 FUN_00128cd8(undefined8 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_00128e90(void);
undefined4 FUN_00129068(undefined8 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_001291f8(void);
void FUN_00129258(int param_1);
undefined4 FUN_001297d8(undefined8 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_00129968(void);
undefined4 FUN_00129970(undefined4 param_1,undefined8 param_2,undefined4 param_3,undefined4 param_4);
void FUN_00129d08(int param_1,undefined8 param_2);
void FUN_0012a2a8(int param_1);
undefined4 FUN_0012a618(int *param_1,int *param_2,undefined4 *param_3);
undefined4 FUN_0012a740(int *param_1,int *param_2,undefined4 *param_3);
undefined8 FUN_0012a858(int *param_1);
undefined8 FUN_0012a870(int *param_1);
undefined4 FUN_0012a888(undefined8 *param_1,undefined8 param_2);
undefined4 FUN_0012a9b0(undefined8 *param_1,undefined8 param_2);
undefined8 FUN_0012aad8(undefined8 *param_1,undefined4 *param_2);
undefined8 FUN_0012ab78(undefined8 *param_1,undefined4 *param_2);
undefined4 FUN_0012ac18(undefined8 *param_1);
undefined4 FUN_0012ad28(undefined8 *param_1);
void FUN_0012ae38(void);
void FUN_0012aed0(undefined8 *param_1,undefined4 *param_2);
void FUN_0012b000(undefined8 *param_1,undefined4 *param_2);
undefined4 FUN_0012b130(void **param_1,int param_2);
int FUN_0012b1a8_reset_some_struct(ProductsAndPurchasesData_W **param_1);
undefined4 FUN_0012b208(void **param_1);
undefined8 FUN_0012b268(int *param_1);
undefined4 FUN_0012b2c0(void **param_1,int param_2);
undefined8 FUN_0012b338(int *param_1);
undefined4 FUN_0012b390(int param_1);
undefined8 FUN_0012b3f0(void);
undefined4 FUN_0012b490(void **param_1,int param_2,long param_3);
undefined8 FUN_0012b538(int *param_1);
undefined4 FUN_0012b5b0(void **param_1,int param_2);
undefined8 FUN_0012b5f8(void **param_1,int param_2);
int rt_memory_free_Proxy_G(int *param_1);
int MediusBillingRequest_WS(undefined8 param_1,undefined8 *param_2,int param_3);
size_t FUN_0012b890(undefined8 param_1,void *param_2,ulong param_3);
undefined4 MediusCreateClan(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusDisbandClan(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusGetClanByName(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusGetClanByID(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusTransferClanLeadership(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012bbf0_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusRemovePlayerFromClan(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusInvitePlayerToClan(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusCheckMyClanInvitations(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusGetClanInvitationsSent(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusRespondToClanInvitation(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusRevokeClanInvitation(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusGetMyClanMessages(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusSendClanMessage(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusModifyClanMessage(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusDeleteClanMessage(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusRequestClanTeamChallenge(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusRespondToClanTeamChallenge(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusRevokeClanTeamChallenge(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusGetClanTeamChallenges(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusGetMyClans(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012c3a8_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusGetAllClanMessages(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusGetClanTeamChallengeHistory(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusUpdateClanStats(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012c588_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusClanLadderList(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusClanLadderPosition(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusGetClanMemberList_ExtraInfo(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012c780_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusConnectionHandle(void);
undefined4 MediusInitFlag(void);
void * MediusSetNatServiceAddress_G(void *param_1);
void * MediusGetNatServiceAddress(void *param_1);
void MediusSetProcessingState(undefined4 param_1);
undefined4 MediusGetProcessingState(void);
void * FUN_0012c890(undefined8 *param_1);
void * MediusGetClientAddrList_G(void *param_1);
void MGCLResolveAddrCallback(int *param_1);
void MediusSetQueuedRequest(undefined *param_1,void *param_2);
void MediusGetQueuedRequestType(undefined4 *param_1);
void MediusGetQueuedRequest(void *param_1);
undefined4 MediusCheckRequestQueue(void);
void * BillingLoginCallback_S(undefined8 param_1,undefined4 *param_2);
void * BillingLogoutCallback_S(void);
void MediusLocalConnectCallback_G(undefined4 *param_1);
void MediusSetClientConnectCallback_G(undefined4 param_1,undefined4 param_2);
undefined4 MediusGetClientConnectCallback_G(void);
undefined4 MediusGetClientConnectCallbackArg_G(void);
void MediusClearClientConnectCallback_G(void);
void MediusLocalConnectCallback(undefined8 param_1);
void MediusSetClientConnectCallback_G(undefined4 param_1);
undefined4 MediusGetClientConnectCallback(void);
undefined4 MediusInitializeBare_similar_G(undefined4 *param_1,undefined4 *param_2);
undefined4 MediusInitializeBare_G(undefined4 *param_1,undefined4 *param_2);
undefined4 FUN_0012d0d0_medius_build(long param_1);
undefined4 FUN_0012d100_print_medius_info_G(long param_1);
undefined4 MediusGetServerTime(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusGetMySessionKey(char *param_1);
undefined4 FUN_0012d1e0_similar_MediusCloseBare_G(void);
undefined4 FUN_0012d250_similar_MediusCloseBare_G(void);
void MediusSendMessage(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4);
undefined4 MediusConnect(void *param_1,undefined4 *param_2,undefined8 param_3);
undefined4 MediusSetDefaultDisconnectParams(long param_1);
void MediusDisconnectCB(undefined4 *param_1);
void MUISDisconnectCB(int param_1);
undefined8 MediusDisconnect(long param_1,undefined4 param_2);
long MediusUpdate(void);
long MediusUpdateUniverseInformation(void);
undefined8 MediusUpdateBare(void);
undefined4 MediusUpdateClientState(undefined8 param_1);
undefined4 FUN_0012d778_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusSessionEnd(long param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012d880_medius(undefined8 param_1);
undefined4 MediusDnasSignature(undefined8 param_1);
undefined4 MediusAccountLogin(undefined8 *param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusAccountLoginInternal(void);
undefined4 MediusAccountLogout(undefined8 *param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusAccountLogoutInternal(void);
undefined4 FUN_0012ddb0_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusAccountRegistration(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012dea8_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusAccountUpdateStats(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012dfb8_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusAccountDelete(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusAnonymousLogin_C(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusCreateGame(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusTextFilter(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012e268_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusCreateChannel(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusJoinGame(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusJoinChannel(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012e560_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012e5d8_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012e650_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusGetGamePlayers(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusGetPlayerInfo(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012e7b8_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusGetGameInfo(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusFindPlayer(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012e928_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012e9a8_medius(undefined8 param_1);
undefined4 FUN_0012ea10_medius(undefined8 param_1);
undefined4 FUN_0012ea70_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusAddToBuddyList(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusRemoveFromBuddyList(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012ebd8_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012ec50_medius(undefined8 param_1);
undefined4 MediusGetIgnoreList(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusAddToIgnoreList(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusRemoveFromIgnoreList(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusGetPolicy(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusSendPlayerReport(undefined8 param_1);
undefined4 MediusSendWorldReport(undefined8 param_1);
undefined4 MediusSendEndGameReport(undefined8 param_1);
undefined4 MediusGetAnnouncements(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusGetAllAnnouncements(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012f140_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012f1b8_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusGetGameListFilter(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined8 MediusCreateMessageID(int param_1,undefined8 param_2,int param_3);
undefined4 FUN_0012f300_medius(undefined4 param_1,undefined4 param_2);
undefined4 FUN_0012f330_medius(undefined4 param_1,undefined4 param_2);
undefined4 FUN_0012f360_medius(undefined4 param_1,undefined4 param_2);
undefined4 FUN_0012f390_medius(undefined4 param_1,undefined4 param_2);
undefined4 MediusGetMyIP(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012f438_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012f4b0_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusAccountGetID(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusGetLocations(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012f618_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 get_LastDMENetError_medius_W(void);
undefined4 FUN_0012f6a0_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012f718_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012f790_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012f808_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
char * codeToMediusCallbackStatusName_W:(int error_code_W);
undefined4 codeToMediusErrorName_W(int code_W);
void * FUN_0012f950_medius(void *param_1);
void * FUN_0012f980_medius(void *param_1);
char * MediusSetDefaultConnectInParams(undefined4 *param_1,long param_2,char *param_3,undefined4 param_4,undefined4 param_5);
undefined4 FUN_0012fab0_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012fb28_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012fba0_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012fc18_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusSetLocalizationParams(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012fd08_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusGetUniverseInformation(undefined8 param_1,undefined4 param_2,undefined4 param_3,undefined8 param_4,undefined4 param_5);
undefined4 MediusGetBuddyList_ExtraInfo(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusGetTotalRankings(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusGetLobbyPlayerNames_ExtraInfo(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0012ffd0_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_00130048_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_001300c0_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusLadderPosition_ExtraInfo(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_001301c0_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_00130238_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_001302b0_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_00130328_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_001303a0_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_00130418_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_00130490_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusSetLobbyWorldFilter(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_001305c0_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
void vLocalSetLobbyWorldFilter(void);
undefined4 MediusFileCreate(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusFileUpload(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusFileClose(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusFileDownload(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_001308e8_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MediusFileDelete(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined8 FUN_001309d8_medius(void *param_1);
undefined4 MediusFileListFiles(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined8 MediusFileInitAttributes(void *param_1);
undefined4 FUN_00130aa0_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_00130b18_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_00130b90_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_00130c08_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_00130c80_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_00130cf8_medius(undefined4 *param_1);
undefined4 FUN_00130d38_medius(undefined8 param_1,undefined4 param_2,undefined4 param_3);
void FUN_00130db0(void);
void FUN_00130db8(void);
void FUN_00130dc0(void);
void FUN_00130dc8(void);
void FUN_00130dd0(void);
void FUN_00130dd8(void);
undefined4 MediusUniqueCallbackErrorMessageHandler_G(void);
undefined4 FUN_00130e18_medius_RegisterPackets_callback(void);
undefined4 FUN_00130e20_medius_RegisterPackets_callback(void);
undefined4 FUN_00130e28_medius_RegisterPackets_callback(void);
undefined4 MediusUniqueCallbackSessionBeginResponseHandler(void);
undefined4 MediusUniqueCallbackSessionEndResponseHandler(void);
undefined4 FUN_00130ed8_medius_RegisterPackets_callback(void);
undefined4 MediusUniqueCallbackDnasSignaturePostHandler_G(void);
undefined4 MediusUniqueCallbackAccountLoginResponseHandler(void);
undefined4 MediusUniqueCallbackAccountLogoutResponseHandler_G(void);
undefined4 MediusUniqueCallbackAccountRegistrationResponseHandler_G(void);
undefined4 MediusUniqueCallbackAccountGetProfileResponseHandler_G(void);
undefined4 MediusUniqueCallbackAccountUpdateProfileResponseHandler_G(void);
undefined4 MediusUniqueCallbackAccountUpdatePasswordResponseHandler_G(void);
undefined4 MediusUniqueCallbackAccountUpdateStatsResponseHandler_G(void);
undefined4 MediusUniqueCallbackAnonymousLoginResponseHandler_G(void);
undefined4 MediusUniqueCallbackCreateGameResponseHandler_G(void);
undefined4 MediusUniqueCallbackCreateChannelResponseHandler_G(void);
undefined4 MediusUniqueCallbackAccountGetIDResponseHandler(void);
undefined4 MediusUniqueCallbackJoinGameResponseHandler_G(void);
undefined4 MediusUniqueCallbackJoinChannelResponseHandler_G(void);
undefined4 MediusUniqueCallbackJoinChannelFwdResponseHandler_G(void);
undefined4 MediusUniqueCallbackGameListResponseHandler_G(void);
undefined4 MediusUniqueCallbackChannelListResponseHandler_G(void);
undefined4 MediusUniqueCallbackLobbyWorldPlayerListResponseHandler_G(void);
undefined4 MediusUniqueCallbackGameWorldPlayerListResponseHandler_G(void);
undefined4 MediusUniqueCallbackPlayerInfoResponseHandler_G(void);
undefined4 MediusUniqueCallbackGameInfoResponseHandler_G(void);
undefined4 MediusUniqueCallbackChannelInfoResponseHandler_G(void);
undefined4 MediusUniqueCallbackFindWorldByNameResponseHandler_G(void);
undefined4 MediusUniqueCallbackFindPlayerResponseHandler_G(void);
undefined4 FUN_001313e0(void);
undefined4 MediusUniqueCallbackGenericChatMessageHandler_G(void);
undefined4 FUN_001313f0_medius_RegisterPackets_callback(void);
undefined4 MediusUniqueCallbackBinaryMessageHandler_G(void);
undefined4 MediusUniqueCallbackBinaryFwdMessageHandler_G(void);
undefined4 MediusUniqueCallbackGetBuddyListResponseHandler_G(void);
undefined4 MediusUniqueCallbackAddToBuddyListResponseHandler_G(void);
undefined4 MediusUniqueCallbackRemoveFromBuddyListResponseHandler_G(void);
undefined4 MediusUniqueCallbackAddToBuddyListConfirmationResponseHandler_G(void);
undefined4 MediusUniqueCallbackAddToBuddyListFwdConfirmationRequestHandler_G(void);
undefined4 MediusUniqueCallbackAddToBuddyListFwdConfirmationResponseHandler_G(void);
undefined4 FUN_00131588_medius_RegisterPackets_callback(void);
undefined4 MediusUniqueCallbackGetIgnoreListResponseHandler_G(void);
undefined4 MediusUniqueCallbackAddToIgnoreListResponseHandler_G(void);
undefined4 MediusUniqueCallbackRemoveFromIgnoreListResponseHandler_G(void);
undefined4 MediusUniqueCallbackGetPolicyResponseHandler_G(void);
undefined4 MediusUniqueCallbackUpdateUserStateHandler(void);
undefined4 MediusUniqueCallbackGetAnnouncementsResponseHandler_G(void);
undefined4 MediusUniqueCallbackSetGameListFilterResponseHandler0_G(void);
undefined4 MediusUniqueCallbackClearGameListFilterResponseHandler_G(void);
undefined4 MediusUniqueCallbackGetGameListFilterResponseHandler0_G(void);
undefined4 MediusUniqueCallbackCreateClanResponseHandler_G(void);
undefined4 MediusUniqueCallbackDisbandClanResponseHandler_G(void);
undefined4 MediusUniqueCallbackGetClanByIDResponseHandler_G(void);
undefined4 MediusUniqueCallbackGetClanByNameResponseHandler_G(void);
undefined4 MediusUniqueCallbackTransferClanLeadershipResponseHandler_G(void);
undefined4 MediusUniqueCallbackAddPlayerToClanResponseHandler_G(void);
undefined4 MediusUniqueCallbackRemovePlayerFromClanResponseHandler_G(void);
undefined4 MediusUniqueCallbackInvitePlayerToClanResponseHandler_G(void);
undefined4 MediusUniqueCallbackCheckMyClanInvitationsResponseHandler_G(void);
undefined4 MediusUniqueCallbackGetClanInvitationsSentResponseHandler_G(void);
undefined4 MediusUniqueCallbackRespondToClanInvitationResponseHandler_G(void);
undefined4 MediusUniqueCallbackRevokeClanInvitationResponseHandler_G(void);
undefined4 MediusUniqueCallbackRequestClanTeamChallengeResponseHandler_G(void);
undefined4 MediusUniqueCallbackGetMyClanMessagesResponseHandler_G(void);
undefined4 MediusUniqueCallbackSendClanMessageResponseHandler_G(void);
undefined4 MediusUniqueCallbackModifyClanMessageResponseHandler_G(void);
undefined4 MediusUniqueCallbackDeleteClanMessageResponseHandler_G(void);
undefined4 MediusUniqueCallbackRespondToClanTeamChallengeResponseHandler_G(void);
undefined4 MediusUniqueCallbackRevokeClanTeamChallengeResponseHandler_G(void);
undefined4 MediusUniqueCallbackGetMyClansResponseHandler_G(void);
undefined4 MediusUniqueCallbackGetClanTeamChallengesResponseHandler_G(void);
undefined4 MediusUniqueCallbackConfirmClanTeamChallengeResponseHandler_G(void);
undefined4 MediusUniqueCallbackGetAllClanMessagesResponseHandler_G(void);
undefined4 MediusUniqueCallbackGetClanTeamChallengeHistoryResponseHandler_G(void);
undefined4 MediusUniqueCallbackUpdateClanStatsResponseHandler_G(void);
undefined4 MediusUniqueCallbackGetMyIPResponseHandler_G(void);
undefined4 MediusUniqueCallbackVersionServerResponseHandler_G(void);
undefined4 MediusUniqueCallbackGetWorldSecurityLevelResponseHandler_G(void);
undefined4 MediusUniqueCallbackBanPlayerResponseHandler_G(void);
undefined4 MediusUniqueCallbackAccountDeleteResponseHandler(void);
undefined4 MediusUniqueCallbackAccountGetIDResponseHandler_G(void);
undefined4 MediusUniqueCallbackGetLocationsResponseHandler_G(void);
undefined4 MediusUniqueCallbackPickLocationResponseHandler_G(void);
undefined4 MediusUniqueCallbackGetClanMemberListResponseHandler_G(void);
undefined4 FUN_00131f48_medius_RegisterPackets_callback(void);
undefined4 MediusUniqueCallbackLadderPositionFastResponseHandler_G(void);
undefined4 FUN_00131fb8_medius_RegisterPackets_callback(void);
undefined4 FUN_00131ff0_medius_RegisterPackets_callback(void);
undefined4 MediusUniqueCallbackTextFilterResponseHandler_G(void);
undefined4 MediusUniqueCallbackReassignGameMediusWorldIDHandler_G(void);
undefined4 MediusUniqueCallbackGetTotalGamesResponseHandler_G(void);
undefined4 MediusUniqueCallbackGetTotalChannelsResponseHandler_G(void);
undefined4 MediusUniqueCallbackGetLobbyPlayerNamesResponseHandler_G(void);
undefined4 MediusUniqueCallbackGetTotalUsersResponseHandler_G(void);
undefined4 MediusUniqueCallbackSetLocalizationParamsResponseHandler_G(void);
undefined4 MediusUniqueCallbackSetMessageAsReadResponseHandler_G(void);
undefined4 MediusUniqueCallbackClanLadderListResponseHandler_G(void);
undefined4 MediusUniqueCallbackClanLadderPositionResponseHandler_G(void);
undefined4 MediusUniqueCallbackGetBuddyList_ExtraInfoResponseHandler_G(void);
undefined4 MediusUniqueCallbackGetTotalRankingsResponseHandler_G(void);
undefined4 MediusUniqueCallbackGetLobbyPlayerNames_ExtraInfoResponseHandler_G(void);
undefined4 MediusUniqueCallbackGetClanMemberList_ExtraInfoResponseHandler_G(void);
undefined4 FUN_00132338_medius_RegisterPackets_callback(void);
undefined4 MediusUniqueCallbackChannelList_ExtraInfoResponseHandler_G(void);
undefined4 MediusUniqueCallbackLadderList_ExtraInfoResponseHandler_G(void);
undefined4 MediusUniqueCallbackUpdateLadderStatsResponseHandler_G(void);
undefined4 MediusUniqueCallbackUpdateLadderStatsWideResponseHandler_G(void);
undefined4 FUN_00132450_medius_RegisterPackets_callback(void);
undefined4 MediusUniqueCallbackGetLadderStatsWideResponseHandler_G(void);
undefined4 MediusUniqueCallbackLadderPosition_ExtraInfoResponseHandler_G(void);
undefined4 MediusUniqueCallbackFileCreateResponseHandler_G(void);
undefined4 MediusUniqueCallbackFileUploadFromClientResponseHandler_G(void);
undefined4 MediusUniqueCallbackFileUploadResponseHandler_G(void);
undefined4 MediusUniqueCallbackFileCloseResponseHandler_G(void);
undefined4 MediusUniqueCallbackFileDownloadResponseHandler_G(void);
undefined4 MediusUniqueCallbackFileDownloadStreamResponseHandler_G(void);
undefined4 MediusUniqueCallbackFileDeleteResponseHandler_G(void);
undefined4 MediusUniqueCallbackFileListFilesResponseHandler_G(void);
undefined4 MediusUniqueCallbackFileUpdateAttributesResponseHandler_G(void);
undefined4 MediusUniqueCallbackFileGetAttributesResponseHandler_G(void);
undefined4 MediusUniqueCallbackFileUpdateMetaDataResponseHandler_G(void);
undefined4 MediusUniqueCallbackFileGetMetaDataResponseHandler_G(void);
undefined4 MediusUniqueCallbackFileSearchByMetaDataResponseHandler_G(void);
undefined4 MediusUniqueCallbackFileCancelOperationResponseHandler_G(void);
undefined4 MediusUniqueCallbackUniverseNewsHandler_G(void);
undefined4 MediusUniqueCallbackUniverseStatusListHandler_G(void);
undefined4 MediusUniqueCallbackUniverseStatusList_ExtraInfoHandler_G(void);
int MediusUniqueCallbackUniverseSvoURLHandler(void);
char * MediusUniqueCallbackUniverseVariableInfoHandler(void);
undefined4 MediusUtilGetServerVersionResponseHandler_G(void);
undefined4 MediusUtilAddLobbyWorldResponseHandler_G(void);
undefined4 MediusUtilAddGameWorldResponseHandler_G(void);
undefined4 MediusUtilUpdateLobbyWorldResponseHandler_G(void);
undefined4 MediusUtilUpdateGameWorldResponseHandler_G(void);
undefined4 MediusUtilEventMsgHandler_G(void);
undefined4 MediusUniqueCallbackGetBuddyInvitationsResponseHandler_G(void);
undefined4 MediusUniqueCallbackSetLobbyWorldFilterResponseHandler(void);
undefined4 MediusUniqueCallbackPostDebugInfoResponseHandler(void);
undefined4 MediusUniqueCallbackUpdateClanLadderStatsWide_DeltaResponseHandler_G(void);
undefined4 FUN_001330c8_medius_RegisterPackets_callback(void);
undefined4 FUN_00133100_create_product_hash_table(long param_1,short param_2);
undefined8 FUN_001331e8(void);
undefined8 FUN_00133228_clear_product_cache(void);
undefined4 FUN_00133268_add_product_to_hash_table(undefined8 *param_1);
undefined4 FUN_00133358_retrieve_product_from_hash_table(undefined8 param_1);
undefined4 FUN_001333e8_retrieve_product_from_hash_table2(undefined8 param_1,undefined8 param_2);
undefined8 copyMediusProducts_W(char *param_1,undefined8 param_2,void *param_3);
void FUN_00133488(undefined8 param_1,undefined8 param_2);
bool compareMediusProducts_W(void *param_1,void *param_2);
undefined4 FUN_001334d0(undefined4 *param_1,undefined4 param_2);
void FUN_00133508(undefined4 param_1);
undefined4 FUN_00133528(void);
undefined8 FUN_00133568_iterator_hash_table(void);
undefined4 FUN_00133678(long param_1);
void FUN_001336a8(void);
void FUN_001336c0(void);
undefined8 FUN_001336d8(undefined4 param_1,int param_2,undefined4 *param_3);
undefined4 FUN_00133748_create_purchase_hash_table(long param_1,undefined4 param_2);
undefined8 FUN_00133848(void);
undefined8 FUN_00133888_clear_purchase_cache(void);
int addPurchase_S(long param_1);
undefined4 FUN_001339a8_retrieve_product_from_hashtable(undefined8 param_1);
undefined4 FUN_00133a38_retrieve_purchase_from_hashtable(undefined8 param_1,undefined8 param_2);
undefined8 FUN_00133a88(char *param_1,undefined8 param_2,void *param_3);
void FUN_00133ad8(undefined8 param_1,undefined8 param_2);
bool FUN_00133b00(void *param_1,void *param_2);
undefined4 FUN_00133b20(undefined4 *param_1,undefined4 param_2);
void FUN_00133b58(undefined4 param_1);
undefined4 FUN_00133b78(void);
undefined8 FUN_00133bb8_iterate_hashtable(void);
undefined4 FUN_00133cc8_addPurchase(long param_1);
void FUN_00133d08(void);
void FUN_00133d20(void);
undefined8 FUN_00133d38(undefined4 param_1,int param_2,undefined4 *param_3);
undefined4 FUN_00133da8_medius_pre_RegisterPackets_callback(void);
undefined4 FUN_00133db0_medius_pre_RegisterPackets_callback(void);
undefined4 FUN_00133de0_medius_pre_RegisterPackets_callback(void);
undefined2 FUN_00133de8_medius_pre_RegisterPackets_callback(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined2 *param_4);
undefined4 FUN_00133f80_medius_pre_RegisterPackets_callback(void);
undefined2 FUN_00133f88_medius_pre_RegisterPackets_callback(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined2 *param_4);
undefined4 FUN_00134238_medius_pre_RegisterPackets_callback(void);
undefined2 FUN_00134240_medius_pre_RegisterPackets_callback(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined2 *param_4);
undefined4 FUN_00134700_medius_pre_RegisterPackets_callback(void);
undefined2 FUN_00134708_medius_pre_RegisterPackets_callback(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined2 *param_4);
undefined4 FUN_001348b8_medius_pre_RegisterPackets_callback(void);
undefined2 FUN_001348c0_medius_pre_RegisterPackets_callback(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined2 *param_4);
undefined8 FUN_001349f0(void);
undefined8 RegisterPackets(void);
long FUN_00135618_create_hash_table(MediusHashTable_W *param_1,void *param_2,long param_3);
int FUN_00135840(int param_1,uint param_2,long param_3);
undefined4 FUN_00135880(void);
undefined8 FUN_001358b0(int param_1);
undefined4 FUN_00135a00(long param_1,long param_2,undefined4 *param_3,undefined4 *param_4);
undefined4 FUN_00135bd0(long param_1,long param_2,long param_3);
undefined4 FUN_00135c38(long param_1,long param_2);
undefined4 FUN_00135c58(long param_1,long param_2);
undefined4 FUN_00135c88(long param_1,long param_2);
undefined4 FUN_00135cb8(long param_1,long param_2);
undefined4 FUN_00135e20(long param_1,long param_2);
undefined4 FUN_00135f00(long param_1,long param_2,uint param_3);
undefined4 FUN_00136070(long param_1,undefined8 param_2);
undefined8 FUN_001361a0(long param_1);
undefined4 FUN_00136260(long param_1,undefined8 param_2,long param_3);
undefined4 FUN_00136348(long param_1,long param_2,long param_3);
undefined4 FUN_00136518(long param_1,code *param_2,long param_3);
undefined8 FUN_00136670(undefined4 param_1);
undefined4 FUN_00136888(int param_1,long param_2);
undefined4 FUN_001368b0(int param_1);
undefined4 FUN_00136980(int param_1,uint *param_2);
undefined4 FUN_00136a30(int param_1,undefined4 *param_2);
undefined8 FUN_00136a98(int *param_1,int param_2);
int FUN_00136ae0(int param_1,uint param_2);
long FUN_00136b68(int param_1,long param_2,int **param_3);
undefined8 FUN_00136c80(long param_1);
void ** FUN_00136cc0(int param_1,void *param_2);
undefined8 FUN_00136d60(int param_1,undefined4 *param_2);
undefined8 iCreateAndAllocateMessageID(undefined8 param_1,undefined8 param_2,undefined8 param_3,char *param_4);
undefined8 iGetMessageIDValues(char *param_1,char *param_2,uint *param_3,uint *param_4);
void MGCLSetProcessingState(undefined4 param_1);
undefined4 MGCLGetProcessingState(void);
void MGCLSetClientAddrList(undefined8 *param_1);
void MGCLGetClientAddrList(undefined8 *param_1);
void MGCLResolveAddrCallback(int *param_1);
void MGCLSetQueuedRequest(long param_1,undefined8 *param_2);
void MGCLGetQueuedRequest(undefined8 *param_1);
void MGCLGetQueuedRequestType(undefined4 *param_1);
undefined4 MGCLCheckRequestQueue(void);
void MGCLSetClientConnectCallback_G(undefined4 param_1,undefined4 param_2);
undefined4 FUN_00137250(void);
undefined4 MGCLGetClientConnectCallback(void);
undefined * MGCLGetServerType(void);
void MGCLSetServerType(undefined *param_1);
undefined4 MGCLGetServerPort(void);
void MGCLSetServerPort(undefined4 param_1);
char * MGCLGetServerSessionKey(long param_1);
char * MGCLSetServerSessionKey(long param_1);
void MGCLGetNATServiceAddress(undefined4 *param_1);
void MGCLSetNATServiceAddress(undefined4 *param_1);
undefined4 FUN_001373b0(void);
undefined4 FUN_001373e8(void);
undefined4 GlobalMediusTypeServerCreateGameOnMeCallback(void);
undefined4 GlobalMediusTypeServerEndGameOnMeCallback(void);
undefined4 GlobalMediusTypeServerWorldStatusCallback(void);
undefined4 FUN_001374c8(void);
undefined4 GlobalMediusTypeServerEndGameCallback(void);
undefined4 GlobalMediusTypeServerAuthenticationCallback(void);
undefined4 GlobalMediusTypeServerSessionBeginCallback(void);
undefined4 FUN_00137670_GlobalMedius(void);
undefined4 FUN_001376a8_GlobalMedius(void);
undefined4 GlobalMediusTypeServerSessionEndCallback(void);
undefined4 GlobalMediusTypeServerMoveGameWorldOnMeCallback(void);
undefined4 MGCLAuthenticationSend(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MGCLSessionBegin(long param_1,undefined4 param_2,undefined4 param_3);
undefined4 MGCLSessionEnd_C(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MGCLSessionEnd_similar_C(undefined8 param_1,undefined4 param_2,undefined4 param_3);
long MGCLUpdate(void);
undefined4 MGCLClose(void);
undefined4 MGCLConnect(void *param_1,undefined4 *param_2,undefined8 param_3);
undefined4 FUN_00137ca0_mgcl(long param_1);
void FUN_00137cf0(undefined4 *param_1);
undefined4 MGCLDisconnect_GC(long param_1,undefined4 param_2);
undefined4 MGCLInitialize(undefined4 *param_1,undefined4 *param_2);
undefined4 MGCLSendServerReport(undefined8 param_1);
undefined4 MGCLGetServerTimestamp_GC(undefined4 *param_1);
undefined4 FUN_001381c8_mgcl(long param_1,long param_2);
undefined8 FUN_00138220_mgcl(char *param_1);
undefined8 MGCLGetMGCLVersion(char *param_1);
undefined4 MGCLCreateGameResponse_Q1(undefined8 param_1);
undefined4 MGCLCreateGameResponse_Q2(undefined8 param_1);
undefined4 MGCLJoinGameResponse(undefined8 param_1);
undefined4 MGCLEndGameResponse_Q(undefined8 param_1);
undefined4 MGCLWorldStatusResponse(undefined8 param_1);
undefined4 FUN_00138468_mgcl(undefined8 param_1);
undefined4 MGCLCreateGameOnMeRequest(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MGCLEndGameOnMeRequest(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MGCLSendWorldReportOnMe(undefined8 param_1);
undefined4 MGCLMoveGameWorldOnMe(undefined8 param_1,undefined4 param_2,undefined4 param_3);
undefined4 MGCLSetDefaultConnectParams(long param_1);
undefined4 MGCLSetAuthConnectParams(long param_1,char *param_2,undefined4 param_3,undefined4 param_4,long param_5);
undefined4 FUN_001388e8_mgcl(undefined8 param_1);
void MGCLLocalConnectCallback(undefined4 *param_1);
undefined4 iTerminateString(long param_1,long param_2);
void * lintSetSmallValue(undefined4 *param_1,undefined4 param_2);
uint IsEven(uint *param_1);
undefined4 IsZero(int *param_1);
undefined4 IsOne(int *param_1);
undefined4 IsEqual(int param_1,int param_2);
bool lintGetBit(int param_1,uint param_2);
void lintSetBit(int param_1,uint param_2);
void lintClearBit((int param_1,uint param_2);
void lintIncrement(uint *param_1,uint param_2);
void lintDecrement(uint *param_1,uint param_2);
void * FUN_00138c68(void *param_1,void *param_2,undefined8 param_3);
void * lintSub(void *param_1,void *param_2,undefined8 param_3);
void * MOD(void *param_1,void *param_2,undefined8 param_3);
void * QUO_G(void *param_1,void *param_2,void *param_3);
void QRMOD(void *param_1,void *param_2,undefined8 param_3,undefined8 param_4);
void * GCD(void *param_1,void *param_2,void *param_3);
void * EMOD(void *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4);
undefined4 lintIsbSPRP_G(undefined8 param_1,undefined8 param_2);
void lintRandomize(int param_1,uint param_2);
long FUN_001394b0(undefined8 param_1);
void lintPrime(undefined8 param_1,long param_2);
void * EMODM(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4);
void RSAGenerateKeyPair(void *param_1,undefined8 param_2,undefined8 param_3,uint param_4);
int lintGetBits(int param_1);
bool IsGreater(int param_1,int param_2);
bool IsGreater_G_smaller?(int param_1,int param_2);
bool IsNotGreater(int param_1,int param_2);
bool IsNotGreater_G_smaller?(int param_1,int param_2);
void ShiftRight(uint *param_1,ulong param_2);
void ShiftLeft(long param_1,ulong param_2);
void lintAddIP(uint *param_1,uint *param_2);
void lintAddIPR(uint *param_1,uint *param_2,ulong param_3);
void lintSubIP(uint *param_1,uint *param_2);
void lintSubIPR(uint *param_1,uint *param_2,ulong param_3);
void MODIP(undefined8 param_1,undefined8 *param_2);
void MULT(undefined4 *param_1,uint *param_2,uint *param_3);
void XMOD(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4);
int FUN_0013a830(int param_1,long param_2,int param_3);
void MontPro(undefined4 *param_1,uint *param_2,uint *param_3,uint *param_4,int param_5);
void RCInitialize(undefined4 *param_1,int param_2);
void RCSaltyInitialize(undefined4 *param_1,int param_2,undefined4 param_3);
void RCEncrypt(int *param_1,byte *param_2,int param_3);
void RCDecrypt(int *param_1,byte *param_2,int param_3);
void * RSAEncryptBlock(void *param_1,undefined8 param_2,void *param_3,void *param_4);
void * RSADecryptBlock(void *param_1,void *param_2,void *param_3,void *param_4);
int RSAEncrypt(undefined8 param_1,int param_2,int param_3,int param_4);
int RSADecrypt(undefined8 param_1,undefined8 param_2,int param_3,int param_4,uint param_5);
void SHAInit(undefined8 *param_1);
void * SHAUpdate_G(undefined8 *param_1,undefined8 *param_2,ulong param_3);
void SHAFinal(undefined8 param_1,undefined8 param_2,ulong param_3);
void endianTest(undefined4 *param_1);
void SHSTransform(uint *param_1);
void longReverse(undefined8 *param_1,int param_2);
void SHAtoByte(undefined *param_1,undefined8 *param_2,int param_3);
void KM_MD5(undefined8 param_1,undefined8 param_2,undefined8 param_3);
void KM_Salted_MD5(long param_1,long param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5);
void md5Init(undefined4 *param_1);
void * md5Update(undefined8 param_1,undefined8 *param_2,ulong param_3);
void * md5Final(undefined8 param_1,undefined8 param_2);
void md5Transform(int *param_1);
void md5Encode(undefined *param_1,undefined8 *param_2,int param_3);
void rt_crypt_resolve_interface(void);
undefined4 IsNullRCKey(long param_1);
undefined4 * NewKeyChain(void);
void DeleteKeyChain(long param_1);
void AppendKeyChain(long param_1,int *param_2);
void GetKeyChain(long param_1,uint param_2);
void RemoveKeyChain(long param_1,long param_2);
void FUN_0013e880_KM|Net(undefined8 param_1,undefined8 param_2);
void * FUN_0013e8b8(void *param_1,void *param_2);
char * KM_GetVersionStringPtr_G(void);
uchar * KM_SHA1(uchar *d,size_t n,uchar *md);
void KM_Salted_SHA1(long param_1,long param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6);
undefined4 KM_Create(long param_1,long param_2,undefined8 param_3);
void KM_SetLocalClientID_G(undefined8 param_1,undefined4 param_2);
undefined4 KM_SetPublicKey(undefined8 param_1,undefined8 param_2,undefined8 param_3);
undefined4 KM_GetPublicKey(undefined8 param_1,undefined8 param_2,long param_3);
undefined4 KM_SetLocalKeyPair(undefined8 param_1,undefined8 param_2);
undefined4 KM_SetGameSessionKey(undefined8 param_1,undefined4 param_2,undefined8 param_3);
undefined4 KM_GetGameSessionKey(undefined8 param_1,undefined8 param_2,long param_3);
undefined4 KM_AddSymmetricKey_Q(undefined8 param_1,undefined8 param_2,undefined8 param_3);
undefined4 KM_GetSymmetricKey(undefined8 param_1,undefined8 param_2,long param_3);
undefined8 KM_CompareSymmetricKey_G(undefined8 param_1,undefined8 param_2,undefined8 param_3);
void * KM_DeleteSymmetricKey_G(undefined8 param_1,undefined8 param_2);
undefined4 KM_CopyKeys(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4);
undefined4 KM_DigiSign(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,long param_5);
undefined4 KM_DigiVerify_G(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4);
void KM_DeleteKeys_G(undefined8 param_1,undefined8 param_2);
int * KM_Destroy(void);
void KM_Cleanup_G(long param_1);
void InitializePRNG(void);
void KM_CreateRandomRCKey(int param_1);
uint KM_Encrypt(undefined8 param_1,long param_2,long param_3,size_t param_4);
uint KM_Encrypt2(long param_1,long param_2,long param_3,size_t param_4);
int KM_Decrypt(undefined8 param_1,undefined8 param_2,uint param_3,undefined8 param_4,size_t param_5);
int KM_Decrypt2_G(long param_1,long param_2,uint param_3,undefined8 param_4,size_t param_5);
void * KM_RSAAdjust(void *param_1,void *param_2);
void GetSoftwareKeyPair(undefined8 *param_1,undefined8 *param_2);
undefined4 rt_ac_get_total_interrupt_handlers(long param_1);
undefined4 rt_ac_get_active_thread_count(long param_1);
undefined4 rt_ac_get_remenant_thread_count(long param_1);
undefined4 rt_ac_get_thread_info(s32 param_1,undefined8 *param_2,ulong param_3,long param_4);
undefined4 rt_ac_iop_memory_request(void *param_1,undefined8 param_2,long param_3);
undefined8 rt_ac_free_iop_data(void);
undefined8 rt_ac_iop_query(char *param_1,long param_2,uint *param_3);
undefined8 rt_ac_iop_relocatable_tweak(uint *param_1,int param_2);
undefined8 get_n_intc(s32 param_1,long param_2,int *param_3);
void rt_msg_client_resolve_interface(void);
void NetUseClientServer(void);
undefined4 rt_msg_client_get_client_security_mode(void);
undefined8 rt_msg_mutex_lock(void);
void rt_msg_mutex_unlock(void);
undefined * rt_msg_client_get_version_ptr_G(void);
char * rt_msg_client_get_build_timestamp_g(void);
long rt_msg_client_startup_G(undefined8 param_1);
long rt_msg_client_shutdown_G(void);
long rt_msg_client_connect(undefined8 param_1,undefined8 param_2);
long rt_msg_client_disconnect(undefined8 param_1,undefined8 param_2);
long rt_msg_client_disconnect_all(void);
long rt_msg_client_update(undefined8 param_1,undefined8 param_2);
long rt_msg_client_update_all(undefined8 param_1);
long rt_msg_client_send_target(undefined8 param_1,long param_2,ulong param_3,long param_4,ulong param_5,long param_6);
long rt_msg_client_send_client_set_G(undefined8 param_1,ulong param_2,ulong param_3,long param_4,ulong param_5,long param_6,ulong param_7,long param_8);
int rt_msg_client_get_buffer_status_G(undefined8 param_1,int *param_2,int *param_3,uint *param_4,uint *param_5);
long rt_msg_client_get_local_ip_G(undefined8 param_1);
long rt_msg_client_get_broadcast_ip(undefined8 param_1);
long rt_msg_client_get_host_by_name(long param_1,undefined8 param_2);
long rt_msg_client_get_connection_ip(undefined8 param_1,undefined4 *param_2);
long rt_msg_client_set_recv_flag(undefined8 param_1,byte param_2);
long rt_msg_client_receive_broadcasts(undefined8 param_1,long param_2);
long rt_msg_client_get_metrics(long param_1,undefined4 *param_2);
long rt_msg_client_set_send_aggregation_time(undefined8 param_1,undefined4 param_2);
long rt_msg_client_set_server_send_aggregation_time(undefined8 param_1,undefined2 param_2);
void * rt_msg_client_set_default_connect_options_G(undefined4 *param_1);
long rt_msg_client_display_comm_state(void);
long rt_msg_client_get_interface_data(undefined8 param_1,long param_2);
long rt_msg_client_iconnect(uint *param_1,uint *param_2);
void rt_msg_client_idisconnect(undefined8 param_1,undefined param_2);
long rt_msg_client_update_single(undefined8 param_1,long param_2);
long rt_msg_client_update_connection(undefined8 param_1,long param_2);
long rt_msg_client_update_comm_wait(undefined8 param_1);
long rt_msg_client_update_send(undefined8 param_1,undefined8 param_2);
int rt_msg_client_create_channel_info(undefined4 param_1,undefined8 param_2,undefined8 param_3);
void rt_msg_client_destroy_channel_info(long param_1);
long rt_msg_client_create_new_connection_index(uint *param_1,uint param_2,uint param_3,uint param_4);
int rt_msg_client_free_connection_index(ulong param_1,undefined8 param_2);
undefined4 rt_msg_client_is_valid_connection(long param_1);
undefined8 rt_msg_client_is_valid_connection_id(uint param_1);
undefined4 rt_msg_client_get_connection(uint param_1);
undefined8 rt_msg_client_get_valid_connection(void);
bool rt_msg_client_is_valid_channel(int param_1);
void rt_msg_client_store_pkey_msg_in_send_buf(undefined8 param_1);
long rt_msg_client_store_connect_msg_in_send_buf(uint *param_1);
int rt_msg_client_calc_connect_msg_size(int param_1);
undefined4 rt_msg_client_calc_connect_aux_udp_msg_size(void);
long rt_msg_client_store_connect_aux_udp(int *param_1,undefined8 param_2);
long rt_msg_client_store_msg_in_send_buf(undefined8 param_1,int param_2,int param_3,long param_4,ulong param_5,int param_6);
long rt_msg_client_create_send_buf_space(undefined8 param_1,uint param_2);
long rt_msg_client_process_recv_buf(undefined8 param_1,undefined8 param_2);
undefined8 rt_msg_client_process_message(undefined8 param_1,undefined8 param_2,uint param_3,int param_4,int param_5);
long FUN_00143398(uint *param_1,int param_2,undefined8 param_3,uint param_4);
long FUN_00143608(int param_1,undefined8 param_2,undefined8 param_3,ulong param_4);
undefined8 rt_msg_client_process_connect_complete(undefined4 *param_1,undefined8 param_2,undefined8 param_3,uint param_4);
undefined4 rt_msg_client_process_client_connect_notify(uint *param_1,int param_2,undefined8 param_3,ulong param_4);
undefined4 rt_msg_client_process_app_message(undefined4 *param_1,int param_2,int param_3,uint param_4);
undefined8 rt_msg_client_process_server_echo_message(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4);
undefined8 rt_msg_client_process_disconnect_message_G(undefined4 *param_1,undefined8 param_2,undefined *param_3,long param_4);
long rt_msg_client_process_crypt_key_peer(undefined8 param_1,int param_2,int param_3,int param_4);
long rt_msg_client_process_info_aux_udp(undefined8 param_1,undefined8 param_2,undefined8 param_3,ulong param_4);
undefined8 rt_msg_client_process_system_message(int param_1,undefined8 param_2,undefined *param_3,int param_4);
undefined8 rt_msg_client_process_cheat_query(undefined8 param_1,undefined8 param_2,undefined *param_3,ulong param_4);
undefined8 rt_msg_client_process_memory_poke(undefined8 param_1,undefined8 param_2,undefined8 param_3,ulong param_4);
long rt_msg_client_send_buffer(undefined8 param_1,int param_2,int param_3,uint param_4);
long rt_msg_client_send_channel_circ_buf(undefined8 param_1);
long rt_msg_client_recv_channel_circ_buf(int *param_1);
long rt_msg_client_set_scratch_buf_min_size(uint param_1);
long rt_msg_client_transfer_last_msg(int param_1);
uint rt_msg_client_calc_send_size(byte *param_1,uint param_2,uint param_3);
long rt_msg_client_channel_send_buf(int *param_1,undefined8 param_2,ulong param_3,undefined8 param_4);
undefined8 rt_msg_client_get_encryption_key(ulong param_1);
bool rt_msg_client_have_encryption_key(void);
undefined4 rt_msg_client_is_server_compatible(ulong param_1,byte param_2,byte param_3);
undefined8 rt_msg_client_send_server_message(undefined8 param_1,void *param_2,ulong param_3,ulong param_4);
long rt_msg_client_set_send_max_message_len(undefined8 param_1,undefined2 param_2);
long rt_msg_client_peer_query_single(undefined8 param_1,undefined2 param_2,undefined param_3);
long rt_msg_client_peer_query_list(undefined8 param_1,ulong param_2,int param_3,void *param_4,undefined param_5);
long rt_msg_client_wallclock_query(undefined8 param_1);
long rt_msg_client_timebase_query(long param_1,undefined8 param_2);
undefined8 rt_msg_client_process_timebase_query(undefined8 param_1,undefined8 param_2,undefined8 param_3);
undefined4 rt_msg_client_process_startup_info_notify(undefined4 *param_1,undefined8 param_2,byte *param_3);
long rt_msg_client_send_systemmsg(undefined8 param_1,undefined *param_2);
undefined8 rt_msg_client_process_connect_require(undefined4 *param_1,undefined8 param_2,undefined8 param_3);
long rt_msg_client_send_token_msg_G(undefined8 param_1,undefined2 param_2,int param_3);
long rt_msg_client_send_token_set_msg(undefined8 param_1,ulong param_2,ulong param_3,void *param_4,int param_5);
undefined4 rt_msg_client_process_server_token_notify(undefined4 *param_1,int param_2,undefined8 param_3,uint param_4);
long rt_msg_client_send_hello(undefined4 *param_1);
long rt_msg_client_process_server_hello(undefined8 param_1,undefined8 param_2,undefined8 param_3,ulong param_4);
undefined4 rt_msg_client_process_peer_query_notify(undefined4 *param_1,undefined8 param_2,byte *param_3);
undefined8 rt_msg_client_process_peer_query_list_notify(undefined4 *param_1,undefined8 param_2,byte *param_3);
void DorkFunk(void);
undefined8 rt_list_buf_create(long param_1,ulong param_2);
void * rt_list_buf_destroy(long param_1);
void rt_list_buf_clear(long param_1);
long rt_list_buf_insert(long param_1,long param_2,long param_3);
long rt_list_buf_set_new_head(long param_1,undefined8 param_2);
long rt_list_buf_remove(long param_1,int *param_2);
long rt_list_buf_append_data(long param_1,undefined8 param_2,long param_3,size_t param_4);
int FUN_00146cf8_in_rt_list_buf_set_new_head(long param_1);
int rt_list_buf_get_tail(long param_1);
long FUN_00146d80(long param_1,long param_2);
long FUN_00146f00(long param_1,uint param_2);
undefined8 rt_list_buf_remove(int param_1);
undefined4 FUN_001470a8(int param_1,long param_2);
undefined4 pool_alloc_G(uint *param_1,long param_2);
undefined4 pool_alloc_G2(uint *param_1,long param_2);
long FUN_00147170_in_rt_list_buf_insert(undefined8 param_1,undefined8 param_2,uint param_3);
undefined4 FUN_00147240_in_rt_list_buf_remove(undefined8 param_1,int param_2,long param_3);
undefined8 FUN_001472f0_in_rt_list_buf_remove(uint *param_1);
undefined8 FUN_00147358_in_rt_list_buf_remove(int param_1);
void FUN_001473e0_Net|rt(void);
void rt_p2p_resolve_interface(void);
long rt_p2p_create(undefined4 *param_1,void **param_2);
void rt_p2p_destroy_G(undefined4 *param_1);
undefined4 rt_p2p_get_current_address_type_G(long param_1,uint param_2,undefined4 *param_3);
long rt_p2p_get_peer_address(long param_1,uint param_2,int param_3,undefined8 param_4,undefined8 param_5);
long rt_p2p_get_my_address(long param_1,int param_2,undefined8 param_3,undefined8 param_4);
undefined4 rt_p2p_get_my_peer_index(long param_1,long param_2);
undefined4 rt_p2p_get_host_index_G(long param_1,long param_2);
undefined4 rt_p2p_get_virtual_port_G(long param_1,long param_2);
undefined4 rt_p2p_get_buffer_stats(long param_1,long param_2,long param_3,long param_4,long param_5);
undefined4 rt_p2p_get_peer_buffer_stats_G(long param_1,uint param_2,long param_3,long param_4,long param_5,long param_6);
undefined8 rt_p2p_set_send_aggregation_G(long param_1);
undefined4 rt_p2p_host(long param_1,long param_2);
long rt_p2p_incoming_peer(long param_1,undefined8 param_2);
long rt_p2p_connect(long param_1,undefined8 param_2,undefined4 param_3);
void rt_p2p_disconnect(long param_1);
undefined4 rt_p2p_send(long param_1);
long rt_p2p_update(long param_1);
long rt_p2p_send(long param_1,uint param_2,ushort param_3,undefined8 param_4);
long rt_p2p_send_list(long param_1,uint param_2,uint param_3,long param_4,ushort param_5,undefined8 param_6);
long rt_p2p_receive_broadcasts(long param_1,undefined4 param_2);
undefined8 rt_p2p_send_to(long param_1,undefined8 param_2);
undefined4 rt_p2p_get_max_peers_G(long param_1,long param_2);
undefined4 rt_p2p_set_max_peers_G(long param_1,undefined2 param_2);
undefined8 rt_p2p_set_overlay_type(long param_1,byte param_2,ulong param_3);
long rt_p2p_join_overlay_G(long param_1,byte param_2);
long rt_p2p_quit_overlay(long param_1,byte param_2);
long rt_p2p_quit_all_overlays(long param_1);
long rt_p2p_ignore_peer_in_overlay_G(long param_1,byte param_2,ushort param_3,ulong param_4);
undefined4 rt_p2p_get_overlay_peer_count_G(long param_1,uint param_2,long param_3);
undefined4 rt_p2p_is_peer_in_overlay_G(long param_1,uint param_2,uint param_3,long param_4);
undefined4 rt_p2p_send_overlay_G(long param_1,uint param_2,uint param_3,uint param_4,uint param_5,long param_6);
uint rt_p2p_pack_type(uint param_1,uint param_2);
void rt_p2p_unpack_type(undefined8 param_1,uint *param_2,ushort *param_3);
void rt_udp_event_cb(int param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5);
void rt_udp_data_cb(int param_1,undefined8 param_2,int param_3,int param_4,undefined2 param_5,undefined8 param_6,undefined8 param_7);
void rt_p2p_send_peer_info(undefined8 param_1,undefined8 param_2,uint param_3);
void rt_p2p_handle_connect_event(undefined8 param_1,undefined8 param_2);
void rt_p2p_handle_connected_event(undefined8 param_1,int param_2);
void rt_p2p_handle_timeout_event(undefined8 param_1,int param_2,undefined8 param_3);
void rt_p2p_handle_closed_event(undefined8 param_1,undefined8 param_2,undefined8 param_3);
void rt_p2p_handle_reset_event(undefined8 param_1,undefined8 param_2,undefined8 param_3);
void rt_p2p_handle_error_event(undefined8 param_1,undefined8 param_2,undefined8 param_3);
undefined4 rt_p2p_get_peer_by_address(long param_1,undefined8 *param_2,ushort *param_3);
uint rt_p2p_get_peer_by_connection(int param_1,int param_2);
void rt_p2p_get_my_peer_status(int param_1,int *param_2,undefined2 *param_3);
ushort rt_p2p_find_free_peer_index(long param_1);
long rt_p2p_set_peer_update_bit_G(undefined8 param_1,ushort param_2,undefined2 *param_3);
undefined8 NetMapMsgClientError(undefined8 param_1,undefined8 param_2,ulong param_3);
long rt_p2p_process_new_peer(undefined8 param_1,undefined8 param_2,undefined8 *param_3);
undefined8 rt_p2p_process_coordinate_data(undefined8 param_1,uint param_2);
undefined8 rt_p2p_process_connect_complete(undefined8 param_1,uint param_2);
undefined8 rt_p2p_process_broadcast_update(int param_1,uint param_2,undefined4 *param_3);
undefined8 rt_p2p_process_connection_detached(int param_1,undefined8 param_2,uint *param_3);
undefined8 rt_p2p_process_broadcast_disconnect(int param_1,undefined8 param_2,uint *param_3);
undefined8 rt_p2p_process_local_broadcast_test_G(int param_1,uint param_2);
undefined8 rt_p2p_process_overlay_type(int param_1,undefined8 param_2,undefined8 *param_3);
long rt_p2p_process_join_overlay(long param_1,uint param_2,undefined4 *param_3);
long rt_p2p_process_join_response(long param_1,uint param_2,uint *param_3);
long rt_p2p_process_quit_overlay(long param_1,uint param_2,uint *param_3);
undefined8 rt_p2p_process_ignore_update(int param_1,undefined8 param_2,undefined8 *param_3);
undefined8 rt_p2p_process_grid_data(undefined8 param_1,uint param_2,int param_3,int param_4);
long rt_p2p_complete_connection(undefined8 param_1);
undefined8 rt_p2p_send_local_broadcast_tests(undefined4 *param_1);
undefined8 rt_p2p_isend(undefined4 *param_1,int param_2,undefined2 param_3,undefined8 param_4);
undefined8 rt_p2p_isend_list(undefined4 *param_1,long param_2,uint param_3,undefined2 param_4);
undefined8 rt_p2p_send_my_broadcast_flag(undefined8 param_1,uint param_2);
long rt_p2p_generic_disconnect(undefined8 param_1,undefined8 param_2,undefined8 param_3);
undefined4 rt_p2p_determine_new_host(int param_1,long param_2);
undefined8 rt_p2p_send_connection_detached_to_host(long param_1,undefined2 param_2,undefined2 param_3);
undefined8 rt_p2p_send_broadcast_disconnect(undefined8 param_1,ushort param_2);
undefined8 rt_p2p_notify_peers_disconnect_forwarding(int param_1,undefined8 param_2,long param_3,undefined2 param_4,uint param_5);
undefined8 rt_p2p_notify_peers_disconnect(int param_1,uint param_2,uint param_3);
undefined8 rt_p2p_save_backlog_connection(undefined4 *param_1,int param_2);
long rt_p2p_find_backlog_connection(undefined4 *param_1,undefined8 *param_2,undefined4 *param_3);
undefined8 rt_p2p_timeout_backlog_connection(undefined4 *param_1);
undefined8 rt_p2p_generate_grid_fill_empties(int param_1,char param_2,char *param_3);
long rt_p2p_generate_grid_add_peer(undefined8 param_1,byte param_2);
long rt_p2p_generate_grid(undefined8 param_1,uint param_2);
undefined8 rt_p2p_get_peer_grid_edges(int param_1,ulong param_2,ulong param_3,int *param_4);
long rt_p2p_update_grid(undefined8 param_1,int **param_2,uint param_3);
long rt_p2p_send_token_msg_G(long param_1,undefined2 param_2,undefined8 param_3,undefined param_4,uint param_5);
long rt_p2p_send_token_list_msg(long param_1,undefined8 param_2,undefined param_3,undefined8 param_4,undefined param_5,undefined8 param_6,undefined8 param_7,uint param_8);
undefined4 rt_p2p_process_token_data(int param_1,uint param_2,int param_3,uint param_4);
long rt_p2p_token_event_notify_G(undefined4 *param_1,undefined2 param_2,undefined2 param_3,long param_4,undefined param_5,undefined8 param_6,long param_7);
undefined8 rt_p2p_timebase_query(undefined8 param_1);
long rt_p2p_process_timebase_data(long param_1,uint param_2,int param_3);
long rt_p2p_get_latency_info(long param_1,uint param_2,undefined8 param_3);
undefined8 rt_p2p_set_host_invactivity_timeout_session(int param_1);
undefined8 rt_p2p_set_host_inactivity_timeout_connection(int param_1,undefined8 param_2);
undefined2 rt_udp_get_sequence_id(int param_1);
void FUN_0014cfe0(undefined8 param_1,int param_2,long param_3);
void FUN_0014d108(char *param_1,int param_2,int param_3);
undefined8 rt_udp_ack_list_flush(undefined4 *param_1,int param_2);
undefined8 rt_udp_buffer_ack(undefined8 param_1,int param_2,ushort param_3);
ushort * rt_udp_get_first_sub_header(ushort *param_1);
undefined4 GetUDPSecurityMode(void);
int randomNonZero(long param_1);
void rt_udp_resolve_interface(void);
char * rt_udp_get_version_string(void);
long rt_udp_create(long param_1,undefined4 *param_2);
void rt_udp_destroy(long param_1);
undefined8 rt_udp_set_buffer_size_G(long param_1,long param_2,long param_3,long param_4);
undefined8 rt_udp_set_aggregation_interval_G(long param_1,undefined4 param_2);
undefined4 rt_udp_get_buffer_size_G(long param_1,long param_2,int param_3,int *param_4);
undefined8 rt_udp_set_aggregation_interval_G(long param_1,undefined4 *param_2);
undefined8 rt_udp_get_virtual_port_G(long param_1,undefined2 *param_2);
undefined4 rt_udp_get_buffer_stats(long param_1,long param_2,int param_3,long param_4,long param_5,long param_6);
long rt_udp_resolve_address(long param_1,undefined8 *param_2);
undefined8 rt_udp_get_resolved_address(long param_1,undefined8 param_2,undefined8 param_3);
undefined8 rt_udp_get_local_address(long param_1,undefined4 *param_2,undefined4 *param_3);
undefined4 rt_udp_get_address(long param_1,long param_2,undefined4 *param_3,undefined4 *param_4);
undefined8 rt_udp_disable_nat_service_heartbeat_G(long param_1);
undefined4 rt_udp_connect(long param_1,undefined8 *param_2,long param_3);
void rt_udp_disconnect(long param_1,long param_2);
void rt_udp_set_peer_id(long param_1,undefined4 param_2);
long rt_udp_send(long param_1,long param_2,uint param_3,long param_4);
long rt_udp_send_list(long param_1,int **param_2,int param_3,uint param_4,undefined8 *param_5);
long rt_udp_send_unconnected(long param_1,undefined8 param_2,long param_3,long param_4);
long rt_udp_broadcast(long param_1,ulong param_2,long param_3);
undefined4 rt_udp_listen_G(long param_1,undefined4 param_2);
undefined4 rt_udp_accept(long param_1,long param_2);
undefined4 rt_udp_deny_G(long param_1,long param_2);
long rt_udp_pre_accept(long param_1,undefined8 param_2,undefined8 param_3);
long rt_udp_event_process(long param_1);
long rt_udp_event_check_G(long param_1);
void rt_udp_add_conn_to_list(int param_1,int param_2);
void rt_udp_del_conn_from_list(int param_1,int param_2);
int * rt_udp_find_free_connection(int param_1);
void * rt_udp_setup_packet_sub_header(int param_1,long param_2,ushort param_3,ushort param_4,ushort *param_5);
undefined4 rt_udp_buffer_data_for_send(undefined8 param_1,undefined8 param_2,undefined4 *param_3,ushort param_4,undefined4 param_5);
long rt_udp_append_data_to_packet(undefined8 param_1,undefined8 param_2,ushort param_3,long param_4,undefined8 param_5);
undefined8 rt_udp_get_packet_seed(long param_1,undefined4 *param_2);
undefined8 rt_udp_set_packet_seed(long param_1,undefined4 param_2);
long rt_udp_send_messages(undefined4 *param_1,int param_2);
void rt_udp_remove_non_delivery_critical_packets(undefined8 param_1,int *param_2);
undefined8 rt_udp_send_broadcasts(undefined4 *param_1);
undefined8 rt_udp_receive_messages(undefined8 param_1);
long rt_udp_process_message(undefined8 param_1,undefined8 param_2,long param_3,uint param_4);
long rt_udp_process_version_exchange(undefined8 param_1,undefined8 param_2,ushort *param_3,undefined8 param_4);
long rt_udp_send_version_exchange(undefined8 param_1,undefined8 param_2);
long rt_udp_process_new_connect(undefined8 param_1,undefined4 *param_2,undefined8 param_3,undefined8 param_4,undefined4 param_5);
undefined8 rt_udp_process_disconnect(undefined8 param_1,undefined8 param_2,long param_3);
undefined8 rt_udp_process_reset(long param_1);
undefined8 rt_udp_process_heartbeat(undefined8 param_1,void *param_2,long param_3);
long rt_udp_process_acknowlege(long param_1,undefined8 param_2,uint param_3,undefined2 *param_4);
long rt_udp_process_data(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4);
undefined8 rt_udp_process_unconnected_data(int param_1,ushort *param_2,undefined8 param_3,undefined4 param_4);
int * rt_udp_find_connection(long param_1,ushort *param_2,undefined8 param_3,int param_4);
undefined8 rt_udp_send_reset(undefined4 *param_1,int param_2);
void rt_udp_send_ack(undefined8 param_1,undefined8 param_2,undefined8 param_3);
undefined4 rt_udp_is_duplicate_packet(long param_1,undefined8 param_2,undefined4 *param_3);
undefined4 rt_udp_calculate_rto(long param_1,ulong param_2);
long rt_udp_create_shared_channel_data(undefined8 param_1);
undefined8 rt_udp_destroy_shared_channel_data(undefined4 *param_1);
void rt_udp_uber_resolve_cb(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,long param_6);
undefined4 rt_udp_set_inactivity_timeout_G(long param_1);
undefined8 rt_udp_get_inactivity_timeout(undefined4 *param_1);
undefined4 rt_udp_set_connection_inactivity_timeout(int param_1,long param_2);
undefined4 rt_udp_get_latency_info(long param_1,long param_2);
long rt_udp_mgr_create_G(long param_1,undefined4 *param_2);
undefined8 rt_udp_mgr_destroy_G(void);
undefined4 rt_udp_mgr_get_channel_ref(undefined4 *param_1,long param_2);
undefined4 rt_udp_mgr_release_channel_ref_G(short param_1);
undefined4 rt_udp_mgr_find_channel_ref(short param_1,long param_2);
undefined4 NetGetClientVersion(long param_1);
undefined4 FUN_00151b68(long param_1);
undefined4 NetSetDefaultInitializeParams(long param_1);
long NetInitialize(long param_1,long param_2);
long NetClose(void);
long NetGetAverageDelayToClient(undefined8 param_1,undefined8 param_2);
long FUN_00151ea0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5);
long NetSetSendAggregationInterval(undefined8 param_1,undefined8 param_2,undefined8 param_3);
long FUN_00151fc0(long param_1);
long NetRegisterMessage_G(undefined8 param_1,undefined8 param_2,undefined8 param_3);
long NetRegisterApplicationMessage(undefined8 param_1,undefined8 param_2);
long NetSendMessage(undefined param_1,int param_2,undefined4 param_3,undefined8 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7);
long NetSendApplicationMessage(undefined param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6);
long FUN_001522d0_net(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4);
undefined4 FUN_00152368(long param_1);
void NetRegisterMemoryCallbacks(void);
long FUN_001523b0(undefined8 param_1,undefined8 param_2);
long NetConnect(undefined8 param_1,undefined8 param_2);
undefined4 NetSetDefaultJoinParams(long param_1);
long NetHostPeerToPeer(undefined8 param_1,undefined8 param_2);
long NetSetNATServiceAddr_G(undefined8 param_1);
long NetSetDefaultResolveAddrParams(undefined8 param_1);
long NetResolveAddr(undefined8 param_1,undefined8 param_2);
long FUN_001526a8(undefined8 param_1,undefined8 param_2);
long NetSetMyClientReceiveBroadcast_G(undefined8 param_1,undefined8 param_2);
long NetPing_proxy_G(undefined8 param_1,undefined8 param_2,undefined8 param_3);
long FUN_00152808(undefined8 param_1,undefined8 param_2);
long FUN_00152880(undefined8 param_1,undefined8 param_2);
long FUN_00152910_net(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8);
long FUN_001529f8_net(undefined8 param_1,undefined8 param_2,undefined8 param_3);
long FUN_00152a80_net(undefined8 param_1);
long FUN_00152ae8_net(undefined8 param_1,undefined8 param_2);
long FUN_00152b70_net(long param_1,undefined8 param_2);
long NetResolveAddr_G(undefined8 param_1,undefined8 param_2,undefined8 param_3);
long FUN_00152c80_net(long param_1,long param_2,undefined8 param_3);
long NetGetMyIpAddress(undefined8 param_1);
long NetGetMyNetAddress_G(undefined8 param_1,undefined8 param_2);
long FUN_00152de8(undefined8 param_1,undefined8 param_2,undefined8 param_3);
long NetGetMyClientIndex(undefined8 param_1,undefined8 param_2);
long FUN_00152ed8(undefined8 param_1,undefined8 param_2);
undefined4 NetGetLocalTime(long param_1);
undefined4 NetGetTime(long param_1,long param_2);
long NetGetConnectStatus_G(undefined8 param_1,undefined8 param_2);
long NetGetValidClientCount_G(undefined8 param_1,undefined8 param_2);
undefined4 NetSetDefaultStreamMediaParams(long param_1);
long FUN_00153120(undefined8 param_1,undefined8 param_2);
long FUN_00153190_net(undefined8 param_1,undefined8 param_2);
long FUN_00153208(undefined8 param_1,undefined8 param_2);
long NetUpdate(void);
long NetGetNetUpdateErrors(undefined8 param_1);
long FUN_00153330(void);
long NetLeave_G(undefined8 param_1);
undefined4 NetSetDefaultDisconnectParams(long param_1);
long NetDisconnect(undefined8 param_1);
long NetStreamMediaJoinChannel(undefined8 param_1,undefined8 param_2);
long NetStreamMediaEndRecording_0x30(undefined8 param_1,undefined8 param_2);
long NetStreamMediaGetChannelInfo(undefined8 param_1,undefined8 param_2,undefined8 param_3);
long NetStreamMediaGetChannelInfo_x38(undefined8 param_1,undefined8 param_2,undefined8 param_3);
long NetStreamMediaEndRecording(undefined8 param_1,undefined8 param_2);
long NetStreamMediaGetCurrentChannelState(undefined8 param_1,undefined8 param_2);
long FUN_00153770(long param_1);
long FUN_001537e0(undefined8 param_1);
long NetJoin(undefined8 param_1,undefined8 param_2);
long FUN_001538c0_net(undefined8 param_1,undefined8 param_2);
long FUN_00153970_net(undefined8 param_1);
undefined4 NetSetDefaultNetUsePeerToPeerInParams_x114(long param_1);
long FUN_00153a60(undefined8 param_1);
long FUN_00153b00(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6);
undefined4 NetSetDefaultNetUsePeerToPeerInParams(long param_1);
long NetSendMessage_G(undefined8 param_1,undefined8 param_2);
long FUN_00153ca8_net(void *param_1,size_t param_2);
long FUN_00153d28_net(long param_1,long param_2,long param_3,ulong param_4,long param_5,long param_6);
undefined4 BinaryAddressToNetAddress(long param_1,undefined8 param_2,long param_3,uint param_4,int param_5);
undefined4 StringAddressToNetAddress(long param_1,undefined8 param_2,long param_3,uint param_4,int param_5);
undefined4 NetAddressToBinaryAddress(long param_1,long param_2,long param_3,long param_4,long param_5);
undefined4 NetIAddressToStringAddress(long param_1,long param_2,long param_3,ulong param_4,long param_5,long param_6);
long FUN_001542a0_net(undefined4 param_1,undefined4 param_2,undefined4 param_3);
long FUN_00154338_net(undefined8 param_1);
undefined8 FUN_001543b0(undefined4 *param_1);
long FUN_00154408_net(void);
long FUN_00154468(undefined8 param_1);
void FUN_001546c8(undefined4 param_1,undefined4 param_2);
long LANFindGetMyPeerDesc(undefined4 *param_1,undefined8 param_2);
uint LANFindPacketHandler(void);
uint LANFindResultsPacketHandler_G(void);
undefined8 SendLANFindResultsOnExchange(undefined4 *param_1,int *param_2,undefined8 param_3);
undefined8 SendLANFindReply(short **param_1);
long FUN_00154ef0(undefined4 *param_1,int param_2);
long InitLANFindReply(undefined4 *param_1,int param_2,undefined8 param_3);
undefined8 OnReceivedLANFindRequest(int param_1,undefined4 *param_2);
undefined8 OnReceivedLANFindReply_G(undefined2 *param_1,undefined4 *param_2);
void ClearInterfacePointers(void);
undefined4 FUN_00155510(long param_1);
undefined4 NetBitMaskIsSet(long param_1,int param_2,uint *param_3);
undefined4 NetBitMaskSet(long param_1,int param_2);
undefined4 NetBitMaskSet_WithTilde(long param_1,int param_2);
undefined4 NetGenerateClientList(int *param_1,long param_2);
undefined4 NetGenerateJoinedClientList(int *param_1,long param_2);
void FUN_00155818(undefined4 *param_1);
void FUN_00155868(undefined4 *param_1);
void FUN_001558e0(void);
undefined4 GetSoftwareID(void);
long NetIGetMyIntIP(undefined8 param_1);
undefined8 NetIGetMyExtIP(undefined8 param_1);
void SendMyClientStatus(undefined8 param_1,long param_2);
int RtMsgToDmeConnectionIndex(ulong param_1);
undefined4 NetIGetAverageDelayToClient(long param_1,undefined8 param_2);
long FUN_00155c38(long param_1,long param_2,long param_3,long param_4,long param_5);
long NetISetSendAggregationInterval(int param_1,undefined8 param_2,undefined8 param_3);
undefined4 FUN_00155de0(long param_1);
undefined4 NetIGetMyClientIndex(long param_1,long param_2);
undefined4 FUN_00155e80(long param_1,long param_2);
undefined8 NetSetPeerToPeerHostChangeCallback(undefined4 param_1,undefined4 param_2);
void NetResetTime(undefined4 param_1);
void * DMEmalloc(int param_1);
int DmeFree(int *param_1);
undefined4 NetIRegisterMemoryCallbacks(long param_1);
undefined4 NetIGetMyIpAddress(long param_1);
long NetIGetMyNetAddress(undefined4 *param_1,long param_2);
undefined4 FUN_001560e8(long param_1,undefined8 param_2,undefined8 param_3);
void RemoteClientConnects(long param_1,ulong param_2,undefined8 param_3,undefined4 param_4);
void * RemoteClientDisconnects(void);
undefined4 NetIGetCurrentUDPSourceBinaryIP(long param_1);
undefined4 NetIGetLocalTime(void);
undefined4 NetIGetTime(int param_1);
undefined4 NetIGetConnectStatus_G(long param_1,int param_2);
undefined4 NetIGetValidClientCount(long param_1,int *param_2);
long FUN_001565f8(long param_1,long param_2);
undefined4 FUN_00156688(long param_1,long param_2);
undefined4 NetISendTo(undefined8 param_1,undefined8 param_2,ulong param_3,ulong param_4,long param_5);
undefined8 NetBitMaskToSendMask_G(int param_1,int param_2,uint param_3);
long NetSendMessageByUDP(undefined param_1,undefined8 param_2,undefined4 *param_3,undefined8 param_4);
undefined4 NetSendMessageByTCP_G(byte param_1,int param_2,undefined4 *param_3,int param_4);
long NetFragSendCB_G(undefined8 param_1,undefined *param_2);
int NetISendMessage(int *param_1,int *param_2,undefined8 param_3);
void ParseMessageList(undefined8 param_1,long param_2);
undefined4 RemoteClientDisconnectEvent(long param_1,ulong param_2);
void RemoteClientEvent|IncomingMessageFunc(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4);
long NetIInitialize(long param_1,long param_2);
undefined4 FUN_001574c8(long param_1,undefined4 param_2);
undefined4 NetIEnableUDP(void);
undefined4 NetCreateP2PInfo(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7,int param_8,undefined4 param_9);
void RemoteClientEvent(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4);
undefined8 MapMsgClientFailureReason(long param_1,ulong param_2);
void MyClientConnectsPeerToPeer(long param_1,ulong param_2,long param_3,int param_4,undefined4 param_5);
void MsgClientDisconnectCallback(long param_1,long param_2,int param_3,long param_4,undefined8 param_5);
void MsgClientConnectCallback(int param_1);
undefined4 NetSetDefaultConnectParams_G(long param_1);
undefined4 NetIConnect(long param_1,long param_2);
int NetConnect_ClientServerTCP(long param_1,long param_2,long param_3);
int NetConnect_PeerToPeerUDP(long param_1,long param_2,long param_3);
undefined4 NetSetDefaultHostPeerToPeerParams(long param_1);
int NetIHostPeerToPeer(long param_1,long param_2);
undefined4 NetISetNATServiceAddr(long param_1);
undefined4 NetISetDefaultResolveAddrParams(long param_1);
undefined4 NetIResolveAddr(long param_1,long param_2);
undefined4 FUN_00158ee8(long param_1);
undefined4 FUN_00158f28(long param_1,long param_2);
undefined4 NetSetIncomingClient(int param_1,long param_2,long param_3);
long NetISetMyClientReceiveBroadcast(long param_1);
int FindFreePingSlot(void);
undefined4 NetPing_G(long param_1,ulong param_2,long param_3);
long NetPingIP_GC(undefined8 param_1,long param_2);
int NetUpdateAll(long param_1);
long FUN_00159748(void);
long NetIUpdate(void);
undefined4 NetIGetNetUpdateErrors(long param_1);
undefined4 NetIDisconnect(long param_1);
undefined8 NetIClose(void);
undefined4 NetMapRtError(uint param_1);
int NetGetClientPingInfo(ulong param_1);
undefined8 NetCleanupClientPingInfoArray(void);
undefined4 NetGetConnInfo(ulong param_1);
undefined8 NetCleanupConnInfo(undefined8 param_1);
void NetCreateConnInfoBare(void);
undefined4 NetSetConnInfo(int param_1,int param_2);
undefined4 NetCreateConnInfo(ulong param_1,long param_2);
void NetDestroyConnInfoBare(undefined4 param_1);
void NetDestroyConnInfo(long param_1);
undefined4 NetGetClientInfo(long param_1,ulong param_2);
undefined4 NetCreateClientInfo(long param_1,ulong param_2,long param_3);
void NetDestroyClientInfo(long param_1,int param_2);
undefined8 NetGetServerIpAddress(undefined8 param_1,long param_2);
undefined4 NetSetServerIpAddress(long param_1,long param_2);
undefined8 NetCheckForPingTimeouts(void);
undefined4 NetIsPeerToPeerHost(long param_1,long param_2);
void EchoRequestCallback_GC(undefined8 param_1,uint param_2);
long NetProcessEchoRequests(long param_1);
long NetDisablePingIPs(void);
undefined4 FUN_0015a7d0(long param_1,ulong param_2,long param_3);
undefined8 NetProcessP2PDisconnect(void);
undefined NetClientIndexToClientIndexPacket(undefined param_1);
undefined4 NetGetNatService(long param_1);
undefined4 NetConvertTransportFlags(char param_1,long param_2);
void p2p_connect_cb(short param_1,undefined8 param_2,long param_3,long param_4);
void p2p_disconnect_cb(long param_1,long param_2);
void TokenEvent(uint param_1,long param_2,long param_3);
void p2p_host_change_cb(uint param_1,long param_2);
void udp_resolve_cb(undefined8 param_1,long param_2,undefined8 param_3,undefined4 param_4,long param_5);
void p2p_peer_update_cb(undefined2 param_1,ulong param_2,long param_3);
void p2p_incoming_data_cb(uint param_1,undefined8 param_2,undefined8 param_3,long param_4,undefined8 param_5);
undefined4 NetGetMyWorldID(void);
void udp_unconnected_data_cb(undefined8 param_1,undefined8 param_2,undefined4 param_3,undefined8 param_4,undefined8 param_5);
void udp_event_cb(undefined8 param_1,undefined8 param_2,long param_3);
void p2p_broadcast_update_cb(undefined2 param_1,long param_2,long param_3);
void MsgClientSystemMessageCallback(undefined4 param_1,undefined param_2,undefined4 param_3,undefined4 param_4,undefined param_5,undefined2 param_6,undefined4 param_7);
undefined8 NetMutexLock(void);
void NetMutexUnlock(void);
undefined4 FUN_0015b1b8(ulong param_1,uint param_2);
undefined8 FUN_0015b270(long param_1);
undefined4 FUN_0015b300(int param_1,undefined2 param_2,long param_3,long param_4,long param_5,long param_6);
void FUN_0015b3c0(undefined8 *param_1);
undefined4 ClientConnectsPacketHandler(long param_1,undefined8 param_2,undefined8 param_3,int param_4);
undefined4 ServerVersionPacketHandler(long param_1,undefined8 param_2,undefined8 param_3,char *param_4);
undefined4 RequestServersPacketHandler(void);
undefined4 ServerResponsePacketHandler(void);
undefined4 PingPacketHandler(long param_1,undefined8 param_2,long param_3,int param_4);
undefined4 UpdateClientStatusPacketHandler(long param_1,undefined8 param_2,ulong param_3,byte *param_4);
void RegisterDMEmessages(void);
undefined4 FUN_0015bd10(long param_1);
undefined4 FUN_0015bd50(int *param_1);
undefined4 FUN_0015bef0(int param_1);
void TokenEvent(undefined4 param_1,undefined4 param_2,undefined8 *param_3,uint param_4);
undefined4 NetIRegisterMessage(void);
undefined4 NetIRegParseMessage(int param_1,undefined4 param_2,void *function);
void NetIRegisterApplicationMessage(undefined8 param_1,undefined8 param_2);
undefined4 FUN_0015c310(undefined8 param_1,undefined8 param_2,undefined8 param_3);
undefined4 FUN_0015c460(undefined8 param_1,ulong param_2,ulong param_3,long param_4,undefined8 param_5);
undefined4 FUN_0015c620(int param_1,undefined8 param_2,undefined2 *param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,undefined4 *param_9,undefined4 param_10);
void p2p_system_change_cb(long param_1,ulong param_2,ulong param_3,int param_4,uint param_5,int param_6,ushort *param_7,ulong param_8,int param_9);
void TokenNotifyEvent(long param_1,undefined8 param_2,undefined8 param_3,ulong param_4,undefined8 param_5,int param_6,uint param_7);
void TokenHostEvent(int param_1,undefined2 param_2);
undefined4 FUN_0015cf80(long param_1,undefined8 param_2,long param_3);
undefined4 FUN_0015d010(long param_1,long param_2);
undefined8 FUN_0015d048(long param_1,undefined8 param_2);
undefined8 FUN_0015d0f0(long param_1,undefined8 param_2);
int FUN_0015d1b0(long param_1,undefined8 *param_2,undefined8 *param_3);
int FUN_0015d3b8(long param_1,undefined8 *param_2,undefined8 *param_3);
undefined4 FUN_0015d5d0(int param_1,undefined8 param_2);
undefined4 FUN_0015d608(int param_1,undefined8 param_2);
undefined4 FUN_0015d640(int param_1,undefined8 param_2,undefined8 param_3);
void FUN_0015d688_token_table_string_in_Deadlocked_binary(long param_1);
undefined4 rt_circ_buf_create(long param_1,long param_2,undefined4 param_3);
undefined4 rt_circ_buf_destroy(long param_1);
undefined4 rt_circ_buf_clear(long param_1);
long rt_circ_buf_free(long param_1,uint param_2);
long rt_circ_buf_use(long param_1,uint param_2);
long rt_circ_buf_store(long param_1,long param_2,ulong param_3);
long rt_circ_buf_copy(long param_1,long param_2,size_t param_3);
undefined4 rt_circ_buf_normalize(long param_1,long param_2);
long rt_circ_buf_normalize_with_buf(long param_1,int param_2,long param_3);
undefined4 rt_circ_buf_get_used(long param_1,long param_2);
undefined4 rt_circ_buf_get_used_nowrap(long param_1,long param_2);
undefined4 rt_circ_buf_get_avail(long param_1,long param_2);
undefined4 rt_circ_buf_get_avail_nowrap(long param_1,long param_2);
long rt_circ_buf_get_start_used_ptr(long param_1,long param_2);
long rt_circ_buf_get_start_avail_ptr(long param_1,long param_2);
undefined4 rt_circ_buf_is_wrapped(long param_1,long param_2);
undefined * getCommVersion_W(void);
char * FUN_0015df28(void);
long rt_comm_startup(void);
void rt_comm_shutdown(void);
long rt_comm_update(void);
void * rt_comm_set_default_options(undefined4 *param_1);
long rt_comm_create(int *param_1,undefined8 param_2,undefined4 param_3,long param_4);
void rt_comm_destroy(undefined8 param_1);
long rt_comm_send(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4);
long rt_comm_send_to(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4,undefined8 param_5,undefined8 param_6);
long FUN_0015e400(undefined8 param_1,undefined8 param_2,undefined8 param_3);
long rt_comm_vsend_to(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4,undefined8 param_5);
long rt_comm_send_echo(undefined8 param_1,long param_2,undefined8 param_3,undefined8 param_4);
long rt_comm_receive(undefined8 param_1,long param_2,undefined8 param_3,undefined8 param_4);
long rt_comm_receive_from(int param_1,undefined8 param_2,undefined8 param_3,long param_4,undefined8 param_5,long param_6);
long rt_comm_receive_echo(int param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4);
long FUN_0015e918(undefined8 param_1,undefined8 param_2);
void rt_comm_get_local_ip(void);
void rt_comm_get_broadcast_ip(void);
void rt_comm_get_host_by_name(void);
undefined8 FUN_0015ea38(int param_1,undefined8 param_2);
void rt_comm_display_state(void);
void * rt_comm_get_metrics_G(void *param_1);
undefined4 rt_comm_get_interface_data(int param_1,int *param_2);
undefined4 rt_comm_get_local_port(int param_1,undefined4 *param_2);
long rt_comm_is_connected(int param_1,int *param_2);
long rt_comm_get_host_by_name_nb(long param_1);
undefined8 rt_comm_generate_lookup_query(int param_1,char *param_2);
undefined8 rt_comm_resend_lookup_query(undefined4 *param_1);
undefined8 rt_comm_check_for_query_response(undefined8 param_1);
long rt_comm_process_response_header(undefined8 param_1,undefined8 param_2,uint param_3,undefined8 param_4,uint *param_5);
undefined8 rt_comm_skip_query_section(undefined8 param_1,int param_2,uint param_3,uint *param_4);
undefined8 rt_comm_process_rr(undefined8 param_1,int param_2,uint param_3,uint *param_4,undefined8 *param_5,uint *param_6);
bool rt_isdigit(int param_1);
undefined4 * rt_comm_get_new_channel_id(void);
int rt_comm_release_channel_id(undefined4 param_1);
undefined4 rt_comm_is_valid_channel(long param_1);
void rt_comm_metric_init(void);
void rt_comm_metric_add_data(long param_1,long param_2,int param_3);
void rt_comm_metric_update(void);
void rt_comm_metric_update_single(uint *param_1,long param_2);
void rt_comm_linkaddress_setnull(void);
void rt_comm_linkaddress_isnull(undefined8 param_1);
void rt_comm_linkaddress_isequal(undefined8 param_1,undefined8 param_2);
void rt_comm_linkaddress_tostr(undefined8 param_1,undefined8 param_2);
void rt_comm_linkaddress_toext(undefined8 param_1,undefined8 param_2);
void rt_comm_linkaddress_toint(void);
undefined4 FUN_0015f918(void);
void FUN_0015f928(undefined4 *param_1);
long FUN_0015f930(undefined4 *param_1);
undefined8 rt_comm_echo_send(undefined8 param_1,undefined8 param_2,undefined8 param_3);
long rt_comm_echo_update(void);
undefined4 rt_comm_echo_shutdown(void);
void * KM_Initialize(int param_1,long param_2);
undefined4 IsNullRSAKey(int *param_1);
int KM_GetLocalPublicKey(int param_1,long param_2);
void GetKeyMaster(int param_1);
uint rt_ip_string2ip(long param_1);
void rt_ip_ip2string(char *param_1,uint param_2);
undefined4 FUN_0015fe40(long param_1);
long FUN_0015fe70(long param_1);
undefined4 FUN_0015ff48(long param_1);
long FUN_0015ff78(long param_1);
undefined4 FUN_00160050(long param_1);
undefined8 FUN_00160090(void);
undefined4 FUN_001600a8(long param_1);
undefined4 LANTextMessageHandler(void);
undefined4 LANRawMessageHandler(void);
undefined4 rt_memory_allocate(void **param_1,int param_2);
undefined4 FUN_001602e8(void **param_1,int param_2);
long rt_memory_allocate_init_zero(void **param_1,int param_2);
int rt_memory_free(void *param_1);
long rt_memory_align_alloc(long param_1,ulong param_2,uint param_3);
long rt_memory_align_alloc_init_zero(long param_1,size_t param_2,undefined2 param_3);
int rt_memory_align_free(long param_1);
undefined8 rt_memory_register_callbacks(undefined4 param_1,undefined4 param_2);
undefined8 rt_memory_register_another_callback(undefined4 param_1);
undefined4 rt_memory_get_aligned_address(long param_1,long param_2,uint param_3);
undefined4 FUN_001605f0(long param_1,undefined param_2);
undefined4 FUN_00160610(long param_1,long param_2);
undefined4 rt_msg_set_ubyte(long param_1,undefined param_2);
undefined4 rt_msg_get_ubyte(long param_1,long param_2);
undefined4 FUN_00160680(long param_1,undefined4 param_2);
undefined4 FUN_001606a8(long param_1,long param_2);
undefined4 rt_msg_set_u2byte(long param_1,uint param_2);
undefined4 rt_msg_get_u2byte(long param_1,long param_2);
undefined4 FUN_00160740(long param_1,undefined4 param_2);
undefined4 FUN_00160778(long param_1,long param_2);
undefined4 rt_msg_set_u4byte(long param_1,undefined4 param_2);
undefined4 rt_msg_get_u4byte(long param_1,long param_2);
undefined4 FUN_00160870(long param_1,undefined4 param_2);
undefined4 FUN_00160898(long param_1,long param_2);
undefined4 rt_msg_set_u2byte(long param_1,uint param_2);
undefined4 rt_msg_get_u2byte_be(long param_1,long param_2);
undefined4 FUN_00160930(long param_1,undefined4 param_2);
undefined4 FUN_00160968(long param_1,long param_2);
undefined4 FUN_001609c4(long param_1,undefined4 param_2);
undefined4 FUN_00160a00(long param_1,long param_2);
void seedMT(uint param_1);
void seedMTUsingArray(uint *param_1,uint param_2);
void reloadMT(void);
void FUN_00160c88(void);
uint randomMT(void);
void randomMTSetCharArray(int param_1,long param_2);
void setNewSeed(void);
void ScrambleSeed(int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7,int param_8);
void setNewSeed_platform(undefined4 param_1);
int rt_mutex_create(rt_mutex_data *mutex);
int rt_mutex_destroy(rt_mutex_data *mutex_W);
long rt_mutex_lock(void *medius_llock_W,long param_2);
long rt_mutex_lock_no_block(long param_1,long param_2);
long rt_mutex_unlock(void *medius_unlock_W,long param_2);
void rt_mutex_begin_critical_section(void);
void rt_mutex_end_critical_section(void);
int rt_mutex_platform_create(rt_mutex_data *mutex_W);
int rt_mutex_platform_destroy(rt_mutex_data *mutex_W);
undefined4 rt_mutex_platform_lock_G(long param_1);
undefined4 rt_mutex_platform_lock_no_block(long param_1,long param_2);
undefined4 rt_mutex_platform_unlock(long param_1);
undefined4 rt_mutex_platform_get_thread_id(long param_1);
undefined8 rt_mutex_platform_begin_critical_section(void);
undefined8 rt_mutex_platform_end_critical_section(void);
void rt_init_pack_buffer(undefined4 *param_1,ulong param_2,ulong param_3);
void rt_pack_anything(int param_1,int param_2,void *param_3,ulong param_4);
void rt_pack_1byte(int param_1,int param_2,undefined *param_3);
void rt_pack_cu2byte(long param_1,int param_2,ushort *param_3);
void rt_pack_cstring_G(long param_1,undefined8 param_2,long param_3);
long rt_parse_initialize_G(undefined4 param_1,ulong param_2,ulong param_3,undefined4 param_4);
undefined8 rt_parse_shutdown(void);
undefined4 rt_parse_register(long param_1,uint param_2,undefined4 param_3);
undefined4 rt_parse_reg_parser(uint param_1,uint param_2,void *param_3);
undefined4 rt_parse_execute(undefined4 param_1,undefined4 param_2,undefined4 param_3,long param_4,uint param_5,long param_6);
undefined4 rt_parse_get_callback(uint param_1,uint param_2,long param_3);
undefined4 FUN_00161d38(uint param_1);
undefined4 FUN_00161dc0(uint param_1,undefined4 *param_2,uint param_3);
long rt_parse_fragment_message(uint param_1,uint param_2,long param_3,uint param_4,long param_5,undefined8 param_6);
undefined8 rt_parse_timeout_frag_msg(void);
void rt_parse_update(void);
int * rt_parse_find_frag_msg(int param_1,int param_2,int param_3,char *param_4);
char * FUN_00162430(char *param_1,char *param_2,int param_3);
int FUN_00162468(long param_1);
int rt_strnlen(char *param_1,int param_2);
void rt_time_get_local(void);
long rt_time_get_msecs(long param_1);
long rt_time_get_msecs(long param_1);
void rt_time_start(void);
void rt_time_get_time_stamp(void);
void rt_time_elapsed(void);
long rt_time_elapsed_secs(long param_1,long param_2);
long rt_time_elapsed_msecs(long param_1,long param_2);
long rt_time_elapsed_usecs(long param_1,long param_2);
long rt_time_delay(uint param_1);
long rt_time_initialize(void);
long rt_time_initialize(void);
undefined4 rt_time_calc_diff(long param_1,long param_2,long param_3);
undefined4 rt_time_timestamp_to_secs(long param_1,long param_2);
undefined4 rt_time_timestamp_to_msecs(long param_1,long param_2);
undefined4 rt_time_timestamp_to_usecs(long param_1,long param_2);
long rt_time_get_base_diff(long param_1);
long rt_time_elapsed_timestamp(long param_1,long param_2);
void FUN_00162a80(void);
void FUN_00162a98(void);
undefined8 FUN_00162ab0(void);
void FUN_00162b08(void);
void rt_time_get_gmtime(void);
undefined4 rt_time_platform_get_time_stamp(long param_1);
undefined8 FUN_00162b90(uint param_1);
undefined4 rt_time_platform_update_date_time(void);
undefined4 rt_time_platform_get_time_string_G(long param_1);
void rt_time_platform_get_gmtime(void);
undefined4 rt_time_platform_get_date_time(long param_1);
void rt_time_platform_fast_elapsed_secs_G(void);
void re_time_platform_fast_elapsed_msecs(void);
undefined4 rt_time_platform_timer_getcount(void);
undefined8 rt_time_platform_init(void);
undefined4 rt_time_platform_update_base(void);
void rt_timebase_get_globaltime(int *param_1);
void rt_timebase_get_localtime(void);
undefined8 rt_timebase_restart(void);
void rt_timebase_reset_globaltime(undefined4 param_1);
undefined4 rt_timebase_update_globaltime(uint param_1,int param_2);
undefined8 rt_timebase_get_percentiledelay(uint *param_1);
void rt_timebase_is_query_ready(undefined4 *param_1);
void rt_timebase_start(void);
undefined8 rt_token_start(void **param_1);
void rt_token_shutdown(int *param_1);
bool rt_token_is_valid(ulong param_1);
bool rt_token_free_owner_G(uint param_1,ulong param_2,long param_3);
undefined4 FUN_001636b0_rt_token(uint param_1,long param_2);
bool FUN_00163720_rt_token(uint param_1,long param_2);
void rt_token_grant_ownership_G(uint param_1,int param_2);
void rt_token_free_owner(ulong param_1,long param_2);
void FUN_001638b8_rt_token(undefined4 *param_1,int param_2);
undefined8 FUN_001638f8_rt_token(void *param_1,uint *param_2,int param_3);
void FUN_00163990_rt_token(undefined4 *param_1,undefined4 *param_2);
void rt_token_check_ownership(uint param_1,uint *param_2,int *param_3);
undefined8 rt_token_grant_ownership(uint param_1,uint *param_2,long param_3);
undefined8 rt_token_release_ownership(uint param_1,ulong param_2,long param_3);
undefined8 rt_token_update_ownership(uint param_1,long param_2,int param_3);
void rt_token_list_check_ownership(long param_1,uint param_2,uint param_3,undefined2 *param_4,uint *param_5,int *param_6);
undefined8 rt_token_list_grant_ownership(int param_1,uint param_2,int param_3,undefined4 param_4,int param_5);
undefined8 rt_token_list_release_ownership(long param_1,uint param_2,uint param_3,ulong param_4,int *param_5);
undefined8 rt_token_list_update_ownership(int param_1,uint param_2,int param_3,short *param_4,ulong param_5,int param_6);
undefined8 rt_token_create_table(uint param_1,long param_2);
undefined8 rt_token_expand_table(undefined8 param_1,long param_2);
void rt_token_destroy_table(long param_1);
void rt_token_add_ownership(int param_1,undefined2 param_2,long param_3);
void rt_token_remove_ownership(int param_1,undefined8 param_2);
undefined4 rt_token_build_token_msg_G(long param_1,ulong param_2,int *param_3,byte param_4,undefined2 param_5,undefined2 param_6);
undefined4 rt_token_build_token_list_msg(long param_1,ulong param_2,undefined4 *param_3,byte param_4,ulong param_5,ulong param_6,void *param_7,long param_8,uint param_9);
undefined * GetupnpVersion_W(void);
long rt_upnp_create(long param_1,long param_2,undefined4 param_3);
undefined4 rt_upnp_destroy(long param_1);
undefined4 FUN_00164840(void);
undefined4 FUN_00164848(void);
undefined4 FUN_00164850(void);
undefined4 FUN_00164858(void);
undefined4 FUN_00164860(void);
undefined4 FUN_00164868(void);
undefined4 FUN_00164870(void);
undefined4 FUN_00164878(void);
undefined4 FUN_00164880(void);
long rt_upnp_resolve_external_address(long param_1,undefined8 param_2,undefined8 param_3,long param_4);
undefined4 rt_upnp_get_external_address(long param_1,long param_2,long param_3);
undefined4 rt_upnp_disable_natservice_heartbeat(long param_1);
undefined8 rt_upnp_uber_resolve(long param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4,undefined4 param_5);
undefined8 rt_upnp_update(long param_1);
undefined8 rt_upnp_set_memory_ceiling(void);
void upnp_iresolve_cb(int param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4);
undefined8 process_heartbeat_timeslice(undefined4 *param_1);
undefined8 process_nat_resolution_timeslice(undefined8 param_1);
undefined8 lgAudInit(code *param_1,code *param_2);
undefined4 lgAudOpen(undefined4 param_1,long param_2,long param_3);
undefined4 lgAudRead(undefined4 param_1,undefined param_2,long param_3,long param_4);
undefined4 lgAudWrite(undefined4 param_1,undefined param_2,long param_3,long param_4);
undefined4 lgAudWriteVag(undefined4 param_1,undefined param_2,long param_3,long param_4);
undefined4 lgAudPrepareForReboot(void);
undefined4 lgAudARead(undefined4 param_1,undefined param_2,long param_3,long param_4);
undefined4 lgAudAWrite(undefined4 param_1,undefined param_2,long param_3,long param_4);
undefined4 lgAudAWriteVag(undefined4 param_1,undefined param_2,long param_3,long param_4);
undefined8 FUN_00165cf8(void);
undefined4 lgAudEnumHint(long param_1);
undefined4 lgAudEnumerate(undefined4 param_1,undefined8 *param_2);
undefined4 lgAudClose(undefined4 param_1);
undefined4 lgAudGetRemainingPlaybackBytes(undefined4 param_1,undefined4 *param_2);
undefined4 lgAudGetAvailableRecordingBytes(undefined4 param_1,undefined4 *param_2);
undefined4 lgAudGetMixer(undefined4 param_1,long param_2);
undefined4 lgAudSetMixer(undefined4 param_1,long param_2);
undefined4 lgAudStartRecording(undefined4 param_1);
undefined4 lgAudStartRecording(undefined4 param_1);
undefined4 lgAudStartPlayback(undefined4 param_1);
undefined4 lgAudStopPlayback(undefined4 param_1);
undefined4 lgAudResumePlayback(undefined4 param_1);
undefined4 lgAudStopPlayback(undefined4 param_1,undefined param_2,undefined param_3);
undefined4 lgAudStopPlayback(undefined4 param_1,undefined param_2,undefined param_3);
int lgAudASync(long param_1,long param_2);
int FUN_00166b30_lgAud_memcpy(void **param_1);
int FUN_00166b98_lgAud_init_param(int param_1);
void BitPackCBuffer(byte **param_1,short param_2,int param_3);
float CalcCostFunc(float param_1,float param_2,int *param_3,undefined8 param_4,int param_5,int param_6);
float DotProd(float *param_1,float *param_2,int param_3);
int QuanGainSC3(float param_1);
void FUN_00166ed0(undefined8 param_1);
int QuanPvSC3(float param_1,float param_2,float param_3);
void UnQuanPvSC3(undefined4 param_1,uint param_2,undefined4 *param_3,undefined4 *param_4);
void NellyQuantSC3(undefined4 *param_1,int param_2,int param_3);
void corrfunc(float param_1,float param_2,float param_3,float param_4,float *param_5,int param_6,int param_7,int param_8,float *param_9);
undefined4 FUN_00167170(int param_1,float *param_2,undefined8 param_3,undefined8 param_4);
void FUN_001672f8(float *param_1,float *param_2);
void FUN_001673f0(undefined8 param_1,float *param_2,float *param_3,float *param_4,undefined8 param_5);
undefined4 NellyInitVocalFry(long param_1);
undefined8 NellyFreeVocalFry(int *param_1);
int EstOnset(int param_1,undefined8 param_2,undefined8 param_3,int param_4,float *param_5);
bool NellyInitEstOnset(int *param_1);
undefined8 NellyFreeEstOnset(int *param_1);
float powerpoly_125(float param_1);
undefined4 NellyLDPDA(undefined8 param_1,undefined8 param_2,undefined8 param_3);
void GetPitchTable(undefined4 *param_1,undefined4 *param_2);
bool NellyInitLDPDA(undefined4 *param_1);
undefined8 NellyFreeLDPDA(int *param_1);
int FindBaseBand(int param_1,int param_2);
int FindBestCandidates(float *param_1,int param_2,int param_3);
void UpdateLDPDA_MBlk(undefined4 param_1,undefined4 param_2,undefined4 *param_3);
void SelectPeaks(float param_1,undefined8 param_2,int param_3,int *param_4,undefined8 param_5);
void CalcRSbyPower(int param_1,int param_2,float *param_3,int param_4);
void CalcMaskEnvelope(undefined4 *param_1,int param_2,float *param_3,int param_4);
void NellyMSVQEncPred(float param_1,int param_2,undefined4 *param_3,int param_4);
void CompPredCoef(int param_1,int param_2,int param_3,float *param_4,int param_5);
void RS2StageVQ2Enc(undefined4 *param_1,undefined8 param_2,int param_3,undefined4 param_4,undefined4 param_5,undefined8 param_6,undefined8 param_7,undefined4 param_8,undefined4 param_9,undefined4 param_10,undefined4 param_11);
void FUN_001689f0(undefined4 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,undefined4 param_9,undefined4 param_10);
void VQ2mbest(float *param_1,float *param_2,int param_3,int param_4,int param_5);
void RotScaleVQ2(float *param_1,int param_2,int param_3,float *param_4);
void DeRotScaleVQ2(float *param_1,int param_2,int param_3,float *param_4);
undefined4 SelectOutCellCB(int *param_1,int param_2,int param_3);
int FUN_00168d08(float param_1,float *param_2,int param_3);
undefined4 ScalarLUT(int param_1,long param_2,long param_3);
int Dim2VectorQuantize(float *param_1,float *param_2,int param_3);
void Dim2VectorLUT(ulong param_1,int param_2,ulong param_3,undefined4 *param_4);
void SymWindowSignal(float *param_1,float *param_2,float *param_3,uint param_4);
void HammingWindowNormSC(undefined8 param_1,int param_2);
void WindowKernel(float param_1,float param_2,float *param_3,uint param_4);
bool InitSpCBM(undefined8 param_1,int *param_2);
void FreeSpCBM(int *param_1);
void PutFrameSpCBM(int *param_1,undefined8 param_2,int param_3,undefined8 param_4);
void GetFrameSpCBM(int *param_1,int param_2,int param_3,undefined8 param_4);
int CalcCircBufPosition(int param_1,int param_2,long param_3);
void NellyDurbin(float *param_1,uint param_2,float *param_3,float *param_4,float *param_5);
void PeakPick(int param_1,int param_2,int param_3,int param_4,int *param_5,int *param_6);
void NellySeevocFlattop(float param_1);
int NellySeevocPeaksFast(float param_1,int param_2,int param_3,float *param_4,int param_5,float *param_6,float *param_7,int param_8);
void NellySTFTpeaks(undefined8 param_1,undefined8 param_2,undefined8 param_3,int param_4,int param_5,undefined8 param_6,undefined8 param_7);
void BandExpand(float param_1,float *param_2,float *param_3,long param_4);
void NellySquareLawPeaks(float *param_1,float *param_2,int param_3,int param_4,int param_5,int *param_6,int param_7);
float QuadraticPeak(float param_1,float param_2,float param_3,float *param_4);
void NellyLogEnvelopeToAs(undefined4 *param_1,int param_2,float *param_3,undefined8 param_4,undefined8 param_5);
void FUN_00169ee8(undefined4 param_1,int param_2,int param_3,undefined4 *param_4,int param_5);
void FUN_0016a020_fake(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3,long param_4);
void FUN_0016a068(float param_1,int param_2,uint param_3,int param_4,float *param_5,float *param_6);
void K2ASK(int param_1,float *param_2,float *param_3);
void FUN_0016a230(int param_1,undefined4 *param_2,uint param_3);
void MidFrameParam(undefined4 param_1,undefined4 *param_2,float *param_3,undefined8 param_4,undefined8 param_5,long param_6);
float MidFramePv(float param_1,float param_2,float param_3,float param_4,float *param_5);
void GetWindowedSpeech(undefined8 param_1,undefined8 param_2,undefined4 *param_3,undefined8 param_4);
float MidEstPitch(float param_1,float param_2,float param_3,float param_4);
float TDPitchRefine(float param_1,float param_2,undefined8 param_3,int param_4,undefined8 param_5);
void NellyPackSC3(undefined *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined2 param_5,uint param_6);
void FUN_0016a898_fake?(short *param_1,float *param_2,long param_3,float *param_4);
bool NellyInitPreProc(undefined4 param_1,undefined4 *param_2);
void NellyFreePreProc(int *param_1);
int SelectPitchCandidates(undefined4 param_1,float param_2,undefined8 param_3,undefined8 param_4,undefined4 param_5,undefined4 param_6,int param_7,float *param_8,int *param_9);
int BackWard_Check(float param_1,float param_2,int param_3,float *param_4);
int HarmThreshold(undefined8 param_1,int *param_2,int *param_3);
void EliminateSmallP0(int param_1,int *param_2,int *param_3,int *param_4);
void AddBackTrackCand(int param_1,int param_2,int *param_3,int *param_4,int *param_5);
float RefineLDPitch(undefined4 param_1,long param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6,float *param_7);
int NellyQuanPitchSC3(float param_1);
void NellyUnQuanPitchSC3(int param_1);
void FUN_0016b3f0(void);
undefined8 NellyRefineC0(float param_1,float *param_2,int param_3,int param_4,float *param_5,float *param_6,float *param_7);
float NellyQuadRoot(float param_1);
void ScaleAndCompress(float param_1,float *param_2,int param_3,undefined4 *param_4);
void NellySTCVoicing(float *param_1,undefined8 param_2,float *param_3,float *param_4,undefined8 param_5,undefined8 param_6,int param_7,undefined8 param_8);
float ComputePv(float param_1,float param_2,float param_3);
float ModifyPv(float param_1,float param_2,float param_3,float param_4,float param_5);
float VoicingLD(float param_1,int param_2,int param_3,int param_4);
int FindBand4VoicLD(float param_1,int param_2);
void NellyWarpSC36(int param_1,int param_2);
undefined4 NellyAdaptiveWindow(float param_1);
float EnergyToLevel(float param_1);
undefined8 nciEnableVAD(long param_1);
undefined4 nciDisableVAD(long param_1);
undefined4 nciSetVADSilenceDuration(long param_1,undefined2 param_2);
undefined4 nciGetVADSilenceDuration_G(long param_1,undefined2 *param_2);
undefined4 nciSetVADEnergyTrigLevel(long param_1,ushort param_2);
undefined4 nciSetVADVoiceActivity_G(long param_1,long param_2);
undefined4 nciGetVADVoiceActivity(long param_1,long param_2);
undefined4 FUN_0016c3f8(long param_1);
undefined4 FUN_0016c448(long param_1);
undefined4 FUN_0016c498(long param_1,undefined2 param_2);
undefined4 FUN_0016c4e4(long param_1,long param_2);
undefined4 FUN_0016c540_fake?(long param_1,undefined2 param_2);
undefined4 FUN_0016c590_fake?(long param_1,long param_2);
undefined8 nemAgcVadMain(undefined4 param_1,undefined4 param_2,int param_3);
undefined2 nemAgcCalc(int param_1,short param_2);
void nemAgcMeanEngLevel(uint param_1,float **param_2);
undefined4 nemAgcGetMeanEnergy(int param_1);
void nemAgcUpdateCounter(float **param_1);
undefined4 nemAgcInit(long param_1);
undefined4 nemAgcFree(int **param_1);
void nemVadBlockDec(float param_1,float *param_2);
void nemVadSpkrDec(float param_1,float param_2,short param_3,int param_4);
void nemVadUpdateNoiseFlr(float param_1,float *param_2);
undefined nemVadTransmit(float param_1,short param_2,uint param_3,int param_4);
undefined4 nemVadVoicingDec(float param_1,int param_2,short param_3);
undefined4 nemVadInit(float param_1,long param_2,short param_3);
undefined8 nemVadFree(int *param_1);
undefined4 NellyEncodeSC(short *param_1,undefined8 param_2,undefined8 param_3);
undefined8 NellyInitEncodeSC3(long param_1,undefined4 param_2);
undefined8 NellyFreeEncodeSC3(int *param_1);
void CoarsePitchAndFrameEnergy(undefined8 param_1,undefined8 param_2,float *param_3);
void PitchAdaptiveSpectrum(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined4 *param_5,int *param_6);
void NellyLinearInterpolate(float param_1,int param_2,int param_3);
void OuterFrameParam(undefined4 param_1,undefined8 param_2,undefined8 param_3,int param_4,int param_5,undefined8 param_6,int param_7,undefined8 param_8,undefined4 *param_9);
void ApplyCustomVoiceFont(int param_1,float *param_2,float *param_3);
void FUN_0016dc28(undefined4 param_1,int param_2);
void FUN_0016dc38(undefined4 param_1,int param_2);
void FUN_0016dc48(float param_1,int param_2);
void FUN_0016dc70(undefined4 param_1,int param_2);
void FUN_0016dc80(float param_1,int param_2);
void FUN_0016dca8(float param_1,int param_2);
void FUN_0016dcc0(float param_1,int param_2);
undefined4 nciEncodeSase3200(long param_1,long param_2);
undefined8 nciInitEncodeSase3200(void *encoderState_S);
undefined4 nciFreeEncodeSase3200(long nci_encoderState_param_S);
void NellyAskToEnv(undefined4 param_1,undefined4 param_2,float *param_3,undefined4 *param_4,short param_5,short param_6,int param_7,int param_8);
void reflectionToLpc_Q(int param_1,float *param_2);
void lpcToCepstrum(undefined4 param_1,int param_2,undefined4 *param_3);
void spectralWarp(float param_1,float *param_2,short param_3,short param_4,float *param_5);
void BitUnpackCBuffer(byte **param_1,byte *param_2,uint param_3);
void FUN_0016e6e0(float param_1,int param_2,int param_3,undefined2 *param_4,undefined8 param_5,float *param_6,int param_7,int param_8);
void FftTripleSumCosOlAdd(float param_1,float param_2,float param_3,int param_4,int param_5,int param_6,int param_7,short *param_8,int param_9,int param_10,int param_11);
void FUN_0016ee10(float param_1,float param_2,float param_3,float param_4,int param_5,int param_6,int param_7,int param_8,int param_9_00,short *param_10_00,int param_11,int param_12,int param_9,int param_10);
void FUN_0016f3a8(int param_1,int param_2,undefined8 param_3,undefined4 *param_4);
void NellyMSVQDecPred_G(float param_1,int param_2,int param_3,int param_4,int param_5);
void rsmsvqDecode_G(int param_1,int param_2,int *param_3,float *param_4);
void SetAmpAndPhase_G(int param_1,int param_2,int *param_3,int param_4,float *param_5);
float FUN_0016f7b0(float param_1);
void NellyMemZero(float param_1,float param_2,undefined4 param_3,float param_4,int param_5,int param_6,int param_7,int param_8,int param_9,int param_10,int param_11);
void SubFrameAltSynth(undefined4 *param_1,undefined4 *param_2,undefined8 param_3,int *param_4);
void SubFrameAltSynth(undefined4 *param_1,undefined4 *param_2,undefined8 param_3,int *param_4);
void NellyAltSWSynth_G_2(float param_1,float param_2,undefined4 param_3,undefined8 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined8 param_8,undefined8 param_9_00,undefined8 param_10,undefined8 param_11,undefined4 param_9);
void NellyAltSWSynth_G(float param_1,float param_2,undefined4 param_3,undefined4 param_4,undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,undefined8 param_9_00,undefined8 param_10_00,undefined4 param_11,float *param_9,int *param_10);
void FUN_00170030(uint *param_1);
float fSetKLFactor(float param_1,undefined4 param_2);
void NellyHFRegeneration(float param_1,float *param_2,float *param_3,int param_4);
bool NellyInitHFRegen(long param_1);
void NellyFreeHFRegen(int *param_1);
void excitePhaseInvertAmps(float param_1,float param_2,int param_3,int param_4,int param_5);
void insertSubHarmonics(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6);
void vuRandFast_G(long param_1,long param_2,undefined8 param_3,int param_4);
void scaleAmps(int param_1,float *param_2);
void FUN_00170560(undefined8 param_1,short *param_2,undefined2 *param_3,undefined4 param_4,undefined2 param_5,ushort *param_6,byte *param_7,undefined4 param_8,undefined4 param_9,undefined4 *param_10);
void FUN_001707b0_nelly(undefined8 param_1,undefined2 *param_2,undefined2 *param_3,undefined4 param_4,undefined2 param_5,ushort *param_6,byte *param_7,undefined4 param_8,undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 *param_12,int param_13);
void NellyTripleDecodeSase3200(int param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 *param_8,undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 *param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16,undefined4 param_17,undefined4 *param_18);
undefined4 NellyInitDecodeSase3200(long param_1);
undefined8 NellyFreeDecodeSase3200_G(int *param_1);
float MidEstPitch(float param_1,float param_2,float param_3,float param_4);
void unquantize_G(int param_1,int *param_2,undefined8 param_3,undefined4 *param_4);
void FUN_00171418(undefined4 param_1,int param_2);
void FUN_00171420(undefined4 param_1,int param_2);
void FUN_00171428(undefined4 param_1,int param_2);
void FUN_00171430(undefined4 param_1,int param_2);
void FUN_00171438(float param_1,int param_2);
void FUN_00171460(float param_1,int param_2);
void FUN_00171488(float param_1,int param_2);
void FUN_001714b8(float param_1,int param_2);
void FUN_001714e8(undefined4 param_1,int param_2);
void FUN_001714f0(int param_1,undefined2 *param_2);
void FUN_00171500(int param_1,undefined2 param_2);
void FUN_00171508(int param_1,undefined2 *param_2,undefined2 *param_3);
undefined4 nciGetInfoSase3200(nciCodecInfo_W *nci_codecInfo_param_W);
void nciDecodeSase3200Proxy_W(undefined8 param_1,undefined8 param_2);
undefined4 nciDecodeSase3200_WG(long param_1,long param_2,long param_3);
void nciTripleDecodeVoicePropSase3200_Proxy_G(void);
undefined4 nciTripleDecodeVoicePropSase3200(long param_1,long param_2,long param_3,long param_4,long param_5,long param_6,long param_7,long param_8,undefined4 *param_9);
undefined4 FUN_00171d58(undefined4 param_1,undefined4 param_2,undefined4 param_3,long param_4,long param_5,long param_6);
void nciTripleDecodeSase3200_G(void);
undefined4 nciTripleDecodeVoicePropSase3200_G(long param_1,long param_2,long param_3,long param_4,long param_5,long param_6,long param_7,long param_8,undefined4 *param_9,undefined4 *param_10,undefined4 *param_11,undefined4 *param_12);
undefined4 FUN_00172430(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,long param_5,long param_6,long param_7,long param_8);
undefined8 nciInitDecodeSase3200(long nci_decoderState_param_S);
undefined4 nciFreeDecodeSase3200(long nci_decoderState_param_S);
undefined4 FUN_00172750(int param_1);
undefined8 FUN_00172770(int param_1,undefined *param_2);
undefined4 FUN_00172788(long param_1);
undefined4 FUN_00172820(long param_1);
undefined4 FUN_00172870(long param_1,undefined2 param_2);
undefined4 FUN_001728c8(long param_1,undefined4 *param_2);
undefined4 setCallocFunc_W(void *func);
undefined4 setFreeFunc_W(void *func);
undefined8 setMemsetFunc_W(void *func);
undefined8 setMemcpyFunc_W(void *func);
undefined8 setCoffunc_W(void *func);
undefined8 setSinffunc_W(void *func);
void NellyFftCenter512(undefined4 *param_1,int param_2,uint param_3,undefined8 param_4,undefined8 param_5);
void realFft512(undefined8 param_1,undefined8 param_2,int param_3);
void realFft(undefined8 param_1,undefined8 param_2,int param_3);
void inverseRealFft(undefined8 param_1,undefined8 param_2,int param_3);
void fftCore4CFG(int param_1,int param_2,int param_3);
void unpack2G(float *param_1,float *param_2,int param_3);
void pack2G(float *param_1,float *param_2,int param_3);
void fftCore4CFGV(undefined8 param_1,undefined8 param_2,int param_3);
undefined4 FUN_001733c0(void);
void rFft_vu4(undefined8 param_1,undefined8 param_2,int param_3);
undefined4 setVuFftMode(long param_1);
undefined4 GET_nellyVuFftMode_G(void);
bool NellyMemZero(void);
undefined4 updateVuFft(void);
void nvuInitVuFft4CFG(void);
void nvuFftCenter512(undefined4 *param_1,int param_2,uint param_3,undefined8 param_4,undefined8 param_5);
void nvuRealFft(undefined8 param_1,undefined8 param_2,int param_3);
void nvuInverseRealFft(undefined8 param_1,undefined8 param_2,int param_3);
undefined4 nciEnableVu0Optimizations(void);
undefined8 FUN_001739b0(void);
long VU0Save(int param_1);
long VU0Restore(int param_1);
undefined4 FUN_00173ac0(long param_1);
void FUN_00173af0(undefined4 param_1);
undefined4 FUN_00173b00(void);
void NellyMagSq(float *param_1,float *param_2,int param_3,float *param_4);
void NellyMagSq_G2(float *param_1,int param_2,float *param_3);
void ScaleVector(float param_1,float *param_2,long param_3,float *param_4);
void FindMaxValueFlt(float *param_1,int param_2,int *param_3,float *param_4);
float NellyLog2(uint param_1);
uint NellyInvLog2(float param_1);
void PostFilter(float param_1,float *param_2,float *param_3);
int FUN_00173f78_unused(int param_1,int param_2,int param_3);
undefined8 expired(long param_1);
undefined4 FUN_00175050(void);
void FUN_001750c8(void);
void * clearFunctionAddress_W2(void *address_W);
int FUN_00175118_called_after_clearing_address(void *param_1,long param_2,void *param_3,undefined4 param_4);
int * FUN_001751e8(int **param_1);
int * FUN_001751f0(int **param_1,long param_2);
void FUN_001752e8(void);
int * FUN_00175490(int param_1);
int * FUN_001754c8(undefined8 param_1,int param_2);
int * FUN_00175538(long param_1,short param_2,int param_3);
undefined8 FUN_001755f0(int *param_1,ulong param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6);
void FUN_001756f0(undefined8 param_1,void *param_2);
void FUN_00175788(void);
void FUN_00175848(void);
uint FUN_0017a7a8_ipv4_null_checks_2_W(uint param_1);
undefined2 FUN_00175940(undefined2 flags_W);
char * FUN_00175960(void);
void error_print_W(const_char *some_string);
void warning_print_W(const_char *some_string_W);
int FUN_00175af0(int param_1);
void * FUN_00175b68(int param_1);
int FUN_00175d70(uint param_1);
long FUN_00176128_eenet_allocation_G(ulong param_1);
long FUN_00176208_eenet_allocation_G(long param_1,uint param_2);
void FUN_00176488_eenet_allocation_G(long param_1);
undefined4 FUN_00176540_eenet_allocation_G(void *param_1,size_t param_2);
int FUN_001767a8_eenet_allocation_G(void);
void knetBytesUsed_W_eenet_allocation_G(long param_1);
long eenet_malloc_S(long param_1);
int eenet_free_S(undefined8 param_1);
long eenet_realloc_S(long param_1,long param_2);
undefined8 FUN_00176bf0_eenet_allocation_G(uint param_1,uint param_2);
void free_page_SW(int *param_1,int param_2,int param_3);
void free_chunk_SW(void *param_1,int param_2,int **param_3);
void FUN_00177248(void);
long FUN_00177270(undefined8 param_1,undefined2 param_2);
long MGETHDR_S(undefined8 param_1,undefined2 param_2);
void FUN_00177368(void);
long FUN_00177440(undefined8 param_1,undefined8 param_2);
long FUN_001774d0(undefined8 param_1,undefined8 param_2);
long FUN_00177568(undefined8 param_1,undefined8 param_2);
undefined4 FUN_00177610(undefined4 *param_1);
void FUN_00177710(int *param_1);
long FUN_00177828(undefined8 param_1,ulong param_2,undefined8 param_3);
void FUN_00177958(void);
void FUN_00177978(void);
int m_copym_S(undefined4 *param_1,int param_2,uint param_3,undefined8 param_4,int param_5);
long FUN_00177d60(undefined4 *param_1,undefined8 param_2);
void m_copydata_S(undefined4 *param_1,int param_2,uint param_3,long param_4);
void FUN_00178110(int **param_1,long param_2);
void FUN_001781d8(undefined4 *param_1,int param_2);
undefined4 * m_pullup_S(undefined4 *param_1,uint param_2);
undefined4 * FUN_001785a0(undefined4 *param_1,uint param_2,undefined8 param_3);
int FUN_00178870(void *param_1,uint param_2,long param_3,undefined4 param_4,long param_5);
void FUN_00178b38(undefined4 *param_1,int param_2,uint param_3,void *param_4);
int ** m_pulldown_S(int **param_1,int *param_2,uint param_3,long param_4);
void Encode(undefined *param_1,undefined4 *param_2,uint param_3);
void Decode(uint *param_1,byte *param_2,uint param_3);
void md4Init(undefined4 *param_1);
void FUN_001791f0(undefined8 param_1,void *param_2,uint param_3);
void * FUN_001792e0(undefined8 param_1,undefined8 param_2);
void * FUN_00179380(int *param_1,undefined8 param_2);
void FUN_0017a390(undefined8 param_1,undefined8 param_2);
ulong FUN_0017a3a0(ulong param_1,ulong param_2,int param_3);
ulong FUN_0017a490(ulong param_1,void *param_2,int param_3);
void anotherPrintingFunctionIdk_W(int code_W,const_char *format_W,...);
void panic_print_WS(const_char *format,...);
uint FUN_0017a7a8_ipv4_null_checks_W(uint ip_W);
undefined2 FUN_0017a7e0_returns_ip_and_udp_headers(undefined2 param_1);
int FUN_0017a800(void);
void FUN_0017a860(undefined4 param_1);
undefined4 FUN_0017a870(void);
void FUN_0017a8e0(void);
undefined4 eenet_tsleep_SW(uint param_1,long param_2);
int FUN_0017ab18(int param_1);
void FUN_0017ab70(undefined8 param_1);
int FUN_0017ab80(short param_1,uint param_2);
int FUN_0017ac20(int param_1);
int FUN_0017ac78(int param_1);
void FUN_0017acf8(int param_1,undefined2 *param_2);
void FUN_0017ad08(short *param_1);
void FUN_0017ad48(void);
long FUN_0017ad68(undefined8 param_1,void **param_2,int param_3,long param_4);
undefined8 FUN_0017af08(undefined8 param_1,undefined8 param_2);
long FUN_0017af78(undefined8 param_1,uint param_2);
void FUN_0017b038(undefined8 param_1);
long soclose_SW(undefined8 param_1);
void FUN_0017b290(int param_1);
undefined8 soaccept_SW(undefined8 param_1,undefined8 param_2);
undefined8 FUN_0017b368(undefined8 param_1,undefined8 param_2);
undefined8 FUN_0017b420(undefined8 param_1,undefined8 param_2);
undefined8 FUN_0017b490(undefined8 param_1);
ulong FUN_0017b518(undefined8 param_1,int param_2,long param_3,long param_4,int param_5,uint param_6);
ulong FUN_0017bc20(undefined8 param_1,long param_2,undefined8 param_3,long param_4,undefined4 *param_5,uint *param_6);
undefined8 FUN_0017c868(undefined8 param_1,ulong param_2);
void FUN_0017c900(undefined8 param_1);
long FUN_0017ca28(undefined8 param_1,long param_2,long param_3,long param_4);
undefined8 FUN_0017cdb8(undefined8 param_1,long param_2,long param_3,undefined8 param_4);
void FUN_0017d060(int param_1);
void FUN_0017d068(undefined8 param_1,ulong param_2,undefined8 param_3);
ulong FUN_0017d0d8(int param_1,ulong param_2,undefined8 param_3);
int FUN_0017d288(void);
int FUN_0017d2d8(int param_1);
void FUN_0017d350(int param_1);
void FUN_0017d368(undefined8 param_1,undefined8 param_2);
void FUN_0017d438(undefined8 param_1);
void FUN_0017d4a0(undefined8 param_1);
long FUN_0017d508(undefined8 param_1,long param_2);
void FUN_0017d6a0(int param_1,int param_2,long param_3);
undefined4 FUN_0017d700(int param_1,long param_2);
void FUN_0017d788(int param_1);
void FUN_0017d7c0(int param_1);
void FUN_0017d7f8(int param_1);
long FUN_0017d828(int param_1);
void FUN_0017d8a0(undefined8 param_1,undefined8 param_2);
undefined4 FUN_0017d918(int param_1,undefined8 param_2,undefined8 param_3);
undefined4 FUN_0017d9c0(int param_1,ulong param_2);
void FUN_0017da20(int param_1);
void FUN_0017da50(int param_1,long param_2);
void FUN_0017dad8(long *param_1,long param_2);
void FUN_0017dba8(long *param_1,long param_2);
undefined4 sbappendaddr_SW(long *param_1,byte *param_2,int **param_3,int **param_4);
undefined4 sbappendcontrol_SW(long *param_1,int *param_2,int **param_3);
void sbcompress_S(long *param_1,int **param_2,int **param_3);
void sbflush_SW(undefined8 param_1);
void sbdrop_SW(long *param_1,long param_2);
void FUN_0017e648(long *param_1);
long sbcreatecontrol_S(void *param_1,undefined8 param_2,int param_3,int param_4);
undefined4 FUN_0017e920(undefined4 param_1);
void FUN_0017e978(void);
bool FUN_0017e9b8_eenet_spl_sema(void);
int FUN_0017ea10_eenet_spl_sema(long param_1);
undefined4 FUN_0017ea38(void);
int FUN_0017ea48(long param_1);
undefined8 FUN_0017ea70(int param_1,ulong param_2,int **param_3);
long hashinit_SW(long param_1,long *param_2);
undefined4 FUN_0017ec40(long param_1,long param_2,long param_3,long param_4,undefined8 param_5);
undefined4 FUN_0017ecd8(long param_1,long param_2,long param_3,undefined4 param_4);
undefined4 FUN_0017ed48(long param_1,long param_2,long param_3,long param_4,undefined8 param_5);
undefined4 FUN_0017ede0(long param_1,long param_2,long param_3,undefined8 param_4);
int FUN_0017ee50(long param_1,long param_2,long param_3,ulong param_4,undefined8 param_5,ulong param_6);
undefined4 FUN_0017ef38(long param_1,long param_2,long param_3,undefined8 param_4);
undefined4 FUN_0017efe0(long param_1,long param_2,long param_3,uint param_4,undefined8 param_5,uint param_6);
undefined4 FUN_0017f078(long param_1,long param_2,long param_3,undefined8 param_4,uint param_5);
void FUN_0017f0d8(long *param_1);
void FUN_0017f170(int param_1,long *param_2);
void FUN_0017f328(undefined8 *param_1,int param_2);
undefined4 FUN_0017f5f8(ulong *param_1);
long FUN_0017f660(undefined8 param_1,long param_2,int param_3,int *param_4,int param_5);
void FUN_0017f8c8(undefined4 *param_1,int param_2);
void bpf_detachd_SW(int **param_1);
void FUN_0017f9c0(void);
undefined4 FUN_0017fa10(ulong param_1);
undefined8 FUN_0017fa80(int param_1);
long FUN_0017fae8(int param_1,undefined8 param_2);
long FUN_0017fc68(int param_1,undefined8 param_2);
void FUN_0017fd60(int param_1);
long FUN_0017fd88(int param_1,ulong param_2,undefined8 param_3);
undefined4 FUN_001801a0(undefined8 param_1,uint *param_2);
long FUN_001802b0(undefined8 param_1,byte *param_2);
void FUN_00180418(int param_1,undefined8 param_2);
void FUN_00180430(int param_1,undefined8 param_2,undefined8 param_3);
long bpf_mcpy_SW(long param_1,undefined4 *param_2,uint param_3);
void FUN_00180560(int param_1,int *param_2);
void FUN_00180628(undefined8 param_1,undefined8 param_2,ulong param_3,ulong param_4,code *param_5);
undefined4 FUN_00180778(int param_1);
void FUN_001807e0(int param_1);
void bpfattach_SW(undefined4 *param_1,undefined4 param_2,undefined4 param_3,int param_4);
void FUN_00180900(int param_1);
void bpf_change_type_SW(int param_1,undefined4 param_2,int param_3);
long FUN_00180a88(undefined8 param_1,long param_2);
uint FUN_00180b50(int *param_1,int param_2,undefined4 *param_3);
undefined2 FUN_00180c78(int *param_1,int param_2,undefined4 *param_3);
uint FUN_00180d00(long param_1,undefined8 param_2,uint param_3,uint param_4);
bool FUN_001811f0(uint *param_1,int param_2);
void FUN_001812e0(void);
undefined4 FUN_00181330(void);
void FUN_00181338(void);
void FUN_00181340(void);
undefined4 FUN_00181348(void);
undefined4 FUN_00181350(void);
void FUN_00181358(void);
void FUN_00181360(void);
uint FUN_00181368(void);
void if_attach_SW(undefined8 param_1);
void FUN_00181720(int param_1);
void if_detach_SW(undefined8 param_1);
undefined8 delete_rt_entry_proxy_SW(undefined8 param_1,int param_2);
undefined8 FUN_00181a48(undefined8 param_1);
undefined4 FUN_00181aa8(undefined8 param_1);
int * FUN_00181b20(byte *param_1,long param_2);
void FUN_00181bd8(void *param_1);
void FUN_00181c18(int *param_1);
undefined4 FUN_00181c48(int *param_1);
int * FUN_00181d00(undefined8 param_1);
int * FUN_00181df0(undefined8 param_1);
int * FUN_00181ec0(int param_1);
long FUN_00182048(undefined8 param_1);
int * FUN_00182098(ulong param_1);
int * FUN_00182100(undefined8 param_1,int param_2);
void FUN_00182248(int param_1,undefined8 param_2,undefined8 param_3);
void FUN_00182310(undefined8 param_1);
void FUN_00182390(int param_1);
void FUN_001823a8(int *param_1);
void FUN_001823f8(void);
int FUN_001824a8(char *param_1);
undefined8 FUN_00182528(undefined8 param_1,ulong param_2,undefined8 param_3);
undefined8 FUN_00182ae8(long param_1,int *param_2);
undefined8 FUN_00182cc0(int param_1,long param_2,undefined8 param_3,long param_4);
void FUN_001832a0(int param_1,undefined8 param_2);
undefined1 * FUN_00183680(byte *param_1);
void FUN_001836f8(int param_1,undefined8 param_2);
void * FUN_001837b0(int param_1);
undefined4 FUN_00183858(int param_1,undefined8 param_2,undefined8 param_3);
long FUN_00183958(int param_1,int param_2);
long FUN_00183ad0(int param_1,int param_2);
void FUN_00183bf0(void);
undefined4 looutput_SW(int param_1,UnreliablePacket_W *param_2,int param_3,long param_4);
void FUN_00183ed0(undefined8 param_1,long param_2);
undefined4 FUN_00183ee8(int param_1,ulong param_2,long param_3);
void FUN_00183f80(undefined4 *param_1,undefined4 param_2,void *param_3,void *param_4);
void ifmedia_add_SW(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_00184038(undefined8 param_1,int param_2,int param_3);
void ifmedia_set_S(undefined8 param_1,undefined8 param_2);
long FUN_00184110(long param_1,long param_2,long param_3,long param_4);
int * FUN_00184340(int param_1,uint param_2,uint param_3);
void FUN_00184380(int param_1,uint param_2);
void FUN_00184428(void);
undefined4 FUN_00184468(undefined8 param_1,int param_2);
void FUN_001845b8(undefined8 param_1);
int FUN_00184660(ulong param_1,int param_2);
int FUN_001846b8_pppoe(void *param_1,int param_2,int param_3);
int FUN_001847a8(void);
void FUN_001847d0(void);
void FUN_001848f8_pppoe(char *param_1,ulong param_2,undefined8 param_3,int param_4);
void FUN_00184f10(undefined8 param_1);
void FUN_00184f60_pppoe(UnreliablePacket_W *param_1);
undefined4 FUN_00185118_pppoe(int param_1,undefined8 param_2);
undefined8 FUN_00185260(undefined8 param_1,ulong param_2,undefined8 param_3);
undefined4 * FUN_00185480(int param_1);
undefined8 pppoe_send_padi_SW(int param_1);
void FUN_00185938(undefined8 param_1);
long FUN_00185ae8(undefined8 param_1);
undefined8 FUN_00185b98(undefined8 param_1);
void FUN_00185c50(undefined8 param_1);
undefined8 pppoe_send_padr_SW(int param_1);
undefined8 FUN_00185f00(undefined8 param_1);
void FUN_00185fa8(int param_1);
void FUN_00185fc8(int param_1);
void FUN_00186000(undefined8 param_1);
void FUN_00186188(void);
void FUN_00186198(UnreliableLargeData_W *data_W,UnreliablePacket_W *array_maybe_W);
int FUN_00186730(undefined8 param_1,long param_2,int param_3);
void * FUN_00186b48(undefined8 param_1);
void FUN_00186c78(int param_1);
void FUN_00186d28(int param_1);
bool FUN_00186df0(int param_1);
int FUN_00186e50(undefined8 param_1);
int FUN_00186f28(int param_1);
undefined8 FUN_00186f88(undefined8 param_1,ulong param_2,SomeBuffersAndStuff1_W *param_3);
void FUN_00187278(UnreliableLargeData_W *param_1,ushort moduleFlag_W,byte param_3,byte param_4,uint param_5,undefined4 param_6);
void input_S(SomeModuleIdk_W *module_W,UnreliableLargeData_W *data_W,UnreliablePacket_W *param_3);
void up_S(SomeModuleIdk_W *module_W,undefined8 param_2);
void down_S(SomeModuleIdk_W *param_1,undefined8 param_2);
void open_S(SomeModuleIdk_W *param_1,undefined8 param_2);
void close_W(SomeModuleIdk_W *module_W,UnreliableLargeData_W *param_2);
void FUN_001888d0(long param_1,undefined8 param_2);
void FUN_00188b48(SomeModuleIdk_W *module_W,UnreliableLargeData_W *param_2,undefined8 param_3);
void FUN_00188c38(int param_1);
void FUN_00188c60(undefined8 param_1);
void FUN_00188d48(undefined8 param_1);
void FUN_00188e18(undefined8 param_1);
void FUN_00188fc8_close_lcp(UnreliableLargeData_W *data_W);
void FUN_00188fd8(undefined8 param_1);
bool FUN_00188fe8(undefined8 param_1,int param_2,int param_3);
void FUN_001897d0_lcp_reject(UnreliableLargeData_W *param_1,int param_2,int param_3);
void FUN_00189970_lcp_nak(UnreliableLargeData_W *param_1,int param_2,int param_3);
void FUN_00189d10(undefined8 param_1);
void FUN_00189f48(undefined8 param_1);
void FUN_0018a018(undefined8 param_1);
void FUN_0018a098(undefined8 param_1);
void FUN_0018a108(UnreliableLargeData_W *param_1);
undefined4 FUN_0018a370(int param_1);
void FUN_0018a3c8(UnreliableLargeData_W *param_1);
void FUN_0018a418(int param_1);
void FUN_0018a440_ipcp(undefined8 param_1);
void FUN_0018a450_ipcp(undefined8 param_1);
void FUN_0018a460_ipcp(undefined8 param_1);
void FUN_0018a628_ipcp(UnreliableLargeData_W *param_1);
void FUN_0018a638_ipcp(undefined8 param_1);
bool ipcpPrintParseOptsAndValues_W(UnreliableLargeData_W *param_1,int param_2,int param_3);
void FUN_0018ac48_ipcp_reject(int param_1,int param_2,int param_3);
void FUN_0018adb8_ipcp_nak(int param_1,int param_2,int param_3);
void FUN_0018b130_ipcp(undefined8 param_1);
void FUN_0018b190_ipcp(int param_1);
void FUN_0018b1a8_ipcp(int param_1);
void FUN_0018b1b8_ipcp(int param_1);
void FUN_0018b1d0_ipcp(UnreliableLargeData_W *param_1);
void FUN_0018b3a8(void);
void FUN_0018b3b0_ipv6cp(void);
void FUN_0018b3b8_ipv6cp(void);
void FUN_0018b3c0_ipv6cp(void);
void FUN_0018b3c8_ipv6cp(void);
void FUN_0018b3d0_ipv6cp(void);
undefined8 FUN_0018b3d8_ipv6cp(void);
void FUN_0018b3e0_ipv6cp(void);
void FUN_0018b3e8_ipv6cp(void);
void FUN_0018b3f0_ipv6cp(void);
void FUN_0018b3f8_ipv6cp(void);
void FUN_0018b400_ipv6cp(void);
void FUN_0018b408_ipv6cp(void);
void FUN_0018b410_ipv6cp(void);
void chap_input_S(undefined8 param_1,int param_2);
void FUN_0018bc20(int param_1);
void FUN_0018bc38_chap(UnreliableLargeData_W *param_1);
void FUN_0018bcb8_chap(UnreliableLargeData_W *param_1);
void FUN_0018bce0_chap(UnreliableLargeData_W *param_1);
void FUN_0018bdd0_chap(undefined8 param_1);
void FUN_0018bf10_chap(undefined8 param_1);
void FUN_0018bff8_chap(UnreliableLargeData_W *param_1);
void FUN_0018c060_chap(UnreliableLargeData_W *param_1);
void pap_input_S(undefined8 param_1,UnreliablePacket_W *param_2);
void * FUN_0018c698(int param_1);
void FUN_0018c6c0_pap(undefined8 param_1);
void FUN_0018c758_pap(UnreliableLargeData_W *param_1);
void FUN_0018c780_pap(UnreliableLargeData_W *param_1);
void FUN_0018c860_pap(undefined8 param_1);
void FUN_0018c910_pap(undefined8 param_1);
void FUN_0018c998_pap(UnreliableLargeData_W *param_1);
void FUN_0018ca00_pap(UnreliableLargeData_W *param_1);
void FUN_0018cab0(SomeModuleIdk_W *module_W,UnreliableLargeData_W *data_W,byte param_3,byte param_4,int param_5,char *welcome_message_W,undefined8 param_7,char *param_8);
void FUN_0018cda8(void);
undefined4 FUN_0018cf60(undefined8 param_1,long param_2,SomeBuffersAndStuff1_W *param_3);
void FUN_0018d290(int param_1,int *param_2);
undefined4 * FUN_0018d3a0(int param_1,undefined4 *param_2);
void FUN_0018d928(undefined8 param_1);
char * toNetworkingThing_W(ulong flag_W);
char * toResultNetworkingThing_W(short flags_W,byte param_2);
char * toIdkNetworkingThing_W(undefined param_1);
char * toIdkDnsNetworkingThing_W(ulong flag_W);
char * toSomeNetworkingState_W(undefined8 flags_W);
char * toPhase_SW(int someCode_W);
char * toModuleName_W(undefined8 moduleFlag_W);
void printValueOfInput_maybe_WG(byte *param_1,short param_2);
void printSomeKindOfValue_WG(byte *param_1,short param_2);
char * printIpv4Address_W(ulong ip_W);
int FUN_0018e100(char *param_1,int param_2);
void FUN_0018e130_pap_chap(void);
int FUN_0018e138(int param_1,int param_2);
int FUN_0018e178(int param_1,int param_2,int param_3);
bool FUN_0018e1c8(byte *param_1,byte *param_2);
int FUN_0018e288(undefined8 param_1,long param_2,undefined8 param_3);
undefined4 FUN_0018e328(byte *param_1,int param_2,int param_3);
short ** FUN_0018e3b8(undefined8 param_1,undefined4 *param_2);
int FUN_0018e630(undefined4 param_1,uint param_2,int param_3);
int FUN_0018e678(undefined8 param_1,int *param_2,undefined4 *param_3,undefined8 param_4);
undefined4 * rn_addmask_S(byte *param_1,long param_2,int param_3);
undefined4 FUN_0018eb48(byte *param_1,byte *param_2);
undefined2 * FUN_0018ebb8(undefined4 *param_1,undefined4 param_2);
short ** FUN_0018ec78(short *param_1,short *param_2,undefined8 param_3,short **param_4);
int * rn_delete_S(undefined8 param_1,long param_2,int **param_3);
long FUN_0018f4e0(int *param_1,code *param_2,undefined8 param_3);
undefined4 FUN_0018f5f8(int **param_1,undefined8 param_2);
void rn_init_S(void);
long FUN_0018f888(undefined8 param_1,undefined2 param_2);
void FUN_0018f930(undefined8 param_1);
void FUN_0018f980(int param_1);
void FUN_0018f9a8(void);
void FUN_0018f9b8(undefined8 param_1,short *param_2,undefined4 param_3,undefined4 param_4);
void FUN_0018fb98(int param_1,int param_2);
void FUN_0018fbb8(int param_1,int param_2);
int raw_usrreq_SW(undefined8 param_1,long param_2,undefined8 param_3,long param_4,long param_5);
void FUN_0018fe08(int param_1);
void FUN_0018fe70(void);
void FUN_0018fee8(int *param_1);
int FUN_0018ff40(undefined8 param_1,long param_2);
void rtfree_S(long param_1);
void thunk_FUN_001ae500(void);
void FUN_00190190(void *param_1,void *param_2,undefined8 param_3,ulong param_4,void *param_5,long param_6);
long FUN_001903a8(int param_1);
undefined8 FUN_00190458(int param_1,int param_2);
void FUN_00190498(int param_1,undefined8 param_2);
undefined4 FUN_001904c0(void);
int * FUN_001904c8(ulong param_1,undefined8 param_2,undefined8 param_3);
undefined4 delete_rt_entry_SW(int param_1,undefined8 param_2,undefined4 param_3,int param_4,uint param_5,long param_6);
undefined4 FUN_00190b30(int param_1,undefined8 param_2,undefined8 param_3);
void FUN_00190d08(byte *param_1,byte *param_2,byte *param_3);
long rtinit_S(undefined4 *param_1,long param_2,uint param_3);
void FUN_00190f98(void);
long FUN_00190ff0(ulong param_1);
void FUN_00191098(undefined8 *param_1,undefined8 param_2);
void FUN_001910a0(int param_1,long param_2);
void FUN_00191198(int param_1);
undefined4 FUN_00191220(int param_1,int param_2,int param_3);
void FUN_00191358(void);
long FUN_001914a0(undefined8 param_1,long param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5);
long route_output_SW(long param_1,int param_2);
void FUN_00191e60(ulong param_1,int param_2,int param_3);
void FUN_00191f10(byte *param_1,byte *param_2,int *param_3);
long rt_msg1_SW(int param_1,uint *param_2,undefined8 param_3,undefined8 param_4);
undefined4 FUN_001921a8(int param_1,uint *param_2,undefined2 *param_3,long param_4,int *param_5);
void FUN_00192388(undefined8 param_1,undefined8 param_2,uint param_3,undefined4 param_4);
void FUN_00192458(int param_1);
void FUN_00192548(long param_1,int *param_2,undefined4 param_3,long param_4);
void FUN_00192768(int param_1,undefined2 param_2);
long FUN_00192820(int param_1,undefined8 param_2);
long sysctl_iflist_SW(ulong param_1,undefined8 param_2,long param_3);
long FUN_00192c48(byte *param_1,int param_2,long param_3,uint *param_4,long param_5);
void FUN_00192e50(undefined8 param_1);
void FUN_00192ed0(undefined8 param_1,int param_2);
undefined4 FUN_00192fa0(int param_1,undefined8 param_2,int **param_3,int param_4);
int FUN_00193628(long param_1,int param_2,undefined8 param_3,undefined8 param_4);
int FUN_001936f8(undefined8 param_1,uint param_2,int param_3,long param_4,int param_5,ushort **param_6,uint *param_7);
undefined1 * FUN_00193c18(byte *param_1,int param_2);
void arp_drain_S(void);
void FUN_00193d88(void);
void arp_rtrequest_S(int param_1,undefined8 param_2);
void FUN_00194218(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4);
undefined4 arpresolve_S(undefined8 param_1,int param_2,undefined8 param_3,int param_4,undefined8 param_5);
void arpintr_SW(void);
void FUN_001946d0_arp_ip_related(undefined8 param_1);
void arptfree_SW(int param_1);
undefined4 arplookup_S(undefined4 *param_1,long param_2,long param_3);
void FUN_00195000(undefined8 param_1,int param_2);
void FUN_00195090(undefined8 param_1);
void FUN_00195128(undefined8 param_1);
void FUN_00195280(undefined8 param_1);
undefined4 FUN_001953b0(undefined8 param_1,undefined8 param_2,undefined8 param_3);
void FUN_001954b0(void);
void FUN_00195538(void);
void FUN_00195568(void);
undefined4 FUN_001955a0(int param_1);
int * FUN_00195648(int param_1);
void FUN_001956d0(long param_1,int param_2,undefined4 param_3);
void FUN_00195f30(undefined8 param_1);
void FUN_00195ff0(undefined8 param_1);
void FUN_00196098(void);
void FUN_001961c8(void);
void FUN_00196230(undefined4 *param_1,undefined param_2);
undefined4 FUN_001963d8(uint param_1);
undefined4 FUN_00196470(uint param_1);
void FUN_00196518(char *param_1);
undefined * FUN_00196558(undefined4 param_1);
void FUN_001965c0(void);
int FUN_00196618(char *param_1);
void FUN_001966b0(undefined8 param_1,uint param_2);
long in_control_SW(undefined8 param_1,ulong param_2,undefined8 param_3,int *param_4);
void FUN_001970b0(undefined8 param_1,undefined8 param_2);
void FUN_001971c8(undefined8 param_1);
undefined8 in_lifaddr_ioctl_S(undefined8 param_1,ulong param_2,long param_3,long param_4);
void FUN_00197610(int param_1,undefined8 param_2);
long FUN_00197688(undefined8 param_1,undefined8 param_2,undefined8 *param_3,long param_4);
undefined4 FUN_00197ac8(int param_1,int param_2);
void FUN_00197bb0(int param_1);
void FUN_00197cd8(int param_1,int param_2);
void FUN_00197e00(int param_1);
int * FUN_00197e78(int *param_1,undefined8 param_2);
void FUN_00198090(undefined8 param_1);
void FUN_00198160(void);
uint cksum4_S(undefined4 *param_1,undefined param_2,uint param_3,uint param_4);
uint cksum_S(undefined4 *param_1,int param_2);
void FUN_00198840(void *param_1,undefined8 param_2,undefined8 param_3);
undefined4 FUN_001988d8(int param_1,int *param_2);
undefined4 FUN_00198990(undefined8 param_1,long param_2);
int FUN_00198c38(undefined8 param_1,int param_2);
void FUN_00198e80(undefined8 param_1);
void FUN_00198ee8(undefined8 param_1);
void FUN_00198fb0(int param_1,int param_2);
void FUN_00199020(int param_1,int param_2);
int FUN_00199090(int param_1,int param_2,short param_3,int param_4,short param_5,undefined4 param_6,long param_7);
void FUN_001991e0(int *param_1,int param_2,undefined8 param_3,void *param_4);
void FUN_00199280(int *param_1,int param_2);
void FUN_00199398(int param_1);
void FUN_00199440(int param_1);
int * FUN_00199478(int *param_1,int param_2,short param_3,long param_4);
int ** FUN_00199588(void *param_1,int *param_2,short param_3,int *param_4,short param_5);
int ** FUN_001996e0(void *param_1,int *param_2,short param_3);
void FUN_00199850(int *param_1,long param_2);
undefined4 FUN_00199b18(int param_1);
int * FUN_00199b88(undefined8 param_1,undefined8 param_2,ulong param_3,long param_4,undefined4 *param_5);
void FUN_00199d90(void);
void FUN_00199e00(void *func);
void FUN_00199e90_icmp(int *param_1,ulong param_2,long param_3,undefined4 param_4,int param_5);
void FUN_0019a320(long param_1,int param_2,undefined4 param_3);
void FUN_0019a888(undefined8 param_1);
void FUN_0019ae28(undefined8 param_1,undefined8 param_2);
void FUN_0019aed8(void);
long FUN_0019af40(int *param_1,long param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6);
void FUN_0019b040(int param_1,undefined4 param_2);
int FUN_0019b2c8(int param_1,long param_2);
void icmp_mtudisc_timeout_SW(long param_1);
undefined8 FUN_0019b3e0(void);
void FUN_0019b3e8(void);
void ip_init_SW(void);
void FUN_0019b798(void);
void FUN_0019b818(long param_1);
int ** FUN_0019c050(undefined8 param_1,long param_2);
void FUN_0019c6a8(undefined8 param_1);
void FUN_0019c768(void);
void FUN_0019c888(void);
undefined4 FUN_0019c940(int param_1);
undefined4 FUN_0019ce78(int param_1);
void FUN_0019cf30(undefined8 param_1,undefined4 param_2);
long FUN_0019cf98(void);
void FUN_0019d0a8(int param_1);
void FUN_0019d160(undefined8 param_1,int param_2);
void FUN_0019d5e0(int param_1,long param_2,int param_3,int param_4);
undefined8 FUN_0019d6d8(undefined4 *param_1,int param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6);
void FUN_0019daa8(void);
int FUN_0019dad0(undefined4 *param_1,int param_2,int *param_3,uint param_4,int *param_5,int *param_6);
undefined4 FUN_0019e6c0(int param_1);
long FUN_0019e6d8(long param_1,int param_2,int *param_3);
uint FUN_0019e8e0(byte *param_1,undefined *param_2);
undefined8 FUN_0019e9e0(int param_1,int param_2,long param_3,undefined8 param_4,undefined8 param_5);
undefined4 FUN_0019ed68(int *param_1,long param_2);
undefined4 FUN_0019ef28(undefined4 param_1,int **param_2,long param_3);
undefined4 FUN_0019f488(int param_1,long param_2,int *param_3);
void FUN_0019f5d8(long param_1);
void FUN_0019f660(undefined4 param_1,undefined8 param_2,undefined4 param_3);
void FUN_0019f790(void);
void FUN_0019f7b8(undefined8 param_1,undefined8 param_2,uint param_3);
undefined8 FUN_0019faf8(long param_1,int param_2);
undefined8 FUN_0019fd38(int param_1,undefined8 param_2,long param_3,long param_4,undefined8 param_5);
undefined4 FUN_0019fe80(int param_1,int param_2);
undefined4 FUN_0019ff28(int param_1,int param_2);
void FUN_0019ff88(int param_1);
int rip_usrreq_SW(undefined8 param_1,long param_2,ulong param_3,long param_4,long param_5);
uint FUN_001a0288(int param_1,long param_2,int *param_3,int **param_4);
void FUN_001a07a8(undefined8 param_1,int param_2);
void FUN_001a2a98(int param_1,char *param_2,int param_3,int param_4,undefined4 *param_5);
void tcp_pulloutofband_SW(int param_1,int param_2,int *param_3,int param_4);
void FUN_001a2e18(int param_1,int param_2);
undefined4 FUN_001a2f40(int param_1,int param_2);
void FUN_001a3020(void);
void FUN_001a3098(int *param_1,int param_2);
void FUN_001a35d0(void);
void FUN_001a3a30(int param_1);
undefined4 * FUN_001a3b98(undefined8 param_1,undefined8 param_2,int **param_3);
long FUN_001a3cb0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,int param_5,undefined8 param_6,undefined8 param_7);
void FUN_001a4280(undefined8 param_1,undefined8 param_2,int param_3);
void FUN_001a4428(undefined8 param_1,undefined8 param_2,int param_3);
undefined4 FUN_001a45f8(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,int param_5,undefined8 param_6,long param_7,undefined8 param_8,int param_9);
undefined8 FUN_001a4a30(int param_1,long param_2);
void FUN_001a4e28(int param_1);
long tcp_output_SW(undefined8 param_1);
void FUN_001a5da0(int param_1);
void tcp_init_SW(void);
undefined4 * FUN_001a5fe0(int *param_1);
undefined8 FUN_001a61a8(long param_1,long param_2,long param_3,byte *param_4,undefined4 param_5,undefined4 param_6,byte param_7);
long FUN_001a67d0(int param_1,int param_2);
undefined8 FUN_001a6960(undefined8 param_1,short param_2);
undefined8 FUN_001a6a08(undefined8 param_1);
undefined4 FUN_001a6ca0(int param_1);
void FUN_001a6d30(void);
void FUN_001a6e08(int param_1,long param_2);
undefined8 FUN_001a6eb8(uint param_1,undefined8 param_2,long param_3);
void FUN_001a7168(int param_1);
void FUN_001a7188(undefined4 param);
void FUN_001a71c8(undefined8 param_1,undefined8 param_2);
ulong FUN_001a72a8(long param_1,long param_2);
void FUN_001a7328(undefined8 param_1,uint param_2);
void FUN_001a7468(int param_1);
void FUN_001a7548(int param_1);
uint FUN_001a7688(undefined8 param_1,undefined8 param_2,long param_3);
undefined4 FUN_001a7720(int param_1);
void FUN_001a7738(int param_1);
void FUN_001a7770(void);
void FUN_001a77d8(void);
void FUN_001a79c0(int param_1);
undefined8 FUN_001a79f0(undefined8 param_1,long param_2);
void FUN_001a7e78(void);
long tcp_usrreq_SW(undefined8 param_1,long param_2,ulong param_3,ulong param_4,long param_5);
undefined8 FUN_001a8408(long param_1,undefined8 param_2,long param_3,long param_4,undefined8 param_5);
long FUN_001a8618(undefined8 param_1);
long FUN_001a8708(undefined8 param_1);
long FUN_001a87c0(long param_1);
undefined4 FUN_001a8890(uint *param_1,int param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6);
void FUN_001a8980(void);
void FUN_001a89e0(long param_1,int param_2);
void FUN_001a8cc8(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4);
int FUN_001a8e00(undefined8 param_1,int param_2,undefined8 param_3,int param_4);
void FUN_001a9038(int param_1,undefined2 param_2);
undefined8 FUN_001a90a0(uint param_1,char *param_2,long param_3);
undefined4 FUN_001a91c8(long param_1,int param_2);
int udp_usrreq_SW(undefined8 param_1,long param_2,ulong param_3,long param_4,long param_5);
undefined8 FUN_001a9750(int *param_1,long param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6);
undefined4 FUN_001a9838(void);
int FUN_001a9888(short param_1);
int FUN_001a98f0(short param_1);
int FUN_001a9970(int param_1);
undefined4 * thread_enter_S(void);
undefined4 FUN_001a9ae8(int param_1,long param_2);
undefined * eenet_sysctl_S(void);
undefined * FUN_001a9ba0(void);
int FUN_001a9bd8(void);
undefined4 FUN_001a9c50(void);
void FUN_001a9cc0(void);
undefined4 FUN_001a9d00(short param_1);
void FUN_001a9e18(int param_1,int param_2);
void FUN_001a9e30(int param_1);
undefined4 socket(undefined8 param_1,undefined8 param_2,undefined8 param_3);
undefined8 FUN_001a9f38(undefined8 param_1,undefined8 param_2,undefined8 param_3);
undefined8 FUN_001a9ff8(undefined8 param_1,undefined8 param_2);
undefined4 accept_SW(undefined8 param_1,long param_2,uint *param_3);
undefined8 FUN_001aa338(undefined8 param_1,undefined8 param_2,undefined8 param_3);
undefined4 send_S(undefined8 param_1,undefined4 param_2,undefined4 param_3,undefined8 param_4);
undefined4 FUN_001aa558(undefined8 param_1,undefined4 param_2,undefined4 param_3,undefined8 param_4,undefined4 param_5,undefined4 param_6);
undefined4 sendmsg_S(undefined8 param_1,void *param_2,undefined8 param_3);
long FUN_001aa728(undefined8 param_1,undefined8 param_2,int *param_3,undefined8 param_4,int *param_5);
undefined4 recv_S(undefined8 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
undefined4 FUN_001aa9a0(undefined8 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,long param_6);
undefined4 FUN_001aaa78(undefined8 param_1,undefined8 param_2,undefined4 param_3);
long FUN_001aabb8(undefined8 param_1,undefined8 param_2,int *param_3,long param_4,int *param_5);
undefined8 FUN_001aae28(undefined8 param_1,undefined8 param_2);
undefined8 setsockopt_S(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4,ulong param_5);
undefined8 FUN_001aafc8(undefined8 param_1,undefined8 param_2,undefined8 param_3,int param_4,uint *param_5);
undefined8 FUN_001ab1f8(undefined8 param_1,undefined8 param_2,uint *param_3);
undefined8 FUN_001ab300(undefined8 param_1,undefined8 param_2,uint *param_3);
undefined4 FUN_001ab420(int *param_1,undefined8 param_2,ulong param_3,long param_4);
int FUN_001ab560(long param_1,int param_2,int param_3,int param_4,long param_5);
undefined4 FUN_001ab890(undefined4 param_1,uint *param_2,uint *param_3,int param_4,int *param_5);
void FUN_001aba50(undefined8 param_1,uint *param_2,int param_3);
int knetTcpSocketPoll_WS(undefined4 param_1,undefined8 param_2,long param_3);
undefined8 FUN_001abe10(undefined8 param_1,undefined4 *param_2,int param_3,int *param_4);
void FUN_001abed0(undefined8 param_1,undefined4 *param_2,int param_3);
undefined8 eenet_ioctl(undefined8 param_1,ulong param_2,undefined8 param_3);
undefined8 sysctl_S(undefined8 param_1,int param_2,undefined8 param_3,undefined4 *param_4,undefined8 param_5,undefined8 param_6);
undefined8 knetSocketClose_WS(undefined8 param_1);
undefined8 FUN_001ac260(undefined8 param_1);
undefined8 FUN_001ac2c8(long param_1,long param_2);
undefined8 FUN_001ac330(undefined8 param_1,long param_2);
undefined8 FUN_001ac4d8(undefined8 param_1);
undefined8 FUN_001ac558(undefined8 param_1);
uint get_ifindex_S(char *param_1);
undefined4 FUN_001ac660(void);
int FUN_001ac718(void);
void FUN_001ac728(void);
void FUN_001ac780(void);
long sceEENetInit_G(int param_1,int param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5);
long sceEENetTerm_S(void);
undefined4 FUN_001acb08(void);
undefined4 FUN_001acb78(void);
undefined8 FUN_001acc40(void);
void FUN_001acce8(void);
void FUN_001acd40(void);
undefined8 FUN_001acd80(void);
void FUN_001acdf8(void);
s32 FUN_001acf98(void);
undefined4 FUN_001acfc8(long *param_1);
int eenet_bpfopen_S(void);
undefined8 FUN_001ad178(undefined8 param_1);
int eenet_bpfread(undefined8 param_1,undefined4 param_2,int param_3);
int eenet_bpfwrite(undefined8 param_1,undefined4 param_2,int param_3);
undefined8 eenet_bpfioctl_S(undefined8 param_1,undefined8 param_2,undefined8 param_3);
undefined4 FUN_001ad388(const_char *param_1,s32 param_2);
undefined4 FUN_001ad440(void);
void FUN_001ad4b0(undefined4 param_1);
undefined4 FUN_001ad4c0(void);
undefined1 * FUN_001ad4d0(void);
undefined8 getDnsAddress_WS(long param_1,long param_2);
undefined8 FUN_001ad530(long param_1,long param_2);
undefined4 __sceEENetSetDNSSockAddr_WS(long param_1,long param_2);
undefined8 sceEENetGetIfnames_S(long param_1,int *param_2);
undefined4 sceEENetGetIfstat_S|sceEENetGetIfinfo_S(char *param_1,int param_2);
undefined4 FUN_001adc28(char *param_1,undefined8 *param_2);
undefined4 FUN_001add08(uint param_1,long param_2,int *param_3);
void FUN_001ae048(undefined8 param_1,undefined8 param_2);
undefined8 * FUN_001ae070(void);
undefined4 FUN_001ae080(void);
undefined8 * FUN_001ae090(void);
undefined8 FUN_001ae0a0(undefined8 *param_1,int *param_2);
undefined8 FUN_001ae1c8(undefined8 *param_1,int *param_2);
void FUN_001ae2e8(void);
void FUN_001ae338(void);
void FUN_001ae388(void);
void FUN_001ae3d8(void);
void FUN_001ae428(undefined4 param_1);
void FUN_001ae450(undefined4 param_1);
void FUN_001ae478(undefined4 param_1);
void FUN_001ae4a0(undefined4 param_1);
void eenet_malloc(void);
void FUN_001ae500(void);
void FUN_001ae538(void);
long FUN_001ae570(int param_1,int param_2);
void FUN_001ae5c0_memory_allocate(void);
bool FUN_001ae5f8(void);
undefined8 FUN_001ae638(void);
int CreateSema(int param_1,int param_2,const_char *param_3);
s32 create_start_thread_S(void *func,void *stack,int stack_size,int initial_priority,undefined8 first_thread_argument,char *option);
long FUN_001ae778(char *param_1);
int FUN_001ae7d8(int param_1,undefined4 *param_2);
undefined4 FUN_001ae810(uint param_1,uint param_2,int *param_3);
undefined4 FUN_001ae880(uint param_1,uint param_2,int *param_3);
undefined4 FUN_001ae8f0(uint param_1,uint *param_2);
undefined4 FUN_001ae950(int param_1,int *param_2);
long FUN_001ae9b0_allocate_sif_code(int param_1);
undefined4 devman|eenet_add_driver_list_S(int **param_1);
undefined4 FUN_001aeb60_devman(int *param_1);
undefined4 FUN_001aec20_search(int param_1,undefined4 *param_2);
undefined4 FUN_001aec58_add_device_list(undefined4 *param_1);
int FUN_001aed00_start_rpc_server(s32 param_1);
undefined8 FUN_001aed28_devman(uint param_1,undefined8 param_2);
undefined8 SceEENetDevmanThread_Func_W(void);
long sceEENetDriverRegInit_S(undefined8 param_1,undefined4 param_2);
long sceEENetRegDriver_S(sceEENetDriverIdk_W *param_1);
long sceEENetUnregDriver_S(sceEENetDriverIdk_W *param_1);
long FUN_001af5b0(void);
undefined8 setFunctionsSomewhere_W(void *func1,void *func2,void *func3);
undefined4 FUN_001af698(char *param_1,char *param_2,size_t param_3,char *param_4,size_t param_5);
void FUN_001af758_handler(undefined8 param_1,undefined8 param_2);
int FUN_001af788(int param_1);
undefined4 FUN_001af7b0(undefined8 param_1,undefined8 param_2);
undefined4 FUN_001af7f8(void);
undefined4 FUN_001af880(void);
undefined4 FUN_001af8f8(undefined8 param_1,void *param_2,undefined4 param_3);
undefined4 FUN_001af9b0(int param_1);
undefined8 FUN_001afa50(long param_1,undefined4 param_2,void *param_3,int param_4,void *param_5,void *param_6,int param_7);
void FUN_001afb50(SifRpcClientData_t *cd_W,int param_2,int param_3);
void FUN_001afbc8(SifRpcClientData_t *param_1,int param_2,int param_3,void *param_4,int param_5,void *param_6,int param_7,void *param_8,void *param_9);
undefined4 FUN_001afc88(void);
undefined8 FUN_001afcf0(void);
undefined8 sceEENetNotifyEEDriverIsReady_S(undefined4 param_1);
undefined8 sceEENetNotifyEEDriverIsTerminated_S(undefined4 param_1);
undefined8 time(long param_1);
int FUN_001afe60(int param_1,int param_2,char *param_3,int param_4);
void FUN_001b05f8(char *param_1);
undefined8 FUN_001b0628(char *buffer_W,undefined8 param_2,undefined8 param_3);
void FUN_001b06f0(undefined8 param_1,undefined8 param_2);
int FUN_001b0720(long param_1,long param_2,undefined4 param_3,undefined4 param_4);
void FUN_001b0ae0(void);
undefined4 FUN_001b0b10(undefined8 param_1,long param_2,long param_3,undefined4 param_4,undefined4 param_5);
undefined4 FUN_001b0cc8(undefined4 *param_1,undefined8 param_2,undefined4 *param_3);
undefined4 FUN_001b0dc8(int *param_1,undefined8 param_2,byte **param_3);
ulong FUN_001b0fa8(undefined4 param_1);
ulong FUN_001b0ff8(ulong param_1,uint param_2);
uint FUN_001b10e0(undefined4 param_1);
uint FUN_001b1128(byte *param_1);
char * FUN_001b12e0(undefined4 param_1);
undefined8 inet_ntop_WS(long param_1,undefined8 param_2,char *param_3,undefined8 param_4);
undefined8 FUN_001b13f0(byte *param_1,undefined8 param_2,uint param_3);
undefined8 inet_pton_S(long param_1,undefined8 param_2,undefined8 param_3);
undefined4 FUN_001b1520(byte *param_1,long param_2,long param_3);
undefined4 FUN_001b17e8(undefined8 param_1);
void FUN_001b1818(undefined8 param_1,undefined8 param_2);
uint FUN_001b1838(undefined8 param_1,int *param_2,char *unused_3_W,char *unused_4_W,int *param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8);
long FUN_001b1978(void);
void FUN_001b19b8(void);
int FUN_001b19d8(int param_1);
undefined4 FUN_001b1a20(char *param_1);
undefined8 FUN_001b1ae0(char *param_1);
undefined8 FUN_001b1b28(char *param_1);
undefined4 FUN_001b1bd8(char *param_1);
undefined2 FUN_001b1c08(undefined *param_1);
uint FUN_001b1c20(byte *param_1);
void FUN_001b1c50(uint param_1,undefined *param_2);
void FUN_001b1c68(undefined4 param_1,undefined *param_2);
byte * FUN_001b1c88(byte *param_1,byte *param_2,int param_3);
undefined4 FUN_001b1e70(char *param_1,undefined *param_2,int param_3);
byte * FUN_001b20b0(byte *param_1,byte *param_2,byte *param_3,undefined *param_4,int param_5);
byte * FUN_001b2260(byte *param_1,ulong param_2,int param_3,int *param_4,int param_5);
long FUN_001b2480(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5);
undefined8 FUN_001b2538(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5);
undefined4 FUN_001b25f0(byte **param_1,byte *param_2);
undefined4 FUN_001b2680(undefined4 param_1);
bool FUN_001b26b8(int param_1);
int FUN_001b26c8(int param_1);
int FUN_001b26e8(byte *param_1,int param_2,byte **param_3,byte **param_4);
void FUN_001b2838(undefined4 param_1,undefined4 param_2);
void FUN_001b2850(void);
void FUN_001b2860(long param_1,long param_2);
undefined4 FUN_001b2888(int param_1);
uint FUN_001b2a38(void);
int FUN_001b2a80(uint param_1,undefined4 param_2,uint param_3,undefined2 param_4,long param_5,ulong param_6,undefined8 param_7,long param_8,int param_9);
long FUN_001b2d80(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5);
long FUN_001b2fb8(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5);
undefined8 FUN_001b30c0(undefined8 param_1,long param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6);
void FUN_001b32a8(undefined4 param_1);
void FUN_001b32b8(undefined4 param_1);
undefined4 FUN_001b32c8(int param_1);
undefined4 FUN_001b3380(undefined8 param_1,long param_2,long param_3,undefined8 param_4,uint param_5);
undefined4 FUN_001b34d8(undefined8 param_1,uint param_2,undefined8 param_3,uint param_4);
int FUN_001b3668(short *param_1,int param_2,uint *param_3,int param_4);
void FUN_001b4208(int param_1);
undefined8 _sce_eenet_sppp_open_S(undefined8 param_1,undefined8 param_2);
undefined4 _sce_eenet_sppp_state(undefined8 param_1,char *param_2);
undefined4 _sce_eenet_sppp_error_code_S(undefined8 param_1,char *param_2);
undefined8 FUN_001b4498(undefined8 param_1,undefined8 param_2);
undefined4 _sce_eenet_sppp_config_param(undefined8 param_1,char *param_2,int param_3);
undefined4 _sce_eenet_if_set_mtu_S(undefined8 param_1,undefined8 param_2);
undefined4 _sce_eenet_sppp_config_address_S(undefined8 param_1,char *param_2);
undefined4 _sce_eenet_sppp_config_dns_and_route_S(undefined8 param_1,char *param_2,undefined8 param_3);
uint _sce_eenet_is_ipcp_up(undefined8 param_1,char *param_2);
undefined4 _sce_eenet_sppp_auth_message_S(undefined8 param_1,char *param_2,char *param_3);
undefined4 _sce_eenet_sppp_phone_number_S(undefined8 param_1,char *param_2,char *param_3);
long FUN_001b4c40(char *param_1,long param_2);
undefined4 FUN_001b4d30_localhost_and_external_net_if_setaddr_S(char *param_1,int param_2,char *param_3,char *param_4);
undefined4 FUN_001b4ee8(char *param_1,uint param_2);
undefined8 FUN_001b4fe8(char *param_1,long param_2,long param_3,long param_4);
undefined4 FUN_001b5100(char *param_1);
long FUN_001b51b8(undefined8 param_1,int param_2);
undefined8 FUN_001b5250(char *param_1,undefined4 param_2);
int _sce_eenet_set_route_S(undefined param_1,long param_2,long param_3,long param_4,undefined4 param_5);
undefined8 add_default_route_S(int param_1,undefined8 param_2);
undefined8 FUN_001b55a0(int param_1);
s32 _sce_eenet_set_arp_rtmsg_S(undefined4 param_1,undefined8 param_2,int param_3,long param_4,long param_5,long param_6,undefined4 param_7,int param_8);
long _sce_eenet_set_arp_S(void *param_1,int *param_2);
long _sce_eenet_set_arp_S(undefined8 param_1,int *param_2);
undefined4 _sce_eenet_flush_route_S(void);
void FUN_001b5e98(void);
undefined4 FUN_001b5eb0_dhclient(int param_1);
undefined4 FUN_001b6158_dhclient(int param_1);
void FUN_001b63a8(long param_1);
void FUN_001b6458_dhclient(undefined8 param_1,ulong param_2);
void FUN_001b6550(undefined8 param_1);
undefined4 init_S(undefined8 param_1);
undefined4 wait_offer_S(undefined8 param_1,long param_2);
undefined4 selecting_S(undefined8 param_1);
undefined4 requesting_S(undefined8 param_1,long param_2);
undefined4 bound_S(undefined8 param_1);
undefined4 renewing_S(undefined8 param_1,long param_2);
undefined4 rebinding_S(undefined8 param_1,long param_2);
long FUN_001b7e20(char *param_1,long param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6);
int eenet_dhclient_S(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5);
void dhclient_thread_S(undefined8 param_1);
undefined4 FUN_001b86b8(int param_1,undefined4 *param_2,int param_3);
uint FUN_001b8738(ushort *param_1,ushort *param_2,int param_3);
uint FUN_001b87d8(ushort *param_1,int param_2);
undefined4 FUN_001b8828(undefined8 param_1,long param_2);
undefined4 config_if_S(undefined8 param_1,int param_2);
undefined4 getmac_S(undefined8 param_1,undefined8 param_2);
void FUN_001b8b30(uint *param_1);
undefined4 FUN_001b8b88(int param_1);
long arp_check_S|dhclient_send_arp_req_S(int param_1,void *param_2,undefined4 *param_3);
undefined4 FUN_001b8ef0(undefined8 param_1,undefined8 param_2);
undefined4 dhclient_arp_resolv_S(undefined8 param_1,undefined8 param_2);
undefined8 arp_reply_S(int param_1,void *param_2);
undefined4 send_unicast_S(undefined4 *param_1,undefined4 param_2);
undefined4 rexmt_S(int param_1);
undefined4 FUN_001b9478_dhclient(int param_1,int param_2);
char * FUN_001b97e0(int param_1,int param_2,char param_3);
undefined4 FUN_001b9a10_dhclient(byte *param_1,int param_2,undefined8 param_3);
void FUN_001ba270(char *param_1,char *param_2,int param_3);
void * FUN_001ba2b0(long param_1);
undefined4 FUN_001ba2c8(int param_1,byte param_2);
undefined8 FUN_001ba368_code(undefined8 param_1,int param_2);
undefined8 FUN_001ba428_code(char *param_1,int param_2);
undefined8 FUN_001ba578_code(char *param_1,int param_2);
undefined8 FUN_001ba690_code(char *param_1,int param_2);
undefined8 FUN_001ba820_code(char *param_1,int param_2);
int FUN_001ba900(int param_1);
void FUN_001ba968(undefined8 param_1);
undefined4 make_request_S(undefined8 param_1,long param_2);
undefined4 make_decline_S(undefined8 param_1,long param_2);
undefined4 FUN_001bbb50(int param_1);
undefined4 pppoe_create_S(undefined8 param_1);
undefined4 pppoe_destroy_S(undefined8 param_1);
undefined4 pppoe_reset_max_phase(undefined8 param_1);
undefined4 pppoe_set_error_code_S(undefined8 param_1,int param_2,int param_3);
void FUN_001bc188(long param_1);
int FUN_001bc1e8(char *param_1,long param_2,long param_3,long param_4,undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined4 param_8);
int eenet_pppoectl_S(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5);
void FUN_001bc638(undefined8 param_1);
undefined4 FUN_001bc950(int param_1,undefined4 *param_2,int param_3);
undefined4 link_state_S(undefined8 param_1,undefined8 param_2);
long FUN_001bcae8_pppctl(long param_1,char *param_2,int *param_3);
long FUN_001bcba0(long param_1,char *param_2,int *param_3);
undefined4 ppp_modemconf(undefined4 param_1,int param_2,int param_3);
undefined4 ppp_asyncconf(undefined8 param_1);
undefined4 ppp_reset_max_state_S(undefined8 param_1);
undefined4 ppp_set_error_code_S(undefined8 param_1,int param_2);
void FUN_001bd250(long param_1);
int eenet_pppctl_S(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined8 param_6);
void FUN_001bd4e8(undefined8 param_1);
undefined4 FUN_001bd938(int param_1,undefined4 *param_2,int param_3);
undefined4 FUN_001bda60(long param_1);
undefined8 set_staticaddr_func_S(undefined8 param_1);
int FUN_001bdc40(int param_1,void *stack,undefined4 stack_size,undefined4 initial_priority,long param_5);
int CreateSema(int param_1,int param_2,const_char *param_3);
undefined8 FUN_001bde18(int param_1,undefined4 param_2,undefined8 param_3);
long sceEENetDeviceSMAPReg_G(undefined4 param_1,undefined4 param_2);
long sceEENetDeviceSMAPUnreg_S(void);
undefined8 FUN_001bdfa8_smap_seems_like_init_G(undefined8 param_1,int param_2);
undefined8 FUN_001be118(undefined8 param_1,int param_2);
int FUN_001be1a0(int *param_1);
int FUN_001be2d8(undefined8 param_1,int param_2);
undefined4 smap_input_S(undefined8 param_1);
int FUN_001be508(int param_1,int param_2);
undefined8 FUN_001be560(undefined8 param_1);
undefined8 FUN_001be6c0(int param_1);
void FUN_001be6f0(int param_1);
undefined8 FUN_001be788(undefined4 *param_1);
void FUN_001be7a8(int *param_1,int param_2);
void FUN_001be7f0(int param_1);
int FUN_001be800(int param_1);
void FUN_001be988(undefined8 param_1);
long FUN_001be9c8(undefined8 param_1,ulong param_2,undefined8 param_3);
undefined8 FUN_001bed30(long param_1,undefined8 param_2);
undefined4 smap_rpc_server_S(smap_rpc_server_struct_W *param_1);
undefined ** FUN_001beef8(int param_1);
int CreateSema(int param_1,int param_2,const_char *param_3);
s32 create_start_thread_S_2(void *func,void *stack,int stack_size,int initial_priority,undefined8 first_thread_argument,char *option);
undefined4 FUN_001bf0c8(int *param_1);
undefined4 FUN_001bf1d0(int *param_1);
int FUN_001bf2a8(char *param_1);
undefined8 FUN_001bf480(int param_1,undefined8 param_2);
undefined8 FUN_001bf5f0(void);
long sceEENetCtlInit_G(undefined8 param_1,undefined4 param_2,undefined8 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8);
long sceEENetCtlTerm_S(void);
undefined4 FUN_001bf958(char *param_1);
void FUN_001bf9d8(int param_1,int param_2);
void FUN_001bfd90(undefined8 param_1);
void FUN_001c0038(void);
undefined4 rt_msg_client_map_comm_error(long param_1);
undefined4 FUN_001c0340(long param_1);
bool FUN_001c0350(int param_1,long param_2);
undefined4 FUN_001c03a8(int param_1);
undefined8 FUN_001c0498(undefined8 param_1);
undefined4 FUN_001c0550(undefined8 param_1,long param_2,undefined8 param_3);
long FUN_001c0718(undefined8 param_1,long param_2,int *param_3,long param_4,uint *param_5);
undefined8 FUN_001c0828(undefined4 *param_1);
void FUN_001c0888(undefined8 param_1,undefined8 param_2,undefined8 param_3);
void printSomeActionState_W(int param_1);
void FUN_001c09e8(int param_1,int param_2);
undefined4 FUN_001c0a10(int param_1,long param_2);
undefined4 FUN_001c0ab0(int param_1,int param_2);
undefined8 FUN_001c0ae0(undefined8 param_1,long param_2);
undefined4 eenetctl_action_S(undefined8 param_1,undefined8 array_of_x28_elements_W,long param_3,undefined4 param_4);
undefined4 FUN_001c1360(int param_1);
int eenetctl_main_S(void);
undefined4 FUN_001c1b70(long param_1,long param_2,long param_3);
void FUN_001c1d90(undefined8 param_1);
void FUN_001c1db0(undefined8 param_1);
undefined8 FUN_001c1dd0(long param_1);
undefined4 FUN_001c1de8(void *param_1);
undefined4 FUN_001c1e50(int *param_1);
int FUN_001c1ee8(char *param_1,undefined8 param_2,long param_3);
int FUN_001c1f90(char *param_1,undefined8 param_2,long param_3,long param_4);
int FUN_001c2070(char *param_1,undefined8 param_2,long param_3,undefined8 param_4);
int FUN_001c2140(undefined8 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6);
undefined4 FUN_001c2260(void);
long FUN_001c22b0(void);
undefined4 FUN_001c2398(void);
undefined4 FUN_001c2418(void);
undefined8 FUN_001c2490(void);
undefined8 FUN_001c24b8(void);
undefined4 delete_default_route_S(ulong param_1);
undefined4 FUN_001c2650(void);
char * FUN_001c2658(undefined8 param_1,undefined8 param_2,char *param_3);
undefined8 set_dns_and_route_S(int param_1,long param_2,long param_3,long param_4,char *param_5);
long FUN_001c2950(void);
s32 FUN_001c29d8(void);
int * FUN_001c29e8(char *param_1);
int ezNetCnfInit(void);
int ezNetCnfExit(void);
int enZetCnfGetCount(char *param_1);
int ezNetCnfGetCombinationList(char *param_1,undefined4 param_2,void *param_3);
int * ezNetCnfGetCombination(void *configList_W,int param_2);
uint * ezNetCnfGetDefault(void *ConfigList_W);
uint ezNetCnfGetProperties(char *param1,char *param2,char *param3);
int ezNetCtlInit(void);
int ezNetCtlExit_S(ulong param_1);
int ezNetCtlSetProperties(char *attach_ifc_SW);
int ezNetCtlSetCombination_S(char *param_1,char *param_2);
int ezNetCtlPreloadModemCnf_S(char *param_1);
int ezNetCtlUnloadModemCnf_S(void);
undefined8 ezNetCtlUpInterface_G(void);
undefined8 ezNetCtlDownInterface_QS(void);
long ezNetCtlGetStatus_Q(undefined8 *param_1,undefined8 param_2,undefined8 param_3);
int ezNetCtlWaitEventTO(long param_1);
undefined8 FUN_001c3c38(void);
undefined * FUN_001c3c58(undefined8 param_1,undefined8 param_2,int param_3);
void FUN_001c3e90(EzNetMessageEntry2_W *param_1,EzNetMessageEntry2_W *param_2,EzNetMessageEntry2_W *param_3);
int * getMsgEntry(int param_1,int *param_2);
void ezNetCtlLocalizeMessage(long param_1,size_t param_2,undefined8 param_3,undefined8 param_4);
int FUN_001c40c8(char *param_1,char *param_2,undefined8 param_3,int param_4,int param_5);
int FUN_001c4110(char *param_1,char *param_2,undefined8 param_3,undefined8 param_4,int param_5);
int FUN_001c4190(char *param_1,char *param_2,undefined8 param_3,undefined8 param_4,int param_5);
int FUN_001c4248(char *param_1,char *param_2,undefined8 param_3,undefined8 param_4,int param_5);
undefined4 FUN_001c4260(void);
undefined8 FUN_001c4308(void);
int FUN_001c4348(long param_1,undefined8 param_2,undefined8 param_3,s32 param_4);
int FUN_001c4410(void);
void FUN_001c4470(void);
void FUN_001c4490(void);
undefined8 lintSetSmallValue(undefined8 *param_1);
undefined8 FUN_001c4580(undefined4 param_1);
void * FUN_001c4590(char *param_1,undefined4 param_2);
void * FUN_001c45f8(char *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void * FUN_001c4688(char *param_1,undefined4 param_2,char *param_3,undefined4 param_4);
undefined4 FUN_001c4720(undefined8 param_1,uint param_2,char *param_3,undefined8 param_4);
void * FUN_001c4ae8(char *param_1,undefined4 param_2,char *param_3);
void * FUN_001c4b70(char *param_1,undefined4 param_2,char *param_3,char *param_4);
void * FUN_001c4c10(char *param_1,undefined4 param_2,char *param_3);
void * FUN_001c4c90(char *param_1,undefined4 param_2,char *param_3);
void * FUN_001c4d10(char *param_1);
void * FUN_001c4d68(char *param_1);
void * FUN_001c4dc0(char *param_1);
void * FUN_001c4e18(char *param_1,undefined4 param_2,char *param_3);
void * FUN_001c4ea0(void);
void * FUN_001c4ed8(undefined4 param_1);
void * FUN_001c4f18(void);
void * FUN_001c4f50(undefined4 param_1);
undefined8 FUN_001c4fa0(void);
undefined8 FUN_001c4fe0(uint param_1,undefined8 param_2);
void FUN_001c50c8(void);
s32 FUN_001c5138(undefined8 *param_1,void *param_2,int param_3,int param_4);
s32 FUN_001c51e8(s32 param_1);
void FUN_001c5240(void *param_1);
void printEzNetConfigData_W(ezNetConfigData_W *param_1);
int FUN_001c5528(int param_1);
int FUN_001c5550(void);
undefined8 FUN_001c55b0(void);
void * FUN_001c5608(SifRpcClientData_t *cd_W,void *param_2,undefined8 param_3);
undefined4 FUN_001c5698(int param_1);
void * FUN_001c5728(void);
undefined4 FUN_001c5768(undefined8 param_1);
undefined8 FUN_001c5818(void);
undefined4 FUN_001c5868(char *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined4 *param_5);
void FUN_001c5940(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6);
undefined8 FUN_001c5970(void);
void FUN_001c5990(undefined8 param_1);
undefined8 FUN_001c59f8(void);
void FUN_001c5a18(void);
void FUN_001c5ab8(void);
long FUN_001c5ad8(undefined8 param_1);
void FUN_001c5b20(void);
undefined8 FUN_001c5b40(void);
undefined8 FUN_001c5b48(void);
void FUN_001c5b68(void);
void FUN_001c5b88(void);
void FUN_001c5ba8(void);
void FUN_001c5bc8(void);
void FUN_001c5be8(undefined4 param_1);
undefined4 FUN_001c5c18(void);
void FUN_001c5c68(undefined4 param_1);
void FUN_001c5c98(void);
void FUN_001c5cb8(undefined4 param_1);
void FUN_001c5ce8(undefined8 param_1,undefined8 param_2,char *param_3,undefined8 param_4);
void FUN_001c5d08(void);
void FUN_001c5d28(undefined2 param_1);
void FUN_001c5d48(void);
void FUN_001c5d68(undefined2 param_1);
void FUN_001c5d88(void);
void FUN_001c5da8(void);
void FUN_001c5dc8(void);
void FUN_001c5de8(void);
void FUN_001c5e08(void);
void FUN_001c5e28(void);
void FUN_001c5e48(void);
void FUN_001c5e68(void);
void FUN_001c5e88(void);
void FUN_001c5ea8(void);
void FUN_001c5ec8(void);
void FUN_001c5ee8(void);
void FUN_001c5f08(undefined8 param_1);
void FUN_001c5f40(void);
undefined4 sceDbcGetModVersion(void);
undefined4 sceDbcInit_G(void);
undefined4 FUN_001c6258(void);
undefined4 FUN_001c62a0(void);
undefined4 sceDbcSetWorkAddr(undefined4 param_1);
undefined4 sceDbcCreateSocket_G(undefined4 *param_1,undefined4 param_2,undefined4 param_3);
undefined4 sceDbcDeleteSocket(undefined4 param_1);
undefined4 sceDbcGetDepNumber(int param_1);
undefined4 sceDbcGetConnection(int param_1);
undefined4 sceDbcInitSocket(undefined4 param_1);
undefined4 sceDbcResetSocket_G(undefined4 param_1);
undefined4 sceDbcGetDeviceStatus_G(undefined4 param_1);
undefined4 sceDbcGetDeviceStatus_G(int param_1);
int sceDbcSRData(undefined4 param_1,undefined4 param_2,int *param_3,undefined *param_4,int *param_5,int param_6);
int sceDbcSendData(undefined4 param_1,undefined4 param_2,int *param_3,undefined *param_4);
undefined4 sceDbcSendData2(undefined4 param_1,undefined4 param_2,int *param_3,undefined *param_4);
undefined4 sceDbcSendData3_G(undefined4 param_1,undefined4 param_2,int *param_3,undefined *param_4,void *param_5);
int sceDbcReceiveData(undefined4 param_1,undefined4 param_2,int *param_3,int param_4);
void DPRINT_G(char *param_1);
undefined4 scePad2Init(void);
long scePad2End(void);
long scePad2CreateSocket(long param_1,ulong param_2);
long scePad2DeleteSocket(int param_1);
uint scePad2Read(undefined8 param_1,void *param_2);
uint scePad2GetButtonProfile(undefined8 param_1,void *param_2);
undefined scePad2GetState(undefined8 param_1);
uint FUN_001c76a0(int param_1,int param_2,int param_3);
void * scePad2InitDmaDBuff(int param_1);
long scePad2LinkDriver(int param_1);
void * scePad2GetSide(int param_1);
void * scePad2GetSide2(int param_1);
undefined4 scePad2CheckDma(int param_1);
undefined4 scePad2SetButtonOrder(byte *param_1,undefined4 *param_2);
undefined4 * FUN_001c7a30(ulong param_1,char *param_2);
int sceVibGetProfile(undefined8 param_1,undefined8 param_2);
void sceVibSetActParam(undefined8 param_1,size_t param_2,void *param_3,size_t param_4,void *param_5);
undefined4 sceMc2Init(void);
undefined4 sceMc2End(void);
undefined8 sceMc2CreateSocket(int param_1);
undefined4 FUN_001c7ee8(void);
long FUN_001c7f68(undefined4 param_1,undefined4 param_2);
undefined4 FUN_001c8018(long param_1);
undefined4 FUN_001c8050(long param_1);
undefined4 sceMc2FormatAsync(undefined8 param_1);
undefined4 FUN_001c8138_async_G(undefined8 param_1);
undefined4 sceMc2GetInfoAsync(undefined8 param_1,undefined4 param_2);
undefined4 sceMc2GetInfoAsync_G2(undefined8 param_1,char *param_2,undefined4 param_3);
undefined4 FUN_001c83a8(undefined8 param_1);
undefined4 sceMc2ReadFileAsync_C(undefined8 param_1,char *param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5);
undefined4 FUN_001c8578_async_G(undefined8 param_1,char *param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5);
undefined4 FUN_001c8698_async_G(undefined8 param_1,char *param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5);
undefined4 sceMc2WriteFileAsync_C(undefined8 param_1,char *param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5);
undefined4 sceMc2CreateFileAsync_C(undefined8 param_1,char *param_2);
undefined4 sceMc2DeleteAsync_C(undefined8 param_1,char *param_2);
undefined4 sceMc2GetDirAsync_C(undefined8 param_1,char *param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6);
undefined4 sceMc2MkdirAsync_C(undefined8 param_1,char *param_2);
undefined4 FUN_001c8ce0_async_G(undefined8 param_1,char *param_2,undefined4 param_3);
undefined4 sceMc2MkdirAsync|sceMc2CreateFileAsync_G(undefined8 param_1,char *param_2,uint param_3);
undefined4 sceMc2DeleteAsync_G(undefined8 param_1,char *param_2,char *param_3);
undefined4 sceMc2GetInfoAsync_G3(undefined8 param_1,char *param_2);
void basic_thread(void);
undefined4 sceMc2Sync2(long param_1,long param_2,long param_3);
void sceMc2CheckAsync(undefined8 param_1,undefined8 param_2);
void sceMc2CheckAsync_but_param_0(undefined8 param_1,undefined8 param_2);
int sceMc2GetInfo_G(void);
int sceMc2Format_G(void);
int FUN_001c94c0_Mc2_Proxy_G(void);
int FUN_001c9500_Mc2_Proxy_G(void);
int FUN_001c9540_Mc2_Proxy_G(void);
int FUN_001c9580_Mc2_Proxy_G(void);
int FUN_001c95c0_Mc2_Proxy_G(void);
int sceMc2CreateFileAsync_Proxy_G(void);
int sceMc2DeleteAsync_Proxy_G(void);
int sceMc2Delete_G(void);
int sceMc2MkdirAsync_Proxy_G(void);
int FUN_001c9700_Mc2_Proxy_G(void);
int sceMc2GetDirAsync_Proxy_G(void);
int sceMc2MkdirAsync|sceMc2CreateFileAsync_Proxy_G(undefined8 param_1,undefined8 param_2,undefined2 param_3);
int sceMc2GetInfo_G2(void);
int sceMc2GetInfo_G3(void);
int instr(char *param_1,char param_2);
undefined4 isCorrNameSize(char *param_1);
undefined4 isCorrFname(char *param_1);
undefined4 FUN_001c9968(char *param_1);
bool isWildFit(char *param_1,char *param_2);
char * _strtok(char *__s,char *__delim);
int _get_dir_nest(char *param_1);
undefined4 _make_path(int param_1,char *param_2,char *param_3);
undefined4 _sceMcFatInit(void);
undefined4 FUN_001c9ef0(int param_1);
int _sceMcFatGetFatClustNum(undefined8 param_1,int param_2,undefined4 *param_3);
undefined4 _sceMcFatFlushFatCache(undefined8 param_1);
undefined4 _sceMcFatReadFatData(undefined8 param_1,int param_2,int *param_3);
long _sceMcFatGetNextClust(undefined8 param_1,undefined8 param_2,undefined4 *param_3);
ulong _sceMcFatGetNextClustSelf(undefined8 param_1,undefined8 param_2,int *param_3);
undefined4 _sceMcFatWriteFatData(undefined8 param_1,int param_2,undefined4 param_3,undefined8 param_4);
int _sceMcFatGetFreeClust(undefined8 param_1,undefined8 param_2);
int _sceMcFatGetFreeClustSize(undefined8 param_1,undefined8 param_2);
int _GetEntryByPos(undefined8 param_1,undefined8 *param_2,undefined8 param_3,int param_4);
int _fat_chain_trace(undefined8 param_1,ulong param_2);
void _reset_problem_patch(undefined8 param_1,int param_2);
int _sceMcFatGetInfo(undefined8 param_1,long param_2);
int _sceMcFatFormat(undefined8 param_1);
undefined4 _sceMcFatUnFormat(undefined8 param_1);
undefined4 _CheckFileDiscript_C1(undefined8 param_1);
undefined4 _CheckFileDiscript_C2(undefined8 param_1,undefined8 param_2,undefined8 param_3);
int _SearchEntry(undefined8 param_1,undefined8 *param_2,long param_3,char *param_4,ulong param_5,int param_6);
long _sceMcFatSearchFile(undefined8 param_1,char *param_2,undefined8 *param_3,undefined4 *param_4,undefined4 *param_5);
int _SetEntryByPos(undefined8 param_1,undefined8 *param_2,ulong param_3,int param_4);
int _GetFreeEntrySize(undefined8 param_1,ulong param_2,int param_3,undefined8 param_4);
int _CreateEntry(undefined8 param_1,undefined8 *param_2,ulong param_3,int param_4,undefined8 param_5);
long FUN_001cc5a8(undefined8 param_1,undefined8 param_2,int param_3);
long _sceMcFatSearchFile_C(undefined8 param_1,const_char *param_2,long param_3);
int _sceMcFatCreateFile(undefined8 param_1,const_char *param_2,ulong param_3);
size_t _sceMcFatReadFile(undefined8 param_1,const_char *param_2,void *param_3,int param_4,size_t param_5);
size_t _sceMcCoreReadPage3_CW(undefined8 param_1,const_char *param_2,void *param_3,int param_4,size_t param_5);
int _sceMcFatWriteFile(undefined8 param_1,const_char *param_2,void *param_3,int param_4,size_t param_5);
ulong FUN_001cd890(undefined8 param_1,undefined8 param_2,undefined8 param_3);
size_t _sceMcCoreWritePage3_CW(undefined8 param_1,const_char *param_2,void *param_3,int param_4,size_t param_5);
int _sceMcFatDeleteFile(undefined8 param_1,const_char *param_2);
long _sceMcFatChDir(undefined8 param_1,const_char *param_2,long param_3);
int _sceMcFatGetDir(undefined8 param_1,undefined8 param_2,int param_3,int param_4,undefined8 *param_5,int *param_6);
long _sceMcFatSetAttr_C(undefined8 param_1,const_char *param_2,ushort param_3);
long _sceMcFatRename(undefined8 param_1,const_char *param_2,const_char *param_3);
int _sceMcFatGetEntSpace_C(undefined8 param_1,const_char *param_2);
undefined4 FUN_001cec30(void);
void _sceMcpGetCardSpec(void);
void _sceMcpCheckNewCard(void);
void _sceMcpAuthentication(void);
undefined4 _sceMcpReadSysInfo(undefined8 param_1);
bool _sceMcpWriteSysInfo(undefined8 param_1);
void _sceMcpReadClust(int param_1,undefined8 param_2,int param_3,int param_4);
void _sceMcpWriteClust(int param_1,undefined8 param_2,int param_3,int param_4);
undefined8 _sceMcpFlushCache(int param_1);
undefined8 _sceMcpWriteUserClustOnCache(undefined8 param_1,undefined8 *param_2,int param_3);
undefined8 _sceMcpReadUserClustOnCache(undefined8 param_1,undefined8 *param_2,int param_3);
void _sceMcpReadUserClust(void);
void FUN_001cf4f0(int param_1,undefined8 param_2,int param_3,int param_4);
void FUN_001cf538(int param_1,undefined8 param_2,int param_3,int param_4);
undefined4 _sceMcpWriteUserClust(undefined8 param_1,undefined8 param_2,int param_3,int param_4);
undefined4 _sceMcpIsSpeckOutBlock_G(int param_1,int param_2);
void _sceMcpIsSpeckOutClust_G(int param_1,int param_2);
undefined4 _sceMcpMakeSpecoutBlock(undefined4 param_1,int *param_2,int *param_3);
undefined ** SyncDma(void);
undefined ** SyncDmaForRead(void);
int sceMc2SifCallback(void);
undefined4 _sceMcCoreInit(void);
undefined4 FUN_001cf9e8(void);
undefined4 _sceMcCoreSetWriteBackHole(int param_1,undefined4 param_2,undefined4 param_3);
undefined4 _sceMcCoreSetCardSpec(int param_1,undefined8 *param_2);
undefined4 _sceMcCoreGetCardSpec_G(int param_1,undefined8 *param_2);
undefined4 _sceMcCoreCheckNewCard(int param_1);
bool _sceMcCoreClearNewCardFlag(int param_1);
bool _sceMcCoreAuthentication(int param_1);
undefined4 _sceMcCoreWriteBack(int param_1);
undefined4 _sceMcCoreReadClock_G(int param_1,undefined8 *param_2);
int _sceMcCoreReadPage2(int param_1,void *param_2,undefined4 param_3,int param_4,undefined4 param_5);
void _sceMcCoreReadPage(void);
undefined8 _sceMcCoreWritePage(int param_1,void *param_2,undefined4 param_3,undefined8 param_4);
undefined8 FUN_001d0578(int param_1,undefined4 param_2,undefined8 param_3);
bool _sceMcCoreCheckNewCard_G(int param_1,undefined4 param_2);
undefined4 FUN_001d0800(int param_1,void *param_2,int param_3,int param_4);
undefined8 FUN_001d0a30(int param_1,void *param_2,undefined4 param_3,undefined8 param_4);
bool _sceMcCoreGetConnection(int param_1);
int _get_free_slot(void);
long _sceMcCoreCreateSocket(uint *param_1);
bool FUN_001d0d40(ulong param_1);
bool FUN_001d0d70(int param_1);
int _sceMcCoreChangeSocketTypeDbc2Mc(int param_1);
undefined4 _sceMcCoreChangeSocketTypeMc2Dbc(int param_1);
void _dualPrimeVector(int param_1,int *param_2,int *param_3,long param_4,long param_5);
void _getAllRefs(undefined8 param_1,undefined8 param_2,undefined8 param_3,uint param_4,long param_5,undefined4 *param_6,uint *param_7,undefined8 param_8);
undefined4 _motionComp0(undefined8 param_1,int param_2,int param_3,ulong param_4,undefined8 param_5);
void _getRef0_G(int param_1,int *param_2,int param_3,int param_4,int param_5,int param_6,int param_7,int param_8,uint param_9,uint param_10,uint param_11,int param_12);
void _doMC(undefined8 param_1,int param_2);
bool _sceMpegPictureData0(undefined8 param_1);
long _slice0(undefined8 param_1,int param_2);
void _motionVector(undefined8 param_1,int *param_2,int *param_3,long param_4,long param_5,long param_6,long param_7,long param_8);
void _motionVectors(undefined8 param_1,int param_2,undefined8 param_3,int param_4,int param_5,long param_6,long param_7,undefined8 param_8,undefined4 param_9,int param_10,undefined4 param_11);
undefined4 _decMB0(undefined8 param_1,uint *param_2,int *param_3,int *param_4,undefined8 param_5,uint *param_6,undefined8 param_7);
int _sceMpegMbAddressIncrement(undefined8 param_1);
void _sceMpegWaitIpuIdle(int param_1);
long _sceMpegWaitIpuIdle64(int param_1);
uint _sceMpegNextBit(undefined8 param_1,uint param_2);
uint _sceMpegPeepBit(undefined8 param_1,int param_2);
void _sceMpegFlushBuf(undefined8 param_1,ulong param_2);
void _waitIpuIdle(void);
void _sceMpegFlushBuf(undefined8 param_1,ulong param_2);
bool _skipMB0(undefined8 param_1,undefined4 *param_2,undefined4 *param_3,uint *param_4,uint *param_5);
void _copyAddRefImage(undefined4 *param_1,undefined (*param_2) [16],undefined (*param_3) [16]);
void _copyRefImage(undefined4 *param_1,undefined (*param_2) [16]);
int dmaRefImage(int param_1);
void _rix_000(undefined4 *param_1);
void _ri0_000(int *param_1);
void _rix_001(undefined4 *param_1);
void _ri0_001(int *param_1);
void _rix_010(undefined4 *param_1);
void _ri0_010(int *param_1);
void _rix_011(undefined4 *param_1);
void _ri0_011(int *param_1);
void _rix_100(undefined (**param_1) [16]);
void _ri0_100(undefined (**param_1) [16]);
void _rix_101(undefined (**param_1) [16]);
void _ri0_101(undefined (**param_1) [16]);
void _rix_110(undefined (**param_1) [16]);
void _ri0_110(undefined (**param_1) [16]);
void _rix_111(undefined (**param_1) [16]);
void _ri0_111(undefined (**param_1) [16]);
int receiveDataFromIPU(uint param_1,int param_2);
undefined4 _sceMpegSliceA0(undefined8 param_1,undefined8 param_2,int *param_3,int *param_4,undefined4 *param_5);
void _initSeq(int *param_1);
void _sequenceHeader(undefined8 param_1);
void _groupOfPicturesHeader(undefined8 param_1);
void _pictureHeader(undefined8 param_1);
void _sequenceExtension(undefined8 param_1);
void _quantMatrixExtension(undefined8 param_1);
void _sequenceScalableExtension(undefined8 param_1);
void _unknown_extension(undefined8 param_1);
void _pictureCodingExtension(undefined8 param_1);
void _pictureSpatialScalableExtension(undefined8 param_1);
void _pictureTemporalScalableExtension(undefined8 param_1);
void _extensionAndUserData(undefined8 param_1);
void _waitIpuIdle(void);
void _sceMpegFlushBuf(undefined8 param_1,ulong param_2);
undefined4 _sceMpegNextHeader(undefined8 param_1);
void flushBuf32(undefined8 param_1);
void flushByteBoundary(undefined8 param_1);
void _sequenceDisplayExtension(undefined8 param_1);
void _copyrightExtension(undefined8 param_1);
void _pictureDisplayExtension(undefined8 param_1);
void _clearOnce(undefined8 param_1);
undefined4 sceMpegCreate(undefined8 param_1,void *param_2,size_t param_3);
int FUN_001d5f20(int param_1,uint param_2,int param_3);
void _clearEach(int param_1);
long _getpic(int param_1);
bool _updateRefImage(int param_1,long param_2);
ulong _decodeOrSkipFrame(long param_1,long param_2,long param_3);
undefined4 _decodeOrSkipField(long param_1,long param_2,long param_3);
undefined4 sceMpegInit(void);
undefined4 sceMpegDelete(void);
undefined4 FUN_001d6948(int param_1,undefined8 param_2,int param_3);
void sceMpegGetPicture(int param_1,uint param_2,undefined4 param_3);
void FUN_001d69d0(int param_1,uint param_2,undefined4 param_3);
void FUN_001d6a18(int param_1);
undefined4 sceMpegReset(int param_1);
undefined4 sceMpegIsEnd(int param_1);
bool sceMpegIsRefBuffEmpty(int param_1);
void FUN_001d6ac8(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_001d6ae0(int param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4);
void * sceMpegAddCallback(int param_1,int param_2,void *callback,MpegStream *stream);
undefined4 FUN_001d6b38(int param_1,ulong param_2);
undefined4 FUN_001d6b70(int param_1);
undefined8 _sceMpegDispatchMpegCallback(long param_1,int *param_2);
undefined4 _sceMpegDispatchMpegCbNodata(long param_1);
void _decodeOrSkip(undefined8 param_1);
undefined4 sceMpegClearRefBuff(int param_1);
void FUN_001d6d10(int param_1,uint param_2,int param_3,int param_4);
undefined4 FUN_001d6d60(int param_1,undefined8 param_2);
undefined4 FUN_001d6d78(int param_1);
undefined4 FUN_001d6d90(int param_1,undefined4 param_2);
undefined4 FUN_001d6da0(int param_1);
undefined4 FUN_001d6db0(int param_1);
int FUN_001d6dc0(int param_1);
int FUN_001d6dd0(int param_1);
undefined4 FUN_001d6de0(int param_1,undefined4 param_2);
undefined4 FUN_001d6df0(int param_1,undefined8 param_2);
long _decPicture(undefined8 param_1);
void _sceMpegAlalcInit(undefined4 *param_1,undefined4 param_2,undefined4 param_3);
void _sceMpegAlalcSetDynamic(int param_1);
void _sceMpegAlalcFree(int param_1);
int _sceMpegAlalcAlloc(undefined8 param_1,int *param_2,int param_3,long param_4);
int FUN_001d6f80(int *param_1);
undefined4 _sceMpegDefaultStopDMA(int param_1);
undefined4 _sceMpegDefaultRestartDMA(int param_1);
void _cpr8(int param_1,uint *param_2);
void _dispRefImage(undefined8 param_1,undefined8 param_2);
void _dispRefImageField(undefined8 param_1,undefined8 param_2,undefined8 param_3);
undefined4 _sceMpegFlush(int param_1);
void _sceMpegOutputFrame(undefined8 param_1,int param_2,long param_3);
s32 _doCSC2(undefined8 param_1,uint param_2,int param_3);
void _sceMpegCscStoreRefImage(undefined8 param_1,uint *param_2);
undefined8 _ch3dmaCSC(undefined8 param_1,int *param_2);
undefined4 _ch4dma(undefined8 param_1,uint *param_2);
void _ErrMessage(undefined8 param_1);
void _sceMpegStopIpuDma(void);
void _sceMpegErrorBdec(undefined8 param_1);
void _sceMpegError(long param_1,char *param_2);
void _sceMpegError1(undefined8 param_1,char *param_2,...);
int setD3_CHCR(undefined4 param_1);
int setD4_CHCR(undefined4 param_1);
void sceIpuStopDMA(undefined4 *param_1);
void sceIpuRestartDMA(int *param_1);
uint sceIpuSync(int param_1);
int setD4_CHCR(undefined4 param_1);
void sceIpuInit(void);
ulong FUN_001d8bb0(void *param_1);
undefined4 FUN_001d8db0_usbpspcm(void *param_1);
void FUN_001d8ec8_handler(int param_1,undefined4 *param_2);
undefined4 FUN_001d8f08(undefined4 param_1);
void sceSifRpcLoopProxy_G(SifRpcDataQueue_t *cd_W);
undefined4 FUN_001d9080(void);
undefined8 FUN_001d90c0(void);
char * strend(char *str);
u32 ReadHufWord(u8 **loc_ptr);
void kstrcpy(char *dst,const_char *src);
void kstrcpyup(char *dst,const_char *src);
void kstrcat(char *dest,const_char *src);
void kstrncat(char *dest,const_char *src,s32 count);
char * kstrinsert(char *str,char pad,s32 count);
char * basename(char *s);
char * DecodeFileName(const_char *name);
char * MakeFileName(int type,const_char *name,int new_string);
u32 FileExists(const_char *name);
void FileDelete(const_char *name);
void FileCopy(const_char *a,const_char *b);
s32 FileLength(char *filename);
u8 * FileLoad(char *name,kheapinfo *heap,u8 *memory,u32 malloc_flags,s32 *size_out);
s32 FileSave(char *name,u8 *data,s32 size);
u8 * ksmalloc(kheapinfo *heap,s32 size,u32 flags,char *name);
kheapinfo * kheapstatus(kheapinfo *param_1);
kheapinfo * kinitheap(kheapinfo *heap,u8 *mem,s32 size);
u32 kheapused(kheapinfo *heap);
u8 * kmalloc(kheapinfo *heap,s32 size,u32 flags,const_char *name);
void kfree(u8 *a);
void kmemopen_from_c(kheapinfo *heap,const_char *name);
void kmemopen(u32 heap,u32 name);
void kmemclose(void);
void __thiscall CCrc32.Init_T(void *this,uint *param_1);
uint Crc32_WT(const_uchar *param_1,int param_2);
void InitOnce_WS(void);
void DisplayInit_T(DisplayParams_TG *param_1);
void DisplayCreate_T(uint param_1,uint param_2,int zoomMode,bool param_4);
void DisplayAddFrame_T(DmaTag *tag,bool flag);
void DisplayStart_T(void);
void DisplayStop_T(void);
void DisplaySetPause_T(bool param_1);
void DisplaySetCaption_T(DmaTag *const_tag);
undefined4 DisplayGetCaption_T(void);
bool DisplayIsFlushed_T(void);
void DisplayDestroy_T(void);
void DisplayWorkVblank_T(uint param_1);
undefined4 DisplayGetQueuedFrameCount_T(void);
int DisplayGetUploadedFrameCount_T(void);
int _GetNumPages_T(int param_1,int param_2,int param_3);
void Build16x16TexUploadGifTags_T(DmaTag *dmaTag,void *ptr,size_t size);
void BuildClearAndDrawGifTags_T(DmaTag *dmaTag,bool param_2,bool param_3,uint param_4,uint param_5,uint param_6,uint param_7,uint param_8,uint param_9,uint param_10,uint param_11);
void BuildContrastAndBrightnessGifTags_T(DmaTag *tag,float contrast_W,float brightness_W);
void DmaInit_T(void);
undefined4 DmaSync_T(uint edmaChannel,int value);
void DmaSetChannelOptions_T(uint edmaChannel,int param_2,int param_3,int param_4,int param_5,uint param_6,uint param_7,uint param_8);
void DmaStart_T(uint edmaChannel,void *ptr,uint size);
void DmaStartChain_T(uint edmaChannel,DmaTag *dmaTag);
bool DmaIsBusy_T(uint edmaChannel);
void setLoadImageDest_T(DmaTag *dmaTag,uint param_2,uint param_3,int param_4);
void setLoadImageTagsRows_T(DmaTag *dmaTag,void *ptr,uint param_3,uint param_4,int param_5);
void setLoadImageTagsColumns_T(DmaTag *dmaTag,void *ptr,uint param_3,uint param_4,int param_5);
int GetMemRequirements_T(uint param1,uint param2,uint empegVideoType);
void MemInit_T(void *ptr,uint size);
void MemTerminate_T(void);
uint MemAlloc_T(uint param_1,uint param_2);
void MemReset_T(void);
void MpegInit_T(void);
void MpegCreate_T(MpegStream *stream,uint empegVideoType,void *callback1,void *callback2,uint param_5,int param_6,uint param_7);
undefined4 MpegGetVideo_T(DmaTag **dmaTagPtr,uint param);
ulong MpegIsEnd_T(void);
void MpegRewind_T(void);
void MpegIdle_T(void);
sceMpeg * MpegBind_T(MpegStream *stream);
void MpegDelete_T(void);
undefined4 _createCore_T(int param_1,MpegStream *stream,uint empegVideoType,void *callback1,void *callback2,uint param_6,int param_7,uint param_8);
undefined4 _getVideoCore_T(void);
void _mywaitipuidle_T(int param);
undefined4 _videoCallback_T(sceMpeg *mpeg,sceMpegCbDataStr *cbData,void *userData);
undefined4 _nodataCallback_T(sceMpeg *mpeg,sceMpegCbData *cbData,void *userData);
undefined4 _backgroundCallback_T(sceMpeg *mpeg,sceMpegCbData *cbData,void *userData);
undefined4 _errorCallback_T(sceMpeg *mpeg,sceMpegCbData *cbData,void *userData);
undefined4 _fillBuff_T(int param_1);
undefined4 PlayerInit_T(PlayerParams *params);
void PlayerStart_T(uint param1,uint param2);
undefined4 PlayerStop_T(int param_1);
void PlayerSetPause_T(uint param_1);
undefined4 PlayerWork_T(void);
void PlayerIdle_T(void);
void PlayerSetCaption_T(DmaTag *captionTag_W);
undefined4 PlayerGetCaption_T(void);
DmaTag * PlayerGetTexture_T(void);
void PlayerRewind_T(void);
void PlayerWorkVblank_T(void);
void PlayerTerminate_T(void);
undefined4 knetPatch_W_calls_lzo1x_decompres(int param_1,ulong param_2,int *param_3,ulong param_4,undefined8 param_5,ulong param_6,ulong param_7,ulong param_8);
undefined4 lzo1x_decompress(byte *param_1,int param_2,byte *param_3,int *param_4);
void SceInitTrue_W(void);
void FUN_002662e8(void);
void FUN_00266300(void);
void FUN_00266360(void);
void entry(void);
void Exit(s32 exit_code);
void KernelDispatch(u32 dispatcher_func);
int KernelCheckAndDispatch(void);
void KernelShutdown(u32 reason);
s32 goal_main(int argc,const_char **argv);
u32 ReceiveToBuffer(char *buff);
s32 SendFromBuffer(char *buff,s32 size);
char * InitListenerConnect(void);
void InitCheckListener(void);
char * WaitForMessageAndAck(void);
void CloseListener(void);
void InitGoalProto(void);
void ShutdownGoalProto(void);
void GoalProtoHandler(int event,int param,GoalProtoBlock *opt);
s32 SendFromBufferD(s32 msg_kind,u64 msg_id,char *data,s32 size);
void GoalProtoStatus(void);
void init_output(void);
void clear_output(void);
void clear_print(void);
void reset_output(void);
void output_unload(const_char *name);
void output_segment_load(const_char *name,void *link_block,u32 flags);
void output_sql_query(char *param_1);
void cprintf(const_char *format,...);
void Msg(s32 k,const_char *format,...);
void MsgWarn(const_char *format,...);
void MsgErr(const_char *format,...);
void reverse(char *str);
char * round(float x,s32 *param_2,char *start,char *sEnd,char padchar,s32 *param_6);
s32 cvt_float(float x,s32 precision,s32 *lead_char,char *buff_start,char *buff_end,u32 flags);
void ftoa(char *out_str,float x,s32 desired_len,char pad_char,s32 precision,u32 flags);
char * kitoa(char *buffer,s64 value,u64 base,s32 length,char pad,u32 flag);
void kqtoa_G(void);
s32 format_impl_jak3(uint64_t *args);
void globalPowerOff_W(void);
int * initializePowerOffHandler_W(void);
int DecodeSymbolId(ulong param_1);
void FUN_002684f4_cd_dvd_disk_drive_ready(void);
void InitCD(void);
void InitParms(int argc,const_char **argv);
void DumpIOPMemStats_Q(const_char *param);
int FUN_00268b40(void);
void convertPathSeparators_W(char *param_1,long toUnix);
void FUN_00268c44(char *param_1,char **param_2);
void MakeDriverPath_S(char *outDriverPath_W,char *outDriverPathChild_W,long fromHost_W,bool useLocalDnasMc300scee_W);
void MakeVagwadPath_S(long param_1,long param_2,ulong param_3);
long sceSifLoadModule_wrong_G(long param_1,long param_2,ulong param_3,void *param_4,undefined **param_5);
long loadIOPModuleAndStuff_W(const_char *moduleName_W,undefined8 param_2,char *parameterForModule_W,long param_4,long param_5);
s32 InitIOP(void);
void InitVideo(void);
int InitMachine(void);
int StopIOP_G(void);
int ShutdownMachine(int reasonIndex);
void CacheFlush(void *mem,int size);
u64 CPadOpen(u64 cpad_info,s32 pad_number);
u64 CPadGetData(u64 cpad_info);
u32 MouseGetData(u32 mouse);
u32 KeybdGetData(u32 mouse);
void InstallHandler(u32 handler_idx,u32 handler_func);
void InstallDebugHandler(void);
bool FUN_0026a8a0_probably_kernel(void);
undefined8 FUN_0026a918_probably_kernel(void);
u64 kopen(u64 fs,u64 name,u64 mode);
int kmkdir_G(int param_1);
s32 klength(u64 fs);
s32 kseek(u64 fs,s32 offset,s32 where);
s32 kread(u64 fs,u64 buffer,s32 size);
s32 kwrite(u64 fs,u64 buffer,s32 size);
u64 kclose(u64 fs);
bool dma_to_iop(void *param_1,int param_2,void *param_3);
u16 DecodeLanguage(void);
u16 DecodeAspect(void);
u16 DecodeVolume(void);
undefined4 DecodeTerritory(void);
u16 DecodeTimeout(void);
u16 DecodeInactiveTimeout(void);
void DecodeTime(u32 ptr);
void PutDisplayEnv(u32 ptr);
void InitMachineScheme(void);
undefined4 kget_audio_language_mask_S(void);
u64 new_illegal(u32 allocation,u32 type);
u64 delete_illegal(u32 obj);
u64 goal_malloc(u32 heap,u32 size,u32 flags,u32 name);
u64 alloc_from_heap(u32 heapSymbol,u32 type,s32 size,u32 pp);
u64 alloc_heap_memory(u32 heap,u32 size);
u64 alloc_heap_object(u32 heap,u32 type,u32 size,u32 pp);
u64 new_structure(u32 heap,u32 type);
u64 new_dynamic_structure(u32 heap_symbol,u32 type,u32 size);
void delete_structure(u32 s);
u64 new_basic(u32 heap,u32 type,u32 size,u32 pp);
void delete_basic(u32 s);
u64 new_pair(u32 heap,u32 type,u32 car,u32 cdr);
void delete_pair(u32 s);
u64 make_string(u32 size);
String * make_string_from_c(const_char *c_str);
u64 make_debug_string_from_c(const_char *c_str);
Function * make_function_from_c(void *func,bool arg3_is_pp);
u64 make_nothing_func(void);
u64 make_zero_func(void);
u64 symbol_to_string_from_c(u32 sym);
void make_function_symbol_from_c(char *name,void *f);
u32 make_raw_function_symbol_from_c(const_char *name,u32 value);
Symbol4 * set_fixed_symbol(FixedSymbolOffset offset,const_char *name,u32 value);
Symbol4 * find_symbol_in_area(const_char *name,u32 start,u32 end);
Symbol4 * find_symbol_from_c(uint16_t sym_id,const_char *name);
u32 * intern_from_c(int sym_id,int flags,const_char *name);
u64 intern(u32 name);
Type * alloc_and_init_type(undefined *sym,u32 method_count,bool force_global_type);
Type * intern_type_from_c(int a,int b,const_char *name,u64 methods);
Type * intern_type(u32 name,u64 methods);
Type * set_fixed_type(FixedSymbolTypeOffset offset,const_char *name,Symbol4 *parent_symbol,u64 flags,u32 print,u32 inspect);
Type * new_type(u32 symbol,u32 parent,u64 flags);
Type * set_type_values(Type *type,Type *parent,u64 flags);
u64 type_typep(Type *t1,Type *t2);
u64 method_set(u32 type_,u32 method_id,u32 method);
u64 call_method_of_type(u32 arg,Type *type,u32 method_id);
u64 call_goal_function(Function *func);
u64 call_goal_function_arg2(Function *func,u64 a,u64 b);
u64 call_goal_function_by_name(const_char *name);
u64 call_method_of_type_arg2(u32 arg,Type *type,u32 method_id,u32 a1,u32 a2);
u64 sprint(u32 obj);
u64 print_object(u32 obj);
u64 print_structure(u32 s);
u64 print_basic(u32 obj);
u64 print_pair(u32 obj);
u64 print_integer(u64 obj);
u64 print_binteger(u64 obj);
u64 print_float(u32 f);
u64 print_symbol(u32 obj);
u64 print_type(u32 obj);
u64 print_string(u32 obj);
u64 print_function(u32 obj);
u64 print_vu_function(u32 obj);
u64 asize_of_basic(u32 it);
u64 copy_fixed(u32 it);
u64 copy_structure(u32 it,u32 unknown);
u64 copy_basic(u32 obj,u32 heap,u32 unused,u32 pp);
u64 inspect_object(u32 obj);
u64 inspect_pair(u32 obj);
u64 inspect_integer(u64 obj);
u64 inspect_binteger(u64 obj);
u64 inspect_float(u32 f);
u64 inspect_string(u32 obj);
u64 inspect_symbol(u32 obj);
u64 inspect_type(u32 obj);
u64 inspect_structure(u32 obj);
u64 inspect_basic(u32 obj);
u64 inspect_link_block(u32 ob);
u64 inspect_vu_function(u32 obj);
int InitHeapAndSymbol(void);
u64 load(u32 file_name_in,u32 heap_in);
u64 loadb(u32 file_name_in,u32 heap_in,u32 param3);
u64 loadc(const_char *file_name,kheapinfo *heap,u32 flags);
u64 loado(u32 file_name_in,u32 heap_in);
u64 unload(u32 name);
s64 load_and_link(const_char *filename,char *decode_name,kheapinfo *heap,u32 flags);
void network_bootstrapProxy(void);
void jak3_begin(uint8_t *object_file,const_char *name,int32_t size,kheapinfo heap,uint32_t flags);
uint32_t jak3_work(void);
uint32_t jak3_work_opengoal(void);
void jak3_finish(bool jump_from_c_to_goal);
undefined4 link_busy(void);
void link_reset(void);
uint8_t * link_and_exec(uint8_t *data,const_char *name,int32_t size,kheapinfo *heap,uint32_t flags,bool jump_from_c_to_goal);
uint64_t link_begin(u64 *args);
uint64_t link_resume(void);
void ultimate_memcpy_G(void *dst,void *src,uint32_t size);
byte * c_rellink3(int param_1,int param_2,byte *param_3);
byte * c_symlink2(uint *param_1,uint param_2,byte *param_3);
byte * c_symlink3(uint *param_1,uint param_2,byte *param_3);
void update_goal_fns(void);
void InitListener(void);
void ClearPending(void);
void SendAck(void);
void ProcessListenerMessage(char *msg);
int sql_query_sync(String *string_in);
void BeginLoadingDGO(const_char *name,u8 *buffer1,u8 *buffer2,u8 *currentHeap);
u8 * GetNextDGO(u32 *lastObjectFlag);
void ContinueLoadingDGO(u8 *heapPtr);
void LoadDGOTest(void);
void load_and_link_dgo(u64 name_gstr,u64 heap_info,u64 flag,u64 buffer_size);
void load_and_link_dgo_from_c(const_char *name,kheapinfo *heap,u32 linkFlag,s32 bufferSize,bool jump_from_c_to_goal);
int FUN_00270dd0_create_sema(int *param_1);
int FUN_00270e2c_create_sema(int *param_1);
void * FUN_00270e88_identical_to_next(int param_1);
void * FUN_00270f74_identical_to_previous(int param_1);
void FUN_00271060(int param_1);
void * FUN_00271098(int param_1,undefined4 *param_2);
void FUN_002711d0(undefined4 param_1);
void FUN_002711f0(undefined8 param_1,ushort param_2);
void FUN_0027132c(int param_1,short param_2);
void FUN_00271450(int param_1,short param_2);
void FUN_00271684(int param_1);
void FUN_00271798(int param_1);
void FUN_00271918(int param_1,void *param_2);
void FUN_00271978(int param_1,short param_2);
void FUN_00271a94(void);
void FUN_00271a9c_cb(undefined8 param_1);
void cb_format_complete_WG(int param_1,short param_2);
void FUN_00271b88_cb(undefined8 param_1);
void cb_unformat(int param_1,short param_2);
void cb_wait_for_ramdisk_WG(int param_1);
void cb_wait_for_ramdisk_load_WG(undefined8 param_1);
void cb_createfile_erasing_WG(undefined8 param_1,ulong param_2);
void cb_createdir_G(undefined8 param_1,ulong param_2);
void FUN_002720a0_cb(undefined8 param_1,undefined8 param_2);
void FUN_00272314_cb(undefined8 param_1,undefined8 param_2);
void FUN_00272464(undefined8 param_1);
void FUN_00272614_cb(undefined8 param_1,ulong param_2);
void FUN_002726c0_cb(undefined8 param_1,undefined8 param_2);
void FUN_0027273c_cb(undefined8 param_1,undefined8 param_2);
void FUN_002727b8_cb(undefined8 param_1,undefined8 param_2);
void FUN_00272884(undefined8 param_1);
void FUN_00272908_cb(undefined8 param_1,undefined8 param_2);
void FUN_0027293c(undefined8 param_1);
void FUN_002729dc_cb(undefined8 param_1,undefined8 param_2);
void FUN_00272a10(undefined8 param_1);
void FUN_00272a70_cb(undefined8 param_1,undefined8 param_2);
void FUN_00272aa4(undefined8 param_1);
void * FUN_00272b40_cb(undefined8 param_1,undefined8 param_2);
void FUN_00272ca8(undefined8 param_1);
void FUN_00272d04_cb(undefined8 param_1,undefined8 param_2);
void FUN_00272d7c_cb(undefined8 param_1);
void FUN_00272dd8_cb(undefined8 param_1,undefined8 param_2);
void FUN_00272e8c_cb(undefined8 param_1);
void FUN_00272eec_cb(undefined8 param_1,undefined8 param_2);
ulong FUN_00272f20(int param_1,ulong param_2,void *param_3);
ulong FUN_00272f5c(undefined8 param_1,ulong param_2,void *param_3);
undefined4 FUN_00272fa8(int param_1,ulong param_2);
undefined4 cb_check_G(int param_1,uint param_2,undefined4 param_3);
int FUN_0027301c(int param_1);
void FUN_002730e4(void);
void FUN_002732e4(void);
uint Ascii2Sjis(uint param_1);
void ASCII2SJIS_G(char *param_1,char *param_2);
int FUN_002734dc(char *param_1,ulong param_2,ulong param_3,undefined8 param_4);
int FUN_00273554(char *param_1,uint *param_2,int *param_3,undefined8 param_4);
undefined4 sceMc2Init_G_Proxy(void);
int MC_shutdown_G(void);
undefined FUN_00273870_mc(void);
s32 FUN_0027387c(void);
int FUN_00273910_memory_card(void);
void MC_run(void);
u64 MC_format(s32 card_idx);
u64 MC_unformat(s32 card_idx);
u64 MC_createfile(s32 param,u8 *data);
u64 MC_save(s32 card_idx,s32 file_idx,u8 *save_data,u8 *save_summary_data);
undefined4 mc_save_common_S(undefined4 param_1,undefined4 param_2);
undefined4 mc_save_patch_S(undefined4 param_1,undefined4 param_2);
undefined4 mc_save_ghost_S(undefined4 param_1,undefined4 param_2,undefined4 param_3);
u64 MC_load(s32 card_idx,s32 file_idx,u8 *data);
undefined4 mc_load_common_S(undefined4 param_1,undefined4 param_2);
undefined4 mc_load_patch_S(undefined4 param_1,undefined4 param_2);
undefined4 mc_load_ghost_S(undefined4 param_1,undefined4 param_2,undefined4 param_3);
u32 MC_check_result(void);
void MC_get_status(s32 slot,mc_slot_info *info);
uint mc_get_secrets_S(void);
void MC_makefile(s32 port,s32 size);
int MC_set_language(s32 l);
void FUN_00274280(int param_1,long param_2);
void FUN_002743a4(void);
void FUN_002743c0(void);
void FUN_002743dc_dkernel_rpc_callback(int param_1,int *param_2);
void FUN_00274450_dkernel_rpc_callback(int param_1,int *param_2);
void FUN_002744c0_dkernel_rpc_callback(void);
void FUN_002744e0_dkernel_rpc_callback(void);
void FUN_00274500_dkernel_rpc_callback(void);
void FUN_00274520_dkernel_rpc_callback(void);
void FUN_00274540_dkernel_rpc_callback(void);
undefined4 InitUnderlord_S(void);
undefined FUN_00274678(void);
int FUN_00274684_implicit_dkernel_called_in_InitIOP(long param_1,long param_2);
int FUN_0027476c_called_in_DecodeTime_implicit_dkernel(long param_1);
int FUN_0027483c_implicit_dkernel_called_in_InitIOP_too(long param_1);
int loadModuleByString_G(int *param_1,const_char *param_2);
undefined4 UILoadModules(int param_1,int *param_2);
undefined4 FUN_00274cc8(undefined4 *param_1);
undefined4 UIUnloadModules(int param_1,int *param_2);
undefined4 FUN_00274ed4(undefined4 *param_1);
void PowerOffPs2OrDev9_W(long param_1);
int FUN_00274fac_implicit_dkernel_called_in_dnas_load_1(void);
undefined4 FUN_00275034_called_in_dnas_(un)load(undefined4 *param_1);
int FUN_0027504c_implicit_dkernel_called_in_dnas_load_2(void);
undefined4 FUN_002750d0_unlock_dvd_called_in_dnas_unload(undefined4 *param_1);
int FUN_002750e8_implicit_dkernel_called_in_dnas_unload(void);
undefined4 FUN_00275170_load_vagdir_called_in_dnas_unload(undefined4 *param_1);
int FUN_00275188_implicit_dkernel_called_in_dnas_load_3(void);
undefined4 FUN_0027520c(undefined4 *param_1);
int FUN_00275224_implicit_dkernel_called_indirectly_by_psplink_swap_data(undefined4 param_1,undefined4 param_2,long param_3,ulong param_4,long param_5,ulong param_6);
undefined4 FUN_00275364(undefined4 *param_1);
void FUN_0027537c(void);
undefined4 _AddModuleArgs(int startModule_S,long endModule_S);
undefined4 SetOverlayMode_S(int mode_W);
char * CheckOverlayMode_S(void);
bool FUN_00275ac0(void);
char * CatalogOverlayModules_S(void);
void clearFunctionAddress_W(void *function_G);
void * FUN_00275c64(void *param_1);
void HookOrDie_similar_Proxy(void *param_1);
void HookOrDie_similar_proxy_similar_W(int param_1);
long HookOrDie_S(void *param_1,void *param_2,void *param_3);
void HookOrDie_Proxy_G(void *cleared_function_W,void *new,void *old,undefined8 param_4,undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8);
uint HookOrDie_similar_W(long param_1);
undefined4 FUN_00275f90(void);
bool FUN_00276004(uint param_1);
int FUN_002760f8(char *param_1,char *param_2,char param_3);
undefined8 sceCdInitNew(void);
undefined8 sceCdStandbyNew(void);
undefined8 sceCdReadNew(void);
undefined8 sceCdSeekNew(void);
undefined8 sceCdGetErrorNew(void);
undefined8 sceCdGetTocNew(void);
undefined8 sceCdSearchFileNew(void);
undefined8 sceCdSyncNew(void);
undefined8 FUN_002762b8_sce_new(void);
undefined8 sceCdDiskReadyNew(void);
undefined8 sceCdTrayReqNew(void);
undefined8 sceCdStopNew(void);
undefined8 FUN_0027637c_sce_new(void);
long FUN_002763a8_sce_new(undefined8 param_1,long param_2);
undefined8 sceCdPowerOffNew(undefined8 param_1);
undefined8 sceCdStatusNew(void);
undefined8 FUN_002764a8_sce_new(void);
undefined8 sceCdPauseNew(void);
undefined8 sceCdBreakNew(void);
undefined8 FUN_0027652c_sce_new(void);
undefined8 FUN_00276558_sce_new(void);
undefined8 sceCdCtrlADoutNew(void);
undefined8 sceCdReadChainNew(void);
undefined8 sceCdPowerOffNew(void);
undefined8 sceCdMmodeNew(void);
undefined8 sceCdPOffCallbackNew(void);
undefined8 sceCdPowerOff_G_New(void);
undefined8 sceCdLayerSearchFileNew(void);
undefined8 FUN_002766b8_sce_new(void);
undefined8 sceCdInitEeCBNew(void);
undefined8 sceCdReadIOPMemNew(void);
undefined8 sceCdChangeThreadPriorityNew(void);
undefined8 sceCdGetDiskTypeNew(void);
s32 sceOpenNew(const_char *filename,s32 flag);
undefined8 sceCloseNew(long param_1);
size_t sceReadNew(long param_1,long param_2,size_t param_3);
undefined8 sceWriteNew(long param_1,undefined8 param_2,undefined8 param_3);
int SceLseekNew(long param_1,int param_2,long param_3);
undefined8 sceIoctlNew(undefined8 param_1,long param_2,long param_3);
undefined8 FUN_00276b58_sce_new(void);
undefined8 sceMkdirNew(void);
undefined8 sceRmdirNew(void);
undefined8 sceDopenNew(void);
undefined8 sceDcloseNew(void);
undefined8 sceDreadNew(void);
undefined8 sceGetstatNew(void);
undefined8 sceFormatNew(void);
undefined8 sceChstatNew(void);
undefined8 sceRenameNew(void);
undefined8 sceChdirNew(void);
undefined8 sceSyncNew(void);
undefined8 sceMountNew(void);
undefined8 sceUmountNew(void);
undefined8 sceLseek64New(void);
undefined8 sceDevctlNew(undefined8 param_1,long param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6);
undefined8 sceSymlinkNew(void);
undefined8 sceReadlinkNew(void);
undefined8 sceIoctl2New(void);
void sceGsResetGraphNew(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4);
void sceGsSyncVNew(void);
void initSceFunctions_W(bool param_1,long param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8);
void initSceFunctionsTrue_G(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8);
void initSceFunctionsFalse_G(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8);
int RpcCallEndFunction_W(long param_1);
s32 InitRPC(void);
s32 RpcCallProxy(s32 rpcChannel,u32 fno,bool async,void *sendBuff,s32 sendSize,void *recvBuff,s32 recvSize);
s32 RpcCall(s32 rpcChannel,u32 fno,bool async,void *sendBuff,s32 sendSize,void *recvBuff,s32 recvSize,void *callback);
u32 RpcBusy(s32 channel);
void RpcSync(s32 channel);
s32 RpcBind(s32 channel,s32 id);
undefined setStallMsg_G(undefined param_1);
undefined Is_RPC_Initialized_G(void);
int fmv_get_mem_requirements_S(uint param_1,uint param_2,uint param_3);
undefined4 fmv_player_init_S(PlayerParams *param_1);
void fmv_player_start_S(uint param_1,uint param_2);
undefined4 fmv_player_stop_S(int param_1);
void fmv_player_set_pause_S(uint param_1);
undefined4 fmv_player_work_S(void);
void fmv_player_idle_S(void);
void fmv_player_set_caption_S(DmaTag *param_1);
undefined4 fmv_player_get_caption_S(void);
DmaTag * fmv_player_get_texture_S(void);
void fmv_player_rewind_S(void);
void fmv_player_terminate_S(void);
long FUN_00278d78(undefined8 param_1,long param_2);
undefined4 psplink_start_S(void);
undefined4 psplink_stop_S(void);
int psplink_poll_S(void);
long pspLinkSwapData_WS(long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5);
undefined4 FUN_00279298(int param_1);
undefined8 psplink_swap_data_S(long param_1,undefined4 param_2,long param_3);
long psplink_check_swap_data_S(long param_1);
void FUN_00279484(int param_1,long param_2);
void FUN_002794f4(void);
void FUN_00279510(void);
int dnas_load_S(void);
undefined4 dnas_unload_S(void);
undefined8 dnas_init_S(void);
undefined4 dnas_shutdown_S(void);
undefined4 dnas_abort_S(void);
undefined4 dnas_auth_net_start_S(void);
undefined4 dnas_auth_get_unique_id_S(void);
undefined4 dnas_auth_install_S(void);
undefined4 dnas_get_status_S(void);
void dnas_inst_init_mc_S(void);
void dnas_inst_personalize_data_length_mc_S(void);
void dnas_inst_personalize_data_mc_S(void);
void dnas_inst_shutdown_mc_S(void);
undefined8 FUN_00279c54(void);
int FUN_00279d50(void *param_1);
int FUN_00279db0(undefined4 param_1,void *param_2);
int FUN_00279e20(undefined4 param_1,void *param_2);
int FUN_00279e90(int param_1);
int FUN_00279ef0(void);
void knet_scert_net_get_nat_service_S(void);
void knet_patch_S(void);
uint knet_patch_hash_S(int param_1,int param_2);
void knet_get_static_patches_S(void);
void knet_get_dynamic_patches_S(void);
void knet_scert_function_0_args_S(void);
void knet_scert_function_1_args_S(void);
void knet_scert_function_2_args_S(void);
void knet_scert_function_3_args_S(void);
void knet_scert_function_4_args_S(void);
void knet_scert_function_5_args_S(void);
void knet_scert_function_6_args_S(void);
void knet_scert_function_7_args_S(void);
void knet_scert_function_8_args_S(void);
void knet_scert_function_9_args_S(void);
void knet_scert_function_10_args_S(void);
undefined4 * knet_scert_get_extra_params_S(void);
undefined knet_dev9_present_S(void);
char * knet_get_kernel_version_string_S(void);
undefined8 knet_get_disc_flags_S(void);
uint knet_crc_S(const_uchar *param_1,int param_2);
char * knet_get_scus_S(void);
int network_bootstrap_S(void);
int knet_test_S(undefined8 param_1);
void knet_file_erase_S(undefined8 param_1);
void knet_get_local_rtc_S(long param_1);
int knet_dopen_S(const_char *param_1);
int knet_dclose_S(int param_1);
int knet_dread_S(int param_1,sce_dirent *param_2);
int knet_mkdir_S(const_char *param_1,int param_2);
undefined4 knet_eenet_bytes_used_S(void);
void FUN_0027a5b4_dns_lookup_threaded(void);
s32 knet_eenet_dns_start_S(char *param_1);
undefined4 knet_eenet_dns_poll_S(int *param_1);
void knet_eenet_get_dns_addr_S(undefined8 param_1,undefined8 param_2);
void knet_yield_S(void);
undefined4 FUN_0027a7ac(void);
undefined * knet_eenet_get_configname_S(void);
void knet_eenet_set_filter_S(undefined4 param_1);
long _EzNetStartConfig_S(void);
long _EzNetFetchConfig_G(long param_1);
undefined4 _EzNetStopConfig_G(void);
void * FUN_0027abc8_print_stats(void *param_1,undefined8 param_2);
long _EzNetStartHw_S(void);
long _EzNetStopHw_Q(long param_1);
long knet_eenet_start_hw_S(void);
long knet_eenet_poll_is_started_S(long param_1);
long knet_eenet_shutdown_S(void);
long knet_eenet_poll_is_shutdown_S(void);
undefined * knet_eenet_get_config_list_S(void);
undefined4 knet_eenet_get_mac_S(undefined8 param_1);
int FUN_0027bc48_eenet_headset(void);
void lgAudTick_W(void);
void knet_lg_init_S(void);
undefined4 knet_lg_read_S(undefined8 param_1,undefined4 param_2);
undefined4 knet_lg_write_S(undefined8 param_1,undefined4 param_2);
void knet_lg_tick_S(void);
bool knet_lg_got_headset_S(void);
long knet_lg_set_recording_S(bool param_1);
long knet_lg_set_playback_S(bool param_1);
undefined4 knet_lg_bytes_avail_S(void);
undefined4 knet_lg_bytes_in_playback_queue_S(void);
undefined8 knet_lg_aread_S(undefined8 param_1,undefined8 param_2,long param_3);
undefined8 knet_lg_awrite_S(undefined8 param_1,undefined8 param_2,long param_3);
long knet_lg_async_S(long param_1);
void FUN_0027c204_set_smt_in_knet(bool param_1);
void FUN_0027c260_usb(void);
void FUN_0027c2a4_usb(void);
bool FUN_0027c2ec(void);
void FUN_0027c320(long param_1);
void calloc_func_implementation_W(int param_1,int param_2);
void knet_nm_init_Proxied_G(void *param_1,void *param_2);
void knet_nm_init_S(void *param_1,void *param_2);
void knet_nm_encode_S(undefined8 param_1);
void knet_nm_decode_S(undefined8 param_1,int param_2);
bool knet_nm_decoder_needs_input_S(int param_1);
void knet_nm_decode3_S(undefined4 *param_1,int *param_2);
void knet_nm_decode4_S(undefined4 *param_1,int *param_2);
undefined8 knet_nm_reset_decoder_S(int param_1);
undefined8 knet_nm_reset_encoder_S(void);
undefined4 knet_udp_errno_S(void);
long knet_udp_socket_open_S(undefined2 param_1);
void knet_udp_socket_close_S(void);
undefined4 knet_udp_socket_sendto_S(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined2 param_5);
int knet_udp_socket_recvfrom_S(void);
undefined4 knet_tcp_errno_S(void);
long knet_tcp_socket_open_S(ulong param_1);
void knet_tcp_socket_close_S(void);
undefined4 knet_tcp_socket_send_S(void);
undefined4 knet_tcp_socket_recv_S(void);
void knet_tcp_set_sockopt_S(void);
void knet_tcp_socket_connect_S(undefined8 param_1,undefined8 param_2,undefined2 param_3);
void knet_tcp_socket_poll_S(undefined4 param_1,undefined2 param_2);
void knetGetStaticPatches_WS(undefined4 *param_1,undefined4 *param_2);
void knetGetDynamicPatches_WS(undefined4 *param_1,undefined4 *param_2);
void FUN_0027cc90_patch(int *param_1,int param_2);
undefined4 FUN_0027cf44_KM(void);
undefined8 FUN_0027cf50_KM(undefined8 *param_1,undefined8 *param_2);
undefined4 KM_GetMediusPublicKey(long param_1);
void FUN_0027d108(void);
void FUN_0027d160(void);
void FUN_0027d178(void);
void SceInitTrueProxy_W(void);
undefined4 read_clock_code(void);

