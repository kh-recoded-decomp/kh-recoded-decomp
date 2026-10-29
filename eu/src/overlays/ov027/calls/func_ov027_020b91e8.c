#pragma opt_propagation off
#include "src/overlays/ov027/WidgetPosition.h"

extern void MI_CpuFill8(void *, unsigned char, unsigned int);
extern void MI_CpuCopy8(const void *, void *, unsigned int);
extern void IndexedRecord_SetPair(void *, int, const WidgetPoint *);

void func_ov027_020b91e8(void *root, const WidgetPositionRecord *widget, const WidgetPoint *point, int mode) {
    /* The read view is const for the original aliasing pattern. The widget
     * itself must occupy mutable storage: this setter writes its offset. */
    WidgetPositionRecord *target = (WidgetPositionRecord *)widget;
    const WidgetPoint *base;
    WidgetPoint position;
    int i;

    base = GetWidgetPosition(root, target);
    MI_CpuFill8(&position, 0, sizeof(position));

    switch (mode) {
    case WIDGET_POSITION_COMBINED_XY: {
        int x;
        int y;
        MI_CpuCopy8(point, &position, sizeof(position));
        x = (int)((unsigned)point->x - (unsigned)base->x);
        y = (int)((unsigned)point->y - (unsigned)base->y);
        target->offset.x = x;
        target->offset.y = y;
        break;
    }
    case WIDGET_POSITION_COMBINED_X: {
        int x, y;
        x = point->x;
        position.x = x;
        x = (int)((unsigned)x - (unsigned)base->x);
        y = (int)((unsigned)widget->offset.y + (unsigned)base->y);
        target->offset.x = x;
        position.y = y;
        break;
    }
    case WIDGET_POSITION_COMBINED_Y: {
        int x, y;
        y = point->y;
        position.y = y;
        y = (int)((unsigned)y - (unsigned)base->y);
        x = (int)((unsigned)widget->offset.x + (unsigned)base->x);
        target->offset.y = y;
        position.x = x;
        break;
    }
    case WIDGET_POSITION_OFFSET_XY:
        position.x = (int)((unsigned)point->x + (unsigned)base->x);
        position.y = (int)((unsigned)point->y + (unsigned)base->y);
        MI_CpuCopy8(point, &target->offset, sizeof(position));
        break;
    case WIDGET_POSITION_OFFSET_X: {
        int x = point->x;
        int y = widget->offset.y;
        position.x = (int)((unsigned)x + (unsigned)base->x);
        y = (int)((unsigned)y + (unsigned)base->y);
        target->offset.x = x;
        position.y = y;
        break;
    }
    case WIDGET_POSITION_OFFSET_Y: {
        int y = point->y;
        int x = widget->offset.x;
        position.y = (int)((unsigned)y + (unsigned)base->y);
        x = (int)((unsigned)x + (unsigned)base->x);
        target->offset.y = y;
        position.x = x;
        break;
    }
    default:
        return;
    }

    i = 0;
    do {
        if (widget->recordIds[i] != -1) {
            IndexedRecord_SetPair(root, widget->recordIds[i], &position);
        }
        i++;
    } while (i < 2);
}
