#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionSphere {
    VecFx32 center;
    fx32 radius;
} CollisionSphere;

typedef struct CollisionSegment {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
} CollisionSegment;

typedef struct SphereShapeRef {
    CollisionSphere *sphere;
} SphereShapeRef;

typedef struct SegmentShapeRef {
    CollisionSegment *segment;
} SegmentShapeRef;

typedef struct CollisionHit {
    fx32 depth;
    VecFx32 normal;
    fx32 time;
    u8 kind;
} CollisionHit;

extern fx32 func_01ffaff4(VecFx32 *src, VecFx32 *dst);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern int FixedPointMultiply12(int left, int right);
extern BOOL TestSphereAgainstPoint_0203d3d0(const VecFx32 *point, const CollisionSphere *sphere, CollisionHit *hit, u32 flags);
extern int Abs_0203f228(int value);
extern VecFx32 SubtractVecFx32Into_0203f4a8(const VecFx32 *a, const VecFx32 *b);
extern fx32 FX_DivQ27_0203f4d8(fx32 numer, fx32 denom);
extern VecFx32 ScaleVecFx32_0203f4fc(const VecFx32 *v, fx32 scale);
extern BOOL IsNearZeroVec_0203f534(const VecFx32 *vec);
extern VecFx32 ComputeNormalizedCross_0203f548(const VecFx32 *v);
extern VecFx32 NormalizeVec_0203f580(const VecFx32 *src);
extern VecFx32 GetSegmentPointAtTime_0203f5ac(const CollisionHit *hit, const CollisionSegment *segment);
extern VecFx32 NormalizeVecAlt_0203f5d4(const VecFx32 *src);
extern fx32 MultiplyShiftRight27_0203f600(fx32 a, fx32 b);
extern fx32 ComputeOneMinusSquareFraction_02049d6c(fx32 value);

BOOL TestSphereAgainstSegment_0203f2e8(SphereShapeRef *sphereRef, SegmentShapeRef *segmentRef, CollisionHit *hit, u32 flags)
{
    CollisionSphere *sphere = sphereRef->sphere;
    CollisionSegment *segment = segmentRef->segment;
    VecFx32 delta = SubtractVecFx32Into_0203f4a8(&sphere->center, &segment->start);
    fx32 distance = func_01ffaff4(&delta, &delta);
    VecFx32 direction = segment->direction;
    fx32 length = segment->length;
    fx32 cosine = VEC_DotProduct_01ff9e6c(&direction, &delta);
    fx32 perpendicular;
    fx32 along;

    if (cosine <= 0) {
        if (flags & 0x10) {
            if (hit != NULL) {
                hit->time = 0;
            }
            return TestSphereAgainstPoint_0203d3d0(&segment->start, sphere, hit, !(flags & 1));
        }
        return FALSE;
    }
    perpendicular = FixedPointMultiply12(ComputeOneMinusSquareFraction_02049d6c(cosine), distance);
    if (perpendicular > sphere->radius) {
        return FALSE;
    }
    if (hit == NULL) {
        return TRUE;
    }
    hit->kind = 1;
    along = FixedPointMultiply12(cosine, distance);
    hit->time = FX_DivQ27_0203f4d8(along - FixedPointMultiply12(cosine, sphere->radius), length);
    if (hit->time < -1) {
        hit->time = -1;
    }
    if (!(flags & 1)) {
        if (along <= length) {
            hit->depth = sphere->radius - perpendicular;
            VEC_Subtract_01ff9e3c(&delta, &ScaleVecFx32_0203f4fc(&direction, cosine), &delta);
            if (IsNearZeroVec_0203f534(&delta)) {
                hit->normal = ComputeNormalizedCross_0203f548(&direction);
            } else {
                hit->normal = NormalizeVec_0203f580(&delta);
            }
            return TRUE;
        }
        return TestSphereAgainstPoint_0203d3d0(&segment->end, sphere, hit, !(flags & 1));
    } else {
        VecFx32 point = GetSegmentPointAtTime_0203f5ac(hit, segment);
        VecFx32 offset = SubtractVecFx32Into_0203f4a8(&point, &sphere->center);
        hit->normal = NormalizeVecAlt_0203f5d4(&offset);
        hit->depth = MultiplyShiftRight27_0203f600(FixedPointMultiply12(length, Abs_0203f228(VEC_DotProduct_01ff9e6c(&direction, &hit->normal))), 0x8000000 - hit->time);
        return TRUE;
    }
}
