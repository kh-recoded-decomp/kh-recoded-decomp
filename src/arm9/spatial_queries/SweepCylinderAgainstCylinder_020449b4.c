#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionCylinder {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
    fx32 radius;
} CollisionCylinder;

typedef struct CylinderShapeRef {
    CollisionCylinder *cylinder;
    u8 pad_04[0x18];
    s32 kind;
} CylinderShapeRef;

typedef struct SweepResult {
    u32 enterTimeLo;
    s32 enterTimeHi;
    u32 exitTimeLo;
    s32 exitTimeHi;
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

typedef struct CollisionDisc {
    VecFx32 center;
    fx32 radius;
    VecFx32 normal;
} CollisionDisc;

typedef struct Vec2Fx32 {
    fx32 x;
    fx32 y;
} Vec2Fx32;

extern const VecFx32 data_02053438;
extern fx32 FX_Div_01ff9c84(fx32 numerator, fx32 denominator);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void VEC_NormalizeUnchecked_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void InitHitQuery_0203ac24(SweepResult *result);
extern fx32 ComputeDirectionalExtent_0203d718(const CollisionCylinder *cylinder, const VecFx32 *dirA, s32 majorExtent, const VecFx32 *dirB);
extern fx32 func_02047184(const VecFx32 *center, const VecFx32 *dir, const VecFx32 *endpoint, fx32 rimRadius, fx32 sphereRadius, const VecFx32 *axis, fx32 *roots, VecFx32 *normal);
extern BOOL SweepIntervalOnAxis_0204774c(fx32 extent, fx32 distance, const VecFx32 *axis, u8 feature, const VecFx32 *velocity, SweepResult *result, s64 *outTime);
extern BOOL ResolveSweepContact_0204792c(SweepResult *result, void *contact, u32 flags, const VecFx32 *velocity);
extern fx32 SweepCapsuleAgainstCapsule_02048f8c(const VecFx32 *dir, const CollisionDisc *discA, const CollisionDisc *discB, fx32 *roots, VecFx32 *normal);
extern fx32 ComputeOneMinusSquareFraction_02049d6c(fx32 value);
extern void Vec2Add_0204a2e0(const Vec2Fx32 *a, const Vec2Fx32 *b, Vec2Fx32 *out);
extern void ScalePairInPlace_0204a350(Vec2Fx32 *pair, fx32 scale);
extern fx32 DotFx32Xy_0204a390(const Vec2Fx32 *a, const Vec2Fx32 *b);
extern fx32 NormalizeXy_0204a3e4(Vec2Fx32 *pair);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern BOOL AreVecsWithinRange16_0204a8f4(const VecFx32 *a, const VecFx32 *b);
extern fx32 AbsDotProduct_0204a96c(const VecFx32 *a, const VecFx32 *b);
extern void NegateVecFx32_0204aa40(VecFx32 *vec);
extern void GetUnitCross_0204aa68(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);
extern void GetUnitRejectionFromAxis_0204aea8(VecFx32 *out, const VecFx32 *v, const VecFx32 *normal);
extern fx32 BlendVectorsBySqrtComplement_0204b59c(VecFx32 *a, const VecFx32 *b, fx32 t, s32 factor, VecFx32 *out);
extern VecFx32 AverageVecs_0204b604(s32 count, ...);

static inline SweepResult MakeSweepResult(void)
{
    SweepResult result;
    InitHitQuery_0203ac24(&result);
    return result;
}

static inline VecFx32 VecSub(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 diff;
    VEC_Subtract_01ff9e3c(a, b, &diff);
    return diff;
}

static inline VecFx32 VecSubValue(const VecFx32 *a, VecFx32 b)
{
    VecFx32 diff;
    VEC_Subtract_01ff9e3c(a, &b, &diff);
    return diff;
}

static inline VecFx32 VecAdd(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 sum;
    VEC_Add_01ff9e0c(a, b, &sum);
    return sum;
}

static inline VecFx32 HalfSegment(const CollisionCylinder *cylinder)
{
    VecFx32 half;
    VecFx32 span;

    VEC_Subtract_01ff9e3c(&cylinder->end, &cylinder->start, &span);
    half = span;
    half.x >>= 1;
    half.y >>= 1;
    half.z >>= 1;
    return half;
}

static inline VecFx32 Cross(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 cross;
    VEC_CrossProduct_01ff9ea8(a, b, &cross);
    return cross;
}

static inline VecFx32 Normalized(const VecFx32 *v)
{
    VecFx32 unit;
    VEC_NormalizeUnchecked_01ff9f88(v, &unit);
    return unit;
}

static inline VecFx32 Negated(VecFx32 v)
{
    NegateVecFx32_0204aa40(&v);
    return v;
}

static inline VecFx32 Scaled(VecFx32 v, fx32 scale)
{
    ScaleVecFx32InPlace_0204a5e4(&v, scale);
    return v;
}

static inline VecFx32 RejectFromAxis(const VecFx32 *v, const VecFx32 *axis, fx32 dot)
{
    VecFx32 projection;
    VecFx32 scaledAxis;
    VecFx32 rejection;

    scaledAxis = *axis;
    ScaleVecFx32InPlace_0204a5e4(&scaledAxis, dot);
    projection = scaledAxis;
    VEC_Subtract_01ff9e3c(v, &projection, &rejection);
    return rejection;
}

static inline VecFx32 NormalizedCross(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 cross;
    VecFx32 product;
    VecFx32 unit;

    VEC_CrossProduct_01ff9ea8(a, b, &product);
    cross = product;
    VEC_NormalizeUnchecked_01ff9f88(&cross, &unit);
    return unit;
}

static inline VecFx32 MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add)
{
    VecFx32 out;
    VEC_MultAdd_01ffa09c(scale, v, add, &out);
    return out;
}

static inline VecFx32 PerpAxis(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 perp;
    GetUnitCross_0204aa68(&perp, a, b);
    return perp;
}

static inline Vec2Fx32 ScalePair(Vec2Fx32 pair, fx32 scale)
{
    ScalePairInPlace_0204a350(&pair, scale);
    return pair;
}

static inline Vec2Fx32 AddPair(const Vec2Fx32 *a, const Vec2Fx32 *b)
{
    Vec2Fx32 sum;
    Vec2Add_0204a2e0(a, b, &sum);
    return sum;
}

static inline s32 Sign(fx32 value)
{
    return value == 0 ? 0 : (value > 0 ? 1 : -1);
}

static inline fx32 FxMul(fx32 a, fx32 b)
{
    return (fx32)(((s64)a * b + 0x800) >> 12);
}

BOOL SweepCylinderAgainstCylinder_020449b4(CylinderShapeRef *refA, CylinderShapeRef *refB, void *contact, u32 flags, const VecFx32 *velocity)
{
    fx32 dist;
    CollisionCylinder *cylA = refA->cylinder;
    CollisionCylinder *cylB = refB->cylinder;
    s32 isCapsule = refA->kind != 3 ? FALSE : TRUE;
    SweepResult result = MakeSweepResult();
    VecFx32 axis;
    VecFx32 centerA = AverageVecs_0204b604(2, &cylA->start, &cylA->end);
    VecFx32 centerB = AverageVecs_0204b604(2, &cylB->start, &cylB->end);
    fx32 radiusSum = cylA->radius + cylB->radius;
    VecFx32 delta = VecSub(&centerA, &centerB);
    s32 extent;
    VecFx32 halfA = HalfSegment(cylA);
    VecFx32 halfB = HalfSegment(cylB);
    fx32 halfLengthB;
    VecFx32 cross = Cross(&halfA, &halfB);
    VecFx32 axisA;
    u8 i;
    u8 j;
    VecFx32 axisB;
    s32 parallel = AreVecsWithinRange16_0204a8f4(&cross, &data_02053438);
    VecFx32 dir;
    fx32 halfLengthA;

    if (parallel) {
        GetUnitRejectionFromAxis_0204aea8(&axis, &delta, &Normalized(&halfA));
        VEC_NormalizeUnchecked_01ff9f88(&axis, &axis);
    } else {
        VEC_NormalizeUnchecked_01ff9f88(&cross, &axis);
    }
    if (!SweepIntervalOnAxis_0204774c(radiusSum, VEC_DotProduct_01ff9e6c(&axis, &delta), &axis, 0, velocity, &result, NULL)) {
        return FALSE;
    }

    axisA = cylA->direction;
    axisB = cylB->direction;
    halfLengthA = cylA->length / 2;
    halfLengthB = cylB->length / 2;
    dir = Normalized(velocity);

    if (!parallel) {
        const VecFx32 *axes[2];
        const VecFx32 *halves[2];

        halves[0] = &halfA;
        axes[0] = &axisA;
        halves[1] = &halfB;
        axes[1] = &axisB;
        for (i = 0; i < 2; i++) {
            u8 other = i ^ 1;
            const VecFx32 *axisI = axes[i];
            VecFx32 side = Cross(axisI, &dir);

            if (AreVecsWithinRange16_0204a8f4(&side, &data_02053438)) {
                const VecFx32 *otherHalf = halves[other];
                const VecFx32 *nearEnd = &VecAdd(&delta, &Negated(*otherHalf));
                VecFx32 rejA = RejectFromAxis(nearEnd, axisI, VEC_DotProduct_01ff9e6c(nearEnd, axisI));
                const VecFx32 *farEnd = &VecAdd(&delta, otherHalf);
                VecFx32 rejB = RejectFromAxis(farEnd, axisI, VEC_DotProduct_01ff9e6c(farEnd, axisI));

                if (VEC_Mag_01ff9f28(&rejA) < VEC_Mag_01ff9f28(&rejB)) {
                    axis = Normalized(&rejA);
                } else {
                    axis = Normalized(&rejB);
                }
            } else {
                const VecFx32 *unitSide = &Normalized(&side);
                VecFx32 normal = *unitSide;
                VecFx32 perp = Cross(&normal, axisI);
                dist = VEC_DotProduct_01ff9e6c(&normal, &delta);
                fx32 projection = AbsDotProduct_0204a96c(halves[other], &normal);
                fx32 gap = (dist < 0 ? -dist : dist) - projection;

                if (gap < 0) {
                    gap = 0;
                } else if (gap > radiusSum) {
                    gap = radiusSum;
                }
                if (isCapsule && i == 1) {
                    BlendVectorsBySqrtComplement_0204b59c(&normal, &perp, FX_Div_01ff9c84(gap * -Sign(dist), radiusSum), 1, &axis);
                } else {
                    fx32 cosine = VEC_DotProduct_01ff9e6c(&axisB, axisI);
                    VecFx32 rej = RejectFromAxis(&axisB, axisI, cosine);
                    Vec2Fx32 coords;
                    VecFx32 inPlane = cosine < 0xff0 ? Normalized(&rej) : *unitSide;
                    Vec2Fx32 sinCos;
                    Vec2Fx32 perpCoords;
                    fx32 perpDot;
                    Vec2Fx32 blended;
                    fx32 ratio;
                    fx32 stretch;
                    Vec2Fx32 alongCoords;
                    Vec2Fx32 alongPerp;
                    perpDot = VEC_DotProduct_01ff9e6c(&perp, &inPlane);
                    fx32 normalDot;
                    fx32 scaledGap;

                    Vec2Fx32 planeCoords;
                    normalDot = VEC_DotProduct_01ff9e6c(&normal, &inPlane);
                    coords.x = normalDot;
                    coords.y = perpDot;
                    planeCoords = coords;
                    if (cosine < 0) {
                        cosine = -cosine;
                    }
                    ratio = FX_Div_01ff9c84(cylA->radius + FxMul(cylB->radius, cosine), radiusSum);
                    stretch = ratio > 0x10 ? FxMul(coords.x < 0 ? -coords.x : coords.x, FX_Div_01ff9c84(0x1000, ratio) - 0x1000) : 0;
                    scaledGap = gap + FxMul(gap, stretch);
                    if (scaledGap > radiusSum) {
                        scaledGap = radiusSum;
                    }
                    sinCos.x = FX_Div_01ff9c84(scaledGap * -Sign(dist), radiusSum);
                    sinCos.y = ComputeOneMinusSquareFraction_02049d6c(sinCos.x);
                    perpCoords.y = planeCoords.x * 0xFFFFFFFF;
                    perpCoords.x = planeCoords.y;
                    blended = AddPair((alongCoords = ScalePair(planeCoords, DotFx32Xy_0204a390(&sinCos, &coords)), &alongCoords), (alongPerp = ScalePair(perpCoords, FxMul(DotFx32Xy_0204a390(&sinCos, &perpCoords), ratio)), &alongPerp));
                    NormalizeXy_0204a3e4(&blended);
                    axis = Scaled(*unitSide, blended.x * (VEC_DotProduct_01ff9e6c(&perp, &delta) >= 0 ? -1 : 1));
                    axis = MultAdd(blended.y, &perp, &axis);
                }
            }
            if (isCapsule) {
                extent = cylA->radius + AbsDotProduct_0204a96c(&halfA, &axis);
            } else {
                extent = ComputeDirectionalExtent_0203d718(cylA, &axisA, halfLengthA * 2, &axis);
            }
            extent += ComputeDirectionalExtent_0203d718(cylB, &axisB, halfLengthB * 2, &axis);
            if (!SweepIntervalOnAxis_0204774c(extent, VEC_DotProduct_01ff9e6c(&axis, &delta), &axis, 3, velocity, &result, NULL)) {
                return FALSE;
            }
        }
    }

    for (i = 0; i < 2; i++) {
        axis = (i == 0) ? axisB : axisA;
        if (isCapsule) {
            extent = cylA->radius + AbsDotProduct_0204a96c(&halfA, &axis);
        } else if (i == 0) {
            extent = ComputeDirectionalExtent_0203d718(cylA, &axisA, halfLengthA * 2, &axis);
        } else {
            extent = halfLengthA;
        }
        if (i == 1) {
            extent += ComputeDirectionalExtent_0203d718(cylB, &axisB, 2 * halfLengthB, &axis);
        } else {
            extent += halfLengthB;
        }
        if (!SweepIntervalOnAxis_0204774c(extent, VEC_DotProduct_01ff9e6c(&axis, &delta), &axis, 0, velocity, &result, NULL)) {
            return FALSE;
        }
        if (isCapsule) {
            break;
        }
    }

    if (isCapsule || !parallel) {
        CollisionDisc discA;
        CollisionDisc discB;
        VecFx32 endA;
        VecFx32 endB;
        fx32 roots[12];
        VecFx32 hitNormal;

        if (!isCapsule) {
            discA.radius = cylA->radius;
            discB.radius = cylB->radius;
            discA.normal = axisA;
            discB.normal = axisB;
        }
        for (i = 0; i < 2; i++) {
            VecFx32 pointA = (i == 0) ? cylA->start : cylA->end;

            endA = pointA;
            for (j = 0; j < 2; j++) {
                VecFx32 pointB = (j == 0) ? cylB->start : cylB->end;
                endB = pointB;

                fx32 root;
                if (isCapsule) {
                    root = func_02047184(&endA, &dir, &endB, cylB->radius, cylA->radius, &axisB, roots, &hitNormal);
                } else {
                    discA.center = pointA;
                    discB.center = pointB;
                    root = SweepCapsuleAgainstCapsule_02048f8c(&dir, &discA, &discB, roots, &hitNormal);
                }
                if (root != 0x7fffffff) {
                    axis = hitNormal;
                } else {
                    axis = PerpAxis(&dir, &axisB);
                    axis = NormalizedCross(&axis, &dir);
                }
                if (isCapsule) {
                    extent = cylA->radius + AbsDotProduct_0204a96c(&halfA, &axis);
                } else {
                    extent = ComputeDirectionalExtent_0203d718(cylA, &axisA, halfLengthA * 2, &axis);
                }
                extent += ComputeDirectionalExtent_0203d718(cylB, &axisB, halfLengthB * 2, &axis);
                if (!SweepIntervalOnAxis_0204774c(extent, VEC_DotProduct_01ff9e6c(&axis, &delta), &axis, 3, velocity, &result, NULL)) {
                    return FALSE;
                }
            }
        }
    }
    return ResolveSweepContact_0204792c(&result, contact, flags, velocity);
}
