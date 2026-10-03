#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[5];
    VecFx32 position;
} Obj;

typedef struct {
    u8 pad_000[0x130];
    u8 shape[4];
    u8 box[0x1c];
    VecFx32 delta;
    u8 sweptBox[0x18];
} Actor;

extern Actor *func_02036240(u32 id);
extern void SetShapePosition_0203afa0(void *shape, const VecFx32 *position);
extern void OffsetBoxByDelta_0203ac70(const void *src, void *dst, const VecFx32 *delta);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

void SyncActorShapePosition_020a3530(Obj *obj, const VecFx32 *position)
{
    Actor *actor;
    VecFx32 center;

    obj->position = *position;
    actor = func_02036240(obj->actorId);
    center = MakeVec(obj->position.x, obj->position.y + 0x800, obj->position.z);
    SetShapePosition_0203afa0(actor->shape, &center);
    OffsetBoxByDelta_0203ac70(actor->box, actor->sweptBox, &actor->delta);
}

