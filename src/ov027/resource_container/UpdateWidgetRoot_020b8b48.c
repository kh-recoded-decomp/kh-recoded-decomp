#include "nitro/types.h"

typedef struct WidgetRoot {
    u8 pad_0000[0x6450];
    u8 fadeTween[0x18];
    u32 fadeUnk0 : 1;
    u32 fadeUnk1 : 1;
    u32 fadeFinished : 1;
    u8 pad_646c[0x8];
    u16 allowedDirs;
    u8 pad_6476[0x2];
    u32 touchEnabled : 1;
    u32 dpadEnabled : 1;
} WidgetRoot;

extern void ForEachListElement_020b8b1c(WidgetRoot *root);
extern void SampleTweenValue_0205258c(void *tween, s32 *value);
extern void SetClampedFadeLevel_0204f448(WidgetRoot *root, int level);
extern BOOL func_ov027_020b87c8(WidgetRoot *root);
extern void MoveFocusByDpad_020b88c0(WidgetRoot *root, u16 keys);
extern void AlarmCallback_0204f12c(WidgetRoot *root);
extern void NNS_FndInitListWithOffset0_0204f11c(WidgetRoot *root);

void UpdateWidgetRoot_020b8b48(WidgetRoot *root, u16 keys, BOOL notify, BOOL fireAlarm)
{
    BOOL handled;
    s32 fade;

    fade = 0;
    handled = FALSE;
    ForEachListElement_020b8b1c(root);
    if (!root->fadeFinished) {
        SampleTweenValue_0205258c(root->fadeTween, &fade);
        SetClampedFadeLevel_0204f448(root, fade >> 12);
    }
    if (root->touchEnabled) {
        handled = func_ov027_020b87c8(root);
    }
    if (!handled && root->dpadEnabled) {
        MoveFocusByDpad_020b88c0(root, keys);
    } else {
        root->allowedDirs = 0xF0;
    }
    if (notify) {
        if (fireAlarm) {
            AlarmCallback_0204f12c(root);
        } else {
            NNS_FndInitListWithOffset0_0204f11c(root);
        }
    }
}


