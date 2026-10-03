#include "nitro/types.h"

extern void func_01ff869c(const void *src, void *dst, u32 size);

void CopyTileRowPair_020bf098(u16 *tilemap, const u16 *src, int row, int column)
{
    u32 size;

    tilemap += row * 32;
    size = (32 - column) * 2;
    func_01ff869c(src, tilemap + column, size);
    src += 32;
    tilemap += 32;
    func_01ff869c(src, tilemap + column, size);
}
