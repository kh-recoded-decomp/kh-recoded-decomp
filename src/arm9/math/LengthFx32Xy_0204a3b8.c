#include "nitro/types.h"
#include "nitro/fx_types.h"

extern s64 PowFx64_02049ebc(s64 value, int power);

fx32 LengthFx32Xy_0204a3b8(fx32 x, fx32 y)
{
    return (fx32)(PowFx64_02049ebc(((s64)x * x + (s64)y * y) << 12, 2) >> 12);
}
