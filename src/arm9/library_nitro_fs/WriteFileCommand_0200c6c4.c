#include "nitro/types.h"

struct Archive;

typedef int (*ArchiveWriteFunc)(struct Archive *arc, const void *src, u32 pos, u32 len);

typedef struct ArchiveContext {
    u8 pad_00[0x20];
    void *readFunc;
    ArchiveWriteFunc writeFunc;
} ArchiveContext;

typedef struct Archive {
    u8 pad_00[0x20];
    ArchiveContext *context;
} Archive;

typedef struct File {
    u8 pad_00[8];
    Archive *arc;
    u8 pad_0c[0x2c - 0x0c];
    u32 position;
    const void *src;
    u32 lengthRequested;
    u32 length;
} File;

int WriteFileCommand_0200c6c4(File *file)
{
    Archive *const arc = file->arc;
    ArchiveContext *const context = arc->context;
    const u32 position = file->position;
    const u32 length = file->length;
    const void *const src = file->src;

    file->position += length;
    return (*context->writeFunc)(arc, src, position, length);
}
