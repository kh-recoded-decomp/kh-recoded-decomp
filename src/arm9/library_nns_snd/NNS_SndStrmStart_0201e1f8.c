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

extern void func_0200ead4(u32 channelMask, u32 captureMask, u32 alarmMask, u32 flags);
extern void PM_PrependPreSleepCallback_02010ac0(void *info);
extern void PM_AppendPostSleepCallback_02010ad8(void *info);

void NNS_SndStrmStart_0201e1f8(NNSSndStrm *stream)
{
    func_0200ead4(stream->chBitMask, 0, 1 << stream->alarmNo, 0);

    if (!stream->state.bits.startFlag) {
        PM_PrependPreSleepCallback_02010ac0(&stream->preSleepInfo);
        PM_AppendPostSleepCallback_02010ad8(&stream->postSleepInfo);
        stream->state.flags = stream->state.flags | 2;
    }
}
