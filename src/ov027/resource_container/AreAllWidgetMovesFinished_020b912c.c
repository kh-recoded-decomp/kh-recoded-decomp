#include "nitro/types.h"

typedef struct Widget Widget;

typedef struct WidgetRoot {
    u8 pad_0000[0x6434];
    u8 widgetList[0xC];
} WidgetRoot;

extern Widget *NNS_FndGetNextListObject_02012a38(void *list, Widget *obj);
extern BOOL IsWidgetMoveFinished_020b9100(Widget *widget);

BOOL AreAllWidgetMovesFinished_020b912c(WidgetRoot *root)
{
    Widget *widget;
    BOOL finished = TRUE;

    for (widget = NNS_FndGetNextListObject_02012a38(root->widgetList, NULL); widget != NULL;
         widget = NNS_FndGetNextListObject_02012a38(root->widgetList, widget)) {
        if (finished && IsWidgetMoveFinished_020b9100(widget)) {
            finished = TRUE;
        } else {
            finished = FALSE;
        }
    }
    return finished;
}
