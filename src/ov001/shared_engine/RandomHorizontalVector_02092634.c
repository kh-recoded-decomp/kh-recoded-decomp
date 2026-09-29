#include "nitro/types.h"
#include "nitro/fx_types.h"

extern const s16 data_0205356c[];
extern u32 random_next_scaled_0202aa04(u32 upperBound);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);

void RandomHorizontalVector_02092634(fx32 length, VecFx32 *out)
{
    int angleIndex = (int)random_next_scaled_0202aa04(0x10000) >> 4;

    out->x = FixedPointMultiply12(data_0205356c[angleIndex], length);
    out->y = 0;
    out->z = FixedPointMultiply12(data_0205356c[(0x400 - angleIndex) & 0xfff], length);
}
