#include "nitro/types.h"
#include "nitro/fx_types.h"

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

typedef struct ScrollList {
    s16 count;
    s16 slotIndex;
    u8 pad_04[0x34 - 4];
    s32 scrollY;
} ScrollList;

typedef struct SlotMenu {
    s32 state;
    u8 pad_00004[0x11ee4 - 4];
    ScrollList list;
    u8 pad_11F1C[0x12264 - 0x11f1c];
    VecFx32 cameraPos;
    u8 pad_12270[0x49834 - 0x12270];
    s32 phase;
    Tween fadeTween;
    u8 bgPriority;
} SlotMenu;

extern void *func_ov039_020bc1bc(void);
extern void SetSecondaryElementEnabled_020bc084(BOOL enabled);
extern void SampleTweenValue_0205258c(Tween *tween, s32 *value);
extern void func_02052514(Tween *tween, int start, int end, int delay, int duration);
extern void func_0205255c(Tween *tween);
extern void SlotMenu_ReloadSlot_020c6f60(SlotMenu *menu, int slot, int mode);
extern void SetBrightnessAndSyncMain_02029e7c(int value);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void SlotMenu_SetBg0Priority_020c4424(SlotMenu *menu, int priority);
extern void func_ov076_020c83e4(SlotMenu *menu);
extern void SlotMenu_SetBgScrollMode_020c74e4(SlotMenu *menu, int mode, int scrollY);
extern void UpdateWidgetRootAndFireAlarm_020b8c94(void *layout, int arg);
extern void func_ov076_020c7534(SlotMenu *menu, int mode);

void SlotMenu_UpdateCameraTransition_020c5d20(SlotMenu *menu)
{
    void *layout = func_ov039_020bc1bc();
    s32 value;
    VecFx32 restPos;
    VecFx32 startPos;

    startPos.x = 0x80000;
    startPos.y = 0x60000;
    startPos.z = 0x300000;
    restPos = startPos;
    SetSecondaryElementEnabled_020bc084(FALSE);
    switch (menu->phase) {
    case 0:
        func_02052514(&menu->fadeTween, 0, 0, 0x10000, 0x32);
        func_0205255c(&menu->fadeTween);
        menu->cameraPos = startPos;
        menu->cameraPos.x += 0x12c000;
        menu->phase = 1;
        SlotMenu_ReloadSlot_020c6f60(menu, menu->list.slotIndex, 0);
        SetBrightnessAndSyncMain_02029e7c(0x10);
        PlaySoundEffect_0204d924(1, 0xc);
        break;
    case 1:
        SampleTweenValue_0205258c(&menu->fadeTween, &value);
        SetBrightnessAndSyncMain_02029e7c(value >> 12);
        if (menu->fadeTween.flags.finished) {
            menu->phase = 2;
            func_02052514(&menu->fadeTween, 0, 0x10000, 0, 400);
            func_0205255c(&menu->fadeTween);
            menu->bgPriority = 0;
        }
        break;
    case 2:
        SampleTweenValue_0205258c(&menu->fadeTween, &value);
        SetBrightnessAndSyncMain_02029e7c(value >> 12);
        if (menu->fadeTween.flags.finished) {
            menu->phase = 3;
            SlotMenu_SetBg0Priority_020c4424(menu, 0);
        }
        break;
    case 3:
        menu->cameraPos.x -= 0x3c000;
        if (menu->cameraPos.x < restPos.x) {
            menu->cameraPos.x = restPos.x;
            menu->phase = 4;
            func_02052514(&menu->fadeTween, 0, 0, 0, 1000);
            func_0205255c(&menu->fadeTween);
        }
        break;
    case 4:
        SampleTweenValue_0205258c(&menu->fadeTween, &value);
        if (menu->fadeTween.flags.finished) {
            menu->phase = 5;
        }
        break;
    case 5:
        menu->cameraPos.x -= 0x3c000;
        if (menu->cameraPos.x < restPos.x - 0x12c000) {
            SlotMenu_SetBg0Priority_020c4424(menu, 1);
            func_ov076_020c83e4(menu);
        }
        break;
    }
    SlotMenu_SetBgScrollMode_020c74e4(menu, 0, menu->list.scrollY);
    UpdateWidgetRootAndFireAlarm_020b8c94(layout, 0);
    func_ov076_020c7534(menu, 0);
}
