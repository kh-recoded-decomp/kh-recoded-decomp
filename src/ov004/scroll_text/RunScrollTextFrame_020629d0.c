#include "nitro/types.h"

typedef struct {
    u16 startFrame;
    u16 endFrame;
} FrameTimer;

typedef struct {
    s32 waitFrames;
    s32 mode;
    s32 prevMode;
    u8 pad_0c[0x23ac4 - 0xc];
    int unk_bit0 : 1;
    int waitInput : 1;
    s32 skippable;
    u16 lineIndex;
    u16 lineCount;
    u8 pad_23ad0[0x30344 - 0x23ad0];
    FrameTimer exitTimer;
    FrameTimer lineTimer;
} ScrollTextWork;

typedef struct {
    u32 frameCount;
    ScrollTextWork *work;
} ScrollTextGlobals;

extern ScrollTextGlobals g_scrollText_020645a0;
extern void (*data_ov004_02064520[])(void);
extern u16 data_02060500;

extern void func_ov004_020619a0(void);
extern BOOL FrameTimer_IsExpired_0206146c(FrameTimer *timer);
extern void StartScrollTextRoll_02062090(void);
extern void BeginScrollTextExit_02062264(void);
extern void FrameTimer_Start_020613e0(FrameTimer *timer, int duration);
extern void StopSoundStreamAtIndex_0204deb0(int handleIndex, int fadeFrame);

int RunScrollTextFrame_020629d0(void)
{
    s32 mode;
    int done;

    data_ov004_02064520[g_scrollText_020645a0.work->mode]();
    mode = g_scrollText_020645a0.work->mode;
    if (mode == 3) {
        return 0;
    }
    if (mode == 4) {
        return -2;
    }
    if (mode < 2) {
        if (!g_scrollText_020645a0.work->waitInput) {
            func_ov004_020619a0();
            if (!g_scrollText_020645a0.work->waitInput &&
                FrameTimer_IsExpired_0206146c(&g_scrollText_020645a0.work->lineTimer) &&
                g_scrollText_020645a0.work->lineIndex == g_scrollText_020645a0.work->lineCount) {
                switch (g_scrollText_020645a0.work->mode) {
                case 0:
                    StartScrollTextRoll_02062090();
                    break;
                case 1:
                    BeginScrollTextExit_02062264();
                    break;
                }
            }
        } else {
            if (g_scrollText_020645a0.work->skippable == 0) {
                done = data_02060500 & 1;
            } else {
                g_scrollText_020645a0.work->waitFrames++;
                done = g_scrollText_020645a0.work->waitFrames >= 180;
            }
            if (done) {
                g_scrollText_020645a0.work->waitInput = 0;
            }
        }
        if (g_scrollText_020645a0.work->skippable != 0 && (data_02060500 & 8)) {
            g_scrollText_020645a0.work->prevMode = g_scrollText_020645a0.work->mode;
            g_scrollText_020645a0.work->mode = 2;
            FrameTimer_Start_020613e0(&g_scrollText_020645a0.work->exitTimer, 30);
            StopSoundStreamAtIndex_0204deb0(0, 30);
        }
    }
    g_scrollText_020645a0.frameCount++;
    return 0;
}
