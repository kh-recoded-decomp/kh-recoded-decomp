#include "nitro/types.h"

#define FS_RESULT_SUCCESS 0
#define FS_RESULT_ERROR 5

#define FS_ATTRIBUTE_IS_DIRECTORY 0x100
#define FS_ATTRIBUTE_IS_PROTECTED 0x200
#define FS_ATTRIBUTE_IS_OFFLINE 0x400

typedef struct RomFatContext {
    u32 base;
    u32 fat;
    u32 fatSize;
} RomFatContext;

typedef struct RomFatArchive {
    u8 pad_00[0x20];
    RomFatContext *context;
} RomFatArchive;

typedef struct RomFatEntry {
    u32 top;
    u32 bottom;
} RomFatEntry;

typedef struct TableReadParam {
    RomFatArchive *arc;
    u32 pos;
} TableReadParam;

typedef struct DateTime {
    u32 year;
    u32 month;
    u32 day;
    u32 hour;
    u32 minute;
    u32 second;
} DateTime;

typedef struct PathInfo {
    u32 attributes;
    DateTime ctime;
    DateTime mtime;
    DateTime atime;
    u32 fileSize;
    u32 id;
} PathInfo;

extern void func_01ff8830(void *dst, int value, u32 size);
extern int FSi_ROMFAT_FindPath_0200c9d4(RomFatArchive *arc, u32 baseDirId, const char *path, u32 *targetId, BOOL targetIsDirectory);
extern int RunStreamOp_0200be04(TableReadParam *param, void *buffer, u32 size);
extern BOOL func_0200d2ac(RomFatArchive *arc, u32 offset);

int FSi_ROMFAT_GetPathInfo_0200cde0(RomFatArchive *arc, u32 baseDirId, const char *path, PathInfo *info)
{
    int result = FS_RESULT_ERROR;
    u32 id = 0;

    func_01ff8830(info, 0, sizeof(*info));
    if (FSi_ROMFAT_FindPath_0200c9d4(arc, baseDirId, path, &id, TRUE) == FS_RESULT_SUCCESS) {
        info->attributes = FS_ATTRIBUTE_IS_DIRECTORY;
        info->id = id;
        result = FS_RESULT_SUCCESS;
    } else if (FSi_ROMFAT_FindPath_0200c9d4(arc, baseDirId, path, &id, FALSE) == FS_RESULT_SUCCESS) {
        info->attributes = 0;
        info->id = id;
        info->fileSize = 0;
        {
            RomFatContext *context = arc->context;
            u32 pos = id * sizeof(RomFatEntry);
            if (pos < context->fatSize) {
                RomFatEntry entry;
                TableReadParam param;
                param.arc = arc;
                param.pos = context->fat + pos;
                if (RunStreamOp_0200be04(&param, &entry, sizeof(entry)) == FS_RESULT_SUCCESS) {
                    info->fileSize = entry.bottom - entry.top;
                    if (func_0200d2ac(arc, entry.top)) {
                        info->attributes |= FS_ATTRIBUTE_IS_OFFLINE;
                    }
                }
            }
        }
        result = FS_RESULT_SUCCESS;
    }
    info->attributes |= FS_ATTRIBUTE_IS_PROTECTED;
    return result;
}
