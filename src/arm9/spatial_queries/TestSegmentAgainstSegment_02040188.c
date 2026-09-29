#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionSegment {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
} CollisionSegment;

typedef struct SegmentShapeRef {
    CollisionSegment *segment;
} SegmentShapeRef;

typedef struct CollisionHit {
    fx32 depth;
    VecFx32 normal;
    fx32 time;
    u8 kind;
} CollisionHit;

typedef struct PenetrationResult {
    fx32 depth;
    VecFx32 axis;
    s8 axisSign;
    u8 featureId;
    u8 pad_12[2];
} PenetrationResult;

typedef struct Vec2Fx32 {
    fx32 x;
    fx32 y;
} Vec2Fx32;

extern BOOL IsSameVecFx32_0204a8f4(const VecFx32 *a, const VecFx32 *b);
extern PenetrationResult MakeEmptyPenetration_0203fb74(void);
extern VecFx32 AverageVecFx32_0204b604(s32 count, ...);
extern VecFx32 SubtractVecFx32Into_0203f4a8(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 GetHalfSegment_0203ff74(const CollisionSegment *segment);
extern VecFx32 ComputeEdgeAxis_020404a0(const VecFx32 *a, const VecFx32 *b, BOOL *parallel);
extern BOOL TestSeparatingAxis_0203fba4(fx32 extent, const VecFx32 *delta, const VecFx32 *axis, u8 featureId, PenetrationResult *result);
extern void NormalizeCrossProduct_020404c8(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);
extern VecFx32 CrossNormalized_0203fffc(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 ComputeCrossProduct_02040500(const VecFx32 *a, const VecFx32 *b);
extern Vec2Fx32 MakeVec2Fx32_02040530(fx32 x, fx32 y);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern fx32 FX_Div_01ff9c84(fx32 numerator, fx32 denominator);
extern fx32 FX_DivQ27_0203f4d8(fx32 numer, fx32 denom);
extern int FixedPointMultiply12(int left, int right);
extern int Abs_0203f228(int value);
extern void NegateVecFx32_0204aa40(VecFx32 *vec);
extern void WritePenetrationContact_0203d8fc(const PenetrationResult *result, void *contact, u32 flags);

BOOL TestSegmentAgainstSegment_02040188(SegmentShapeRef *refA, SegmentShapeRef *refB, CollisionHit *hit, u32 flags)
{
    CollisionSegment *segA = refA->segment;
    CollisionSegment *segB = refB->segment;

    if ((flags & 2) || IsSameVecFx32_0204a8f4(&segA->start, &segA->end)) {
        PenetrationResult result = MakeEmptyPenetration_0203fb74();
        VecFx32 centerA = AverageVecFx32_0204b604(2, &segA->start, &segA->end);
        VecFx32 centerB = AverageVecFx32_0204b604(2, &segB->start, &segB->end);
        VecFx32 delta = SubtractVecFx32Into_0203f4a8(&centerA, &centerB);
        VecFx32 axis;
        VecFx32 halfA = GetHalfSegment_0203ff74(segA);
        VecFx32 halfB = GetHalfSegment_0203ff74(segB);
        BOOL parallel;
        VecFx32 edgeAxis = ComputeEdgeAxis_020404a0(&halfA, &halfB, &parallel);
        VecFx32 dirs[2];
        fx32 lengths[2];
        fx32 dot;
        u8 i;

        if (!TestSeparatingAxis_0203fba4(0x80, &delta, &edgeAxis, 0, &result)) {
            return FALSE;
        }
        dirs[0] = segA->direction;
        dirs[1] = segB->direction;
        lengths[0] = segA->length;
        lengths[1] = segB->length;
        dot = VEC_DotProduct_01ff9e6c(&dirs[0], &dirs[1]);
        for (i = 0; i < 2; i++) {
            u8 other = i ^ 1;
            fx32 extent;
            axis = dirs[i];
            extent = lengths[i] + FixedPointMultiply12(lengths[other], dot);
            if (!TestSeparatingAxis_0203fba4(extent, &delta, &axis, 0, &result)) {
                return FALSE;
            }
            if (!parallel) {
                NormalizeCrossProduct_020404c8(&axis, &dirs[i], &edgeAxis);
                if (!TestSeparatingAxis_0203fba4(Abs_0203f228(FixedPointMultiply12(lengths[other], VEC_DotProduct_01ff9e6c(&axis, &dirs[other]))), &delta, &axis, 0, &result)) {
                    return FALSE;
                }
            }
        }
        WritePenetrationContact_0203d8fc(&result, hit, flags);
        return TRUE;
    }
    {
        VecFx32 dirA = segA->direction;
        VecFx32 dirB = segB->direction;
        fx32 lengthA = segA->length;
        fx32 lengthB = segB->length;
        VecFx32 normal = CrossNormalized_0203fffc(&dirA, &dirB);

        if (Abs_0203f228(VEC_DotProduct_01ff9e6c(&normal, &segA->start) - VEC_DotProduct_01ff9e6c(&normal, &segB->start)) > 0x80) {
            return FALSE;
        }
        {
            VecFx32 side = ComputeCrossProduct_02040500(&normal, &dirA);
            VecFx32 offset = SubtractVecFx32Into_0203f4a8(&segB->start, &segA->start);
            Vec2Fx32 start = MakeVec2Fx32_02040530(VEC_DotProduct_01ff9e6c(&offset, &dirA), VEC_DotProduct_01ff9e6c(&offset, &side));
            Vec2Fx32 dir = MakeVec2Fx32_02040530(VEC_DotProduct_01ff9e6c(&dirB, &dirA), VEC_DotProduct_01ff9e6c(&dirB, &side));
            fx32 t = FX_Div_01ff9c84(start.y, -dir.y);
            fx32 along;

            if (t > lengthB) {
                return FALSE;
            }
            along = start.x + FixedPointMultiply12(dir.x, t);
            if (along < 0 || along > lengthA) {
                return FALSE;
            }
            if (hit != NULL) {
                hit->depth = lengthA - along;
                hit->normal = ComputeCrossProduct_02040500(&normal, &dirB);
                if (flags & 1) {
                    NegateVecFx32_0204aa40(&hit->normal);
                }
                hit->kind = 0;
                hit->time = FX_DivQ27_0203f4d8(along, lengthA);
            }
            return TRUE;
        }
    }
}
