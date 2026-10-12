#ifndef RECODED_EU_HUD_GAUGE_TABLE_H
#define RECODED_EU_HUD_GAUGE_TABLE_H

#include "nitro/types.h"

typedef struct HudGaugeLayout {
    u32 offset;
    u32 size;
    s32 cellCount;
} HudGaugeLayout;

typedef struct HudGaugeTable {
    s32 header;
    HudGaugeLayout layouts[3];
} HudGaugeTable;

extern HudGaugeTable gHudGaugeTable;
extern u16 gFieldChoiceStringFormat[4];

#endif
