#include "nitro/types.h"

typedef struct Widget {
    u8 pad_00[0xC];
    int id;
} Widget;

typedef struct WidgetRoot {
    u8 pad_0000[0x6434];
    u8 widgetList[0xC];
} WidgetRoot;

extern Widget *NNS_FndGetNextListObject_02012a38(void *list, Widget *obj);

Widget *FindWidgetById_020b90a4(WidgetRoot *root, int id)
{
    Widget *widget = NULL;

    if (id >= 0) {
        for (widget = NNS_FndGetNextListObject_02012a38(root->widgetList, NULL); widget != NULL;
             widget = NNS_FndGetNextListObject_02012a38(root->widgetList, widget)) {
            if (widget->id == id) {
                break;
            }
        }
    }
    return widget;
}
