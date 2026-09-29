#include "nitro/types.h"

typedef struct {
    u16 startFrame;
    u16 endFrame;
} FrameTimer;

extern u32 g_frameCount_020645a0;

u16 FrameTimer_GetElapsed_02061400(FrameTimer *timer)
{
    if (g_frameCount_020645a0 >= timer->endFrame) {
        return timer->endFrame - timer->startFrame;
    }
    return g_frameCount_020645a0 - timer->startFrame;
}
