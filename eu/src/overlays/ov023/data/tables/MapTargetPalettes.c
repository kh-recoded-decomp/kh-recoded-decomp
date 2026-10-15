#include "src/overlays/ov023/MapTargetPalette.h"

#pragma explicit_zero_data on

/* Base and highlight RGB555 palettes used by the map-distance marker. */
u16 gMapTargetBasePalettes[4][4] = {
    {0x7e66, 0x69a1, 0x4d64, 0x3926},
    {0x77e3, 0x52c1, 0x3e02, 0x2144},
    {0x2387, 0x1283, 0x15c4, 0x1125},
    {0x13bf, 0x0696, 0x09d0, 0x1109},
};

u16 data_ov023_020b6efc[8] = {
    0, 1, 2, 3, 4, 5, 5, 6,
};

u16 gMapTargetHighlightPalette[4] = {
    0x14bf, 0x0437, 0x0850, 0x1089,
};
