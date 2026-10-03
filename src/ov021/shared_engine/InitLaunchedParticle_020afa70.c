#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct LaunchedParticle {
    int state;
    VecFx32 position;
    VecFx32 velocity;
    VecFx32 offset;
    int timer;
    int param2c;
    VecFx32 launch;
    fx32 speed;
    int param40;
    int param44;
} LaunchedParticle;

extern const VecFx32 data_02053438;
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);

void InitLaunchedParticle_020afa70(LaunchedParticle *particle, const VecFx32 *position, const VecFx32 *launch, int param40, int param44, int param2c)
{
    VecFx32 zero;

    particle->state = 1;
    particle->position = *position;
    particle->timer = 0;
    particle->param2c = param2c;
    particle->launch = *launch;
    particle->speed = VEC_Mag_01ff9f28(launch);
    particle->param44 = param44;
    particle->param40 = param40;
    zero = data_02053438;
    particle->offset = zero;
    particle->velocity = zero;
}
