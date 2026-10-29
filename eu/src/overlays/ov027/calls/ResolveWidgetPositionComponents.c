#pragma opt_propagation off

#include "src/overlays/ov027/WidgetPosition.h"

extern void MI_CpuFill8(void *dest, unsigned char value, unsigned int size);
extern void MI_CpuCopy8(const void *source, void *dest, unsigned int size);

WidgetPoint *ResolveWidgetPositionComponents(void *context, WidgetPositionRecord *widget,
                                           WidgetPoint *out, int mode)
{
    WidgetPoint *position;
    MI_CpuFill8(out, 0, sizeof(*out));
    position = GetWidgetPosition(context, widget);
    switch (mode) {
    case WIDGET_POSITION_COMBINED_XY: {
        int baseX = position->x;
        int x = (int)((unsigned)baseX + (unsigned)widget->offset.x);
        int y = widget->offset.y;
        out->x = x;
        out->y = (int)((unsigned)position->y + (unsigned)y);
        break;
    }
    case WIDGET_POSITION_COMBINED_X:
        out->x = (int)((unsigned)position->x + (unsigned)widget->offset.x);
        break;
    case WIDGET_POSITION_COMBINED_Y:
        out->y = (int)((unsigned)position->y + (unsigned)widget->offset.y);
        break;
    case WIDGET_POSITION_OFFSET_XY:
        MI_CpuCopy8(&widget->offset, out, sizeof(*out));
        break;
    case WIDGET_POSITION_OFFSET_X:
        out->x = widget->offset.x;
        break;
    case WIDGET_POSITION_OFFSET_Y:
        out->x = widget->offset.y;
        break;
    }
    return out;
}
