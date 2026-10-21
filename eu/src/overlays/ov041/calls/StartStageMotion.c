#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern fx32 FX_Div(fx32 numer, fx32 denom);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);

static inline void VEC_Set(VecFx32 *v, fx32 x, fx32 y, fx32 z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

/*
 * Starts a motion from start to end lasting duration frames: the speed profile sets the starting speed and the
 * acceleration that makes the average come out right. The position is put at the start.
 */
void StartStageMotion(VecFx32 *position, StageMotion *motion, const VecFx32 *start, const VecFx32 *end,
                         fx32 duration, int profile)
{
    fx32 average;

    motion->elapsed = 0;
    motion->duration = duration;
    motion->start = *start;
    motion->end = *end;
    average = FX_Div(VEC_Distance(&motion->start, &motion->end), motion->duration);
    switch (profile) {
    case STAGE_MOTION_EASE_IN:
        motion->speed = 0;
        break;
    case STAGE_MOTION_EASE_OUT:
        motion->speed = FX_Mul(average, 2 * FX32_ONE);
        break;
    case STAGE_MOTION_STEADY:
        motion->speed = average;
        motion->accel = 0;
        break;
    }
    motion->accel = FX_Div(FX_Mul(average - motion->speed, 2 * FX32_ONE), motion->duration);
    VEC_Set(position, motion->start.x, motion->start.y, motion->start.z);
}
