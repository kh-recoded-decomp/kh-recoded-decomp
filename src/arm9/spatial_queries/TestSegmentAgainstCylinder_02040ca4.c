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

extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern fx32 func_01ffaff4(VecFx32 *src, VecFx32 *dst);
extern fx32 ComputeDirectionalExtent_0203d718(const CollisionCylinder *cylinder, const VecFx32 *dirA, s32 majorExtent, const VecFx32 *dirB);
extern void func_0203d8fc(const PenetrationResult *result, void *contact, u32 flags);
extern VecFx32 SubtractVecFx32Into_0203f4a8(const VecFx32 *a, const VecFx32 *b);
extern BOOL func_0203f534(const VecFx32 *vec);
extern void NormalizeVectorInto_0203f580(VecFx32 *dest, const VecFx32 *src);
extern VecFx32 NormalizedVector_0203f580(const VecFx32 *src);
extern VecFx32 AddVecFx32Into_0203f980(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 NegateVecFx32Into_0203f9b0(const VecFx32 *src);
extern PenetrationResult func_0203fb74(void);
extern BOOL func_0203fba4(fx32 extent, const VecFx32 *delta, const VecFx32 *axis, u8 featureId, PenetrationResult *result);
extern VecFx32 func_0203ff74(const CollisionCylinder *cylinder);
extern VecFx32 ComputeCrossProduct_02040500(const VecFx32 *a, const VecFx32 *b);
extern void ComputeVectorRejection_02040aec(VecFx32 *out, const VecFx32 *v, const VecFx32 *axis);
extern VecFx32 VectorRejection_02040aec(const VecFx32 *v, const VecFx32 *axis);
extern VecFx32 func_02040fdc(const CollisionCylinder *cylinder);
extern void func_02041034(VecFx32 *out, fx32 x, fx32 y, fx32 z);
extern fx32 AbsDotProduct_0204a96c(const VecFx32 *a, const VecFx32 *b);
extern void func_0204ad4c(VecFx32 *out, const VecFx32 *v);
extern VecFx32 func_0204b604(s32 count, ...);

BOOL TestSegmentAgainstCylinder_02040ca4(CylinderShapeRef *segmentRef, CylinderShapeRef *cylinderRef, void *contact, u32 flags)
{
    CollisionCylinder *segment = segmentRef->cylinder;
    CollisionCylinder *cylinder = cylinderRef->cylinder;
    BOOL isCapsule = cylinderRef->kind == 3;
    PenetrationResult result = func_0203fb74();
    VecFx32 segmentCenter = func_0204b604(2, &segment->start, &segment->end);
    VecFx32 cylinderCenter = func_0204b604(2, &cylinder->start, &cylinder->end);
    VecFx32 delta = SubtractVecFx32Into_0203f4a8(&segmentCenter, &cylinderCenter);
    VecFx32 normal;
    VecFx32 segmentHalf = func_0203ff74(segment);
    VecFx32 cylinderHalf = func_02040fdc(cylinder);
    VecFx32 cross = ComputeCrossProduct_02040500(&segmentHalf, &cylinderHalf);
    BOOL parallel = func_0203f534(&cross);
    u8 i;

    if (parallel) {
        ComputeVectorRejection_02040aec(&normal, &delta, &NormalizedVector_0203f580(&segmentHalf));
        if (func_0203f534(&normal)) {
            func_0204ad4c(&normal, &segmentHalf);
        }
    } else {
        normal = cross;
    }
    func_01ffaff4(&normal, &normal);
    if (!func_0203fba4(cylinder->radius, &delta, &normal, 0, &result)) {
        return FALSE;
    }
    {
        VecFx32 segmentAxis = segment->direction;
        VecFx32 cylinderAxis = cylinder->direction;
        fx32 length = cylinder->length;
        u8 j;

        if (!parallel) {
            VecFx32 *axes[2];
            VecFx32 *halves[2];
            axes[0] = &segmentAxis;
            axes[1] = &cylinderAxis;
            halves[0] = &segmentHalf;
            halves[1] = &cylinderHalf;
            for (i = 0; i < 2; i++) {
                VecFx32 *axis = axes[i];
                VecFx32 *otherHalf = halves[(u8)(i ^ 1)];
                fx32 extent;
                VecFx32 toNear = VectorRejection_02040aec(&AddVecFx32Into_0203f980(&delta, &NegateVecFx32Into_0203f9b0(otherHalf)), axis);
                VecFx32 toFar = VectorRejection_02040aec(&AddVecFx32Into_0203f980(&delta, otherHalf), axis);
                if (VEC_Mag_01ff9f28(&toNear) < VEC_Mag_01ff9f28(&toFar)) {
                    NormalizeVectorInto_0203f580(&normal, &toNear);
                } else {
                    NormalizeVectorInto_0203f580(&normal, &toFar);
                }
                extent = cylinder->radius;
                extent += AbsDotProduct_0204a96c(&segmentHalf, &normal);
                if (!func_0203fba4(extent, &delta, &normal, 2, &result)) {
                    return FALSE;
                }
            }
        }
        if (isCapsule) {
            for (j = 0; j < 2; j++) {
                VecFx32 segmentPoint = j == 0 ? segment->start : segment->end;
                u8 k;
                for (k = 0; k < 2; k++) {
                    VecFx32 cylinderPoint = k == 0 ? cylinder->start : cylinder->end;
                    VecFx32 diff = SubtractVecFx32Into_0203f4a8(&segmentPoint, &cylinderPoint);
                    if (func_0203f534(&diff)) {
                        func_02041034(&normal, 0x1000, 0, 0);
                    } else {
                        NormalizeVectorInto_0203f580(&normal, &diff);
                    }
                    {
                        fx32 segmentExtent = AbsDotProduct_0204a96c(&segmentHalf, &normal);
                        fx32 cylinderExtent = cylinder->radius + AbsDotProduct_0204a96c(&cylinderHalf, &normal);
                        if (!func_0203fba4(segmentExtent + cylinderExtent, &delta, &normal, 2, &result)) {
                            return FALSE;
                        }
                    }
                }
            }
        } else {
            normal = cylinderAxis;
            if (!func_0203fba4(AbsDotProduct_0204a96c(&segmentHalf, &normal) + ComputeDirectionalExtent_0203d718(cylinder, &cylinderAxis, length * 2, &normal), &delta, &normal, 0, &result)) {
                return FALSE;
            }
        }
    }
    func_0203d8fc(&result, contact, flags);
    return TRUE;
}
