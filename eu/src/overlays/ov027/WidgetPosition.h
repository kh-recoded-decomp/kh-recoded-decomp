#ifndef KH_RECODED_WIDGET_POSITION_H
#define KH_RECODED_WIDGET_POSITION_H

/* Coordinates use 12 fractional bits. */
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
    /* Scalar modes return their component in out->x, including OFFSET_Y. */
    WIDGET_POSITION_OFFSET_Y
} WidgetPositionMode;

WidgetPoint *ResolveWidgetPositionComponents(void *context,
                                            WidgetPositionRecord *widget,
                                            WidgetPoint *out, int mode);

#endif
