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
extern MenuMachine *data_ov040_020be280;
extern s16 data_02053580[];
extern fx32 *func_ov046_020c1608(void);
extern int FX_Div(int numer, int denom);
extern int FX_Mul(int left, int right);

int TickIntroRotation(void)
{
    RotationContext *context = data_ov035_020bc4e0;

    if (context->framesLeft > 0) {
        fx32 *out = func_ov046_020c1608();
        fx32 angle;
        int index;

        context->framesLeft--;
        angle = context->baseAngle
              - FX_Mul(0x400, 0x1000 - FX_Div(context->framesLeft << 12, 0xf000));
        index = (u16)(((s64)angle * 0xb60b60b60bLL + 0x80000000000LL) >> 44) >> 4;
        out[0] = data_02053580[index];
        out[1] = data_02053580[(0x400 - index) & 0xfff];
        return -1;
    }
    data_ov040_020be280->flags |= 0x8000;
    return 8;
}
