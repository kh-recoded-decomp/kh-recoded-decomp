#include "src/overlays/ov001/FieldGraphicsTables.h"

/* The level palette immediately follows the three-byte nearest colour. */
#pragma define_section glowPalette ".rodata" R
#pragma section glowPalette begin

const u8 gProximityGlowNearColor[3] = {28, 0, 0};

const FieldGlowLevelPalette gProximityGlowLevelColors = {{
    {{19, 24, 31}, {0, 13, 31}},
    {{19, 31, 31}, {0, 28, 31}},
    {{19, 31, 31}, {0, 26, 0}},
    {{31, 31, 19}, {31, 27, 0}},
}, 0};

#pragma section glowPalette end
