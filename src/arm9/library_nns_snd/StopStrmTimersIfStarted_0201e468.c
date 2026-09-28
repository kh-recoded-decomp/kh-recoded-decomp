#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    s32 activeFlag : 1;
    s32 startFlag : 1;
    u8 pad_30[0x48 - 0x30];
    u32 alarmNo;
    u32 chBitMask;
} NNSSndStrm;

extern void StopSoundTimers_0200eafc(u32 channelMask, u32 captureMask, u32 alarmMask, u32 reserved);
extern int func_0200f288(void);
extern int audio_flush_reserved_commands_0200f080(u32 submitFlags);
extern void func_0200f21c(u32 tag);

void StopStrmTimersIfStarted_0201e468(NNSSndStrm *stream)
{
    int tag;

    if (!stream->startFlag) return;

    StopSoundTimers_0200eafc(stream->chBitMask, 0, 1 << stream->alarmNo, 0);
    tag = func_0200f288();
    audio_flush_reserved_commands_0200f080(1);
    func_0200f21c(tag);
}
