#include "src/overlays/ov001/FieldUiPatterns.h"

extern void BlitNibbleRunPadded(u8 *dst, int right, int count, int width,
                               int pad, int row, const u8 *pixels);

void DrawShortLabel(u8 *tiles, int right, int index)
{
    BlitNibbleRunPadded(tiles, right, 7, 110, 0, 0, gShortLabelRows[index]);
}
