#ifndef KH_RECODED_FIELD_MENU_PALETTES_H
#define KH_RECODED_FIELD_MENU_PALETTES_H

#include "nitro/types.h"

/* RGB555 ramps; the field menu's palette mode selects one for the VRAM transfer. */
typedef struct FieldMenuStateRamps {
    u16 blue[3];
    u16 red[3];
    u16 green[3];
} FieldMenuStateRamps;

extern FieldMenuStateRamps gFieldMenuStateRamps;
extern u16 gFieldMenuNormalRamps[2][3];
extern u16 gFieldMenuAlternateRamps[2][3];
extern u16 gFieldMenuModeBackgroundPalettes[3][4];
extern u16 gFieldMenuModeHighlightPalettes[3][4];

#endif
