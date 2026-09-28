#include "nitro/types.h"

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

typedef struct File {
    u8 pad_00[8];
    Archive *arc;
    u8 pad_0c[0x30 - 0x0c];
    union {
        struct {
            Archive *arc;
            u32 fileId;
        } openFast;
        struct {
            u32 top;
            u32 bottom;
            u32 index;
        } openDirect;
    } arg;
} File;

extern int RunStreamOp_0200be04(TableReadParam *param, void *buffer, u32 size);
extern int func_0200c6fc(File *file, u32 command, BOOL blocking);

int OpenFileFastCommand_0200c5e8(File *file)
{
    int result;
    Archive *const arc = file->arc;
    ArchiveContext *const context = arc->context;
    const u32 index = file->arg.openFast.fileId;
    u32 pos = index * sizeof(FatEntry);
    FatEntry fat;
    TableReadParam param;

    if (pos >= context->fatSize) {
        return 11;
    }
    param.arc = arc;
    param.pos = context->fat + pos;
    result = RunStreamOp_0200be04(&param, &fat, sizeof(fat));
    if (result != 0) {
        return result;
    }
    file->arg.openDirect.top = fat.top;
    file->arg.openDirect.bottom = fat.bottom;
    file->arg.openDirect.index = index;
    return func_0200c6fc(file, 7, TRUE);
}
