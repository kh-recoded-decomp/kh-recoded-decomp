#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xf4];
    s32 fadeLevel;
} ModeContext;

extern ModeContext *g_activeContext_020a04c4;

extern void G2x_SetBlendAlpha_02006850(vu32 *reg, int plane1, int plane2, int ev1, int ev2);

void ApplyModeFadeBlend_0207a8c8(void)
{
    int level = g_activeContext_020a04c4->fadeLevel;

    if (level > 16) {
        level = 16;
    } else if (level < 0) {
        level = 0;
    }
    G2x_SetBlendAlpha_02006850((vu32 *)0x04000050, 4, 1, level, 16 - level);
}
