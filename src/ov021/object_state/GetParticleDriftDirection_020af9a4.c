#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Particle {
    u8 pad00[0x14];
    VecFx32 position;
    VecFx32 origin;
} Particle;

extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);

void GetParticleDriftDirection_020af9a4(Particle *particle, VecFx32 *direction)
{
    VecFx32 normalized;
    VecFx32 offset;
    VecFx32 input;

    VEC_Subtract_01ff9e3c(&particle->position, &particle->origin, &offset);
    input = offset;
    func_01ff9f88(&input, &normalized);
    *direction = normalized;
}
