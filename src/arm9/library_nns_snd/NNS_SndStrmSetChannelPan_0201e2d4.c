#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u8 preSleepInfo[0x10];
    u8 postSleepInfo[0x10];
    u8 pad_28[4];
    union {
        u32 flags;
        struct {
            s32 activeFlag : 1;
            s32 startFlag : 1;
        } bits;
    } state;
    u8 pad_30[0x18];
    u32 alarmNo;
    u32 chBitMask;
    int numChannels;
    u8 channelNo[16];
} NNSSndStrm;

extern void func_0200ec08(u32 chBitMask, int pan);

void NNS_SndStrmSetChannelPan_0201e2d4(NNSSndStrm *stream, int chNo, int pan)
{
    if (chNo > stream->numChannels - 1) return;
    func_0200ec08((u32)(1 << stream->channelNo[chNo]), pan);
}
