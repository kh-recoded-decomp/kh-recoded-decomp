#include "src/overlays/ov001/FieldUiPatterns.h"

extern void BlitNibbleRunPadded(u8 *dst, int right, int count, int width,
                               int pad, int row, const u8 *pixels);

void BlitFourPixelInsetPattern(u8 *tiles, int right, s32 patternIndex)
{
    BlitNibbleRunPadded(tiles, right, 4, 48, 0, 3, gFourPixelInsetRows[patternIndex]);
}
