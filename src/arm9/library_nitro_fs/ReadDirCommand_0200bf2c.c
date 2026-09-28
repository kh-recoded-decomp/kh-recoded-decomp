#include "nitro/types.h"

typedef struct {
    void *arc;
    u32 pos;
} SyncReadParam;

typedef struct {
    void *arc;
    union {
        struct {
            u16 ownId;
            u16 index;
        } dir;
        u32 fileId;
    } id;
    u32 dirPos;
    u32 isDirectory;
    u32 nameLen;
    char name[1];
} DirEntry;

typedef struct {
    u8 pad_00[8];
    void *arc;
    u8 pad_0c[0x1a];
    u16 index;
    u32 pos;
    u8 pad_2c[4];
    DirEntry *entry;
    int skipString;
} DirCommand;

extern int RunStreamOp_0200be04(void *cursor, void *buffer, u32 size);

int ReadDirCommand_0200bf2c(DirCommand *dir) {
    int result;
    DirEntry *entry = dir->entry;
    u8 len;
    SyncReadParam param;

    param.arc = dir->arc;
    param.pos = dir->pos;

    result = RunStreamOp_0200be04(&param, &len, 1);
    if (result != 0) {
        return result;
    }

    entry->nameLen = len & 0x7f;
    entry->isDirectory = (len >> 7) & 1;

    if (entry->nameLen == 0) {
        result = 1;
        return result;
    }

    if (!dir->skipString) {
        result = RunStreamOp_0200be04(&param, entry->name, entry->nameLen);
        if (result != 0) {
            return result;
        }
        entry->name[entry->nameLen] = 0;
    } else {
        param.pos += entry->nameLen;
    }

    if (entry->isDirectory == 0) {
        entry->arc = dir->arc;
        entry->id.fileId = dir->index;
        dir->index++;
    } else {
        u16 id;
        result = RunStreamOp_0200be04(&param, &id, 2);
        if (result == 0) {
            entry->arc = dir->arc;
            entry->id.dir.ownId = id & 0xfff;
            entry->id.dir.index = 0;
            entry->dirPos = 0;
        }
    }

    if (result == 0) {
        dir->pos = param.pos;
    }
    return result;
}
