#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 target;
    s32 mode;
    s32 duration;
    fx32 rate;
} FadeState;

typedef struct {
    u8 pad_000[0x528];
    FadeState fade;
} SceneWork;

extern u8 *data_ov035_020bc4e0;
extern int func_02029f5c(void);
extern void SetBrightnessAndSyncMain(int brightness);
extern fx32 FX_Mul(fx32 a, fx32 b);

void UpdateSceneFade(void) {
    FadeState *fade = &(*(SceneWork **)(data_ov035_020bc4e0 + 0xb8))->fade;
    int brightness = func_02029f5c();

    switch (fade->mode) {
    case 1:
        brightness += fade->rate >> 12;
        if (brightness > 16) {
            brightness = 16;
        }
        SetBrightnessAndSyncMain(brightness);
        if (brightness == 16) {
            fade->rate = FX_Mul(fade->rate, 2 << 12);
            fade->mode = 2;
        }
        break;
    case 2:
        brightness -= fade->rate >> 12;
        if (brightness < fade->target) {
            brightness = fade->target;
        }
        SetBrightnessAndSyncMain(brightness);
        if (brightness == fade->target) {
            fade->mode = 0;
        }
        break;
    }
}
