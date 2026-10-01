#include "nitro/types.h"

typedef struct {
    u16 startFrame;
    u16 endFrame;
} FrameTimer;

extern u32 g_frameCount_020645a0;

void FrameTimer_Start_020613e0(FrameTimer *timer, u16 duration)
{
    timer->startFrame = g_frameCount_020645a0;
    timer->endFrame = g_frameCount_020645a0 + duration;
}
