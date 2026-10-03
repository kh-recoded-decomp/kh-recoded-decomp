#include "nitro/types.h"

extern void EnterState13WithHalfRate_020bd5a4(void);
extern void FadeInAreaScreens_020bd464(void);
extern void FinishAreaSceneLoad_020bcd4c(void);
extern void FinishAreaTransition_020bd66c(void);
extern void Gfd_DefaultFreeTexVram_020bd728(void);
extern void ResetAreaMeshValues_020bcc60(void);
extern void TickIntroRotation_020bd364(void);
extern void UpdateAreaSceneState_020bd108(void);
extern void func_ov040_020bcd08(void);
extern void func_ov040_020bce50(void);
extern void func_ov040_020bd0d4(void);
extern void func_ov040_020bd298(void);
extern void func_ov040_020bd3f8(void);
extern void func_ov040_020bd528(void);
extern void func_ov040_020bd548(void);
extern void func_ov040_020bd5c0(void);
extern void func_ov040_020bd5e4(void);
extern void func_ov040_020bd604(void);
extern void func_ov040_020bd628(void);

void (*data_ov040_020be1c0[19])(void) = {
    ResetAreaMeshValues_020bcc60,
    func_ov040_020bcd08,
    FinishAreaSceneLoad_020bcd4c,
    func_ov040_020bce50,
    func_ov040_020bd0d4,
    UpdateAreaSceneState_020bd108,
    func_ov040_020bd298,
    TickIntroRotation_020bd364,
    func_ov040_020bd3f8,
    FadeInAreaScreens_020bd464,
    func_ov040_020bd528,
    func_ov040_020bd548,
    EnterState13WithHalfRate_020bd5a4,
    func_ov040_020bd5c0,
    func_ov040_020bd5e4,
    func_ov040_020bd604,
    func_ov040_020bd628,
    FinishAreaTransition_020bd66c,
    Gfd_DefaultFreeTexVram_020bd728,
};
