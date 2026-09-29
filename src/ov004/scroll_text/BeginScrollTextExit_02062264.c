#include "nitro/types.h"

#define reg_GX_DISPCNT     (*(volatile u32 *)0x04000000)
#define reg_GXS_DB_DISPCNT (*(volatile u32 *)0x04001000)

typedef struct {
    u16 startFrame;
    u16 endFrame;
} FrameTimer;

typedef struct {
    u8 pad_00[4];
    s32 mode;
    u8 pad_08[0x30344 - 0x8];
    FrameTimer exitTimer;
} ScrollTextWork;

typedef struct {
    u32 frameCount;
    ScrollTextWork *work;
} ScrollTextGlobals;

extern ScrollTextGlobals g_scrollText_020645a0;
extern char data_ov004_02064578[];

extern void NotifyBothOrOne_02001154(u32 irqMask, const char *name, int channel);
extern void FrameTimer_Start_020613e0(FrameTimer *timer, int duration);
extern void StopSoundStreamAtIndex_0204deb0(int handleIndex, int fadeFrame);

void BeginScrollTextExit_02062264(void)
{
    NotifyBothOrOne_02001154(1, data_ov004_02064578, 0);
    g_scrollText_020645a0.work->mode = 2;
    FrameTimer_Start_020613e0(&g_scrollText_020645a0.work->exitTimer, 0x1e);
    reg_GX_DISPCNT = (reg_GX_DISPCNT & ~0x1f00) | 0x1500;
    reg_GXS_DB_DISPCNT = (reg_GXS_DB_DISPCNT & ~0x1f00) | 0x1100;
    StopSoundStreamAtIndex_0204deb0(0, 0x1e);
}
