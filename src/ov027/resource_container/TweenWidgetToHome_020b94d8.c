#include "nitro/types.h"

typedef struct Widget {
    u8 pad_00[0x2C];
    int homePos[2];
} Widget;

extern void func_ov027_020b9428(void *root, Widget *widget, int duration, const int *from, const int *to, int mode);

void TweenWidgetToHome_020b94d8(void *root, Widget *widget, int duration, int mode)
{
    func_ov027_020b9428(root, widget, duration, NULL, widget->homePos, mode);
}
