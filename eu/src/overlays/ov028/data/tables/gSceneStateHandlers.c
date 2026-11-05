#include "nitro/types.h"

extern void Ov028SceneState_PushVramWhenIdle(void);
extern void FieldSceneState_RestoreActorsAndLoadShadow(void);
extern void Ov028SceneState_WaitForListNodes(void);
extern void FieldSceneState_WaitResourceSlotsAndReset(void);
extern void Ov028SceneState_FinishMenuResourceLoad(void);
extern void ResumeFieldFromMenu(void);
extern void SceneState_WaitPanelReady(void); /* SceneState_WaitPanelReady */
extern s32 PollFieldTransition(void);
extern void Ov028SceneState_StoreEventRecordBytes(void);
extern void Ov028SceneState_BeginScreenModeTransition(void);
extern void SceneState_WaitScreenIdle(void); /* SceneState_WaitScreenIdle */
extern void EnterState12WithHalfRate(void); /* EnterState12WithHalfRate */
extern void FieldSceneState_ResetFieldValueWhenScreenIdle(void);
extern void FieldSceneState_EndSlowdownWhenScreenIdle(void);
extern void EnterOverlayTransition(void); /* EnterOverlayTransition */
extern void Ov028SceneState_BeginFadeOutWhenIdle(void);
extern void Ov028SceneState_WaitFadeOut(void);
extern void ShutdownFieldAndSaveActorPoses(void); /* ShutdownFieldAndSaveActorPoses */
extern void FinishFieldSceneState(void);

void (*gSceneStateHandlers[19])(void) = {
    Ov028SceneState_PushVramWhenIdle,
    FieldSceneState_RestoreActorsAndLoadShadow,
    Ov028SceneState_WaitForListNodes,
    FieldSceneState_WaitResourceSlotsAndReset,
    Ov028SceneState_FinishMenuResourceLoad,
    ResumeFieldFromMenu,
    SceneState_WaitPanelReady, /* SceneState_WaitPanelReady */
    (void (*)(void))PollFieldTransition,
    Ov028SceneState_StoreEventRecordBytes,
    Ov028SceneState_BeginScreenModeTransition,
    SceneState_WaitScreenIdle, /* SceneState_WaitScreenIdle */
    EnterState12WithHalfRate, /* EnterState12WithHalfRate */
    FieldSceneState_ResetFieldValueWhenScreenIdle,
    FieldSceneState_EndSlowdownWhenScreenIdle,
    EnterOverlayTransition, /* EnterOverlayTransition */
    Ov028SceneState_BeginFadeOutWhenIdle,
    Ov028SceneState_WaitFadeOut,
    ShutdownFieldAndSaveActorPoses, /* ShutdownFieldAndSaveActorPoses */
    FinishFieldSceneState,
};
