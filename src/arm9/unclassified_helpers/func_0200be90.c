#include "nitro/types.h"

typedef struct {
    u32 start;
    u16 index;
    u16 parent;
} FntEntry;

typedef struct {
    void *arc;
    u32 pos;
} ReadParam;

typedef struct {
    u8 pad_00[0xc];
    u32 base2;
} TableInfo;

typedef struct {
    u8 pad_00[0x20];
    TableInfo *info;
} Archive;

typedef struct {
    u32 arc;
    u16 ownId;
    u16 index;
    u32 pos;
} DirPos;

typedef struct {
    u8 pad_00[8];
    Archive *arc;
    u8 pad_0c[0x14];
    DirPos dirPos;
    u32 parent;
    DirPos seekArg;
} DirFile;

extern int RunStreamOp_0200be04(ReadParam *param, void *dst, u32 size);

int func_0200be90(DirFile *dir)
{
    Archive *arc;
    TableInfo *info;
    DirPos *arg;
    FntEntry entry;
    ReadParam param;
    int result;

    arc = dir->arc;
    info = arc->info;
    arg = &dir->seekArg;
    param.arc = arc;
    param.pos = info->base2 + arg->ownId * 8;

    result = RunStreamOp_0200be04(&param, &entry, 8);
    if (result == 0) {
        dir->dirPos = *arg;
        if (arg->index == 0 && arg->pos == 0) {
            dir->dirPos.index = entry.index;
            dir->dirPos.pos = info->base2 + entry.start;
        }
        dir->parent = entry.parent & 0xfff;
    }
    return result;
}
