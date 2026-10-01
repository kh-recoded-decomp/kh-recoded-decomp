#include "nitro/types.h"

typedef struct ScreenFade {
    u32 flags;
    s32 progress;
    u8 pad_08[4];
    s32 brightness;
    u8 pad_10[0xC];
    s32 brightnessStep;
} ScreenFade;

typedef void *(*FadeStep)(void);

extern ScreenFade *data_ov001_020a0480;

extern void func_ov001_0206a4e4(void);
extern void SetBrightnessAndSyncMain_02029e7c(int brightness);
extern void SetSecondaryBrightness_02029ed0(int brightness);
extern void *func_ov001_0206a138(void);

FadeStep ScreenFadeOutStep_0206a208(void)
{
    ScreenFade *fade = data_ov001_020a0480;
    FadeStep next = NULL;

    if (fade->flags & 0x20) {
        return next;
    }
    fade->progress -= (fade->flags & 0x200) ? 0x400 : 0x800;
    func_ov001_0206a4e4();
    if (fade->progress <= 0x100) {
        fade->flags &= ~2;
        next = (FadeStep)func_ov001_0206a138;
        if (!(fade->flags & 0x100)) {
            SetBrightnessAndSyncMain_02029e7c(-16);
        }
        fade->brightnessStep = 0x1800;
    }
    if (!(fade->flags & 0x100)) {
        SetSecondaryBrightness_02029ed0(fade->brightness >> 12);
    }
    fade->brightness -= fade->brightnessStep;
    if (fade->brightness < -0x10000) {
        fade->brightness = -0x10000;
    }
    return next;
}
