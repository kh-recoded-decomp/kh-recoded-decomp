#include "nitro/types.h"

typedef struct {
    u16 startFrame;
    u16 endFrame;
} FrameTimer;

extern u32 g_frameCount_020645a0;

BOOL FrameTimer_IsExpired_0206146c(FrameTimer *timer)
{
    return g_frameCount_020645a0 >= timer->endFrame;
}
