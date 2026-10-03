#include "nitro/types.h"

typedef struct TweenFlags {
    u32 started : 1;
    u32 paused : 1;
    u32 finished : 1;
    u32 reserved : 29;
} TweenFlags;

typedef struct Tween {
    s32 mode;
    s32 duration;
    s32 from;
    s32 to;
    s64 startTick;
    TweenFlags flags;
} Tween;

typedef struct SlotMenu {
    s32 state;
    u8 pad_00004[0x11ee6 - 4];
    s16 slotIndex;
    s16 cursorSlot;
    u8 pad_11EEA[0x12368 - 0x11eea];
    s32 offsetY;
    u8 pad_1236C[4];
    s32 velocityY;
    u8 pad_12374[0x49838 - 0x12374];
    Tween fadeTween;
    u8 bgPriority;
    u8 altView;
} SlotMenu;

extern void func_ov076_020c61c8(SlotMenu *menu, u16 style);
extern void func_02052514(Tween *tween, int start, int end, int delay, int duration);
extern void func_0205255c(Tween *tween);

void SlotMenu_StartScrollAnimation_020c8490(SlotMenu *menu)
{
    int style;

    if (menu->slotIndex != menu->cursorSlot) {
        style = 4;
    } else {
        style = 0xc;
    }
    func_ov076_020c61c8(menu, style);
    menu->velocityY = 0x300000;
    menu->offsetY -= 0x2a000;
    menu->altView = 1;
    func_02052514(&menu->fadeTween, 0, 0, 0, 500);
    func_0205255c(&menu->fadeTween);
    menu->state = 7;
}
