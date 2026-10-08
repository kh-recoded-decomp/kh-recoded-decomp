#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct HomingParticle {
    u16 unk_00;
    s16 progress;
    VecFx32 position;
    VecFx32 velocity;
    s32 remaining;
    u32 angle;
} HomingParticle;

extern u32 func_ov035_020bae94(void);
extern VecFx32 *func_ov001_0206dc60(int index);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(VecFx32 *in, VecFx32 *out);
extern void VEC_MultAdd(int scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

#define FX_MUL_ROUND(a, b) ((fx32)(((s64)(a) * (b) + 0x800) >> 12))

BOOL SteerHomingParticle(void *owner, HomingParticle *particle)
{
    VecFx32 steer;
    VecFx32 direction;
    VecFx32 target;
    fx32 distance;
    s32 remaining;
    BOOL done;

    if (func_ov035_020bae94()) {
        particle->remaining = 0;
        return TRUE;
    }
    target = *func_ov001_0206dc60(0);
    VEC_Subtract(&target, &particle->position, &direction);
    distance = func_01ffaff4(&direction, &direction);
    particle->progress += 0xaa;
    if (particle->progress > 0x1000) {
        particle->progress = 0x1000;
    }
    steer.x = FX_MUL_ROUND(-direction.z, 0x1000 - particle->progress);
    steer.z = FX_MUL_ROUND(direction.x, 0x1000 - particle->progress);
    steer.y = 0;
    VEC_MultAdd(particle->progress, &direction, &steer, &steer);
    distance *= 2;
    if (distance > 0x800) {
        distance = 0x800;
    }
    particle->velocity.x = FX_MUL_ROUND(steer.x, distance);
    particle->velocity.y = FX_MUL_ROUND(steer.y, distance);
    particle->velocity.z = FX_MUL_ROUND(steer.z, distance);
    VEC_Add(&particle->velocity, &particle->position, &particle->position);
    remaining = 0x1000 - particle->progress;
    particle->angle = (u16)((((remaining * 720) >> 12) << 16) / 360);
    particle->remaining = remaining;
    done = TRUE;
    if (particle->progress < 0x1000) {
        done = FALSE;
    }
    return done;
}
