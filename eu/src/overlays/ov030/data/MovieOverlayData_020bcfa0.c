#include "nitro/types.h"

typedef int (*SceneStateFunc)(void);

typedef struct {
    u32 id;
    void (*init)(void);
    void (*close)(void);
    u32 workSize;
    u32 flags;
} OverlayDesc;

extern void InitMovieOverlayState_020ba400(void);
extern void MoviePlayer_Close(void);
extern int Ov030SceneState_PushVramWhenIdle(void);
extern int FinishSceneSetup(void);
extern int Ov030SceneState_WaitForListNodes(void);
extern int TryEnterState4_020ba614(void);
extern int Ov030SceneState_FinishMenuResourceLoad(void);
extern int MoviePlayer_EnterPlayback(void);
extern int Ov030SceneState_FinishStartupWhenPanelReady(void);
extern int ResolveMovieSceneAction(void);
extern int Ov030SceneState_StoreEventRecordBytes(void);
extern int Ov030SceneState_BeginScreenModeTransition(void);
extern int SceneState_WaitScreenIdle_020ba894(void);
extern int EnterState12WithHalfRate_020ba8f0(void);
extern int TryReenterState7_020ba90c(void);
extern int Ov030SceneState_FinishSlowdownTransition(void);
extern int Ov030SceneState_StartIdleObjects(void);
extern int Ov030SceneState_BeginFadeOutWhenIdle(void);
extern int Ov030SceneState_WaitFadeOut(void);
extern int MoviePlayer_Stop(void);
extern int FinishMoviePlaybackState(void);

s32 gMobiClipSourceHandle = -1;

OverlayDesc gMovieOverlayDescriptor = {
    0x2000e, InitMovieOverlayState_020ba400, MoviePlayer_Close, 0x68, 0,
};

SceneStateFunc gMovieSceneStateHandlers[] = {
    Ov030SceneState_PushVramWhenIdle,
    FinishSceneSetup,
    Ov030SceneState_WaitForListNodes,
    TryEnterState4_020ba614,
    Ov030SceneState_FinishMenuResourceLoad,
    MoviePlayer_EnterPlayback,
    Ov030SceneState_FinishStartupWhenPanelReady,
    ResolveMovieSceneAction,
    Ov030SceneState_StoreEventRecordBytes,
    Ov030SceneState_BeginScreenModeTransition,
    SceneState_WaitScreenIdle_020ba894,
    EnterState12WithHalfRate_020ba8f0,
    TryReenterState7_020ba90c,
    Ov030SceneState_FinishSlowdownTransition,
    Ov030SceneState_StartIdleObjects,
    Ov030SceneState_BeginFadeOutWhenIdle,
    Ov030SceneState_WaitFadeOut,
    MoviePlayer_Stop,
    FinishMoviePlaybackState,
};
