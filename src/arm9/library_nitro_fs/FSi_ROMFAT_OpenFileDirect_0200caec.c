#include "nitro/types.h"

#define FS_COMMAND_OPENFILEDIRECT 7
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
    u32 openTop;
    u32 openBottom;
    u32 openIndex;
} RomFile;

extern int func_0200c6fc(RomFile *file, int command, BOOL blocking);

int FSi_ROMFAT_OpenFileDirect_0200caec(void *arc, RomFile *file, u32 top, u32 bottom, u32 *fileId)
{
    int result;

    file->openTop = top;
    file->openBottom = bottom;
    file->openIndex = *fileId;
    result = func_0200c6fc(file, FS_COMMAND_OPENFILEDIRECT, TRUE);
    if (result != 0) {
        return result;
    }
    file->stat |= FS_FILE_STATUS_IS_FILE;
    file->stat &= ~FS_FILE_STATUS_IS_DIR;
    file->userdata = &file->prop;
    file->arc = arc;
    return result;
}
