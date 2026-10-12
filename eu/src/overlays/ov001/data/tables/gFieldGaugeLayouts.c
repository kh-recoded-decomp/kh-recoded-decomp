#include "src/overlays/ov001/FieldUiPatterns.h"

#pragma explicit_zero_data on

extern void DrawShortLayoutRow(u8 *tiles, int right, int row);

FieldGaugeLayout gFieldGaugeLayouts[2] = {
    {0, 110, 5, 1, gWideGaugeShadeRamp, 8, DrawShortLayoutRow},
    {0, 48, 4, 3, gNarrowGaugeShadeRamp, 2, BlitFourPixelInsetPattern},
};
