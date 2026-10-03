#include "nitro/types.h"

typedef int (*SceneHandler)(void);

typedef struct {
    SceneHandler states[9];
    u8 pad_24[4];
    SceneHandler onEnter;
    SceneHandler onExit;
} SceneHandlerTable;

extern int MobiClip_SrcOpen_020bb474(void);
extern int func_ov031_020bb48c(void);
extern int func_ov031_020bb4a8(void);
extern int SetModeByte_020bb4c0(void);
extern int IsPxiFifoTagSet_020bb4dc(void);
extern int ReleasePxiFifoTag_020bb4f8(void);
extern int ApplyStartParams_020bb518(void);
extern int func_ov031_020bb55c(void);
extern int ApplyOverlayScaleMode_020bab20(void);
extern int func_ov031_020bbf24(void);
extern int ResetSceneState_020bbf34(void);
extern void ApplyAreaMusicEntry_02064734(int index);

void InstallMovieSceneHandlers_020bbf7c(SceneHandlerTable *table)
{
    table->states[0] = MobiClip_SrcOpen_020bb474;
    table->states[1] = func_ov031_020bb48c;
    table->states[2] = func_ov031_020bb4a8;
    table->states[3] = SetModeByte_020bb4c0;
    table->states[4] = IsPxiFifoTagSet_020bb4dc;
    table->states[5] = ReleasePxiFifoTag_020bb4f8;
    table->states[6] = ApplyStartParams_020bb518;
    table->states[7] = func_ov031_020bb55c;
    table->states[8] = ApplyOverlayScaleMode_020bab20;
    table->onEnter = func_ov031_020bbf24;
    table->onExit = ResetSceneState_020bbf34;
    ApplyAreaMusicEntry_02064734(2);
}
