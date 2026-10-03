#include "nitro/types.h"

typedef struct WidgetRect {
    int x;
    int y;
    int width;
    int height;
} WidgetRect;

typedef struct Widget {
    u8 pad_00[0x94];
    u32 disabled : 1;
    u32 focusable : 1;
    u8 pad_98[0x10];
    void (*onTouch)(struct Widget *widget);
} Widget;

extern BOOL IsWidgetMoveFinished_020b9100(Widget *widget);
extern WidgetRect *func_ov027_020b86a4(void *root, WidgetRect *rect, Widget *widget);

BOOL HitTestWidget_020b86fc(void *root, int x, int y, Widget *widget)
{
    WidgetRect rect;
    BOOL hit = FALSE;

    if (widget->onTouch != NULL && !widget->disabled && widget->focusable &&
        IsWidgetMoveFinished_020b9100(widget) != FALSE) {
        func_ov027_020b86a4(root, &rect, widget);
        if (rect.width == 0xFFFF || rect.height == 0xFFFF) {
            return FALSE;
        }
        if (rect.x <= x && x <= rect.x + rect.width && rect.y <= y && y <= rect.y + rect.height) {
            hit = TRUE;
        }
    }
    return hit;
}
