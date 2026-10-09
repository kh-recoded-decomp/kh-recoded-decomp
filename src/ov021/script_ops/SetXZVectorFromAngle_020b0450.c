#include "nitro/fx_types.h"
#include "nitro/types.h"

extern const s16 data_0205356c[];
extern fx32 FX_Mul(fx32 left, fx32 right);

static inline void SetVector(VecFx32 *out, fx32 x, fx32 y, fx32 z)
{
    out->x = x;
    out->y = y;
    out->z = z;
}

void SetXZVectorFromAngle_020b0450(fx32 angle, fx32 length, VecFx32 *out)
{
    int index = angle >> 4;

    SetVector(out, data_0205356c[(0x400 - index) & 0xFFF], 0,
              data_0205356c[index]);
    out->x = FX_Mul(out->x, length);
    out->z = FX_Mul(out->z, length);
}
