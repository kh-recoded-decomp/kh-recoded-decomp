#include "nitro/types.h"

extern void ResetAreaMeshValues(void); /* ResetAreaMeshValues */
extern void ConfigureAreaSceneSlotsAndReset(void);
extern void FinishAreaSceneLoad(void);
extern void SetupAreaFieldState(void);
extern void AreaSceneState_WaitForPanelReady(void);
extern void UpdateAreaSceneState(void); /* UpdateAreaSceneState */
extern void StartAreaCameraIntro(void);
extern void TickIntroRotation(void); /* TickIntroRotation */
extern void AreaSceneState_SetTransitionAudioAndFlags(void);
extern void FadeInAreaScreens(void); /* FadeInAreaScreens */
extern void AreaSceneState_BeginScreenTransition(void);
extern void FinishAreaScreenTransition(void);
extern void EnterState13WithHalfRate(void); /* EnterState13WithHalfRate */
extern void AreaSceneState_RestoreFieldWhenScreenIdle(void);
extern void AreaSceneState_StartIdleObjects(void);
extern void AreaSceneState_BeginFadeOut(void);
extern void AreaSceneState_WaitForExitTransition(void);
extern void FinishAreaTransition(void); /* FinishAreaTransition */
extern void AreaSceneState_Hold(void); /* Gfd_DefaultFreeTexVram */

void (*gAreaSceneStateHandlers[19])(void) = {
    ResetAreaMeshValues, /* ResetAreaMeshValues */
    ConfigureAreaSceneSlotsAndReset,
    FinishAreaSceneLoad,
    SetupAreaFieldState,
    AreaSceneState_WaitForPanelReady,
    UpdateAreaSceneState, /* UpdateAreaSceneState */
    StartAreaCameraIntro,
    TickIntroRotation, /* TickIntroRotation */
    AreaSceneState_SetTransitionAudioAndFlags,
    FadeInAreaScreens, /* FadeInAreaScreens */
    AreaSceneState_BeginScreenTransition,
    FinishAreaScreenTransition,
    EnterState13WithHalfRate, /* EnterState13WithHalfRate */
    AreaSceneState_RestoreFieldWhenScreenIdle,
    AreaSceneState_StartIdleObjects,
    AreaSceneState_BeginFadeOut,
    AreaSceneState_WaitForExitTransition,
    FinishAreaTransition, /* FinishAreaTransition */
    AreaSceneState_Hold, /* Gfd_DefaultFreeTexVram */
};
