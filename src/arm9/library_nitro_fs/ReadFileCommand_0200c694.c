#include "nitro/types.h"

struct Archive;

typedef int (*ArchiveReadFunc)(struct Archive *arc, void *dst, u32 pos, u32 len);

typedef struct ArchiveContext {
    u8 pad_00[0x20];
    ArchiveReadFunc readFunc;
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
    void *dst;
    u32 lengthRequested;
    u32 length;
} File;

int ReadFileCommand_0200c694(File *file)
{
    Archive *const arc = file->arc;
    ArchiveContext *const context = arc->context;
    const u32 position = file->position;
    const u32 length = file->length;
    void *const dst = file->dst;

    file->position += length;
    return (*context->readFunc)(arc, dst, position, length);
}
