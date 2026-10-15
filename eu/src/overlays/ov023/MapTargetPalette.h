#ifndef EU_MAP_TARGET_PALETTE_H
#define EU_MAP_TARGET_PALETTE_H

#include "nitro/types.h"

typedef struct MapTargetPaletteState {
    u8 reserved00[0x6870];
    s32 paletteIndex;
} MapTargetPaletteState;

/* Four RGB555 colors per palette. Index zero is also the fallback palette. */
extern u16 gMapTargetBasePalettes[4][4];
extern u16 gMapTargetHighlightPalette[4];
/* This blend uploads the first four colors of the existing 24-byte work area. */
extern u16 gMapTargetPaletteWork[12];

typedef char MapTargetPaletteIndexOffsetCheck[
    (u32)&((MapTargetPaletteState *)0)->paletteIndex == 0x6870 ? 1 : -1];

#endif
