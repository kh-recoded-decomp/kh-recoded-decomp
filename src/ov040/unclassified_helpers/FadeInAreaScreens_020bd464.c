#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FadeState {
    fx32 baseAngle;
    u8 pad_04[0x10];
    s8 framesLeft;
} FadeState;

typedef struct AreaContext {
    u8 pad_00[6];
    u16 flags;
    u8 pad_08[0x1a];
    u16 mainLayers;
    u16 subLayers;
    u8 pad_26[0x4a];
    FadeState fade;
} AreaContext;

typedef struct MenuMachine {
    u8 pad_000[0x144];
    int result;
} MenuMachine;

extern AreaContext *data_ov035_020bc4e0;
extern MenuMachine *data_ov040_020be260;
extern s16 data_0205356c[];
extern void *func_ov046_020c15e8(void);
extern int FX_Div_01ff9c84(int numer, int denom);
extern int FixedPointMultiply12(int left, int right);
extern void SetBrightnessAndSyncMain_02029e7c(int value);
extern void SetSecondaryBrightness_02029ed0(int value);
extern void SetFieldMenuSuspended_02077b90(int a, int b);

static inline BOOL TickFade(FadeState *fade)
{
    BOOL done = TRUE;

    if (fade->framesLeft > 0) {
        fade->framesLeft--;
        if (fade->framesLeft < 8) {
            s16 level = data_0205356c[(0x400 - (s16)(FX_Div_01ff9c84(fade->framesLeft << 12, 0x8000) >> 2)) & 0xfff];
            SetBrightnessAndSyncMain_02029e7c(FixedPointMultiply12(0x10000, level) >> 12);
            SetSecondaryBrightness_02029ed0(FixedPointMultiply12(0x10000, level) >> 12);
        }
        done = FALSE;
    }
    return done;
}

int FadeInAreaScreens_020bd464(void)
{
    AreaContext *context = data_ov035_020bc4e0;

    func_ov046_020c15e8();
    if (!TickFade(&data_ov035_020bc4e0->fade)) {
        return -1;
    }
    if (!(context->flags & 4)) {
        *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & 0xffffe0ff) | 0xf00;
        SetFieldMenuSuspended_02077b90(0, 0);
        context->flags |= 4;
    }
    data_ov035_020bc4e0->mainLayers &= 0xfeff;
    data_ov035_020bc4e0->subLayers &= 0xfeff;
    data_ov040_020be260->result = 1;
    return 0x11;
}

