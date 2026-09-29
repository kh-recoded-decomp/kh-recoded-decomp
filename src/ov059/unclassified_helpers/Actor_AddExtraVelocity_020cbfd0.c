#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor {
    u8 pad_000[0x97c];
    VecFx32 extraVelocity;
} Actor;

extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void Actor_AddExtraVelocity_020cbfd0(Actor *actor, const VecFx32 *delta)
{
    VEC_Add_01ff9e0c(delta, &actor->extraVelocity, &actor->extraVelocity);
}
