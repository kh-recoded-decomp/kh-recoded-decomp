#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Particle {
    u8 pad00[0x14];
    VecFx32 position;
    VecFx32 origin;
    VecFx32 velocity;
} Particle;

extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void InitDriftParticleMotion_020afa40(Particle *particle, const VecFx32 *origin, const VecFx32 *offset, const VecFx32 *velocity)
{
    particle->origin = *origin;
    VEC_Add_01ff9e0c(&particle->origin, offset, &particle->position);
    particle->velocity = *velocity;
}
