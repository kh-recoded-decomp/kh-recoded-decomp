#include "nitro/types.h"

typedef struct FileID {
    void *arc;
    u32 fileId;
} FileID;

typedef struct OpenFileFastArgs {
    u32 fileId;
    u32 mode;
} OpenFileFastArgs;

typedef struct File {
    u8 pad_00[8];
    void *arc;
    u32 stat;
    void *argument;
} File;

extern BOOL func_0200a930(File *file, u32 command, BOOL blocking);

BOOL OpenFileFast_0200b4d4(File *file, FileID id)
{
    BOOL result = FALSE;

    if (id.arc != NULL) {
        OpenFileFastArgs args;

        file->arc = id.arc;
        file->argument = &args;
        args.fileId = id.fileId;
        args.mode = 0;
        result = func_0200a930(file, 6, TRUE);
    }
    return result;
}
