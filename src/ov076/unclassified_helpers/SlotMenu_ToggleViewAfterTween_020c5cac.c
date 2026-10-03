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
    u8 pad_00004[0x49838 - 4];
    Tween fadeTween;
    u8 bgPriority;
    u8 altView;
} SlotMenu;

extern void SetSecondaryElementEnabled_020bc084(BOOL enabled);
extern void SampleTweenValue_0205258c(Tween *tween, s32 *value);
extern void func_02052514(Tween *tween, int start, int end, int delay, int duration);
extern void func_0205255c(Tween *tween);
extern void SlotMenu_RefreshView_020c5be0(SlotMenu *menu);

void SlotMenu_ToggleViewAfterTween_020c5cac(SlotMenu *menu)
{
    s32 value;

    SetSecondaryElementEnabled_020bc084(FALSE);
    if (menu->state != 5) {
        SampleTweenValue_0205258c(&menu->fadeTween, &value);
        if (menu->fadeTween.flags.finished) {
            func_02052514(&menu->fadeTween, 0, 0, 0, 500);
            func_0205255c(&menu->fadeTween);
            menu->altView = !menu->altView;
        }
    }
    SlotMenu_RefreshView_020c5be0(menu);
}
