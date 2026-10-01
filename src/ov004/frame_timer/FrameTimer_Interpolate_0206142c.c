#include "nitro/types.h"

typedef struct {
    u16 startFrame;
    u16 endFrame;
} FrameTimer;

extern u32 g_frameCount_020645a0;
extern u32 DivideU32_02023fc8(u32 dividend, u32 divisor);

u16 FrameTimer_Interpolate_0206142c(FrameTimer *timer, u16 value)
{
    if (timer->endFrame <= g_frameCount_020645a0) {
        return value;
    }
    return DivideU32_02023fc8(value * (g_frameCount_020645a0 - timer->startFrame), timer->endFrame - timer->startFrame);
}
