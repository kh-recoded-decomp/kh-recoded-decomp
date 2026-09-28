#include "nitro/types.h"

#define FS_RESULT_SUCCESS 0
#define FS_RESULT_INVALID_PARAMETER 6

typedef enum RomFileSeekMode {
    ROM_SEEK_SET,
    ROM_SEEK_CUR,
    ROM_SEEK_END
} RomFileSeekMode;

typedef struct RomFileProperty {
    u32 ownId;
    s32 top;
    s32 bottom;
    s32 pos;
} RomFileProperty;

typedef struct RomFile {
    u8 pad_00[4];
    RomFileProperty *property;
} RomFile;

int FSi_ROMFAT_SeekFile_0200cc90(void *archive, RomFile *file, int *offset, RomFileSeekMode from)
{
    RomFileProperty *property = file->property;
    int pos = *offset;

    switch (from) {
    case ROM_SEEK_SET:
        pos += property->top;
        break;
    case ROM_SEEK_CUR:
    default:
        pos += property->pos;
        break;
    case ROM_SEEK_END:
        pos += property->bottom;
        break;
    }

    if (pos < property->top || pos > property->bottom) {
        return FS_RESULT_INVALID_PARAMETER;
    }
    property->pos = pos;
    *offset = pos;
    return FS_RESULT_SUCCESS;
}
