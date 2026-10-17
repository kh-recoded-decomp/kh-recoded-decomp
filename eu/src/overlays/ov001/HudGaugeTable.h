#ifndef RECODED_EU_HUD_GAUGE_TABLE_H
#define RECODED_EU_HUD_GAUGE_TABLE_H

#include "nitro/types.h"

typedef enum HudGaugeMarkerStyle {
    HUD_GAUGE_MARKER_FILLED_PAIR = 0,
    HUD_GAUGE_MARKER_PARTIAL_PAIR = 1,
    HUD_GAUGE_MARKER_EMPTY_PAIR = 2,
    HUD_GAUGE_MARKER_FILLED_SINGLE = 3,
    HUD_GAUGE_MARKER_EMPTY_SINGLE = 4,
    HUD_GAUGE_MARKER_NONE = -1
} HudGaugeMarkerStyle;

typedef struct HudGaugeLayout {
    u32 offset;
    u32 size;
    s32 cellCount;
} HudGaugeLayout;

typedef struct HudGaugeTable {
    s32 markerStyle;
    HudGaugeLayout layouts[3];
} HudGaugeTable;

extern HudGaugeTable gHudGaugeTable;
extern u16 gFieldChoiceStringFormat[4];

#endif
