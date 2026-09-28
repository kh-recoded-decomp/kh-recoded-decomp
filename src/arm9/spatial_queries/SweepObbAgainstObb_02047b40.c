#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct OrientedBox {
    VecFx32 center;
    fx32 halfExtents[3];
    VecFx32 axes[3];
} OrientedBox;

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

extern SweepResult func_02047cec(void);
extern VecFx32 SubtractVecFx32Out_02047d2c(const VecFx32 *a, const VecFx32 *b);
extern fx32 func_0203d4d0(const OrientedBox *box, const VecFx32 *axis);
extern BOOL func_02047d5c(fx32 extent, const VecFx32 *diff, const VecFx32 *axis, u8 feature, const VecFx32 *velocity, SweepResult *result, s64 *outTime);
extern BOOL func_0204a9e4(const VecFx32 *a, const VecFx32 *b, VecFx32 *cross);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern int FixedPointMultiply12(int left, int right);
extern fx32 func_02047dac(fx32 value);
extern BOOL func_0204792c(SweepResult *result, void *contact, u32 flags, const VecFx32 *velocity);

BOOL SweepObbAgainstObb_02047b40(OrientedBox **boxARef, OrientedBox **boxBRef, void *contact, u32 flags, const VecFx32 *velocity)
{
    SweepResult result = func_02047cec();
    VecFx32 axis;
    VecFx32 diff = SubtractVecFx32Out_02047d2c(&(*boxARef)->center, &(*boxBRef)->center);
    OrientedBox *boxes[2];
    s8 i;
    s8 j;
    s8 k;
    s8 l;

    boxes[0] = *boxARef;
    boxes[1] = *boxBRef;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++) {
            fx32 extent;
            axis = boxes[i]->axes[j];
            extent = boxes[i]->halfExtents[j];
            if (!func_02047d5c(extent + func_0203d4d0(boxes[(s8)(i ^ 1)], &axis), &diff, &axis, 0, velocity, &result, NULL)) {
                return FALSE;
            }
        }
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (!func_0204a9e4(&boxes[0]->axes[i], &boxes[1]->axes[j], &axis)) {
                fx32 extent;
                func_01ff9f88(&axis, &axis);
                extent = 0;
                for (k = 0; k < 2; k++) {
                    for (l = 0; l < 3; l++) {
                        if (k == 0) {
                            if (l == i) {
                                continue;
                            }
                        } else if (l == j) {
                            continue;
                        }
                        fx32 dot = VEC_DotProduct_01ff9e6c(&axis, &boxes[k]->axes[l]);
                        extent += func_02047dac(FixedPointMultiply12(dot, boxes[k]->halfExtents[l]));
                    }
                }
                if (!func_02047d5c(extent, &diff, &axis, 0, velocity, &result, NULL)) {
                    return FALSE;
                }
            }
        }
    }
    return func_0204792c(&result, contact, flags, velocity);
}
