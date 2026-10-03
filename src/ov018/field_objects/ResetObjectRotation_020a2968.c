#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionShape {
    u8 *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef void (*ComputeBoundsFunc)(CollisionShape *shape, s32 *bounds);

typedef struct {
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[0x3d];
    fx32 rotation[6];
    VecFx32 offset;
} Obj;

typedef struct {
    u8 pad_000[0x130];
    CollisionShape shape;
    VecFx32 delta;
    s32 sweptBounds[6];
} Actor;

extern const VecFx32 data_02053438;
extern ComputeBoundsFunc data_020559c0[];

extern Actor *func_02036240(u32 id);
extern void func_01ff90ec(void *mtx);
extern void OffsetBoxByDelta_0203ac70(const void *src, void *dst, const VecFx32 *delta);
extern void UpdateBoxAxisAlignedFlag_0203b1c0(void *data);

static inline void ComputeBounds(CollisionShape *shape)
{
    data_020559c0[shape->kind](shape, (s32 *)((u8 *)shape + 4));
}

void ResetObjectRotation_020a2968(Obj *obj)
{
    Actor *actor = func_02036240(obj->actorId);

    obj->rotation[0] = 0;
    obj->rotation[1] = 0;
    obj->rotation[2] = 0x1000;
    obj->rotation[3] = 0;
    obj->rotation[4] = 0x1000;
    obj->rotation[5] = 0;
    obj->offset = data_02053438;
    func_01ff90ec(actor->shape.data + 0x18);
    ComputeBounds(&actor->shape);
    OffsetBoxByDelta_0203ac70(actor->shape.bounds, actor->sweptBounds, &actor->delta);
    UpdateBoxAxisAlignedFlag_0203b1c0(actor->shape.data);
}


