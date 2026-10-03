#include "nitro/types.h"

typedef struct TouchPoint {
    u16 x;
    u16 y;
} TouchPoint;

typedef struct Widget {
    u8 pad_00[0xA8];
    void (*onTouch)(struct Widget *widget);
} Widget;

typedef struct WidgetRoot {
    u8 pad_0000[0x6434];
    u8 widgetList[0xC];
} WidgetRoot;

extern Widget *NNS_FndGetNextListObject_02012a38(void *list, Widget *obj);
extern BOOL func_ov027_020b86fc(WidgetRoot *root, int x, int y, Widget *widget);

BOOL DispatchTouchToWidget_020b8874(WidgetRoot *root, TouchPoint *point)
{
    Widget *widget;
    BOOL handled = FALSE;

    for (widget = NNS_FndGetNextListObject_02012a38(root->widgetList, NULL); widget != NULL;
         widget = NNS_FndGetNextListObject_02012a38(root->widgetList, widget)) {
        if (func_ov027_020b86fc(root, point->x, point->y, widget)) {
            widget->onTouch(widget);
            handled = TRUE;
            break;
        }
    }
    return handled;
}
