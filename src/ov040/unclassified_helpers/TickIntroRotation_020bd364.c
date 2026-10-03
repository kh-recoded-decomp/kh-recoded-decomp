#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct RotationContext {
    u8 pad_00[0x70];
    fx32 baseAngle;
    u8 pad_74[0x10];
    s8 framesLeft;
} RotationContext;

typedef struct MenuMachine {
    u8 pad_000[0x13c];
    u16 flags;
} MenuMachine;

extern RotationContext *data_ov035_020bc4e0;
extern MenuMachine *data_ov040_020be260;
extern s16 data_0205356c[];
extern fx32 *func_ov046_020c15e8(void);
extern int FX_Div_01ff9c84(int numer, int denom);
extern int FixedPointMultiply12(int left, int right);

int TickIntroRotation_020bd364(void)
{
    RotationContext *context = data_ov035_020bc4e0;

    if (context->framesLeft > 0) {
        fx32 *out = func_ov046_020c15e8();
        fx32 angle;
        int index;

        context->framesLeft--;
        angle = context->baseAngle
              - FixedPointMultiply12(0x400, 0x1000 - FX_Div_01ff9c84(context->framesLeft << 12, 0xf000));
        index = (u16)(((s64)angle * 0xb60b60b60bLL + 0x80000000000LL) >> 44) >> 4;
        out[0] = data_0205356c[index];
        out[1] = data_0205356c[(0x400 - index) & 0xfff];
        return -1;
    }
    data_ov040_020be260->flags |= 0x8000;
    return 8;
}
