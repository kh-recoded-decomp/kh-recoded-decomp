/* The file system: archives, files, overlays, as the library sources declare them (the NitroSDK / NitroSystem names). */
#ifndef NITRO_FS_H
#define NITRO_FS_H

#include "nitro/types.h"
#include "nitro/mi.h"
#include "nitro/os.h"
#include "nitro/card.h"

struct FSArcListGlobal;
struct FSArchive;
struct FSArchiveFAT;
struct FSArchiveFNT;
struct FSArchiveName;
struct FSFile;
struct FSFileLink;

enum {
    FS_ARCHIVE_NAME_LEN_MAX = 3
};

typedef enum {
    FS_COMMAND_ASYNC_BEGIN = 0,
    FS_COMMAND_READFILE = FS_COMMAND_ASYNC_BEGIN,
    FS_COMMAND_WRITEFILE,
    FS_COMMAND_ASYNC_END,
    FS_COMMAND_SYNC_BEGIN = FS_COMMAND_ASYNC_END,
    FS_COMMAND_SEEKDIR = FS_COMMAND_SYNC_BEGIN,
    FS_COMMAND_READDIR,
    FS_COMMAND_FINDPATH,
    FS_COMMAND_GETPATH,
    FS_COMMAND_OPENFILEFAST,
    FS_COMMAND_OPENFILEDIRECT,
    FS_COMMAND_CLOSEFILE,
    FS_COMMAND_SYNC_END,
    FS_COMMAND_STATUS_BEGIN = FS_COMMAND_SYNC_END,
    FS_COMMAND_ACTIVATE = FS_COMMAND_STATUS_BEGIN,
    FS_COMMAND_IDLE,
    FS_COMMAND_SUSPEND,
    FS_COMMAND_RESUME,
    FS_COMMAND_STATUS_END,
    FS_COMMAND_INVALID
} FSCommandType;

typedef enum {
    FS_RESULT_SUCCESS = 0,
    FS_RESULT_FAILURE,
    FS_RESULT_BUSY,
    FS_RESULT_CANCELED,
    FS_RESULT_CANCELLED = FS_RESULT_CANCELED,
    FS_RESULT_UNSUPPORTED,
    FS_RESULT_ERROR,
    FS_RESULT_PROC_ASYNC,
    FS_RESULT_PROC_DEFAULT,
    FS_RESULT_PROC_UNKNOWN
} FSResult;

typedef FSResult (*FS_ARCHIVE_PROC_FUNC) (struct FSFile *, FSCommandType);

typedef FSResult (*FS_ARCHIVE_READ_FUNC) (struct FSArchive * p, void * dst, u32 pos, u32 size);

typedef FSResult (*FS_ARCHIVE_WRITE_FUNC) (struct FSArchive * p, const void * src, u32 pos, u32 size);

typedef struct FSFileLink {
    struct FSFile * prev;
    struct FSFile * next;
} FSFileLink;

typedef struct FSArchive {
    union {
        char ptr[FS_ARCHIVE_NAME_LEN_MAX + 1];
        u32 pack;
    } name;
    struct FSArchive * next;
    struct FSArchive * prev;
    OSThreadQueue sync_q;
    OSThreadQueue stat_q;
    u32 flag;
    FSFileLink list;
    u32 base;
    u32 fat;
    u32 fat_size;
    u32 fnt;
    u32 fnt_size;
    u32 fat_bak;
    u32 fnt_bak;
    void * load_mem;
    FS_ARCHIVE_READ_FUNC read_func;
    FS_ARCHIVE_WRITE_FUNC write_func;
    FS_ARCHIVE_READ_FUNC table_func;
    FS_ARCHIVE_PROC_FUNC proc;
    u32 proc_flag;
} FSArchive;

typedef struct {
    struct FSArchive * arc;
    u16 own_id;
    u16 index;
    u32 pos;
} FSDirPos;

typedef struct {
    struct FSArchive * arc;
    u32 file_id;
} FSFileID;

typedef struct {
    union {
        FSFileID file_id;
        FSDirPos dir_id;
    };
    u32 is_directory;
    u32 name_len;
    char name[127 + 1];
} FSDirEntry;

typedef struct {
    FSDirPos pos;
} FSSeekDirInfo;

typedef struct {
    FSDirEntry * p_entry;
    BOOL skip_string;
} FSReadDirInfo;

typedef struct {
    FSDirPos pos;
    const char * path;
    BOOL find_directory;
    union {
        FSFileID * file;
        FSDirPos * dir;
    }
    result;
} FSFindPathInfo;

typedef struct {
    u8 * buf;
    u32 buf_len;
    u16 total_len;
    u16 dir_id;
} FSGetPathInfo;

typedef struct {
    FSFileID id;
} FSOpenFileFastInfo;

typedef struct {
    u32 top;
    u32 bottom;
    u32 index;
} FSOpenFileDirectInfo;

typedef struct {
    u32 reserved;
} FSCloseFileInfo;

typedef struct {
    void * dst;
    u32 len_org;
    u32 len;
} FSReadFileInfo;

typedef struct {
    const void * src;
    u32 len_org;
    u32 len;
} FSWriteFileInfo;

typedef struct FSFile {
    FSFileLink link;
    struct FSArchive * arc;
    u32 stat;
    FSCommandType command;
    FSResult error;
    OSThreadQueue queue[1];
    union {
        struct {
            u32 own_id;
            u32 top;
            u32 bottom;
            u32 pos;
        } file;
        struct {
            FSDirPos pos;
            u32 parent;
        } dir;
    }
    prop;
    union {
        FSReadFileInfo readfile;
        FSWriteFileInfo writefile;
        FSSeekDirInfo seekdir;
        FSReadDirInfo readdir;
        FSFindPathInfo findpath;
        FSGetPathInfo getpath;
        FSOpenFileFastInfo openfilefast;
        FSOpenFileDirectInfo openfiledirect;
        FSCloseFileInfo closefile;
    } arg;
} FSFile;

#define FS_ARCHIVE_FLAG_CANCELING 0x00000020

#define FS_FILE_STATUS_CANCEL 0x00000002

typedef int (*FSArchiveReadProc)(char **arc, void *dst, u32 off, u32 len);

typedef int (*FSArchiveWriteProc)(char **arc, const void *src, u32 off, u32 len);

#define FS_FILE_NAME_MAX    127

#define FS_DMA_NOT_USE      ((u32) ~0)

typedef enum {
    FS_SEEK_SET,
    FS_SEEK_CUR,
    FS_SEEK_END
} FSSeekFileMode;

#define FS_FILE_STATUS_BUSY                 0x00000001

#define FS_FILE_STATUS_SYNC                 0x00000004

#define FS_FILE_STATUS_ASYNC                0x00000008

#define FS_FILE_STATUS_IS_FILE              0x00000010

#define FS_FILE_STATUS_IS_DIR               0x00000020

#define FS_FILE_STATUS_OPERATING            0x00000040

#define FS_ARCHIVE_FLAG_REGISTER              0x00000001

#define FS_ARCHIVE_FLAG_LOADED                0x00000002

#define FS_ARCHIVE_FLAG_TABLE_LOAD            0x00000004

#define FS_ARCHIVE_FLAG_SUSPEND               0x00000008

#define FS_ARCHIVE_FLAG_RUNNING               0x00000010

#define FS_ARCHIVE_FLAG_SUSPENDING            0x00000040

#define FS_ARCHIVE_FLAG_UNLOADING             0x00000080

#define FS_ARCHIVE_FLAG_IS_ASYNC              0x00000100

#define FS_ARCHIVE_FLAG_IS_SYNC               0x00000200

#define FS_ARCHIVE_PROC_READFILE        (1 << FS_COMMAND_READFILE)

#define FS_ARCHIVE_PROC_WRITEFILE       (1 << FS_COMMAND_WRITEFILE)

#define FS_ARCHIVE_PROC_ASYNC           (FS_ARCHIVE_PROC_READFILE | FS_ARCHIVE_PROC_WRITEFILE)

#define FS_ARCHIVE_PROC_SEEKDIR         (1 << FS_COMMAND_SEEKDIR)

#define FS_ARCHIVE_PROC_READDIR         (1 << FS_COMMAND_READDIR)

#define FS_ARCHIVE_PROC_FINDPATH        (1 << FS_COMMAND_FINDPATH)

#define FS_ARCHIVE_PROC_GETPATH         (1 << FS_COMMAND_GETPATH)

#define FS_ARCHIVE_PROC_OPENFILEFAST    (1 << FS_COMMAND_OPENFILEFAST)

#define FS_ARCHIVE_PROC_OPENFILEDIRECT  (1 << FS_COMMAND_OPENFILEDIRECT)

#define FS_ARCHIVE_PROC_CLOSEFILE       (1 << FS_COMMAND_CLOSEFILE)

#define FS_ARCHIVE_PROC_SYNC \
    (FS_ARCHIVE_PROC_SEEKDIR | FS_ARCHIVE_PROC_READDIR | \
     FS_ARCHIVE_PROC_FINDPATH | FS_ARCHIVE_PROC_GETPATH | \
     FS_ARCHIVE_PROC_OPENFILEFAST | FS_ARCHIVE_PROC_OPENFILEDIRECT | FS_ARCHIVE_PROC_CLOSEFILE)

#define FS_ARCHIVE_PROC_ACTIVATE        (1 << FS_COMMAND_ACTIVATE)

#define FS_ARCHIVE_PROC_IDLE            (1 << FS_COMMAND_IDLE)

#define FS_ARCHIVE_PROC_SUSPENDING      (1 << FS_COMMAND_SUSPEND)

#define FS_ARCHIVE_PROC_RESUME          (1 << FS_COMMAND_RESUME)

#define FS_ARCHIVE_PROC_STATUS \
    (FS_ARCHIVE_PROC_ACTIVATE | FS_ARCHIVE_PROC_IDLE | FS_ARCHIVE_PROC_SUSPENDING | FS_ARCHIVE_PROC_RESUME)

#define FS_ARCHIVE_PROC_ALL (~0)

typedef struct FSArchiveFAT {
    u32 top;
    u32 bottom;
} FSArchiveFAT;

typedef struct FSArchiveFNT {
    u32 start;
    u16 index;
    u16 parent;
} FSArchiveFNT;

typedef struct {
    FSArchive *arc;
    u32 pos;
} FSiSyncReadParam;

typedef u32 FSOverlayID;

typedef void (*FSOverlayInitFunc)(void);

typedef struct {
    u32 id;                       /* 0x00 */
    u8 *ram_address;              /* 0x04 */
    u32 ram_size;                 /* 0x08 */
    u32 bss_size;                 /* 0x0c */
    FSOverlayInitFunc *sinit_init;        /* 0x10 */
    FSOverlayInitFunc *sinit_init_end;    /* 0x14 */
    u32 file_id;                  /* 0x18 */
    u32 compressed : 24;          /* 0x1c */
    u32 flag : 8;
} FSOverlayInfoHeader;

typedef struct {
    FSOverlayInfoHeader header;   /* 0x00 */
    MIProcessor target;           /* 0x20 */
    CARDRomRegion file_pos;       /* 0x24 */
} FSOverlayInfo;

#define FS_OVERLAY_FLAG_COMP      0x0001

#define FS_OVERLAY_FLAG_AUTH      0x0002

#define FS_OVERLAY_DIGEST_SIZE    20

typedef struct FSArchiveName {
    u32 pack;
} FSArchiveName;

struct FSArcListGlobal {
    FSArchive *arc_list;
    FSDirPos current_dir_pos;
};

#define FSi_WriteDummyCallback DefaultStepDone

#define FSi_ReadDummyCallback DefaultStepDone_2

#endif
