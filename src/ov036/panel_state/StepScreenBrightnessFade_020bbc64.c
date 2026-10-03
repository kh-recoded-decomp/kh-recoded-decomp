#include "nitro/types.h"

typedef struct BrightnessFade {
    s32 from;
    s32 to;
    s32 duration;
    s32 current;
    s32 timer;
} BrightnessFade;

typedef struct ScreenLayer {
    u8 pad_00[0x24];
    u16 flags;
    u8 pad_26[0x2e];
} ScreenLayer;

typedef struct SceneWork {
    u8 pad_0000[0xe84];
    BrightnessFade fades[2];
    u8 pad_0EAC[0x1ec];
    ScreenLayer *layers;
} SceneWork;

typedef struct SceneContext {
    u32 unk_00;
    SceneWork *work;
} SceneContext;

extern SceneContext data_ov036_020c3920;
extern void SetBrightnessAndSyncMain_02029e7c(int brightness);
extern void SetSecondaryBrightness_02029ed0(int brightness);

void StepScreenBrightnessFade_020bbc64(int screen)
{
    SceneWork *work = data_ov036_020c3920.work;
    ScreenLayer *layer = &work->layers[screen];
    BrightnessFade *fade = &work->fades[screen];
    int from;

    fade->timer++;
    from = work->fades[screen].from;
    fade->current = from + fade->timer * (fade->to - from) / fade->duration;
    if (fade->current > 0x10) {
        fade->current = 0x10;
    }
    if (fade->current < -0x10) {
        fade->current = -0x10;
    }
    if (screen == 0) {
        SetBrightnessAndSyncMain_02029e7c(fade->current);
    } else {
        SetSecondaryBrightness_02029ed0(fade->current);
    }
    if (fade->timer >= fade->duration) {
        layer->flags &= ~0x8;
    }
}
