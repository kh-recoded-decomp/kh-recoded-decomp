#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    s32 activeFlag : 1;
    s32 startFlag : 1;
    u8 pad_30[0x40 - 0x30];
    s32 curBuffer;
    u8 pad_44[0x48 - 0x44];
    u32 alarmNo;
    u32 chBitMask;
} NNSSndStrm;

extern int func_02004938(void);
extern int func_0200494c(int state);
extern void func_0201e3b8(NNSSndStrm *stream, int status);
extern void func_0200ead4(u32 channelMask, u32 captureMask, u32 alarmMask, u32 reserved);

void EndSleep_0201e4b4(NNSSndStrm *stream)
{
    int state;

    if (!stream->startFlag) return;

    while (stream->curBuffer != 0) {
        state = func_02004938();
        func_0201e3b8(stream, 1);
        func_0200494c(state);
    }

    func_0200ead4(stream->chBitMask, 0, 1 << stream->alarmNo, 0);
}
