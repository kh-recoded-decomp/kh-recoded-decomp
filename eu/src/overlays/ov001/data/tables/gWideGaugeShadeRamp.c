#include "src/overlays/ov001/FieldUiPatterns.h"

/* The second seven-cell ramp starts immediately after the first. */
#pragma define_section gaugeRamps ".rodata" R
#pragma section gaugeRamps begin
const u8 gWideGaugeShadeRamp[7] = {12, 12, 13, 13, 14, 14, 15};
const u8 gNarrowGaugeShadeRamp[7] = {12, 12, 13, 13, 14, 14, 15};
#pragma section gaugeRamps end
