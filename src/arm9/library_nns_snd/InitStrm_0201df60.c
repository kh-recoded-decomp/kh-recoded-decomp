#include "nitro/types.h"

typedef void (*SleepCallback)(void *arg);

typedef struct {
    u8 pad_00[8];
    SleepCallback preSleepCallback;
    void *preSleepArg;
    u8 pad_10[0x18 - 0x10];
    SleepCallback postSleepCallback;
    void *postSleepArg;
    u8 pad_20[0x2c - 0x20];
    u32 activeFlag : 1;
    u32 startFlag : 1;
    u32 pad_2c : 30;
    u8 pad_30[0x4c - 0x30];
    u32 chBitMask;
    s32 numChannels;
} NNSSndStrm;

extern BOOL data_0205e178;
extern u32 data_0205e17c[];
extern u32 func_0201288c(u32 list, u32 offset, u32 unused0, u32 unused1);
extern void func_0201e468(void *arg);
extern void func_0201e4b4(void *arg);

void InitStrm_0201df60(NNSSndStrm *stream, u32 param2, u32 param3, u32 param4)
{
    if (!data_0205e178) {
        func_0201288c((u32)data_0205e17c, 0, param3, param4);
        data_0205e178 = TRUE;
    }

    stream->activeFlag = FALSE;

    stream->preSleepCallback = func_0201e468;
    stream->preSleepArg = stream;
    stream->postSleepCallback = func_0201e4b4;
    stream->postSleepArg = stream;

    stream->chBitMask = 0;
    stream->numChannels = 0;

    stream->startFlag = FALSE;
}
