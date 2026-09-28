#include "nitro/fx_types.h"

typedef struct {
    fx32 x;
    fx32 y;
} VecFx32_2D;

extern fx32 FX_Div_01ff9c84(fx32 a, fx32 b);
extern fx32 func_0204a3b8(fx32 x, fx32 y);

BOOL NormalizeVec2Fx_0204a460(VecFx32_2D *v, VecFx32_2D *out)
{
    fx32 length = func_0204a3b8(v->x, v->y);

    if (length != 0) {
        out->x = FX_Div_01ff9c84(v->x, length);
        out->y = FX_Div_01ff9c84(v->y, length);
        return FALSE;
    }
    return TRUE;
}
