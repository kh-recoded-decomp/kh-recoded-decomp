#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionBox {
    VecFx32 center;
    fx32 halfExtents[3];
    VecFx32 axes[3];
} CollisionBox;

typedef struct CollisionCapsule {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
    fx32 radius;
} CollisionCapsule;

typedef struct BoxShapeRef {
    CollisionBox *box;
} BoxShapeRef;

typedef struct CapsuleShapeRef {
    CollisionCapsule *capsule;
} CapsuleShapeRef;

typedef struct PenetrationResult {
    fx32 depth;
    VecFx32 axis;
    s8 axisSign;
    u8 featureId;
    u8 pad_12[2];
} PenetrationResult;

extern BOOL TestCapsuleAgainstBox_02044758(BoxShapeRef *boxRef, CapsuleShapeRef *capsuleRef, void *contact, u32 flags);
extern PenetrationResult MakeEmptyPenetration_0203fb74(void);
extern VecFx32 AverageVecFx32_0204b604(s32 count, ...);
extern VecFx32 SubtractVecFx32Into_0203f4a8(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 GetCapsuleHalfSegment_0203ff74(const CollisionCapsule *capsule);
extern VecFx32 CrossNormalized_0203fffc(const VecFx32 *a, const VecFx32 *b);
extern fx32 AbsDotProduct_0204a96c(const VecFx32 *a, const VecFx32 *b);
extern BOOL TestSeparatingAxis_0203fba4(fx32 extent, const VecFx32 *delta, const VecFx32 *axis, u8 featureId, PenetrationResult *result);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern int FixedPointMultiply12(int left, int right);
extern int Abs_0203f228(int value);
extern void WritePenetrationContact_0203d8fc(const PenetrationResult *result, void *contact, u32 flags);

BOOL TestBoxAgainstCapsule_0203fde0(BoxShapeRef *boxRef, CapsuleShapeRef *capsuleRef, void *contact, u32 flags)
{
    CollisionCapsule *capsule = capsuleRef->capsule;
    CollisionBox *box = boxRef->box;

    if ((flags & 2) || capsule->length < 16) {
        PenetrationResult result = MakeEmptyPenetration_0203fb74();
        VecFx32 center = AverageVecFx32_0204b604(2, &capsule->start, &capsule->end);
        VecFx32 delta = SubtractVecFx32Into_0203f4a8(&box->center, &center);
        VecFx32 axis;
        VecFx32 capsuleAxis = GetCapsuleHalfSegment_0203ff74(capsule);
        s8 i;
        s8 j;

        for (i = 0; i < 3; i++) {
            fx32 extent;
            axis = box->axes[i];
            extent = box->halfExtents[i];
            if (!TestSeparatingAxis_0203fba4(extent + AbsDotProduct_0204a96c(&capsuleAxis, &axis), &delta, &axis, 0, &result)) {
                return FALSE;
            }
        }
        if (capsule->length == 0) {
            capsuleAxis.x = 0x1000;
        } else {
            capsuleAxis = capsule->direction;
        }
        for (i = 0; i < 3; i++) {
            if (AbsDotProduct_0204a96c(&box->axes[i], &capsuleAxis) <= 0xFF0) {
                fx32 extent;
                axis = CrossNormalized_0203fffc(&box->axes[i], &capsuleAxis);
                extent = 0;
                for (j = 0; j < 3; j++) {
                    if (j != i) {
                        extent += Abs_0203f228(FixedPointMultiply12(VEC_DotProduct_01ff9e6c(&axis, &box->axes[j]), box->halfExtents[j]));
                    }
                }
                if (!TestSeparatingAxis_0203fba4(extent, &delta, &axis, 0, &result)) {
                    return FALSE;
                }
            }
        }
        WritePenetrationContact_0203d8fc(&result, contact, flags);
        return TRUE;
    }
    return TestCapsuleAgainstBox_02044758(boxRef, capsuleRef, contact, flags ^ 1);
}
