#include "nitro/types.h"

typedef struct {
    u16 startFrame;
    u16 endFrame;
} FrameTimer;

typedef struct {
    u8 pad_00[4];
    s32 mode;
    s32 phase;
    u8 pad_0c[0x23ac8 - 0xc];
    s32 exitMode;
    u8 pad_23acc[0x30344 - 0x23acc];
    FrameTimer fadeTimer;
} ScrollTextWork;

typedef struct {
    u32 frameCount;
    ScrollTextWork *work;
} ScrollTextGlobals;

extern ScrollTextGlobals g_scrollText_020645a0;
extern char data_ov004_02064578[];
extern void (*data_ov004_02064520[])(void);

extern u16 FrameTimer_Interpolate_0206142c(FrameTimer *timer, u16 value);
extern BOOL FrameTimer_IsExpired_0206146c(FrameTimer *timer);
extern void SetBrightnessAndSyncMain_02029e7c(int value);
extern void SetSecondaryBrightness_02029ed0(int value);
extern BOOL IsSoundStreamActive_0204ded4(int handleIndex);
extern void NotifyBothOrOne_02001154(u32 a, char *name, int index);

void UpdateScrollTextFadeOut_02062530(void)
{
    int brightness = -(s16)FrameTimer_Interpolate_0206142c(&g_scrollText_020645a0.work->fadeTimer, 16);

    SetBrightnessAndSyncMain_02029e7c(brightness);
    SetSecondaryBrightness_02029ed0(brightness);
    if (FrameTimer_IsExpired_0206146c(&g_scrollText_020645a0.work->fadeTimer) &&
        !IsSoundStreamActive_0204ded4(0)) {
        if (g_scrollText_020645a0.work->phase == 1) {
            NotifyBothOrOne_02001154(1, data_ov004_02064578, 0);
        }
        g_scrollText_020645a0.work->mode = g_scrollText_020645a0.work->exitMode == 1 ? 3 : 4;
    }
    data_ov004_02064520[g_scrollText_020645a0.work->phase]();
}
