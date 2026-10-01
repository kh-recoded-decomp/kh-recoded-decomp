#include "nitro/types.h"

extern s64 PassThroughFx64_02048ba8(s64 value);

s64 MulFx32Rounded_02048b84(s32 a, s32 b)
{
    return PassThroughFx64_02048ba8(((s64)a * b + 0x800) >> 12);
}
