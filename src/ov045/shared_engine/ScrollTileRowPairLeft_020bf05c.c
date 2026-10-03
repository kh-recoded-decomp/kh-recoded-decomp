#include "nitro/types.h"

extern void func_01ff86d8(const void *src, void *dst, u32 size);
extern void func_01ff8684(u16 value, void *dst, u32 size);

void ScrollTileRowPairLeft_020bf05c(u16 *tilemap, int row, int shift)
{
    tilemap += row * 32;
    func_01ff86d8(tilemap + shift, tilemap, (64 - shift) * 2);
    func_01ff8684(0, tilemap + (32 - shift), shift * 2);
    func_01ff8684(0, tilemap + (64 - shift), shift * 2);
}
