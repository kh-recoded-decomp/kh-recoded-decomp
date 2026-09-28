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
} NNSSndStrm;

extern void StopSoundTimers_0200eafc(u32 channelMask, u32 captureMask, u32 alarmMask, u32 reserved);
extern void PM_DeletePreSleepCallback_02010b04(void *info);
extern void PM_DeletePreSleepCallback_02010b14(void *info);
extern int func_0200f288(void);
extern int audio_flush_reserved_commands_0200f080(u32 submitFlags);
extern void func_0200f21c(u32 tag);
extern void ShutdownStrm_0201e378(NNSSndStrm *stream);

void ForceStopStrm_0201e304(NNSSndStrm *stream)
{
    int tag;

    if (stream->state.bits.startFlag) {
        StopSoundTimers_0200eafc(stream->chBitMask, 0, 1 << stream->alarmNo, 0);
        PM_DeletePreSleepCallback_02010b04(&stream->preSleepInfo);
        PM_DeletePreSleepCallback_02010b14(&stream->postSleepInfo);
        stream->state.flags = stream->state.flags & 0xfffffffd;
        tag = func_0200f288();
        audio_flush_reserved_commands_0200f080(1);
        func_0200f21c(tag);
    }
    ShutdownStrm_0201e378(stream);
}
