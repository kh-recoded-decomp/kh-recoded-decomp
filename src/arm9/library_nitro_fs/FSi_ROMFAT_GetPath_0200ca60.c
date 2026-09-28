#include "nitro/types.h"

#define FS_COMMAND_GETPATH 5

typedef struct RomFile {
    u8 pad_00[0x30];
    u8 *pathBuffer;
    u32 pathBufferLength;
    u16 pathTotalLength;
    u16 pathDirId;
} RomFile;

extern int func_0200c6fc(RomFile *file, int command, BOOL blocking);

int FSi_ROMFAT_GetPath_0200ca60(void *arc, RomFile *file, BOOL isDirectory, char *buffer, u32 *length)
{
    int result;

    file->pathTotalLength = 0;
    file->pathDirId = 0;
    file->pathBuffer = (u8 *)buffer;
    file->pathBufferLength = *length;
    result = func_0200c6fc(file, FS_COMMAND_GETPATH, TRUE);
    if (result == 0) {
        *length = file->pathBufferLength;
    }
    return result;
}
