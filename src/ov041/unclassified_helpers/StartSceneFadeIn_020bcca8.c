#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 state;
    s32 mode;
    s32 duration;
    fx32 rate;
} FadeState;

typedef struct {
    u8 pad_000[8];
    u32 flags;
    u8 pad_00c[0x51c];
    FadeState fade;
} SceneWork;

extern u8 *data_ov035_020bc4e0;
extern void SetBrightnessAndSyncMain_02029e7c(int brightness);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);

void StartSceneFadeIn_020bcca8(s32 duration) {
    SceneWork *work = *(SceneWork **)(data_ov035_020bc4e0 + 0xb8);
    FadeState *fade = &work->fade;

    fade->state = 0;
    if ((work->flags & 0x20000000) == 0) {
        SetBrightnessAndSyncMain_02029e7c(10);
        fade->duration = duration;
        fade->rate = FX_Div_01ff9c84(10 << 12, duration);
        fade->mode = 2;
    }
}
