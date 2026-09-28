#include "nitro/types.h"

typedef struct FileID {
    void *arc;
    u32 fileId;
} FileID;

typedef struct FindPathArgs {
    u32 baseId;
    const char *relativePath;
    u32 targetId;
    BOOL targetIsDirectory;
} FindPathArgs;

typedef struct File {
    u8 pad_00[8];
    void *arc;
    u32 stat;
    void *argument;
    u8 pad_14[0x48 - 0x14];
} File;

extern void *func_0200ac28(const char *path, u32 *baseId, char *relativePath);
extern void func_0200b394(File *file);
extern BOOL func_0200a930(File *file, u32 command, BOOL blocking);

BOOL ConvertPathToFileID_0200b408(FileID *fileId, const char *path)
{
    BOOL result = FALSE;
    void *arc;
    u32 baseId = 0;
    char relativePath[0x118];

    arc = func_0200ac28(path, &baseId, relativePath);
    if (arc != NULL) {
        File file;
        FindPathArgs args;

        func_0200b394(&file);
        file.arc = arc;
        file.argument = &args;
        args.baseId = baseId;
        args.relativePath = relativePath;
        args.targetIsDirectory = FALSE;
        if (func_0200a930(&file, 4, TRUE)) {
            fileId->arc = arc;
            fileId->fileId = args.targetId;
            result = TRUE;
        }
    }
    return result;
}
