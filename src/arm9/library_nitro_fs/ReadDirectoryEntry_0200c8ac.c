#include "nitro/types.h"

#define ATTRIBUTE_IS_DIRECTORY 0x100
#define ATTRIBUTE_IS_OFFLINE 0x400

typedef struct ArchiveContext {
    u32 base;
    u32 fat;
    u32 fatSize;
} ArchiveContext;

typedef struct Archive {
    u8 pad_00[0x20];
    ArchiveContext *context;
} Archive;

typedef struct FatEntry {
    u32 top;
    u32 bottom;
} FatEntry;

typedef struct TableReadParam {
    Archive *arc;
    u32 pos;
} TableReadParam;

typedef struct DirEntry {
    union {
        struct {
            Archive *arc;
            u32 fileId;
        } file;
        struct {
            Archive *arc;
            u16 ownId;
            u16 index;
            u32 pos;
        } dir;
    } id;
    u32 isDirectory;
    u32 nameLength;
    char name[128];
} DirEntry;

typedef struct File {
    u8 pad_00[0x30];
    DirEntry *entry;
    BOOL skipString;
} File;

typedef struct DateTime {
    u32 year;
    u32 month;
    u32 day;
    u32 hour;
    u32 minute;
    u32 second;
} DateTime;

typedef struct DirectoryEntryInfo {
    char shortName[16];
    u32 shortNameLength;
    char longName[260];
    u32 longNameLength;
    u32 attributes;
    DateTime accessTime;
    DateTime modifyTime;
    DateTime createTime;
    u32 fileSize;
    u32 id;
} DirectoryEntryInfo;

extern int func_0200c6fc(File *file, u32 command, BOOL blocking);
extern void MI_CpuCopy8_01ff89a8(const void *src, void *dst, u32 size);
extern int RunStreamOp_0200be04(TableReadParam *param, void *buffer, u32 size);
extern BOOL func_0200d2ac(Archive *arc, u32 offset);

int ReadDirectoryEntry_0200c8ac(Archive *arc, File *file, DirectoryEntryInfo *info)
{
    int result;
    DirEntry entry;

    file->entry = &entry;
    file->skipString = FALSE;
    result = func_0200c6fc(file, 3, TRUE);
    if (result == 0) {
        info->shortNameLength = 0;
        info->longNameLength = entry.nameLength;
        MI_CpuCopy8_01ff89a8(entry.name, info->longName, info->longNameLength);
        info->longName[info->longNameLength] = '\0';
        if (entry.isDirectory) {
            info->attributes = ATTRIBUTE_IS_DIRECTORY;
            info->id = (u32)(entry.id.dir.ownId | (entry.id.dir.index << 16));
            info->fileSize = 0;
        } else {
            info->attributes = 0;
            info->id = entry.id.file.fileId;
            info->fileSize = 0;
            {
                ArchiveContext *const context = arc->context;
                u32 pos = info->id * sizeof(FatEntry);

                if (pos < context->fatSize) {
                    FatEntry fat;
                    TableReadParam param;

                    param.arc = arc;
                    param.pos = context->fat + pos;
                    if (RunStreamOp_0200be04(&param, &fat, sizeof(fat)) == 0) {
                        info->fileSize = fat.bottom - fat.top;
                        if (func_0200d2ac(arc, fat.top)) {
                            info->attributes |= ATTRIBUTE_IS_OFFLINE;
                        }
                    }
                }
            }
        }
        info->modifyTime.year = 0;
        info->modifyTime.month = 0;
        info->modifyTime.day = 0;
        info->modifyTime.hour = 0;
        info->modifyTime.minute = 0;
        info->modifyTime.second = 0;
    }
    return result;
}
