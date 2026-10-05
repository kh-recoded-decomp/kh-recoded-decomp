#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ShapeHolder {
    VecFx32 *origin;
    u8 bounds[0x18];
    s32 type;
    VecFx32 delta;
    u8 movedBounds[0x18];
} ShapeHolder;

typedef struct CollisionSegment {
    VecFx32 start;
    VecFx32 end;
} CollisionSegment;

typedef struct ShapeOwner {
    u8 pad_00[0x7c];
    u8 sweepMode;
    u8 pad_7d[0x33];
    ShapeHolder *holder;
} ShapeOwner;

extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void VEC_Normalize_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void OffsetBoxByDelta_0203ac70(const void *src, void *dst, const VecFx32 *delta);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void InitSegmentFromEndpoints_0203b1f0(CollisionSegment *segment);
extern void SetShapePosition_0203afa0(ShapeHolder *shape, const VecFx32 *position);
extern VecFx32 data_02053438;

void ApplyShapeVelocity_01ffcd30(ShapeOwner *owner, VecFx32 *velocity) {
    ShapeHolder *holder;

    if (owner->sweepMode) {
        if (VEC_Mag_01ff9f28(velocity) > 0x3e8000) {
            VEC_Normalize_01ffaff4(velocity, velocity);
            ScaleVecFx32InPlace_0204a5e4(velocity, 0x3e8000);
        }
        holder = owner->holder;
        holder->delta = *velocity;
        OffsetBoxByDelta_0203ac70(holder->bounds, holder->movedBounds, &holder->delta);
        return;
    }
    holder = owner->holder;
    if (holder->type == 2) {
        VecFx32 end;
        VEC_Add_01ff9e0c(holder->origin, velocity, &end);
        ((CollisionSegment *)owner->holder->origin)->end = end;
        InitSegmentFromEndpoints_0203b1f0((CollisionSegment *)owner->holder->origin);
    } else {
        VecFx32 moved;
        VecFx32 position;
        VEC_Add_01ff9e0c(holder->origin, velocity, &moved);
        position = moved;
        SetShapePosition_0203afa0(holder, &position);
        *velocity = data_02053438;
    }
}
