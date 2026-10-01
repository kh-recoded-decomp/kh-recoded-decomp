#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 LengthFx32Xy_0204a3b8(fx32 x, fx32 y);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);

fx32 NormalizeXy_0204a3e4(fx32 *xy)
{
    fx32 length = LengthFx32Xy_0204a3b8(xy[0], xy[1]);

    xy[0] = FX_Div_01ff9c84(xy[0], length);
    xy[1] = FX_Div_01ff9c84(xy[1], length);
    return length;
}
