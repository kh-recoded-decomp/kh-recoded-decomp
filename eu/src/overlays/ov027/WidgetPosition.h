#ifndef KH_RECODED_WIDGET_POSITION_H
#define KH_RECODED_WIDGET_POSITION_H

#include "../include/ov027/WidgetPoint.h"

/* Recovered prefix; the complete widget allocation extends beyond this view. */
typedef struct WidgetPositionRecord {
    unsigned char unknown00[0xc];
    int id;
    unsigned char unknown10[4];
    int recordIds[2];
    unsigned char unknown1c[0x18];
    WidgetPoint position;
    WidgetPoint offset;
} WidgetPositionRecord;

typedef char WidgetPositionRecordPrefixSizeCheck[
    sizeof(WidgetPositionRecord) == 0x44 ? 1 : -1];

typedef enum WidgetPositionMode {
    WIDGET_POSITION_COMBINED_XY,
    WIDGET_POSITION_COMBINED_X,
    WIDGET_POSITION_COMBINED_Y,
    WIDGET_POSITION_OFFSET_XY,
    WIDGET_POSITION_OFFSET_X,
    /* Getter quirk: OFFSET_Y returns in out->x; COMBINED_Y uses out->y. */
    WIDGET_POSITION_OFFSET_Y
} WidgetPositionMode;

/* This getter returns OFFSET_Y in out->x. The pending setter
 * (src/nonmatching/SetWidgetPositionComponents.c) reads both Y modes from input->y. */
WidgetPoint *ResolveWidgetPositionComponents(void *context,
                                            WidgetPositionRecord *widget,
                                            WidgetPoint *out, int mode);

#endif
