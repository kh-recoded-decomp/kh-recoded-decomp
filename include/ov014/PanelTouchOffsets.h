#ifndef KH_RECODED_PANEL_TOUCH_OFFSETS_H
#define KH_RECODED_PANEL_TOUCH_OFFSETS_H

#include "nitro/types.h"

typedef struct PanelTouchOffsets {
    s8 coordinates[10]; /* Five interleaved (x, y) probe offsets. */
} PanelTouchOffsets;

typedef struct PanelTouchOffsetData {
    PanelTouchOffsets samples;
    u16 reserved0a;
} PanelTouchOffsetData;

extern const PanelTouchOffsetData gPanelTouchProbeOffsets;

#endif
