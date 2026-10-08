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

extern void ForEachListElement(WidgetRoot *root);
extern void SampleTweenValue(void *tween, s32 *value);
extern void SetClampedFadeLevel(WidgetRoot *root, int level);
extern BOOL RouteNewTouchToWidget(WidgetRoot *root);
extern void MoveFocusByDpad(WidgetRoot *root, u16 keys);
extern void AlarmCallback_0204f140(WidgetRoot *root);
extern void NNS_FndInitListWithOffset0_0204f130(WidgetRoot *root);

void UpdateWidgetRoot(WidgetRoot *root, u16 keys, BOOL notify, BOOL fireAlarm)
{
    BOOL handled;
    s32 fade;

    fade = 0;
    handled = FALSE;
    ForEachListElement(root);
    if (!root->fadeFinished) {
        SampleTweenValue(root->fadeTween, &fade);
        SetClampedFadeLevel(root, fade >> 12);
    }
    if (root->touchEnabled) {
        handled = RouteNewTouchToWidget(root);
    }
    if (!handled && root->dpadEnabled) {
        MoveFocusByDpad(root, keys);
    } else {
        root->allowedDirs = 0xF0;
    }
    if (notify) {
        if (fireAlarm) {
            AlarmCallback_0204f140(root);
        } else {
            NNS_FndInitListWithOffset0_0204f130(root);
        }
    }
}
