#include "nitro/types.h"

typedef struct MovieAudio {
    void *stream;
    s16 *leftBuffer;
    s16 *rightBuffer;
} MovieAudio;

typedef struct MovieFrameTimer {
    void *stream;
    u8 alarm[0x2c];
} MovieFrameTimer;

typedef struct MovieGlobals {
    u8 stopped;
    u8 pad_01[3];
    MovieAudio *audio;
    MovieFrameTimer *mainTimer;
} MovieGlobals;

typedef struct MovieFileBank {
    u8 file[0x48];
    u8 pad_48[0x10];
    BOOL stopping;
} MovieFileBank;

extern MovieFileBank data_ov022_020b7d94;
extern MovieGlobals data_ov022_020b7d88;
extern u8 data_ov022_020b7d10[];

extern int runMovieSlotState_020a8730(MovieFrameTimer *timer);
extern void CancelAlarm_020043a8(void *alarm);
extern void EndAlarmSystem_020041b8(void);
extern void NotifyBothOrOne_02001154(u32 mode, u32 table, int index);
extern void StopMovieAudio_020a7ed8(void);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void func_ov022_020a9288(void *stream);
extern BOOL func_0200b5b0(void *file);
extern void func_ov022_020a82f4(void);

void StopMoviePlayback_020a8674(void)
{
    MovieFileBank *bank = &data_ov022_020b7d94;
    MovieFrameTimer *timer = data_ov022_020b7d88.mainTimer;
    MovieAudio *audio = data_ov022_020b7d88.audio;

    if (bank->stopping == 0) {
        bank->stopping = 1;
        while (runMovieSlotState_020a8730(timer) != 0) {
        }
    }
    CancelAlarm_020043a8(timer->alarm);
    EndAlarmSystem_020041b8();
    NotifyBothOrOne_02001154(1, (u32)data_ov022_020b7d10, -1);
    if (audio != NULL) {
        StopMovieAudio_020a7ed8();
        NNSi_FndFreeFromDefaultHeap_0202a1c4(audio->leftBuffer);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(audio->rightBuffer);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(audio);
        data_ov022_020b7d88.audio = NULL;
    }
    func_ov022_020a9288(timer->stream);
    func_0200b5b0(bank->file);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(data_ov022_020b7d88.mainTimer);
    data_ov022_020b7d88.mainTimer = NULL;
    func_ov022_020a82f4();
}
