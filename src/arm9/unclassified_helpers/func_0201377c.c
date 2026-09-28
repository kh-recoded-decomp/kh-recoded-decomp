#include "nitro/types.h"

typedef struct {
    s32 width;
    s32 height;
} Accumulator;

void func_0201377c(u32 unused, s32 startX, s32 endX, s32 height, u32 count, Accumulator *totals)
{
    if (count == 0) {
        return;
    }
    totals->width = totals->width + (endX - startX);
    totals->height = totals->height + height;
}
