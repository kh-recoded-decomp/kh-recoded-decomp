#include "nitro/types.h"

extern void func_01ff8684(u32 fillValue, void *dest, u32 size);

void ClearTilemapRegion_0206ea94(void *dest, int column, int row, int width, int height)
{
    int i;

    if (0x20 < width + column) {
        width = 0x20 - column;
    }
    i = 0;
    if (0 < height) {
        do {
            func_01ff8684(0, (u8 *)dest + (column + (row + i) * 0x20) * 2, width << 1);
            i = i + 1;
        } while (i < height);
    }
}
