#pragma opt_propagation off

#include "src/overlays/ov027/WidgetPosition.h"

extern void MI_CpuFill8(void *dest, unsigned char value, unsigned int size);
extern void MI_CpuCopy8(const void *source, void *dest, unsigned int size);
extern WidgetPoint *GetWidgetPosition(void *context, WidgetPositionRecord *widget);

WidgetPoint *ResolveWidgetPositionComponents(void *context, WidgetPositionRecord *widget,
                                           WidgetPoint *out, int mode)
{
    WidgetPoint *position;
    MI_CpuFill8(out, 0, sizeof(*out));
    position = GetWidgetPosition(context, widget);
    switch (mode) {
    case 0: {
        int baseX = position->x;
        int x = baseX + widget->offset.x;
        int y = widget->offset.y;
        out->x = x;
        out->y = position->y + y;
        break;
    }
    case 1:
        out->x = position->x + widget->offset.x;
        break;
    case 2:
        out->y = position->y + widget->offset.y;
        break;
    case 3:
        MI_CpuCopy8(&widget->offset, out, sizeof(*out));
        break;
    case 4:
        out->x = widget->offset.x;
        break;
    case 5:
        out->x = widget->offset.y;
        break;
    }
    return out;
}
