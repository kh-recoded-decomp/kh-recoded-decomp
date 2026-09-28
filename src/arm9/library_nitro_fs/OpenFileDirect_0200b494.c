#include "nitro/types.h"

typedef struct OpenFileDirectArgs {
    u32 index;
    u32 top;
    u32 bottom;
    u32 mode;
} OpenFileDirectArgs;

typedef struct File {
    u8 pad_00[8];
    void *arc;
    u32 stat;
    void *argument;
} File;

extern BOOL func_0200a930(File *file, u32 command, BOOL blocking);

BOOL OpenFileDirect_0200b494(File *file, void *arc, u32 imageTop, u32 imageBottom, u32 fileIndex)
{
    OpenFileDirectArgs args;

    file->arc = arc;
    file->argument = &args;
    args.index = fileIndex;
    args.top = imageTop;
    args.bottom = imageBottom;
    args.mode = 0;
    return func_0200a930(file, 7, TRUE);
}
