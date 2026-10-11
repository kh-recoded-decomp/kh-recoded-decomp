#include "src/overlays/ov001/FieldUiPatterns.h"

extern void BlitNibbleRunPadded(u8 *dst, int right, int count, int width,
                               int pad, int row, const u8 *pixels);

void DrawShortLayoutRow_02073824(u8 *tiles, int right, int row)
{
    BlitNibbleRunPadded(tiles, right, 5, 110, 0, 1, gShortLayoutRowsA[row]);
}
