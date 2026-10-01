#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct OrientedBox {
    VecFx32 center;
    fx32 halfExtents[3];
    VecFx32 axes[3];
    u8 flags;
} OrientedBox;

typedef struct CollisionSegment {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
} CollisionSegment;

typedef struct SegmentShapeRef {
    CollisionSegment *segment;
    u8 pad_04[0x18];
    s32 kind;
} SegmentShapeRef;

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
extern int FixedPointMultiply12(int left, int right);
extern BOOL func_0203b59c(SegmentShapeRef *segmentRef, OrientedBox **boxRef, void *contact, u32 flags);
extern VecFx32 func_0203ff74(const CollisionSegment *segment);
extern SweepResult func_02047cec(void);
extern VecFx32 SubtractVecFx32Out_02047d2c(const VecFx32 *a, const VecFx32 *b);
extern BOOL func_02047d5c(fx32 extent, const VecFx32 *diff, const VecFx32 *axis, u8 feature, const VecFx32 *velocity, SweepResult *result, s64 *outTime);
extern fx32 func_02047dac(fx32 value);
extern VecFx32 AddVecFx32Out_02047f98(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 NegateVecFx32Out_02047fc8(const VecFx32 *v);
extern void func_02047ff8(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);
extern BOOL func_0204792c(SweepResult *result, void *contact, u32 flags, const VecFx32 *velocity);
extern fx32 AbsDotProduct_0204a96c(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 func_0204b604(s32 count, ...);

BOOL SweepObbAgainstSegment_02047dc4(OrientedBox **boxRef, SegmentShapeRef *segmentRef, void *contact, u32 flags, const VecFx32 *velocity)
{
    OrientedBox *box = *boxRef;
    CollisionSegment *segment = segmentRef->segment;

    if (!(flags & 8)) {
        SegmentShapeRef swappedRef;
        CollisionSegment moved = *segment;
        moved.end = AddVecFx32Out_02047f98(&moved.end, &NegateVecFx32Out_02047fc8(velocity));
        swappedRef.segment = &moved;
        return func_0203b59c(&swappedRef, boxRef, contact, ~flags & 1);
    }
    {
        SweepResult result = func_02047cec();
        VecFx32 axis;
        VecFx32 center = func_0204b604(2, &segment->start, &segment->end);
        VecFx32 diff = SubtractVecFx32Out_02047d2c(&box->center, &center);
        VecFx32 dir = func_0203ff74(segment);
        fx32 extent;
        s8 i;
        s8 j;

        for (i = 0; i < 3; i++) {
            axis = box->axes[i];
            extent = box->halfExtents[i];
            if (!func_02047d5c(extent + AbsDotProduct_0204a96c(&dir, &axis), &diff, &axis, 0, velocity, &result, NULL)) {
                return FALSE;
            }
        }
        dir = segment->direction;
        for (i = 0; i < 3; i++) {
            if (AbsDotProduct_0204a96c(&box->axes[i], &dir) <= 0xff0) {
                func_02047ff8(&axis, &box->axes[i], &dir);
                extent = 0;
                for (j = 0; j < 3; j++) {
                    if (j != i) {
                        extent += func_02047dac(FixedPointMultiply12(VEC_DotProduct_01ff9e6c(&axis, &box->axes[j]), box->halfExtents[j]));
                    }
                }
                if (!func_02047d5c(extent, &diff, &axis, 0, velocity, &result, NULL)) {
                    return FALSE;
                }
            }
        }
        return func_0204792c(&result, contact, flags, velocity);
    }
}
