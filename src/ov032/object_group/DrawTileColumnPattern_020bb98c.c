#include "nitro/types.h"

extern const u8 data_ov032_020bff58[][5];
extern void SetTilePixel4bpp_020bb94c(u8 *tiles, int x, u16 y, u8 color);

void DrawTileColumnPattern_020bb98c(u8 *tiles, int x, int pattern)
{
    int i;
    for (i = 0; i < 5; i++) {
        SetTilePixel4bpp_020bb94c(tiles, x, i + 2, data_ov032_020bff58[pattern][i]);
    }
}
