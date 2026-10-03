#include "nitro/types.h"

extern void EnterOverlayTransition_020bac78(void);
extern void EnterState12WithHalfRate_020babec(void);
extern void SceneState_WaitPanelReady_020ba934(void);
extern void SceneState_WaitScreenIdle_020bab74(void);
extern void ShutdownFieldAndSaveActorPoses_020bad30(void);
extern void func_ov028_020ba67c(void);
extern void func_ov028_020ba6b4(void);
extern void func_ov028_020ba700(void);
extern void func_ov028_020ba738(void);
extern void func_ov028_020ba758(void);
extern void func_ov028_020ba7dc(void);
extern void func_ov028_020ba97c(void);
extern void func_ov028_020bab00(void);
extern void func_ov028_020bab48(void);
extern void func_ov028_020bac10(void);
extern void func_ov028_020bac3c(void);
extern void func_ov028_020bacb0(void);
extern void func_ov028_020bacfc(void);
extern void func_ov028_020bae20(void);

void (*data_ov028_020bb318[19])(void) = {
    func_ov028_020ba67c,
    func_ov028_020ba6b4,
    func_ov028_020ba700,
    func_ov028_020ba738,
    func_ov028_020ba758,
    func_ov028_020ba7dc,
    SceneState_WaitPanelReady_020ba934,
    func_ov028_020ba97c,
    func_ov028_020bab00,
    func_ov028_020bab48,
    SceneState_WaitScreenIdle_020bab74,
    EnterState12WithHalfRate_020babec,
    func_ov028_020bac10,
    func_ov028_020bac3c,
    EnterOverlayTransition_020bac78,
    func_ov028_020bacb0,
    func_ov028_020bacfc,
    ShutdownFieldAndSaveActorPoses_020bad30,
    func_ov028_020bae20,
};
