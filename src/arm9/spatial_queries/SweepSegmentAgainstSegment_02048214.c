#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionSegment {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
} CollisionSegment;

typedef struct SweepResult {
    s64 enterTime;
    s64 exitTime;
    VecFx32 enterAxis;
    fx32 minDepth;
    VecFx32 depthAxis;
    s8 depthSign;
    u8 depthFeature;
    u8 pad_2E[2];
    s8 enterSign;
    u8 touching;
    u8 enterFeature;
    u8 pad_33;
} SweepResult;

extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern void GetSegmentHalfDelta_0203ff74(VecFx32 *out, const CollisionSegment *segment);
extern void NormalizeCrossProduct_020404c8(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);
extern BOOL ResolveSweepContact_0204792c(SweepResult *result, void *contact, u32 flags, const VecFx32 *velocity);
extern void func_02047cec(SweepResult *out);
extern void SubtractVecFx32Out_02047d2c(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);
extern BOOL func_02047d5c(fx32 extent, const VecFx32 *offset, const VecFx32 *axis, u8 feature, const VecFx32 *velocity, SweepResult *result, s64 *outTime);
extern fx32 func_02047dac(fx32 value);
extern void func_020483e4(VecFx32 *out, const VecFx32 *halfA, const VecFx32 *halfB, BOOL *parallel);
extern void AverageVecs_0204b604(VecFx32 *out, int count, ...);

static inline SweepResult MakeSweepResult(void)
{
    SweepResult result;
    func_02047cec(&result);
    return result;
}

static inline VecFx32 Midpoint(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 average;
    AverageVecs_0204b604(&average, 2, a, b);
    return average;
}

static inline VecFx32 VecSub(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 diff;
    SubtractVecFx32Out_02047d2c(&diff, a, b);
    return diff;
}

static inline VecFx32 HalfDelta(const CollisionSegment *segment)
{
    VecFx32 half;
    GetSegmentHalfDelta_0203ff74(&half, segment);
    return half;
}

BOOL SweepSegmentAgainstSegment_02048214(CollisionSegment **refA, CollisionSegment **refB, void *contact, u32 flags, const VecFx32 *velocity)
{
    CollisionSegment *segA = *refA;
    CollisionSegment *segB = *refB;
    SweepResult result;
    VecFx32 axis;
    VecFx32 centerA;
    VecFx32 centerB;
    VecFx32 delta;
    VecFx32 halfA;
    VecFx32 halfB;
    VecFx32 crossAxis;
    VecFx32 dirs[2];
    BOOL parallel;
    fx32 lengths[2];
    fx32 dot;
    fx32 extent;
    u8 i;
    u8 other;

    result = MakeSweepResult();
    centerA = Midpoint(&segA->start, &segA->end);
    centerB = Midpoint(&segB->start, &segB->end);
    delta = VecSub(&centerA, &centerB);
    halfA = HalfDelta(segA);
    halfB = HalfDelta(segB);
    func_020483e4(&axis, &halfA, &halfB, &parallel);
    crossAxis = axis;
    if (!func_02047d5c(0x80, &delta, &axis, 0, velocity, &result, NULL)) {
        return FALSE;
    }
    dirs[0] = segA->direction;
    dirs[1] = segB->direction;
    lengths[0] = segA->length;
    lengths[1] = segB->length;
    dot = VEC_DotProduct_01ff9e6c(&dirs[0], &dirs[1]);
    for (i = 0; i < 2; i++) {
        other = i ^ 1;
        axis = dirs[i];
        extent = lengths[i] + FixedPointMultiply12(lengths[other], dot);
        if (!func_02047d5c(extent + 0x80, &delta, &axis, 0, velocity, &result, NULL)) {
            return FALSE;
        }
        if (!parallel) {
            NormalizeCrossProduct_020404c8(&axis, &dirs[i], &crossAxis);
            if (!func_02047d5c(func_02047dac(FixedPointMultiply12(lengths[other], VEC_DotProduct_01ff9e6c(&axis, &dirs[other]))) + 0x80, &delta, &axis, 0, velocity, &result, NULL)) {
                return FALSE;
            }
        }
    }
    return ResolveSweepContact_0204792c(&result, contact, flags, velocity);
}
