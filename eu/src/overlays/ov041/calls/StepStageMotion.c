#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern fx32 FX_Div(fx32 numer, fx32 denom);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_NormalizeLength(const VecFx32 *source, VecFx32 *dest);
extern void VEC_MultAdd(fx32 a, const VecFx32 *v1, const VecFx32 *v2, VecFx32 *out);
extern fx32 VEC_Mag(const VecFx32 *v);

static inline void VEC_Set(VecFx32 *v, fx32 x, fx32 y, fx32 z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

#define NEAR(a, b) ((b) - 4 <= (a) && (a) <= (b) + 4)

/*
 * Moves a position step frames further along a motion (never past its end or its duration); TRUE once the
 * motion is over or the position has reached the end.
 */
BOOL StepStageMotion(VecFx32 *position, StageMotion *motion, fx32 step)
{
    VecFx32 current = *position;
    BOOL arrived = FALSE;
    VecFx32 delta;
    VecFx32 span;
    VecFx32 direction;
    VecFx32 origin;
    fx32 distance;
    fx32 travelled;

    if (motion->duration <= motion->elapsed) {
        return TRUE;
    }
    if (motion->duration < motion->elapsed + step) {
        step -= motion->elapsed + step - motion->duration;
    }
    origin.x = 0;
    origin.y = 0;
    origin.z = 0;
    distance = FX_Mul(motion->speed + FX_Mul(motion->accel, motion->elapsed + FX_Div(step, 2 * FX32_ONE)), step);
    VEC_Subtract(&motion->end, &motion->start, &span);
    VEC_NormalizeLength(&span, &direction);
    VEC_MultAdd(distance, &direction, &origin, &delta);
    VEC_Add(&current, &delta, &current);
    VEC_Subtract(&current, &motion->start, &direction);
    travelled = VEC_Mag(&direction);
    if (travelled > VEC_Mag(&span)) {
        current = motion->end;
    }
    if (NEAR(current.x, motion->end.x) && NEAR(current.y, motion->end.y) && NEAR(current.z, motion->end.z)) {
        arrived = TRUE;
    }
    VEC_Set(position, current.x, current.y, current.z);
    motion->elapsed += step;
    return arrived;
}
