#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x58];
    u8 objManager[1];
} ScreenState;

extern void set_engine_alpha_blend_0204f400(char *object, int blendAlpha);
extern ScreenState *g_screenState_020b6f64;

void ApplyScreenAlphaBlend_020b6e60(void)
{
    set_engine_alpha_blend_0204f400((char *)g_screenState_020b6f64->objManager, 8);
}
