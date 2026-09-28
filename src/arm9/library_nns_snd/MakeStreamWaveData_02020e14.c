#include "nitro/types.h"

typedef struct AdpcmState {
    s16 prevSample;
    u8 prevIndex;
    u8 padding;
} AdpcmState;

typedef struct StreamPlayer StreamPlayer;

typedef enum StreamSampleFormat {
    STREAM_SAMPLE_PCM8,
    STREAM_SAMPLE_PCM16
} StreamSampleFormat;

typedef enum StreamCallbackStatus {
    STREAM_CALLBACK_SETUP,
    STREAM_CALLBACK_INTERVAL
} StreamCallbackStatus;

typedef void (*StreamCallback)(StreamCallbackStatus status, int numChannels, void *buffer[], u32 length,
                               StreamSampleFormat format, void *arg);
typedef s32 (*ReadStreamFunc)(StreamPlayer *player, void *dest, u32 size, u32 offset);

struct StreamPlayer {
    u8 pad_000[0xc8];
    u8 format;
    u8 loopFlag;
    u8 numChannels;
    u8 pad_0cb;
    u16 sampleRate;
    u16 timer;
    u32 loopStart;
    u32 loopEnd;
    u32 dataOffset;
    u32 numBlocks;
    u32 blockSize;
    u32 blockSamples;
    u32 lastBlockSize;
    u32 lastBlockSamples;
    u8 fader[0x10];
    AdpcmState adpcmState[6];
    BOOL activeFlag : 1;
    BOOL playFlag : 1;
    BOOL startFlag : 1;
    BOOL fadeOutFlag : 1;
    BOOL dirtyFlag : 1;
    BOOL finishFlag : 1;
    BOOL monoFlag : 1;
    volatile int finishCounter;
    volatile BOOL prepareFlag;
    u8 pad_124[0x13c - 0x124];
    StreamCallback strmCallback;
    void *strmCallbackArg;
    void *sndArcStrmCallback;
    u8 pad_148[0x168 - 0x148];
    u32 curSample;
    u8 pad_16c[0x174 - 0x16c];
    ReadStreamFunc readStreamFunc;
};

typedef struct LoadCommand {
    void *prev;
    void *next;
    StreamPlayer *player;
    StreamCallbackStatus status;
    int numChannels;
    void *buffer[6];
    u32 bufLen;
} LoadCommand;

typedef struct StreamThreadGlobals {
    void *prepareThread;
    BOOL initialized;
    u8 *decodeBuffer;
} StreamThreadGlobals;

#define ADPCM_INDEX_COUNT 89

enum {
    STRM_FORMAT_PCM8,
    STRM_FORMAT_PCM16,
    STRM_FORMAT_ADPCM
};

extern const s8 g_adpcmIndexTable_0205311c[16];
extern const s16 g_adpcmStepSizeTable_0205312c[ADPCM_INDEX_COUNT];
extern StreamThreadGlobals g_streamThreadState_0205e324;
extern u8 g_decodeBufferMutex_0205e33c[];

extern u32 DivideU32_02023fc8(u32 dividend, u32 divisor);
extern void MI_CpuFill8_01ff8830(void *dest, u32 value, u32 size);
extern void MI_CpuCopy8_01ff89a8(const void *src, void *dst, u32 size);
extern void DC_FlushRange_0200344c(void *dst, u32 size);
extern void LockSyncObjectRetry_02003158(void *mutex);
extern void ReleaseSyncObject_020031a8(void *obj);
extern void OnStreamDataEnd_02020cd8(StreamPlayer *player);

static inline s16 DecodeAdpcm(int code, AdpcmState *state)
{
    int step;
    int sample;
    int index;
    int delta;

    sample = state->prevSample;
    index = state->prevIndex;

    step = g_adpcmStepSizeTable_0205312c[index];

    delta = step >> 3;
    if (code & 4) delta += step;
    if (code & 2) delta += step >> 1;
    if (code & 1) delta += step >> 2;

    if (code & 8) {
        sample -= delta;
        if (sample < -32768) sample = -32768;
    } else {
        sample += delta;
        if (sample > 32767) sample = 32767;
    }

    index += g_adpcmIndexTable_0205311c[code];

    if (index < 0) index = 0;
    else if (index > ADPCM_INDEX_COUNT - 1) index = ADPCM_INDEX_COUNT - 1;

    state->prevSample = (s16)sample;
    state->prevIndex = (u8)index;

    return (s16)sample;
}

void MakeStreamWaveData_02020e14(LoadCommand *command)
{
    StreamPlayer *player = command->player;
    BOOL loopFlag;
    long destOffset;
    u32 restSize;
    u32 blockNo;
    u32 blockSize;
    u32 blockSamples;
    u32 blockOffsetSample;
    u32 blockOffset;
    u32 offset;
    u32 samples;
    u32 size;
    u32 readSize;
    int channel;
    u32 samplesPerBlock;
    u32 curSample;

    if (player->finishFlag && player->finishCounter > 0) {
        player->finishCounter--;
    }

    destOffset = 0;

    restSize = command->bufLen;
    while (restSize > 0) {
        if (player->finishFlag) {
            for (channel = 0; channel < command->numChannels; channel++) {
                MI_CpuFill8_01ff8830((u8 *)command->buffer[channel] + destOffset, 0, restSize);
            }
            break;
        }

        samplesPerBlock = player->blockSamples;
        curSample = player->curSample;
        blockNo = DivideU32_02023fc8(curSample, samplesPerBlock);

        if (blockNo < player->numBlocks - 1) {
            blockSize = player->blockSize;
            blockSamples = samplesPerBlock;
        } else {
            blockSize = player->lastBlockSize;
            blockSamples = player->lastBlockSamples;
        }

        blockOffsetSample = curSample;
        blockOffsetSample -= blockNo * samplesPerBlock;

        samples = restSize;
        if (player->format != STRM_FORMAT_PCM8) {
            samples >>= 1;
        }

        if (player->dirtyFlag) {
            if (blockOffsetSample == 0) {
                player->dirtyFlag = FALSE;
            } else {
                samples = blockOffsetSample;
                blockOffsetSample = 0;
            }
        }

        loopFlag = FALSE;
        if (blockOffsetSample + samples >= blockSamples) {
            samples = blockSamples - blockOffsetSample;

            if (blockNo >= player->numBlocks - 1) {
                if (player->loopFlag) {
                    loopFlag = TRUE;
                } else {
                    player->finishFlag = TRUE;
                }
            }
        }

        blockOffset = blockOffsetSample;
        size = samples;
        switch (player->format) {
        case STRM_FORMAT_PCM8:
            readSize = size;
            break;
        case STRM_FORMAT_PCM16:
            blockOffset <<= 1;
            size <<= 1;
            readSize = size;
            break;
        case STRM_FORMAT_ADPCM: {
            u32 endSample = blockOffsetSample + samples;
            blockOffset >>= 1;
            endSample++;
            endSample >>= 1;
            readSize = endSample - blockOffset;
            if (blockOffsetSample == 0) {
                readSize += sizeof(AdpcmState);
            } else {
                blockOffset += sizeof(AdpcmState);
            }
            size <<= 1;
            break;
        }
        }

        offset = blockOffset;
        offset += blockNo * player->blockSize * player->numChannels;
        offset += player->dataOffset;

        for (channel = 0; channel < command->numChannels; channel++) {
            void *dest;
            void *readDest;

            dest = readDest = (u8 *)command->buffer[channel] + destOffset;

            if (channel < player->numChannels) {
                s32 resultSize;

                if (player->format == STRM_FORMAT_ADPCM) {
                    LockSyncObjectRetry_02003158(g_decodeBufferMutex_0205e33c);
                    readDest = g_streamThreadState_0205e324.decodeBuffer;
                }

                resultSize = player->readStreamFunc(player, readDest, readSize, offset + channel * blockSize);

                if (resultSize != readSize) {
                    size = 0;
                    samples = 0;
                    loopFlag = FALSE;
                    player->finishFlag = TRUE;
                    if (player->format == STRM_FORMAT_ADPCM) {
                        ReleaseSyncObject_020031a8(g_decodeBufferMutex_0205e33c);
                    }
                    break;
                }

                if (player->format == STRM_FORMAT_ADPCM) {
                    AdpcmState *state = &player->adpcmState[channel];
                    u8 *src = g_streamThreadState_0205e324.decodeBuffer;
                    s16 *out = dest;
                    u32 i;
                    u32 end;

                    if (blockOffsetSample == 0) {
                        *state = *((AdpcmState *)src)++;
                    }

                    end = blockOffsetSample + samples;

                    i = blockOffsetSample;
                    if (i & 1) {
                        *out++ = DecodeAdpcm((*src >> 4) & 0xf, state);
                        i++;
                        src++;
                    }
                    while (i < (end & ~1)) {
                        *out++ = DecodeAdpcm(*src & 0xf, state);
                        i++;
                        *out++ = DecodeAdpcm((*src >> 4) & 0xf, state);
                        i++;
                        src++;
                    }
                    if (i < end) {
                        *out++ = DecodeAdpcm(*src & 0xf, state);
                        i++;
                    }
                    ReleaseSyncObject_020031a8(g_decodeBufferMutex_0205e33c);
                }
            } else {
                if (player->monoFlag) {
                    MI_CpuFill8_01ff8830(dest, 0, size);
                } else {
                    MI_CpuCopy8_01ff89a8((u8 *)command->buffer[0] + destOffset, dest, size);
                }
            }
        }

        if (player->dirtyFlag) {
            player->dirtyFlag = FALSE;
            continue;
        }

        if (loopFlag) {
            player->curSample = player->loopStart;
        } else {
            player->curSample += samples;
        }

        destOffset += size;

        restSize -= size;

        if (player->finishFlag && player->sndArcStrmCallback) {
            OnStreamDataEnd_02020cd8(player);
        }
    }

    if (player->strmCallback != NULL) {
        player->strmCallback(command->status, command->numChannels, command->buffer, command->bufLen,
                             player->format == STRM_FORMAT_PCM8 ? STREAM_SAMPLE_PCM8 : STREAM_SAMPLE_PCM16,
                             player->strmCallbackArg);
    }

    for (channel = 0; channel < command->numChannels; channel++) {
        DC_FlushRange_0200344c(command->buffer[channel], command->bufLen);
    }

    if (command->status == STREAM_CALLBACK_SETUP) {
        player->prepareFlag = TRUE;
    }
}
