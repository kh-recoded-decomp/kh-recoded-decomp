#include "nitro/types.h"
#include "nitro/hw.h"

typedef struct Tween {
    s32 mode;
    s32 duration_ticks;
    s32 from;
    s32 to;
    s64 startTick;
    u32 flags;
} Tween;

typedef struct MessageWindow {
    u8 pad_00[8];
    int state;
    u8 pad_0c[0x10];
    Tween tween;
    u8 pad_38[8];
    int unk40;
    int unk44;
} MessageWindow;

extern int *data_ov001_020a04c4;
extern void func_02052514(Tween *tween, int mode, int from, int to, int duration);
extern void func_0205255c(Tween *tween);

#define BG0CNT (*(volatile u16 *)REG_BG0CNT_ADDR)
#define BG1CNT (*(volatile u16 *)REG_BG1CNT_ADDR)
#define BG2CNT (*(volatile u16 *)REG_BG2CNT_ADDR)
#define BG3CNT (*(volatile u16 *)REG_BG3CNT_ADDR)
#define DISPCNT (*(volatile u32 *)REG_DISPCNT_ADDR)

void OpenMessageWindowLayers_0207a1d0(MessageWindow *window)
{
    int *mode = data_ov001_020a04c4;
    int state;

    window->unk40 = 0;
    window->unk44 = 0;
    if (*mode == 1) {
        BG0CNT = (u16)((BG0CNT & ~3) | 2);
        BG3CNT = (u16)((BG3CNT & ~3) | 1);
        BG2CNT = (u16)((BG2CNT & ~3) | 0);
        BG1CNT = (u16)((BG1CNT & ~3) | 3);
        state = 4;
    } else {
        BG1CNT = (u16)((BG1CNT & ~3) | 0);
        func_02052514(&window->tween, 0, 0, 0x64000, 100);
        func_0205255c(&window->tween);
        state = 3;
    }
    window->state = state;
    DISPCNT = (DISPCNT & ~0x1f00) | (0xf << 8);
}
