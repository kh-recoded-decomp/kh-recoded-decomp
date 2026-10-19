#ifndef KH_RECODED_WIDGET_POSITION_H
#define KH_RECODED_WIDGET_POSITION_H

#include "../include/ov027/WidgetPoint.h"

typedef struct WidgetPositionRecord {
    unsigned char unknown00[0xc];
    int id;
    unsigned char unknown10[0x24];
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
