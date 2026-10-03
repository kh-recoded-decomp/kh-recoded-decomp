#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor {
    u8 pad_000[0x234];
    u32 flags;
    u8 pad_238[0x94c - 0x238];
    VecFx32 knockback;
} Actor;

extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void VEC_Normalize_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void ScaleVecFx32_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);

void Actor_ConsumeKnockback_020c7da8(Actor *actor, VecFx32 *out) {
    VecFx32 push;
    fx32 height;

    if (VEC_Mag_01ff9f28(&actor->knockback) <= 0x200) {
        actor->knockback.z = 0;
        actor->knockback.y = 0;
        actor->knockback.x = 0;
        out->z = 0;
        out->y = 0;
        out->x = 0;
        return;
    }
    push = actor->knockback;
    height = push.y;
    push.y = 0;
    if (VEC_Mag_01ff9f28(&push) > 0x900) {
        VEC_Normalize_01ff9f88(&push, &push);
        ScaleVecFx32_01ffafb4(0x900, &push, &push);
    }
    if (actor->flags & 2) {
        ScaleVecFx32_01ffafb4(0x333, &push, &push);
        ScaleVecFx32_01ffafb4(0x333, &actor->knockback, &actor->knockback);
    }
    push.y = height;
    *out = push;
    actor->knockback.y = 0;
    ScaleVecFx32_01ffafb4(0xc80, &actor->knockback, &actor->knockback);
}
