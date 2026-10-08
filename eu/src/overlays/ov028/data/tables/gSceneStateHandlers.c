#include "nitro/types.h"

extern void func_ov028_020ba69c(void);
extern void func_ov028_020ba6d4(void);
extern void func_ov028_020ba720(void);
extern void func_ov028_020ba758(void);
extern void func_ov028_020ba778(void);
extern void ResumeFieldFromMenu(void);
extern void SceneState_WaitPanelReady(void); /* SceneState_WaitPanelReady */
extern void func_ov028_020ba99c(void);
extern void func_ov028_020bab20(void);
extern void func_ov028_020bab68(void);
extern void SceneState_WaitScreenIdle(void); /* SceneState_WaitScreenIdle */
extern void EnterState12WithHalfRate(void); /* EnterState12WithHalfRate */
extern void func_ov028_020bac30(void);
extern void func_ov028_020bac5c(void);
extern void EnterOverlayTransition(void); /* EnterOverlayTransition */
extern void func_ov028_020bacd0(void);
extern void func_ov028_020bad1c(void);
extern void ShutdownFieldAndSaveActorPoses(void); /* ShutdownFieldAndSaveActorPoses */
extern void FinishFieldSceneState(void);

void (*gSceneStateHandlers[19])(void) = {
    func_ov028_020ba69c,
    func_ov028_020ba6d4,
    func_ov028_020ba720,
    func_ov028_020ba758,
    func_ov028_020ba778,
    ResumeFieldFromMenu,
    SceneState_WaitPanelReady, /* SceneState_WaitPanelReady */
    func_ov028_020ba99c,
    func_ov028_020bab20,
    func_ov028_020bab68,
    SceneState_WaitScreenIdle, /* SceneState_WaitScreenIdle */
    EnterState12WithHalfRate, /* EnterState12WithHalfRate */
    func_ov028_020bac30,
    func_ov028_020bac5c,
    EnterOverlayTransition, /* EnterOverlayTransition */
    func_ov028_020bacd0,
    func_ov028_020bad1c,
    ShutdownFieldAndSaveActorPoses, /* ShutdownFieldAndSaveActorPoses */
    FinishFieldSceneState,
};
