#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor {
    u8 pad_000[0x840];
    VecFx32 position;
    u8 pad_84c[0xef4 - 0x84c];
    u32 flags;
} Actor;

extern void ScaleVecFx32_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *vec);

BOOL Actor_IsNearProjectedPoint_02089a4c(Actor *actor, const VecFx32 *origin, const VecFx32 *direction, fx32 distance)
{
    VecFx32 point;
    VecFx32 delta;

    ScaleVecFx32_01ffafb4(distance, direction, &delta);
    VEC_Add_01ff9e0c(origin, &delta, &point);
    VEC_Subtract_01ff9e3c(&actor->position, &point, &delta);
    if (actor->flags & 0x10) {
        delta.y = 0;
    }
    if (VEC_Mag_01ff9f28(&delta) < 0x19a) {
        return TRUE;
    }
    return FALSE;
}
