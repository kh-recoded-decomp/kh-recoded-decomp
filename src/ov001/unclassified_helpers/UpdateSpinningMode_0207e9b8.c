#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x20];
    s32 isActive;
    u16 angle;
    s16 angleStep;
    s16 angleScale;
    u8 pad_2A[0xAC - 0x2A];
    s32 currentCount;
    s32 targetCount;
} RotatingContext;

extern RotatingContext *data_ov001_020a04d4;
extern void func_ov001_0207e73c(RotatingContext *context, s32 flag);
extern void func_ov001_0207e4f4(RotatingContext *context);
extern void func_ov001_0207e598(RotatingContext *context);

s32 UpdateSpinningMode_0207e9b8(void)
{
    RotatingContext *context = data_ov001_020a04d4;

    if (context->isActive != 0) {
        func_ov001_0207e73c(context, 0);
        context->angle = (context->angle + 0x10000 + context->angleStep * context->angleScale) % 0x10000;
        func_ov001_0207e4f4(context);
        if (context->currentCount < context->targetCount) {
            func_ov001_0207e598(context);
        }
    }
    return 0;
}
