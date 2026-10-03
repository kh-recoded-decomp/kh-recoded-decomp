#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Vec2Fx32 {
    fx32 x;
    fx32 y;
} Vec2Fx32;

extern fx32 FX_Sqrt_01ff9cfc(fx32 value);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);

void NormalizeVec2Fx32_0204a4a8(Vec2Fx32 *out, const Vec2Fx32 *vec, fx32 *outLength)
{
    Vec2Fx32 result;
    fx32 x;
    fx32 y;

    *outLength = FX_Sqrt_01ff9cfc((fx32)(((fx64)vec->x * vec->x + (fx64)vec->y * vec->y) >> 12));
    y = FX_Div_01ff9c84(vec->y, *outLength);
    x = FX_Div_01ff9c84(vec->x, *outLength);
    result.x = x;
    result.y = y;
    *out = result;
}
