#include "nitro/types.h"
#include "nitro/fx.h"

extern void SetStageDrawLayer(int layer);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern void func_ov001_0206a8c8(u32 value);
extern void BeginScreenFadeOut(int mode);
extern void func_ov041_020bcd78(void);
extern void SetStageState(int state, BOOL runNow);

/* Puts the stage on draw layer 0x100, sets the quarter scale, fades the screen out and moves to state 0x15. */
void StartStageFadeOut(void)
{
    SetStageDrawLayer(0x100);
    func_ov001_0206a8c8(FX_Div(16 * FX32_ONE, 64 * FX32_ONE));
    BeginScreenFadeOut(2);
    func_ov041_020bcd78();
    SetStageState(0x15, 0);
}
