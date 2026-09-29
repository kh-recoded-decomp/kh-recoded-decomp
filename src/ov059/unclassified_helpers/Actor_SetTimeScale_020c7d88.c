#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct Actor {
    u8 pad_000[0x340];
    fx32 baseTimeScale;
    u8 pad_344[0x958 - 0x344];
    fx32 timeScale;
} Actor;

extern fx32 FixedPointMultiply12(fx32 left, fx32 right);

void Actor_SetTimeScale_020c7d88(Actor *actor, fx32 scale)
{
    fx32 scaled = FixedPointMultiply12(FX32_ONE, scale);

    actor->baseTimeScale = scale;
    actor->timeScale = scaled;
}
