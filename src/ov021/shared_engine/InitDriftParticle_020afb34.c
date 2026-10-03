#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct DriftParticle {
    int state;
    VecFx32 position;
    VecFx32 velocity;
    u8 pad1c[0xc];
    int timer;
    int param2c;
    int param30;
    u8 pad34[0xc];
    VecFx32 offset;
    int pad4c;
    u32 phase;
} DriftParticle;

extern const VecFx32 data_02053438;
extern u32 random_next_scaled_0202aa04(u32 range);
extern void func_ov021_020afadc(DriftParticle *particle);

void InitDriftParticle_020afb34(DriftParticle *particle, const VecFx32 *position, int param30, int param2c)
{
    VecFx32 zero;

    particle->state = 2;
    particle->position = *position;
    particle->timer = 0;
    particle->param2c = param2c;
    particle->param30 = param30;
    particle->phase = random_next_scaled_0202aa04(0x6488);
    zero = data_02053438;
    particle->offset = zero;
    func_ov021_020afadc(particle);
    particle->velocity = zero;
}
