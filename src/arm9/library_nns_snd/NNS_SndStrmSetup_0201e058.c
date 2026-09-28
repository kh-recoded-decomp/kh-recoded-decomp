#include "nitro/types.h"

typedef void (*NNSSndStrmCallback)(int status, int numChannels, void *buffer[], u32 len, int format, void *arg);

typedef struct {
    u8 pad_00[0x28];
    int format;
    BOOL activeFlag : 1;
    BOOL startFlag : 1;
    u32 chBufLen;
    int interval;
    NNSSndStrmCallback callback;
    void *callbackArg;
    int curBuffer;
    int volume;
    int alarmNo;
    u32 chBitMask;
    int numChannels;
    u8 channelNo[16];
} NNSSndStrm;

typedef struct {
    void *buffer;
    int volume;
} NNSSndStrmChannel;

extern NNSSndStrmChannel data_0205e1c8[];
extern u8 data_0205e17c[];

extern void NNS_SndStrmStop_0201e24c(NNSSndStrm *stream);
extern int func_0201d394(void);
extern u32 func_02023fc8(u32 dividend, u32 divisor);
extern void sound_setup_pcm_channel_0200ec28(int nChannel, int nFormat, const void *pData,
                          int nLoop, int nLoopStart, int nLoopLength,
                          int nVolume, int nShift, int nTimer, int nPan);
extern void func_0200eb60(int id, int tick, int period, void *fn, void *arg);
extern void AppendIntrusiveListObject_020128d0(void *list, void *obj);
extern void AlarmCallback_0201e3a8(void *arg);
extern void StrmCallback_0201e3b8(NNSSndStrm *stream, int status);
extern int func_02004938(void);
extern void func_0200494c(int state);

BOOL NNS_SndStrmSetup_0201e058(NNSSndStrm *stream, int format, void *buffer, u32 bufSize, int timer, int interval, NNSSndStrmCallback callback, void *arg)
{
    NNSSndStrmChannel *chp;
    unsigned int samples;
    unsigned int alarmTimer;
    int chNo;
    int index;

    if (stream->activeFlag) {
        NNS_SndStrmStop_0201e24c(stream);
    }

    bufSize = func_02023fc8(bufSize, 32 * interval * stream->numChannels);
    stream->chBufLen = bufSize * interval * 32;

    samples = stream->chBufLen;
    if (format == 1) samples >>= 1;

    alarmTimer = func_02023fc8(timer * samples, interval);

    stream->alarmNo = func_0201d394();
    if (stream->alarmNo < 0) return FALSE;

    for (index = 0; index < stream->numChannels; index++) {
        chNo = stream->channelNo[index];
        chp = &data_0205e1c8[chNo];
        chp->buffer = (u8 *)buffer + stream->chBufLen * index;
        chp->volume = 0;
        sound_setup_pcm_channel_0200ec28(chNo, format, chp->buffer, 1, 0, (int)(stream->chBufLen >> 2), 127, 0, timer << 5, 64);
    }

    func_0200eb60(stream->alarmNo, alarmTimer, alarmTimer, AlarmCallback_0201e3a8, stream);

    AppendIntrusiveListObject_020128d0(data_0205e17c, stream);

    stream->format = format;
    stream->interval = interval;
    stream->callback = callback;
    stream->callbackArg = arg;
    stream->curBuffer = 0;
    stream->volume = 0;
    stream->activeFlag = TRUE;

    {
        int old = func_02004938();

        stream->interval = 1;
        StrmCallback_0201e3b8(stream, 0);
        stream->interval = interval;

        func_0200494c(old);
    }

    return TRUE;
}
