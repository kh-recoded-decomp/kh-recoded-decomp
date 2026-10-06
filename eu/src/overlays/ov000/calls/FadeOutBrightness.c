#include "nitro/types.h"

typedef struct PanelFade {
    u8 pad_0[0x3c];
    s32 frame;
    s32 fadeInFrames;
    s32 fadeOutFrames;
} PanelFade;

extern int _s32_div_f(int numerator, int denominator);

int FadeOutBrightness(PanelFade *fade)
{
    int level = _s32_div_f(fade->frame << 4, fade->fadeOutFrames) - 0x10;

    if (level > 0) {
        return 0;
    }
    if (level < -0x10) {
        level = -0x10;
    }
    return level;
}
