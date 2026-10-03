#include "nitro/types.h"

extern void StartMenuOverlayWindow_0207ac18(void);
extern void StepSubScreenFadeIn_0207ad04(void);
extern void StepSubScreenFadeIn_0207ad30(void);
extern void UpdateDisplayFadeState_0207ac90(void);
extern void _fp_init_0207abd8(void);
extern void _fp_init_0207ad5c(void);
extern void func_ov001_0207abdc(void);

void (*data_ov001_0209ef4c[7])(void) = {
    _fp_init_0207abd8,
    func_ov001_0207abdc,
    StartMenuOverlayWindow_0207ac18,
    UpdateDisplayFadeState_0207ac90,
    StepSubScreenFadeIn_0207ad04,
    StepSubScreenFadeIn_0207ad30,
    _fp_init_0207ad5c,
};
