#pragma opt_propagation off

typedef struct WidgetPoint {
    int x, y;
} WidgetPoint;

typedef struct WidgetPositionRecord {
    unsigned char unknown[0x34];
    WidgetPoint position;
    WidgetPoint offset;
} WidgetPositionRecord;

typedef enum WidgetPositionMode {
    WIDGET_POSITION_COMBINED_XY,
    WIDGET_POSITION_COMBINED_X,
    WIDGET_POSITION_COMBINED_Y,
    WIDGET_POSITION_OFFSET_XY,
    WIDGET_POSITION_OFFSET_X,
    
    WIDGET_POSITION_OFFSET_Y
} WidgetPositionMode;

WidgetPoint *ResolveWidgetPositionComponents_020b9360(void *context,
                                            WidgetPositionRecord *widget,
                                            WidgetPoint *out, int mode);

extern void MI_CpuFill8_01ff8830(void *dest, unsigned char value, unsigned int size);
extern void MI_CpuCopy8_01ff89a8(const void *source, void *dest, unsigned int size);
extern WidgetPoint *GetWidgetPosition_020b91a8(void *context, WidgetPositionRecord *widget);

WidgetPoint *ResolveWidgetPositionComponents_020b9360(void *context, WidgetPositionRecord *widget,
                                           WidgetPoint *out, int mode)
{
    WidgetPoint *position;
    MI_CpuFill8_01ff8830(out, 0, sizeof(*out));
    position = GetWidgetPosition_020b91a8(context, widget);
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
        MI_CpuCopy8_01ff89a8(&widget->offset, out, sizeof(*out));
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
