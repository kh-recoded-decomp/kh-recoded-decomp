#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 func_ov001_0206db44(void);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);

/* Scales entity speed by global time factor */
void ApplyTimeScaledSpeed_020c7d28(int entity, fx32 targetSpeed)
{
    fx32 speed;

    speed = func_ov001_0206db44();
    speed = FixedPointMultiply12(*(fx32 *)(entity + 0x9f0), speed);
    speed = FixedPointMultiply12(speed, targetSpeed);
    *(fx32 *)(entity + 0x340) = speed;
    *(fx32 *)(entity + 0x9ec) = speed;
    *(fx32 *)(entity + 0x9f4) = targetSpeed;
}
