#include "nitro/types.h"

extern u8 *gMovieContextState;

u32 func_ov035_020baa38(void)
{
    return *(const u16 *)(gMovieContextState + 0x6) & 0x20;
}
