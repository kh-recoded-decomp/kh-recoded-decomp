#include "nitro/types.h"

typedef struct WidgetPoint {
    int x;
    int y;
} WidgetPoint;

typedef struct WidgetDesc {
    int elementId;
    int groupId;
    int keysDefault[2];
    int values10[2];
    int keysAlternate[2];
    WidgetPoint offset;
    WidgetPoint point28;
    WidgetPoint anchor;
    u16 value38;
    u16 value3A;
    int value3C;
    int neighborIds[4];
    int flags;
    int priorityBase;
} WidgetDesc;

typedef struct WidgetFlags {
    unsigned useAlternate : 1;
    unsigned visible : 1;
    unsigned hasOffset : 1;
    unsigned flag3 : 1;
} WidgetFlags;

typedef struct Widget {
    u8 pad_00[0xC];
    int elementId;
    int groupId;
    int slots[2];
    u16 value1C;
    u16 value1E;
    int value20;
    WidgetPoint offset;
    WidgetPoint point2C;
    WidgetPoint anchor;
    WidgetPoint position;
    int keysDefault[2];
    int values10[2];
    int keysAlternate[2];
    u8 tween5C[0x1C];
    u8 tween78[0x1C];
    union {
        u32 all;
        WidgetFlags bits;
    } flags;
    struct Widget *neighbors[4];
    void *onConfirm;
} Widget;

typedef struct WidgetRoot {
    u8 pad_00[0x6434];
    u8 widgetList[0x3C];
    int slotStyle;
} WidgetRoot;

extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff8830(void *dst, int value, u32 size);
extern void func_01ff89a8(const void *src, void *dst, u32 size);
extern void func_020524e8(void *tween);
extern int PXI_Init_0204f0b4(WidgetRoot *root, int key, int groupId);
extern void func_0204f178(WidgetRoot *root, int slot, int priority);
extern void func_0204f298(WidgetRoot *root, int slot, int style);
extern void func_0204f378(WidgetRoot *root, int slot, int visible);
extern void func_0204f3c8(WidgetRoot *root, int slot, int value);
extern void func_ov027_020b91c8(WidgetRoot *root, Widget *widget, const WidgetPoint *point, int mode);
extern void AppendIntrusiveListObject_020128d0(void *list, void *obj);

Widget *CreateWidget_020b8cbc(WidgetRoot *root, const WidgetDesc *desc) {
    Widget *widget;
    int i;
    const int *keys;
    WidgetPoint origin = {0, 0};

    widget = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(Widget));
    if (widget != NULL) {
        func_01ff8830(widget, 0, sizeof(Widget));
        widget->elementId = desc->elementId;
        func_020524e8(widget->tween5C);
        func_020524e8(widget->tween78);

        if (desc->flags & 1) {
            if (desc->keysAlternate[0] >= 0 || desc->keysAlternate[1] >= 0) {
                keys = desc->keysAlternate;
            } else {
                keys = desc->keysDefault;
            }
            widget->flags.bits.useAlternate = 1;
        } else {
            keys = desc->keysDefault;
            widget->flags.bits.useAlternate = 0;
        }

        for (i = 0; i < 2; i++) {
            widget->keysDefault[i] = desc->keysDefault[i];
            widget->values10[i] = desc->values10[i];
            widget->keysAlternate[i] = desc->keysAlternate[i];
            if (keys[i] >= 0) {
                widget->slots[i] = PXI_Init_0204f0b4(root, keys[i], desc->groupId);
                func_0204f178(root, widget->slots[i], (u8)(desc->priorityBase + 1 - i));
                func_0204f298(root, widget->slots[i], root->slotStyle);
            } else {
                widget->slots[i] = -1;
            }
        }

        widget->groupId = desc->groupId;
        widget->value1C = desc->value38;
        widget->value1E = desc->value3A;
        widget->value20 = desc->value3C;
        func_01ff89a8(&desc->anchor, &widget->anchor, 8);

        if (desc->flags & 4) {
            func_ov027_020b91c8(root, widget, &desc->offset, 0);
            func_01ff89a8(&desc->offset, &widget->offset, 8);
            func_01ff89a8(&desc->point28, &widget->point2C, 8);
            widget->flags.all |= 4;
        } else {
            func_ov027_020b91c8(root, widget, &origin, 3);
            widget->flags.all &= ~4;
        }

        if (desc->flags & 2) {
            for (i = 0; i < 2; i++) {
                if (widget->slots[i] != -1) {
                    func_0204f378(root, widget->slots[i], 0);
                }
            }
            widget->flags.all &= ~2;
        } else {
            widget->flags.all |= 2;
        }

        if (desc->flags & 0x10) {
            for (i = 0; i < 2; i++) {
                if (widget->slots[i] != -1) {
                    func_0204f3c8(root, widget->slots[i], 1);
                }
            }
        }

        widget->flags.bits.flag3 = (desc->flags & 8) != 0;
        AppendIntrusiveListObject_020128d0(root->widgetList, widget);
    }
    return widget;
}
