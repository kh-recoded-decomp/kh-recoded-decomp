#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x4c];
    u32 chBitMask;
    s32 numChannels;
    u8 channelNo[1];
} NNSSndStrm;

extern BOOL func_0201d304(u32 chBitFlag);

BOOL AllocStrmChannel_0201dfd4(NNSSndStrm *stream, int numChannels, const u8 chNoList[])
{
    u32 chBitMask = 0;
    int i;

    for (i = 0; i < numChannels; i++) {
        stream->channelNo[i] = chNoList[i];
        chBitMask = chBitMask | 1 << chNoList[i];
    }

    if (!func_0201d304(chBitMask)) {
        return FALSE;
    }

    stream->numChannels = numChannels;
    stream->chBitMask = chBitMask;

    return TRUE;
}
