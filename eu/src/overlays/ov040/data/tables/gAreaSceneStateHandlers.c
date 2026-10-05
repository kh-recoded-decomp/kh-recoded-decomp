#include "nitro/types.h"

extern void ResetAreaMeshValues(void); /* ResetAreaMeshValues */
extern void func_ov040_020bcd28(void);
extern void func_ov040_020bcd6c(void); /* FinishAreaSceneLoad */
extern void func_ov040_020bce70(void);
extern void func_ov040_020bd0f4(void);
extern void func_ov040_020bd128(void); /* UpdateAreaSceneState */
extern void StartAreaCameraIntro(void);
extern void TickIntroRotation(void); /* TickIntroRotation */
extern void func_ov040_020bd418(void);
extern void FadeInAreaScreens(void); /* FadeInAreaScreens */
extern void func_ov040_020bd548(void);
extern void func_ov040_020bd568(void);
extern void EnterState13WithHalfRate(void); /* EnterState13WithHalfRate */
extern void func_ov040_020bd5e0(void);
extern void func_ov040_020bd604(void);
extern void func_ov040_020bd624(void);
extern void func_ov040_020bd648(void);
extern void FinishAreaTransition(void); /* FinishAreaTransition */
extern void func_ov040_020bd748(void); /* Gfd_DefaultFreeTexVram */

void (*gAreaSceneStateHandlers[19])(void) = {
    ResetAreaMeshValues, /* ResetAreaMeshValues */
    func_ov040_020bcd28,
    func_ov040_020bcd6c, /* FinishAreaSceneLoad */
    func_ov040_020bce70,
    func_ov040_020bd0f4,
    func_ov040_020bd128, /* UpdateAreaSceneState */
    StartAreaCameraIntro,
    TickIntroRotation, /* TickIntroRotation */
    func_ov040_020bd418,
    FadeInAreaScreens, /* FadeInAreaScreens */
    func_ov040_020bd548,
    func_ov040_020bd568,
    EnterState13WithHalfRate, /* EnterState13WithHalfRate */
    func_ov040_020bd5e0,
    func_ov040_020bd604,
    func_ov040_020bd624,
    func_ov040_020bd648,
    FinishAreaTransition, /* FinishAreaTransition */
    func_ov040_020bd748, /* Gfd_DefaultFreeTexVram */
};
