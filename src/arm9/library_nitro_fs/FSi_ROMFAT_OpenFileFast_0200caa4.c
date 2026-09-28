#include "nitro/types.h"

#define FS_COMMAND_OPENFILEFAST 6
#define FS_FILE_STATUS_IS_FILE 0x10
#define FS_FILE_STATUS_IS_DIR 0x20

typedef struct RomFileProperty {
    u32 ownId;
    u32 top;
    u32 bottom;
    u32 pos;
} RomFileProperty;

typedef struct RomFile {
    struct RomFile *next;
    RomFileProperty *userdata;
    void *arc;
    u32 stat;
    u8 pad_10[0x10];
    RomFileProperty prop;
    void *openArc;
    u32 openFileId;
} RomFile;

extern int func_0200c6fc(RomFile *file, int command, BOOL blocking);

int FSi_ROMFAT_OpenFileFast_0200caa4(void *arc, RomFile *file, u32 fileId, u32 mode)
{
    int result;

    file->openFileId = fileId;
    file->openArc = arc;
    result = func_0200c6fc(file, FS_COMMAND_OPENFILEFAST, TRUE);
    if (result != 0) {
        return result;
    }
    file->stat |= FS_FILE_STATUS_IS_FILE;
    file->stat &= ~FS_FILE_STATUS_IS_DIR;
    file->userdata = &file->prop;
    file->arc = arc;
    return result;
}
