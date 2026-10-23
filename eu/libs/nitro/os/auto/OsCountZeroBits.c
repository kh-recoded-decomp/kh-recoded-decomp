#include "libs/nitro/os/os_vram_exclusive_internal.h"

u32 OsCountZeroBits(u32 bitmap)
{
    /* GCC leaves clz(0) undefined; the ARM instruction returns 32. */
    return bitmap ? __builtin_clz(bitmap) : 32;
}
