#include "nitro/types.h"

typedef struct {
    void *buffer;
    int volume;
} NNSSndStrmChannel;

typedef enum {
    NNS_SND_STRM_CALLBACK_SETUP,
    NNS_SND_STRM_CALLBACK_INTERVAL
} NNSSndStrmCallbackStatus;

typedef void (*NNSSndStrmCallback)(NNSSndStrmCallbackStatus status, int numChannels, void *buffer[], u32 len, u32 format, void *arg);

typedef struct {
    u8 pad_00[0x28];
    u32 format;
    u8 pad_2c[0x30 - 0x2c];
    u32 chBufLen;
    s32 interval;
    NNSSndStrmCallback callback;
    void *callbackArg;
    s32 curBuffer;
    u8 pad_44[0x50 - 0x44];
    int numChannels;
    u8 channelNo[16];
} NNSSndStrm;

extern int func_02023fc8(u32 chBufLen, int interval);
extern NNSSndStrmChannel data_0205e1c8[];
extern void *data_0205e188[];

void StrmCallback_0201e3b8(NNSSndStrm *stream, NNSSndStrmCallbackStatus status)
{
    u32 blockSize = func_02023fc8(stream->chBufLen, stream->interval);
    u32 offset = blockSize * stream->curBuffer;
    int index;
    int chNo;

    for (index = 0; index < stream->numChannels; index++) {
        chNo = stream->channelNo[index];
        data_0205e188[index] = (u8 *)data_0205e1c8[chNo].buffer + offset;
    }

    stream->callback(status, stream->numChannels, data_0205e188, blockSize, stream->format, stream->callbackArg);

    stream->curBuffer++;
    if (stream->curBuffer >= stream->interval) stream->curBuffer = 0;
}
