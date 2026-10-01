#include "nitro/types.h"

extern s64 MulFx32Rounded_02048b84(s32 a, s32 b);

s64 SquareFx32_02048b74(s32 value)
{
    return MulFx32Rounded_02048b84(value, value);
}
