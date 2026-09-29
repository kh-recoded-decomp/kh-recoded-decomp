#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CollisionSegment {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
} CollisionSegment;

extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 NormalizeVecGetLength_01ffaff4(VecFx32 *src, VecFx32 *dst);

void InitSegmentFromEndpoints_0203b1f0(CollisionSegment *segment)
{
    VecFx32 delta;

    VEC_Subtract_01ff9e3c(&segment->end, &segment->start, &delta);
    segment->direction = delta;
    segment->length = NormalizeVecGetLength_01ffaff4(&segment->direction, &segment->direction);
    if (segment->length == 0) {
        VecFx32 down;
        down.x = 0;
        down.y = -FX32_ONE;
        down.z = 0;
        segment->direction = down;
    }
}
