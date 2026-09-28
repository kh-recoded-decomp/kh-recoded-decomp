#include "nitro/types.h"

typedef int (*ArchiveReadFunc)(void *arc, void *dst, u32 pos, u32 size);
typedef int (*ArchiveWriteFunc)(void *arc, const void *src, u32 pos, u32 size);

typedef struct RomFatContext {
    u32 base;
    u32 fat;
    u32 fatSize;
    u32 fnt;
    u32 fntSize;
    u32 fatBackup;
    u32 fntBackup;
    void *loadMemory;
    ArchiveReadFunc readFunc;
    ArchiveWriteFunc writeFunc;
} RomFatContext;

typedef struct RomFatArchive {
    u8 pad_00[0x28];
    RomFatContext context;
} RomFatArchive;

extern int func_0200cf5c(void *arc, void *dst, u32 pos, u32 size);
extern int func_0200cf84(void *arc, const void *src, u32 pos, u32 size);
extern BOOL FS_MountArchive_0200b044(RomFatArchive *arc, void *userdata, const void *vtbl, u32 reserved);
extern const void *data_020529e0;

BOOL FS_LoadArchive_0200cfb0(RomFatArchive *arc, u32 base, u32 fat, u32 fatSize, u32 fnt, u32 fntSize,
                             ArchiveReadFunc readFunc, ArchiveWriteFunc writeFunc)
{
    RomFatContext *context = &arc->context;

    context->base = base;
    context->fatSize = fatSize;
    context->fat = fat;
    context->fatBackup = fat;
    context->fntSize = fntSize;
    context->fnt = fnt;
    context->fntBackup = fnt;
    context->readFunc = (readFunc != NULL) ? readFunc : func_0200cf5c;
    context->writeFunc = (writeFunc != NULL) ? writeFunc : func_0200cf84;
    context->loadMemory = NULL;
    return FS_MountArchive_0200b044(arc, context, &data_020529e0, 0);
}
