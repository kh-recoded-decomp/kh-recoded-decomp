#include "nitro/types.h"

typedef struct TweenFlags {
    u32 started : 1;
    u32 paused : 1;
    u32 finished : 1;
} TweenFlags;

typedef struct Tween {
    int mode;
    int duration;
    int start;
    int end;
    s64 startTick;
    TweenFlags flags;
} Tween;

typedef struct WidgetPoint {
    int x;
    int y;
} WidgetPoint;

typedef struct Widget {
    u8 pad_00[0x5C];
    Tween tweenX;
    Tween tweenY;
} Widget;

extern void func_ov027_020b9360(void *root, Widget *widget, WidgetPoint *pos, int flags);
extern void SampleTweenValue_0205258c(Tween *tween, int *value);
extern void SetWidgetPosition_020b91c8(void *root, Widget *widget, const WidgetPoint *point, int mode);

void StepWidgetMoveTween_020b8ac8(void *root, Widget *widget)
{
    WidgetPoint next;
    WidgetPoint current;

    func_ov027_020b9360(root, widget, &current, 0);
    if (!widget->tweenX.flags.finished) {
        SampleTweenValue_0205258c(&widget->tweenX, &next.x);
    } else {
        next.x = current.x;
    }
    if (!widget->tweenY.flags.finished) {
        SampleTweenValue_0205258c(&widget->tweenY, &next.y);
    } else {
        next.y = current.y;
    }
    SetWidgetPosition_020b91c8(root, widget, &next, 0);
}

