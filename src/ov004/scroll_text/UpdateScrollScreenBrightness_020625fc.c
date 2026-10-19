#include "nitro/types.h"

typedef struct FrameTimer {
    u16 startFrame;
    u16 endFrame;
} FrameTimer;

typedef struct ScrollScreen {
    u8 reserved00[0x10924];
    FrameTimer fadeTimer;
    u8 reserved10928[4];
    s8 brightness;
    u8 state;
    u8 reserved1092e;
    u8 subState;
    u8 reserved10930[0x10];
} ScrollScreen;

typedef struct ScrollTextWork {
    u32 reserved00;
    s32 mode;
    u8 reserved08[0xc];
    ScrollScreen screens[2];
} ScrollTextWork;

typedef struct ScrollTextGlobals {
    u32 frameCount;
    ScrollTextWork *work;
    u32 reserved08[6];
} ScrollTextGlobals;

typedef struct ScrollFadeCallbacks {
    void (*setBrightness)(s32 planes, s32 brightness);
    void (*finish)(void);
} ScrollFadeCallbacks;

typedef struct ScrollFadeCallbackTable {
    ScrollFadeCallbacks screen[2];
} ScrollFadeCallbackTable;

typedef char ScrollTextGlobalsSizeCheck[(sizeof(ScrollTextGlobals) == 32) ? 1 : -1];
typedef char ScrollScreenStrideCheck[(sizeof(ScrollScreen) == 0x10940) ? 1 : -1];

extern const ScrollFadeCallbackTable gOv004Callbacks;
extern ScrollTextGlobals gScrollTextGlobals;
extern BOOL FrameTimer_IsExpired(const FrameTimer *timer);
extern u16 FrameTimer_Interpolate(const FrameTimer *timer, u16 scale);

/* Apply the screen's timed fade and run its completion callback when due. */
void UpdateScrollScreenBrightness_020625fc(s32 screen)
{
    ScrollFadeCallbackTable table = gOv004Callbacks;
    ScrollFadeCallbacks *callbacks = &table.screen[screen];
    ScrollScreen *work = &gScrollTextGlobals.work->screens[screen];
    s32 planes = (gScrollTextGlobals.work->mode >= 2 ? 0x10 : 0) | 0xc;
    s16 brightness;

    if (FrameTimer_IsExpired(&work->fadeTimer)) {
        switch (work->state) {
        case 1:
            work->brightness = 0;
            callbacks->setBrightness(planes, 0);
            callbacks->finish();
            break;
        case 2:
            work->brightness = 0;
            work->subState = 0;
            callbacks->setBrightness(planes, -16);
            break;
        }
    } else {
        brightness = (s16)FrameTimer_Interpolate(&work->fadeTimer, 16);
        switch (gScrollTextGlobals.work->screens[screen].state) {
        case 1:
            work->brightness = brightness - 16;
            callbacks->setBrightness(planes, work->brightness);
            break;
        case 2:
            work->brightness = -brightness;
            callbacks->setBrightness(planes, work->brightness);
            break;
        }
    }
}
