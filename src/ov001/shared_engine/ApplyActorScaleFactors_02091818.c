#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 func_ov001_0209c3cc(void);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);

void ApplyActorScaleFactors_02091818(u8 *actor)
{
    fx32 value;

    value = func_ov001_0209c3cc();
    value = FixedPointMultiply12(value, *(fx32 *)(actor + 0x39c));
    FixedPointMultiply12(value, *(fx32 *)(actor + 0x3a0));
}
