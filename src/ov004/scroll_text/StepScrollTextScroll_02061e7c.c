#include "nitro/types.h"

typedef struct FrameTimer {
    u16 startFrame;
    u16 endFrame;
} FrameTimer;

typedef struct ScrollScreen {
    u8 pad_00[0xc];
    u8 bg[0x10918 - 0xc];
    s16 startX;
    s16 startY;
    s16 endX;
    s16 endY;
    s16 tileX;
    s16 tileY;
    u8 pad_10924[4];
    FrameTimer scrollTimer;
    u8 pad_1092c[4];
    s16 posX;
    s16 posY;
    u8 pad_10934[0x10940 - 0x10934];
} ScrollScreen;

typedef struct ScrollTextWork {
    u8 pad_00[0x14];
    ScrollScreen screens[2];
} ScrollTextWork;

typedef struct ScrollTextGlobals {
    u32 frameCount;
    ScrollTextWork *work;
} ScrollTextGlobals;

extern ScrollTextGlobals g_scrollText_020645a0;

extern u16 FrameTimer_GetDuration_0206148c(FrameTimer *timer);
extern u16 FrameTimer_GetElapsed_02061400(FrameTimer *timer);
extern u32 DivideU32_02023fc8(u32 dividend, u32 divisor);
extern void CopyScrollTextTiles_02061d5c(void *source, int screenIndex, s16 column, s16 row);

static inline int CompareCoord(int to, int from)
{
    if (from < to) {
        return 2;
    } else if (from <= to) {
        return 1;
    }
    return 0;
}

void StepScrollTextScroll_02061e7c(int screenIndex)
{
    ScrollScreen *screen;
    u32 duration;
    u32 elapsed;
    int endY;
    int endX;
    s16 startX;
    s16 startY;
    s16 dirX;
    s16 dirY;
    s16 x;
    s16 y;
    u8 movedY;

    screen = &g_scrollText_020645a0.work->screens[screenIndex];
    duration = FrameTimer_GetDuration_0206148c(&screen->scrollTimer);
    elapsed = FrameTimer_GetElapsed_02061400(&screen->scrollTimer);
    endX = screen->endX;
    startX = screen->startX;
    dirX = CompareCoord(endX, startX);
    endY = screen->endY;
    startY = screen->startY;
    dirY = CompareCoord(endY, startY);
    x = dirX == 2 ? startX + DivideU32_02023fc8(elapsed * (endX - startX), duration)
                  : startX - DivideU32_02023fc8(elapsed * (startX - endX), duration);
    y = dirY == 2 ? startY + DivideU32_02023fc8(elapsed * (endY - startY), duration)
                  : startY - DivideU32_02023fc8(elapsed * (startY - endY), duration);
    screen->posX = x;
    screen->posY = y;
    movedY = (screen->tileY >> 3) != (y >> 3);
    {
        u8 movedX = (screen->tileX >> 3) != (x >> 3);

        if (movedX || movedY) {
            CopyScrollTextTiles_02061d5c(g_scrollText_020645a0.work->screens[screenIndex].bg, screenIndex, x >> 3, y >> 3);
        }
    }
    screen->tileX = x;
    screen->tileY = y;
}
