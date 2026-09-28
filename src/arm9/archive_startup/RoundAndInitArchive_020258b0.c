#include "nitro/types.h"

typedef struct {
    s32 size;
    u8 pad_04[4];
    s32 sizeCopy;
    u8 pad_0c[0x628];
    s32 chunkSize;
    u8 pad_638[4];
    s32 archiveHeader;
} ArchiveContext;

extern int func_0202c4a0(int flags, s32 archive, s32 chunkSize);
extern int func_0202580c(ArchiveContext *record, int flag, int extra);

int RoundAndInitArchive_020258b0(ArchiveContext *record, int flags, int flag, int extra)
{
    int size;
    int remainder;

    size = func_0202c4a0(flags, record->archiveHeader, record->chunkSize);
    if (size < 0) {
        return 0;
    }

    remainder = size % 4;
    if (remainder != 0) {
        size = size + (4 - remainder);
    }

    record->size = size;
    record->sizeCopy = size;

    return func_0202580c(record, flag, extra);
}
