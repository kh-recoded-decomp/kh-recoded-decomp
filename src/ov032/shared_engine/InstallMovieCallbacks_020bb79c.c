#include "nitro/types.h"

typedef struct {
    void *open;
    void *step;
    void *render;
    void *setMode;
    void *isOpen;
    void *close;
    void *start;
    void *isRunning;
    void *stopAudio;
    void *reserved;
    void *isPaused;
} MovieCallbacks;

extern void MobiClip_SrcOpen_020bb448(int arg);
extern void func_ov032_020bb460(void);
extern void func_ov032_020bb47c(void);
extern void SetContextModeAndFlag_020bb494(u8 mode);
extern BOOL MobiClip_SrcIsOpen_020bb4ac(void);
extern void MobiClip_SrcClose_020bb4c8(void);
extern void StartMoviePlayback_020bb4e0(void *params);
extern BOOL IsContextFlag10Clear_020bb554(void);
extern void func_ov032_020bb368(s32 keepAlive);
extern u32 IsContextFlag20Set_020bb56c(void);
extern int func_ov001_020645c8(int flag);
extern void ApplyAreaMusicEntry_02064734(int entry);

void InstallMovieCallbacks_020bb79c(MovieCallbacks *callbacks)
{
    callbacks->open = MobiClip_SrcOpen_020bb448;
    callbacks->step = func_ov032_020bb460;
    callbacks->render = func_ov032_020bb47c;
    callbacks->setMode = SetContextModeAndFlag_020bb494;
    callbacks->isOpen = MobiClip_SrcIsOpen_020bb4ac;
    callbacks->close = MobiClip_SrcClose_020bb4c8;
    callbacks->start = StartMoviePlayback_020bb4e0;
    callbacks->isRunning = IsContextFlag10Clear_020bb554;
    callbacks->stopAudio = func_ov032_020bb368;
    callbacks->isPaused = IsContextFlag20Set_020bb56c;
    ApplyAreaMusicEntry_02064734(func_ov001_020645c8(0x3ee4) ? 4 : 0);
}
