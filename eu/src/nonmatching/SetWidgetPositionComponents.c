/* Pending func_ov027_020b91e8; excluded from the linked build and C coverage. */
#pragma opt_propagation off
#include "nitro/types.h"
#include "src/overlays/ov027/WidgetPosition.h"

extern WidgetPoint *GetWidgetPosition(void *context, WidgetPositionRecord *widget);
extern void MI_CpuFill8(void *destination, u8 value, u32 size);
extern void MI_CpuCopy8(const void *source, void *destination, u32 size);
extern void IndexedRecord_SetPair(void *context, int record, const WidgetPoint *position);

void SetWidgetPositionComponents(void *context, WidgetPositionRecord *widget,
                                 const WidgetPoint *input, int mode)
{
    WidgetPoint position;
    WidgetPoint *base = GetWidgetPosition(context, widget);
    int slot;

    MI_CpuFill8(&position, 0, sizeof(position));
    switch (mode) {
    case WIDGET_POSITION_COMBINED_XY: {
        int x, y;
        MI_CpuCopy8(input, &position, sizeof(position));
        /* Snapshot both inputs before writing an offset that may alias them. */
        x = (s32)((u32)input->x - (u32)base->x);
        y = (s32)((u32)input->y - (u32)base->y);
        widget->offset.x = x;
        widget->offset.y = y;
        break;
    }
    case WIDGET_POSITION_COMBINED_X: {
        fx32 coordinate = input->x;
        fx32 other = widget->offset.y;
        position.x = coordinate;
        coordinate = (s32)((u32)coordinate - (u32)base->x);
        other = (s32)((u32)other + (u32)base->y);
        widget->offset.x = coordinate;
        position.y = other;
        break;
    }
    case WIDGET_POSITION_COMBINED_Y: {
        fx32 coordinate = input->y;
        fx32 other = widget->offset.x;
        position.y = coordinate;
        coordinate = (s32)((u32)coordinate - (u32)base->y);
        other = (s32)((u32)other + (u32)base->x);
        widget->offset.y = coordinate;
        position.x = other;
        break;
    }
    case WIDGET_POSITION_OFFSET_XY:
        position.x = (s32)((u32)input->x + (u32)base->x);
        position.y = (s32)((u32)input->y + (u32)base->y);
        MI_CpuCopy8(input, &widget->offset, sizeof(widget->offset));
        break;
    case WIDGET_POSITION_OFFSET_X: {
        fx32 coordinate = input->x;
        fx32 other = widget->offset.y;
        position.x = (s32)((u32)coordinate + (u32)base->x);
        fx32 baseOther = base->y;
        widget->offset.x = coordinate;
        position.y = (s32)((u32)other + (u32)baseOther);
        break;
    }
    case WIDGET_POSITION_OFFSET_Y: {
        fx32 coordinate = input->y;
        fx32 other = widget->offset.x;
        position.y = (s32)((u32)coordinate + (u32)base->y);
        fx32 baseOther = base->x;
        widget->offset.y = coordinate;
        position.x = (s32)((u32)other + (u32)baseOther);
        break;
    }
    default:
        return;
    }
    slot = 0;
    do {
        if (widget->recordIds[slot] != -1)
            IndexedRecord_SetPair(context, widget->recordIds[slot], &position);
        slot++;
    } while (slot < 2);
}
