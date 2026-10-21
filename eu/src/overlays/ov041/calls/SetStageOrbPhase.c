#include "nitro/types.h"
#include "src/overlays/ov041/StageOrbs.h"

extern u32 random_next_scaled(u32 range);
extern void DirectionFromYawPitch(fx32 yaw, fx32 pitch, VecFx32 *out);
extern fx32 VEC_NormalizeLength(const VecFx32 *source, VecFx32 *dest);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);

/* Puts an orb in a phase: a burst throws it up in a random direction, homing keeps its heading at speed 0.4. */
void SetStageOrbPhase(StageOrb *orb, int phase)
{
    switch (phase) {
    case STAGE_ORB_BURST:
        DirectionFromYawPitch(random_next_scaled(0x6488), random_next_scaled(0x595) + 0x138c, &orb->velocity);
        ScaleVecFx32InPlace(&orb->velocity, 0x400);
        break;
    case STAGE_ORB_HOMING:
        VEC_NormalizeLength(&orb->velocity, &orb->velocity);
        ScaleVecFx32InPlace(&orb->velocity, 0x666);
        break;
    case STAGE_ORB_FREE:
        break;
    }
    orb->phase = phase;
}
