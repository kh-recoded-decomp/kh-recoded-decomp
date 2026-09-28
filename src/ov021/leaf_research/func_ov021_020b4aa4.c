#include "nitro/types.h"

/* Adds an offset field and a value. */
s32 func_ov021_020b4aa4(s32 base, s32 offset)
{
    return *(s32 *)(base + 0xc) + offset;
}
