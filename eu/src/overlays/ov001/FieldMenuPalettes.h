#ifndef KH_RECODED_FIELD_MENU_PALETTES_H
#define KH_RECODED_FIELD_MENU_PALETTES_H

#include "nitro/types.h"

/* RGB555 ramps; mode selects a complete row for the VRAM transfer. */
extern u16 gFieldMenuBlueRamp[3];
extern u16 gFieldMenuRedRamp[3];
extern u16 gFieldMenuGreenRamp[3];
extern u16 gFieldMenuNormalRamps[2][3];
extern u16 gFieldMenuAlternateRamps[2][3];
extern u16 gFieldMenuModeBackgroundPalettes[3][4];
extern u16 gFieldMenuModeHighlightPalettes[3][4];

#endif
