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
extern int func_02029f48(void);
extern void SetBrightnessAndSyncMain_02029e7c(int brightness);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);

void UpdateSceneFade_020bcce8(void) {
    FadeState *fade = &(*(SceneWork **)(data_ov035_020bc4e0 + 0xb8))->fade;
    int brightness = func_02029f48();

    switch (fade->mode) {
    case 1:
        brightness += fade->rate >> 12;
        if (brightness > 16) {
            brightness = 16;
        }
        SetBrightnessAndSyncMain_02029e7c(brightness);
        if (brightness == 16) {
            fade->rate = FixedPointMultiply12(fade->rate, 2 << 12);
            fade->mode = 2;
        }
        break;
    case 2:
        brightness -= fade->rate >> 12;
        if (brightness < fade->target) {
            brightness = fade->target;
        }
        SetBrightnessAndSyncMain_02029e7c(brightness);
        if (brightness == fade->target) {
            fade->mode = 0;
        }
        break;
    }
}
