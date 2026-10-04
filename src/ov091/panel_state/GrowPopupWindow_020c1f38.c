#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef float f32;

#define INT_TO_FX32(n) ((fx32)(((f32)(n) > 0) ? (0.5f + 4096.0f * (f32)(n)) : (4096.0f * (f32)(n) - 0.5f)))

typedef struct {
    s32 state;
    u32 flags;
    s32 stateTimer;
} PopupWindow;

extern fx32 FX_Div_01ff9c84(fx32 numerator, fx32 denominator);
extern void func_ov091_020c225c(PopupWindow *window, fx32 scale);
extern void SetPopupState_020c2784(PopupWindow *window, s32 state);
extern void SetSubBg2Visible_020c271c(PopupWindow *window, BOOL visible);

void GrowPopupWindow_020c1f38(PopupWindow *window)
{
    fx32 scale = FX_Div_01ff9c84(INT_TO_FX32(window->stateTimer), 0x2000);

    func_ov091_020c225c(window, scale);
    if (scale == 0x1000) {
        SetPopupState_020c2784(window, 4);
    }
    SetSubBg2Visible_020c271c(window, TRUE);
    window->stateTimer++;
}
