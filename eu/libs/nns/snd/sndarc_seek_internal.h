#ifndef NNS_SNDARC_SEEK_INTERNAL_H
#define NNS_SNDARC_SEEK_INTERNAL_H

#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x84];
    const char *filePath;
    void *seekCacheBuffer;
    u32 seekCacheSize;
} NNSSndArcSeekState;

extern NNSSndArcSeekState *sCurrentSoundArchive;

#endif
