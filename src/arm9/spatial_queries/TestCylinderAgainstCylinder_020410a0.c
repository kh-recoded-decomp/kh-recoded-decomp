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

typedef struct PenetrationResult {
    fx32 depth;
    VecFx32 axis;
    s8 axisSign;
    u8 featureId;
    u8 pad_12[2];
} PenetrationResult;

typedef struct Basis3x3 {
    VecFx32 row[3];
} Basis3x3;

extern PenetrationResult InitPenetrationResult_0203fb74(void);
extern VecFx32 AverageVecFx32_0204b604(s32 count, ...);
extern VecFx32 SubtractVecFx32Into_0203f4a8(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 GetHalfSegment_02041670(const CollisionCylinder *cylinder);
extern VecFx32 GetHalfSegmentAlt_02040fdc(const CollisionCylinder *cylinder);
extern VecFx32 ComputeCrossProduct_02040500(const VecFx32 *a, const VecFx32 *b);
extern BOOL IsNearlyZeroVec_0203f534(const VecFx32 *vec);
extern VecFx32 NormalizeVectorInto_0203f580(const VecFx32 *vec);
extern VecFx32 ComputeVectorRejection_02040aec(const VecFx32 *v, const VecFx32 *axis);
extern VecFx32 GetPerpendicularVec_0204ad4c(const VecFx32 *vec);
extern void VEC_Normalize_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern BOOL TestSeparatingAxis_0203fba4(fx32 extent, const VecFx32 *delta, const VecFx32 *axis, u8 featureId, PenetrationResult *result);
extern VecFx32 NegateVecFx32Into_0203f9b0(const VecFx32 *vec);
extern VecFx32 AddVecFx32Into_0203f980(const VecFx32 *a, const VecFx32 *b);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *vec);
extern VecFx32 NormalizeVecFx32Out_020416f8(const VecFx32 *vec);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern int FixedPointMultiply12(int left, int right);
extern VecFx32 ScaleVecFx32_0203f4fc(const VecFx32 *vec, fx32 scale);
extern VecFx32 MultAddVecFx32Out_02040c58(fx32 scale, const VecFx32 *vec, const VecFx32 *add);
extern int NormalizeVecFx32InPlace_0204a9b4(VecFx32 *vec);
extern fx32 AbsDotProduct_0204a96c(const VecFx32 *a, const VecFx32 *b);
extern fx32 ComputeDirectionalExtent_0203d718(const CollisionCylinder *cylinder, const VecFx32 *dirA, s32 majorExtent, const VecFx32 *dirB);
extern VecFx32 func_0204aea8(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 NormalizeVectorAltInto_0203f5d4(const VecFx32 *vec);
extern VecFx32 CrossNormalized_0203fffc(const VecFx32 *a, const VecFx32 *b);
extern Basis3x3 BuildBasisFromAxes_02041728(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 TransformVectorByBasisOut_02041768(const VecFx32 *vec, const Basis3x3 *basis);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern int Abs_0203f228(int value);
extern s32 Min_0203f9e0(s32 a, s32 b);
extern int Sign_0203f240(fx32 value);
extern fx32 Square_0203f268(fx32 value);
extern fx32 FX_Sqrt_01ff9cfc(fx32 value);
extern void func_0203d8fc(const PenetrationResult *result, void *contact, u32 flags);

BOOL TestCylinderAgainstCylinder_020410a0(CylinderShapeRef *refA, CylinderShapeRef *refB, void *contact, u32 flags)
{
    CollisionCylinder *cylA = refA->cylinder;
    CollisionCylinder *cylB = refB->cylinder;
    BOOL isCapsule = refA->kind == 3;
    fx32 radiusB;
    fx32 radiusA;
    fx32 extent;
    BOOL parallel;
    fx32 halfLengthB;
    u8 j;
    fx32 halfLengthA;
    u8 i;
    u8 k;
    PenetrationResult result = InitPenetrationResult_0203fb74();
    VecFx32 centerA = AverageVecFx32_0204b604(2, &cylA->start, &cylA->end);
    VecFx32 centerB = AverageVecFx32_0204b604(2, &cylB->start, &cylB->end);

    radiusA = cylA->radius;
    radiusB = cylB->radius;
    VecFx32 delta = SubtractVecFx32Into_0203f4a8(&centerA, &centerB);
    VecFx32 halfA = GetHalfSegment_02041670(cylA);
    VecFx32 halfB = GetHalfSegmentAlt_02040fdc(cylB);
    VecFx32 axis;
    VecFx32 cross = ComputeCrossProduct_02040500(&halfA, &halfB);

    parallel = IsNearlyZeroVec_0203f534(&cross);
    if (parallel) {
        axis = ComputeVectorRejection_02040aec(&delta, &NormalizeVectorInto_0203f580(&halfA));
        if (IsNearlyZeroVec_0203f534(&axis)) {
            axis = GetPerpendicularVec_0204ad4c(&halfA);
        }
    } else {
        axis = cross;
    }
    VEC_Normalize_01ff9f88(&axis, &axis);
    if (!TestSeparatingAxis_0203fba4(radiusA + radiusB, &delta, &axis, 0, &result)) {
        return FALSE;
    }
    {
        VecFx32 axisA = cylA->direction;
        VecFx32 axisB = cylB->direction;

        halfLengthA = cylA->length / 2;
        halfLengthB = cylB->length / 2;
        if (!parallel) {
            const VecFx32 *axes[2];
            const VecFx32 *halves[2];

            axes[0] = &axisA;
            axes[1] = &axisB;
            halves[0] = &halfA;
            halves[1] = &halfB;
            for (i = 0; i < 2; i++) {
                VecFx32 rejA = ComputeVectorRejection_02040aec(&AddVecFx32Into_0203f980(&delta, &NegateVecFx32Into_0203f9b0(halves[(u8)(i ^ 1)])), axes[i]);
                VecFx32 rejB = ComputeVectorRejection_02040aec(&AddVecFx32Into_0203f980(&delta, halves[(u8)(i ^ 1)]), axes[i]);

                if (VEC_Mag_01ff9f28(&rejA) < VEC_Mag_01ff9f28(&rejB)) {
                    axis = NormalizeVecFx32Out_020416f8(&rejA);
                } else {
                    axis = NormalizeVecFx32Out_020416f8(&rejB);
                }
                if (!isCapsule || i == 0) {
                    VecFx32 unitCross = NormalizeVectorInto_0203f580(&cross);
                    VecFx32 side = ComputeCrossProduct_02040500(&unitCross, axes[i]);
                    fx32 cosine = VEC_DotProduct_01ff9e6c(&axisB, axes[i]);
                    fx32 crossWeight = VEC_DotProduct_01ff9e6c(&axis, &unitCross);
                    fx32 sideWeight = VEC_DotProduct_01ff9e6c(&axis, &side);

                    axis = ScaleVecFx32_0203f4fc(&unitCross, FixedPointMultiply12(crossWeight, cosine));
                    axis = MultAddVecFx32Out_02040c58(sideWeight, &side, &axis);
                    NormalizeVecFx32InPlace_0204a9b4(&axis);
                }
                if (isCapsule) {
                    extent = cylA->radius + AbsDotProduct_0204a96c(&halfA, &axis);
                } else {
                    extent = ComputeDirectionalExtent_0203d718(cylA, &axisA, halfLengthA * 2, &axis);
                }
                extent += ComputeDirectionalExtent_0203d718(cylB, &axisB, halfLengthB * 2, &axis);
                if (!TestSeparatingAxis_0203fba4(extent, &delta, &axis, 3, &result)) {
                    return FALSE;
                }
            }
        }
        for (k = 0; k < 2; k++) {
            axis = (k == 0) ? axisB : axisA;
            if (isCapsule) {
                extent = cylA->radius + AbsDotProduct_0204a96c(&halfA, &axis);
            } else if (k == 0) {
                extent = ComputeDirectionalExtent_0203d718(cylA, &axisA, halfLengthA * 2, &axis);
            } else {
                extent = halfLengthA;
            }
            if (k == 1) {
                extent += ComputeDirectionalExtent_0203d718(cylB, &axisB, halfLengthB * 2, &axis);
            } else {
                extent += halfLengthB;
            }
            if (!TestSeparatingAxis_0203fba4(extent, &delta, &axis, 0, &result)) {
                return FALSE;
            }
            if (isCapsule) {
                break;
            }
        }
        for (i = 0; i < 2; i++) {
            VecFx32 pointA = (i == 0) ? cylA->start : cylA->end;

            for (j = 0; j < 2; j++) {
                VecFx32 pointB = (j == 0) ? cylB->start : cylB->end;
                VecFx32 diff = SubtractVecFx32Into_0203f4a8(&pointA, &pointB);

                if (isCapsule) {
                    VecFx32 toAxis = func_0204aea8(&diff, &axisB);
                    VecFx32 offset = MultAddVecFx32Out_02040c58(-cylB->radius, &toAxis, &diff);

                    axis = NormalizeVectorAltInto_0203f5d4(&offset);
                } else {
                    VecFx32 normal = CrossNormalized_0203fffc(&axisA, &axisB);
                    VecFx32 inPlaneA = CrossNormalized_0203fffc(&normal, &axisA);
                    VecFx32 inPlaneB = CrossNormalized_0203fffc(&normal, &axisB);
                    Basis3x3 basis = BuildBasisFromAxes_02041728(&axisA, &normal);
                    VecFx32 local = TransformVectorByBasisOut_02041768(&inPlaneB, &basis);
                    VecFx32 rimPoint;
                    VecFx32 toRim;
                    fx32 dist = VEC_DotProduct_01ff9e6c(&diff, &inPlaneA) - FX_Div_01ff9c84(FixedPointMultiply12(VEC_DotProduct_01ff9e6c(&diff, &axisA), local.x), local.y);
                    fx32 clamped = Min_0203f9e0(Abs_0203f228(dist), cylA->radius);

                    rimPoint = ScaleVecFx32_0203f4fc(&inPlaneA, Sign_0203f240(dist) * clamped);
                    rimPoint = MultAddVecFx32Out_02040c58(Sign_0203f240(VEC_DotProduct_01ff9e6c(&diff, &normal)) * FX_Sqrt_01ff9cfc(Square_0203f268(cylA->radius) - Square_0203f268(clamped)), &normal, &rimPoint);
                    toRim = SubtractVecFx32Into_0203f4a8(&rimPoint, &diff);
                    {
                        VecFx32 tangentA = ComputeCrossProduct_02040500(&rimPoint, &axisA);
                        VecFx32 tangentB = ComputeCrossProduct_02040500(&toRim, &axisB);

                        axis = CrossNormalized_0203fffc(&tangentA, &tangentB);
                    }
                }
                if (isCapsule) {
                    extent = cylA->radius + AbsDotProduct_0204a96c(&halfA, &axis);
                } else {
                    extent = ComputeDirectionalExtent_0203d718(cylA, &axisA, halfLengthA * 2, &axis);
                }
                extent += ComputeDirectionalExtent_0203d718(cylB, &axisB, halfLengthB * 2, &axis);
                if (!TestSeparatingAxis_0203fba4(extent, &delta, &axis, 3, &result)) {
                    return FALSE;
                }
            }
        }
    }
    func_0203d8fc(&result, contact, flags);
    return TRUE;
}
