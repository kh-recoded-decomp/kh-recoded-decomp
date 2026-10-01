#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 start;
    VecFx32 end;
    u8 pad_18[0x10];
    fx32 scale;
} Segment;

typedef struct {
    VecFx32 low;
    VecFx32 high;
} Bounds;

extern void func_02049b6c(Segment **segmentRef, Bounds *bounds);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern fx32 ComputeOneMinusSquareFraction_02049d6c(fx32 value);
extern void func_0204a5e4(VecFx32 *vec, fx32 scale);

void ShrinkBoundsBySegmentAxis_02049c48(Segment **segmentRef, Bounds *bounds)
{
    Segment *segment = *segmentRef;
    VecFx32 extent;
    VecFx32 dir;
    VecFx32 delta;

    func_02049b6c(segmentRef, bounds);
    VEC_Subtract_01ff9e3c(&segment->end, &segment->start, &delta);
    dir = delta;
    VEC_Normalize_01ff9f88(&dir, &dir);
    extent.x = ComputeOneMinusSquareFraction_02049d6c(dir.x);
    extent.y = ComputeOneMinusSquareFraction_02049d6c(dir.y);
    extent.z = ComputeOneMinusSquareFraction_02049d6c(dir.z);
    func_0204a5e4(&extent, segment->scale);
    VEC_Add_01ff9e0c(&bounds->low, &extent, &bounds->low);
    VEC_Subtract_01ff9e3c(&bounds->high, &extent, &bounds->high);
}
