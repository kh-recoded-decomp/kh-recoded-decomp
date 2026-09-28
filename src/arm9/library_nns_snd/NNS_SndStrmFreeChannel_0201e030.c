#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x4c];
    u32 chBitMask;
    u32 numChannels;
} NNSSndStrm;

extern void NNS_SndUnlockChannel_0201d348(u32 chBitMask);

void NNS_SndStrmFreeChannel_0201e030(NNSSndStrm *stream)
{
    if (stream->chBitMask == 0) {
        return;
    }
    NNS_SndUnlockChannel_0201d348(stream->chBitMask);
    stream->chBitMask = 0;
    stream->numChannels = 0;
}
