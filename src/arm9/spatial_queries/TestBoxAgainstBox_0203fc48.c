#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionBox {
    VecFx32 center;
    fx32 halfExtents[3];
    VecFx32 axes[3];
} CollisionBox;

typedef struct BoxShapeRef {
    CollisionBox *box;
} BoxShapeRef;

typedef struct PenetrationResult {
    fx32 depth;
    VecFx32 axis;
    s8 axisSign;
    u8 featureId;
    u8 pad_12[2];
} PenetrationResult;

extern PenetrationResult MakeEmptyPenetration_0203fb74(void);
extern VecFx32 SubtractVecFx32Into_0203f4a8(const VecFx32 *a, const VecFx32 *b);
extern fx32 ProjectBoxExtent_0203d4d0(const CollisionBox *box, const VecFx32 *axis);
extern BOOL TestSeparatingAxis_0203fba4(fx32 extent, const VecFx32 *delta, const VecFx32 *axis, u8 featureId, PenetrationResult *result);
extern BOOL CrossUnlessParallel_0204a9e4(const VecFx32 *a, const VecFx32 *b, VecFx32 *cross);
extern void VEC_Normalize_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern int FixedPointMultiply12(int left, int right);
extern int Abs_0203f228(int value);
extern void WritePenetrationContact_0203d8fc(const PenetrationResult *result, void *contact, u32 flags);

BOOL TestBoxAgainstBox_0203fc48(BoxShapeRef *refA, BoxShapeRef *refB, void *contact, u32 flags)
{
    PenetrationResult result = MakeEmptyPenetration_0203fb74();
    VecFx32 delta = SubtractVecFx32Into_0203f4a8(&refA->box->center, &refB->box->center);
    CollisionBox *boxes[2];
    VecFx32 axis;
    s8 i;
    s8 j;

    boxes[0] = refA->box;
    boxes[1] = refB->box;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++) {
            VecFx32 faceAxis = boxes[i]->axes[j];
            fx32 extent = boxes[i]->halfExtents[j];
            if (!TestSeparatingAxis_0203fba4(extent + ProjectBoxExtent_0203d4d0(boxes[(s8)(i ^ 1)], &faceAxis), &delta, &faceAxis, 0, &result)) {
                return FALSE;
            }
        }
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (!CrossUnlessParallel_0204a9e4(&boxes[0]->axes[i], &boxes[1]->axes[j], &axis)) {
                fx32 extent;
                s8 boxIndex;
                VEC_Normalize_01ff9f88(&axis, &axis);
                extent = 0;
                for (boxIndex = 0; boxIndex < 2; boxIndex++) {
                    s8 axisIndex;
                    for (axisIndex = 0; axisIndex < 3; axisIndex++) {
                        if (boxIndex == 0) {
                            if (axisIndex == i) {
                                continue;
                            }
                        } else if (axisIndex == j) {
                            continue;
                        }
                        fx32 dot = VEC_DotProduct_01ff9e6c(&axis, &boxes[boxIndex]->axes[axisIndex]);
                        extent += Abs_0203f228(FixedPointMultiply12(dot, boxes[boxIndex]->halfExtents[axisIndex]));
                    }
                }
                if (!TestSeparatingAxis_0203fba4(extent, &delta, &axis, 0, &result)) {
                    return FALSE;
                }
            }
        }
    }
    WritePenetrationContact_0203d8fc(&result, contact, flags);
    return TRUE;
}
