#pragma opt_propagation off
#include "nitro/types.h"

typedef struct WidgetPoint {
    int x;
    int y;
} WidgetPoint;

typedef struct Widget {
    u8 pad_00[0x14];
    int slots[2];
    u8 pad_1C[0x18];
    WidgetPoint base;
    WidgetPoint offset;
} Widget;

typedef struct WidgetRoot WidgetRoot;

extern const WidgetPoint *GetWidgetPosition_020b91a8(WidgetRoot *root, Widget *widget);
extern void MI_CpuFill8_01ff8830(void *dest, int value, u32 size);
extern void MI_CpuCopy8_01ff89a8(const void *src, void *dest, u32 size);
extern void func_0204f13c(WidgetRoot *root, int slot, WidgetPoint *position);

void SetWidgetPosition_020b91c8(WidgetRoot *root, const Widget *widget, const WidgetPoint *point, int mode) {
    Widget *target = (Widget *)widget;
    const WidgetPoint *base;
    WidgetPoint position;
    int i;

    base = GetWidgetPosition_020b91a8(root, target);
    MI_CpuFill8_01ff8830(&position, 0, sizeof(position));

    switch (mode) {
    case 0: {
        int x;
        int y;
        MI_CpuCopy8_01ff89a8(point, &position, sizeof(position));
        x = point->x - base->x;
        y = point->y - base->y;
        target->offset.x = x;
        target->offset.y = y;
        break;
    }
    case 1: {
        int x, y;
        x = point->x;
        position.x = x;
        x = x - base->x;
        y = widget->offset.y + base->y;
        target->offset.x = x;
        position.y = y;
        break;
    }
    case 2: {
        int x, y;
        y = point->y;
        position.y = y;
        y = y - base->y;
        x = widget->offset.x + base->x;
        target->offset.y = y;
        position.x = x;
        break;
    }
    case 3:
        position.x = point->x + base->x;
        position.y = point->y + base->y;
        MI_CpuCopy8_01ff89a8(point, &target->offset, sizeof(position));
        break;
    case 4: {
        int x = point->x;
        int y = widget->offset.y;
        position.x = x + base->x;
        y = y + base->y;
        target->offset.x = x;
        position.y = y;
        break;
    }
    case 5: {
        int y = point->y;
        int x = widget->offset.x;
        position.y = y + base->y;
        x = x + base->x;
        target->offset.y = y;
        position.x = x;
        break;
    }
    default:
        return;
    }

    i = 0;
    do {
        if (widget->slots[i] != -1) {
            func_0204f13c(root, widget->slots[i], &position);
        }
        i++;
    } while (i < 2);
}
