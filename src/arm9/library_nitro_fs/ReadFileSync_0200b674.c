#include "nitro/types.h"

typedef struct {
    void *buffer;
    s32 length;
} ReadFileArgs;

typedef struct {
    u8 pad_00[0x10];
    ReadFileArgs *argument;
    s32 error;
} FSFile;

extern BOOL func_0200a930(FSFile *file, u32 command, BOOL blocking);

s32 ReadFileSync_0200b674(FSFile *file, void *buffer, s32 length) {
    ReadFileArgs args;
    file->argument = &args;
    args.buffer = buffer;
    args.length = length;
    if (func_0200a930(file, 0, TRUE)) {
        length = args.length;
    } else {
        length = -1;
        if (file->error != 6) {
            length = args.length;
        }
    }
    return length;
}
