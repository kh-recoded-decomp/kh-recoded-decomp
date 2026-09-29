#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollBox {
    fx32 maxX;
    fx32 maxY;
    fx32 maxZ;
    fx32 minX;
    fx32 minY;
    fx32 minZ;
} CollBox;

typedef struct CollShape {
    void *data;
    CollBox box;
    s32 kind;
} CollShape;

typedef struct CollSweep {
    CollShape shape;
    VecFx32 delta;
    CollBox sweepBox;
} CollSweep;

typedef struct CollHit {
    s32 unk_00;
    VecFx32 normal;
    fx32 time;
    s32 unk_14;
} CollHit;

typedef struct CollTarget {
    u8 pad_00[0xd];
    u8 isMoving;
    u8 pad_0E[0x16];
    CollSweep sweep;
} CollTarget;

typedef struct CollTargetRef {
    CollTarget *target;
    s32 kind;
} CollTargetRef;

typedef BOOL (*ShapeTestFn)(const CollShape *shape, const CollShape *other, CollHit *hit, u32 flags);
typedef BOOL (*ShapeSweepFn)(const CollShape *shape, const CollShape *other, CollHit *hit, u32 flags, const VecFx32 *delta);

extern const ShapeTestFn g_shapeTestTable_020558a0[][6];
extern const ShapeSweepFn g_shapeSweepTable_02055930[][6];

extern BOOL TestSweepAgainstFace_020310c8(const void *face, const CollSweep *sweep, BOOL moving, CollHit *hit);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

BOOL TestSweepAgainstTarget_02030bc4(const CollSweep *sweep, const CollTargetRef *ref, CollHit *hit)
{
    BOOL moving;
    BOOL result;
    const CollTarget *target;

    if (sweep->delta.x != 0 || sweep->delta.y != 0 || sweep->delta.z != 0) {
        moving = TRUE;
    } else {
        moving = FALSE;
    }
    if (ref->kind == 4) {
        target = ref->target;
        if (target->isMoving) {
            const VecFx32 *relativeDelta;
            VecFx32 relative;
            if (!moving) {
                relativeDelta = NULL;
            } else {
                VecFx32 difference;
                VEC_Subtract_01ff9e3c(&sweep->delta, &target->sweep.delta, &difference);
                relative = difference;
                relativeDelta = &relative;
            }
            target = ref->target;
            if (!moving) {
                result = g_shapeTestTable_020558a0[sweep->shape.kind][target->sweep.shape.kind](
                    &sweep->shape, &target->sweep.shape, hit, 14);
            } else {
                result = g_shapeSweepTable_02055930[sweep->shape.kind][target->sweep.shape.kind](
                    &sweep->shape, &target->sweep.shape, hit, 12, relativeDelta);
            }
        } else if (!moving) {
            result = g_shapeTestTable_020558a0[sweep->shape.kind][target->sweep.shape.kind](
                &sweep->shape, &target->sweep.shape, hit, 6);
        } else {
            result = g_shapeSweepTable_02055930[sweep->shape.kind][target->sweep.shape.kind](
                &sweep->shape, &target->sweep.shape, hit, 4, &sweep->delta);
        }
    } else {
        result = TestSweepAgainstFace_020310c8(ref->target, sweep, moving, hit);
    }
    return result;
}
