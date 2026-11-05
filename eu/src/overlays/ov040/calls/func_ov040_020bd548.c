#include "nitro/types.h"

extern u32 gMovieContextState;
extern void BeginFieldScreenModeTransition();

u32 func_ov040_020bd548(void)
{
    u32 base;

    base = gMovieContextState;
    BeginFieldScreenModeTransition((int)*(s8 *)(gMovieContextState + 0x1c));
    *(u16 *)(base + 6) = *(u16 *)(base + 6) | 0x20;
    return 0xb;
}
