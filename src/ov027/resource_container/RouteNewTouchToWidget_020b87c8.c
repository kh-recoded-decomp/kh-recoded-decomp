#include "nitro/types.h"

typedef struct InputRecord {
    u16 x;
    u16 y;
    u16 touch;
    u16 invalid;
} InputRecord;

typedef struct Widget {
    u8 pad_00[0xA8];
    void (*onTouch)(struct Widget *widget);
} Widget;

typedef struct WidgetRoot {
    u8 pad_0000[0x6434];
    u8 widgetList[0xC];
    InputRecord lastInput;
} WidgetRoot;

extern int CopySourceBlock_020b9f7c(InputRecord *input);
extern BOOL GetLatestValidInputRecord_020b8774(WidgetRoot *root, InputRecord *out);
extern void func_01ff89a8(const void *src, void *dst, u32 size);
extern void *NNS_FndGetNextListObject_02012a38(void *list, void *obj);
extern BOOL HitTestWidget_020b86fc(WidgetRoot *root, int x, int y, Widget *widget);

BOOL RouteNewTouchToWidget_020b87c8(WidgetRoot *root)
{
    BOOL hit = FALSE;
    InputRecord input;
    Widget *widget;

    if (CopySourceBlock_020b9f7c(&input) == 0 && GetLatestValidInputRecord_020b8774(root, &input) == 0) {
        func_01ff89a8(&root->lastInput, &input, sizeof(InputRecord));
    }
    if (((root->lastInput.touch ^ input.touch) & input.touch) && input.invalid == 0) {
        for (widget = NNS_FndGetNextListObject_02012a38(root->widgetList, NULL); widget != NULL;
             widget = NNS_FndGetNextListObject_02012a38(root->widgetList, widget)) {
            if (HitTestWidget_020b86fc(root, input.x, input.y, widget)) {
                func_01ff89a8(&input, &root->lastInput, sizeof(InputRecord));
                widget->onTouch(widget);
                hit = TRUE;
                break;
            }
        }
    }
    if (hit == FALSE) {
        func_01ff89a8(&input, &root->lastInput, sizeof(InputRecord));
    }
    return hit;
}
