#include "nitro/types.h"

typedef struct Tween {
    int duration;
    int mode;
    int start;
    int end;
    u8 pad_10[0xC];
} Tween;

typedef struct Widget {
    u8 pad_00[0x5C];
    Tween tweenX;
    Tween tweenY;
} Widget;

extern void func_ov027_020b9360(void *root, Widget *widget, int *pos, int flags);
extern void func_01ff89a8(const void *src, void *dst, u32 size);
extern void func_02052514(Tween *tween, int duration, int start, int end, int mode);
extern void func_0205255c(Tween *tween);

void StartWidgetMoveTween_020b9428(void *root, Widget *widget, int duration, const int *from, const int *to, int mode)
{
    int pos[2];

    if (from == NULL) {
        func_ov027_020b9360(root, widget, pos, 0);
    } else {
        func_01ff89a8(from, pos, 8);
    }
    func_02052514(&widget->tweenX, duration, pos[0], to[0], mode);
    func_02052514(&widget->tweenY, duration, pos[1], to[1], mode);
    func_0205255c(&widget->tweenX);
    func_0205255c(&widget->tweenY);
}
