#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x44];
    s32 volume;
    u8 pad_48[0x50 - 0x48];
    s32 numChannels;
    u8 channelNo[1];
} NNSSndStrm;

typedef struct {
    u8 pad_00[4];
    s32 volume;
} ChannelInfo;

extern ChannelInfo data_0205e1c8[];
extern u16 func_0200f6a8(int dB);
extern void func_0200ebe0(int chBitMask, int volume, int shift);

void NNS_SndStrmSetVolume_0201e268(NNSSndStrm *stream, int volume)
{
    int chNo;
    int i;
    int vol;
    u16 chVolume;

    stream->volume = volume;
    for (i = 0; i < stream->numChannels; i++) {
        chNo = stream->channelNo[i];
        vol = stream->volume + data_0205e1c8[chNo].volume;
        chVolume = func_0200f6a8(vol);
        func_0200ebe0(1 << chNo, chVolume & 0xff, chVolume >> 8);
    }
}
