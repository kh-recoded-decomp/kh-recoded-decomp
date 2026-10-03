#include "nitro/types.h"

extern u8 data_ov035_020bc414[][5];
extern void func_ov035_020bb884(void *target, void *layout, u16 column, int glyph);

void DrawMovieDigitRow_020bb8c4(void *target, void *layout, int row)
{
    int i;

    for (i = 0; i < 5; i++) {
        func_ov035_020bb884(target, layout, i + 2, data_ov035_020bc414[row][i]);
    }
}