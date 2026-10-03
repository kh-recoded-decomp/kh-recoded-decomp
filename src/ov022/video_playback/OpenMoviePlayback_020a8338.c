#include "nitro/types.h"

typedef struct MovieAudio {
    void *stream;
    s16 *leftBuffer;
    s16 *rightBuffer;
    u8 pad_0C[0x4];
    u32 sampleRate;
    u32 blockSize;
    u32 channels;
    s32 readIndex;
    u32 bufferBlocks;
} MovieAudio;

typedef struct MovieFrameTimer {
    void *stream;
    u8 alarm[0x2c];
    u8 pad_30[0x8];
    u8 frameReady;
    u8 paused;
    u8 active;
    u8 useMainScreen;
    u8 pad_3C[0x4];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    u64 frameTicks;
    void *(*getBuffer)(void);
} MovieFrameTimer;

typedef struct MovieGlobals {
    u8 stopped;
    u8 pad_01[3];
    MovieAudio *audio;
    MovieFrameTimer *mainTimer;
} MovieGlobals;

typedef struct MovieFileBank {
    u8 file[0x48];
    u8 pad_48[0xc];
    s32 option;
    BOOL stopping;
} MovieFileBank;

typedef struct MovieOpenParams {
    const char *path;
    s32 option;
    s32 useMainScreen;
} MovieOpenParams;

extern MovieFileBank data_ov022_020b7d94;
extern MovieGlobals data_ov022_020b7d88;
extern u8 data_ov022_020b7d10[];

extern void func_0200b394(void *file);
extern void *Msg_BuildLangPath_0202b798(const char *path);
extern void CallSelectionHandler_0200b740(void *file, void *path);
extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void func_01ff8830(void *dest, int value, u32 size);
extern void SetupMovieDecoderArenas_020a8264(void);
extern void *GetFrameBuffer_020a7d64(void);
extern void *GetSubScreenBuffer_020a7d7c(void);
extern void *createMovieStream_020a91a0(void *file, int slotCount);
extern u32 ReleaseIfSet_020a92a8(void *stream);
extern u32 ReleaseIfSet_020a92c0(void *stream);
extern u32 ReleaseIfSet_020a92d8(void *stream);
extern void func_020033b4(void);
extern void InitializeAlarmSystem_0200417c(void);
extern void OS_CreateAlarm_02004204(void *alarm);
extern void func_ov022_020a92f0(void *stream);
extern void func_ov022_020a807c(MovieFrameTimer *timer);
extern void flushPendingStereoAudioBlocks_020a809c(MovieAudio *audio);
extern void func_ov022_020a82f4(void);
extern void InvokeForChannelOrBoth_0200110c(u32 mode, void *table, void *callback, int index);
extern void OS_WaitVBlankIntr_020049d0(void);
extern void func_ov022_020a8154(void);

BOOL OpenMoviePlayback_020a8338(const MovieOpenParams *params)
{
    MovieFileBank *bank = &data_ov022_020b7d94;
    MovieFrameTimer *timer;
    u32 channels;
    int i;
    MovieAudio *audio;

    bank->stopping = 0;
    func_0200b394(bank);
    CallSelectionHandler_0200b740(bank, Msg_BuildLangPath_0202b798(params->path));
    data_ov022_020b7d88.mainTimer = NNSi_FndAllocFromDefaultHeapEx_0202a19c(sizeof(MovieFrameTimer), 0x20);
    func_01ff8830(data_ov022_020b7d88.mainTimer, 0, sizeof(MovieFrameTimer));
    timer = data_ov022_020b7d88.mainTimer;
    SetupMovieDecoderArenas_020a8264();
    data_ov022_020b7d94.option = params->option;
    if (params->useMainScreen != 0) {
        data_ov022_020b7d88.mainTimer->getBuffer = GetFrameBuffer_020a7d64;
        data_ov022_020b7d88.mainTimer->useMainScreen = 1;
    } else {
        data_ov022_020b7d88.mainTimer->getBuffer = GetSubScreenBuffer_020a7d7c;
        data_ov022_020b7d88.mainTimer->useMainScreen = 0;
    }

    timer->stream = createMovieStream_020a91a0(bank, 10);
    if (timer->stream != NULL) {

    data_ov022_020b7d88.audio = NULL;
    channels = ReleaseIfSet_020a92d8(timer->stream);
    if (channels != 0) {
        data_ov022_020b7d88.audio = NNSi_FndAllocFromDefaultHeapEx_0202a19c(sizeof(MovieAudio), 0x20);
        func_01ff8830(data_ov022_020b7d88.audio, 0, sizeof(MovieAudio));
        data_ov022_020b7d88.audio->stream = timer->stream;
        data_ov022_020b7d88.audio->channels = channels;
    }

    audio = data_ov022_020b7d88.audio;
    if (audio != NULL) {
        u64 period;
        u32 blocks;

        audio->sampleRate = ReleaseIfSet_020a92a8(audio->stream);
        period = 0xffb0ffULL / (0xffb0ffULL / audio->sampleRate);
        blocks = (u32)((period << 24) / ((u64)ReleaseIfSet_020a92c0(audio->stream) * audio->channels)) + 1;
        audio->blockSize = blocks;
        audio->bufferBlocks = blocks * 10;
        audio->leftBuffer = NNSi_FndAllocFromDefaultHeapEx_0202a19c(audio->bufferBlocks * audio->channels * 2, 0x20);
        audio->rightBuffer = NNSi_FndAllocFromDefaultHeapEx_0202a19c(audio->bufferBlocks * audio->channels * 2, 0x20);
        func_01ff8830(audio->leftBuffer, 0, audio->bufferBlocks * audio->channels * 2);
        func_01ff8830(audio->rightBuffer, 0, audio->bufferBlocks * audio->channels * 2);
        func_020033b4();
    }

    if (audio != NULL && audio->stream == timer->stream) {
        void *stream = audio->stream;
        u64 ticks = 0xffb0ffULL / audio->sampleRate;

        timer->frameTicks = ((u64)ReleaseIfSet_020a92c0(stream) * 0xffb0ffULL) / (ticks * audio->sampleRate);
        audio->readIndex = 0;
    } else {
        timer->frameTicks = ReleaseIfSet_020a92c0(timer->stream);
    }

    timer->paused = 0;
    timer->active = 1;
    InitializeAlarmSystem_0200417c();
    OS_CreateAlarm_02004204(timer->alarm);
    timer->unk_44 = 0;
    timer->unk_40 = 0;
    timer->unk_48 = 0;
    timer->frameReady = 0;
    for (i = 0; i < 10; i++) {
        func_ov022_020a92f0(timer->stream);
        func_ov022_020a807c(timer);
        if (audio != NULL && audio->stream == timer->stream) {
            flushPendingStereoAudioBlocks_020a809c(audio);
        }
    }
    data_ov022_020b7d88.stopped = 0;
    InvokeForChannelOrBoth_0200110c(1, data_ov022_020b7d10, func_ov022_020a8154, -1);
    OS_WaitVBlankIntr_020049d0();
    return TRUE;
    }
    func_ov022_020a82f4();
    NNSi_FndFreeFromDefaultHeap_0202a1c4(timer);
    data_ov022_020b7d88.mainTimer = NULL;
    return FALSE;
}
