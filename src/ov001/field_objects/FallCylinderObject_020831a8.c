#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct CollisionCylinder {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
    fx32 radius;
} CollisionCylinder;

typedef struct CollisionShape {
    CollisionCylinder *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct SweptShape {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBounds;
} SweptShape;

typedef struct {
    u8 pad_000[0x1a4];
} QueryWorkspace;

typedef struct {
    s32 unk_00;
    s32 mask;
} QueryFilter;

typedef struct {
    s32 words[0x18];
} CollisionQuery;

typedef struct FallActor {
    u8 pad_000[0x119];
    u8 sweepPending;
    u8 pad_11a[0x16];
    SweptShape body;
} FallActor;

typedef struct FallObject {
    u8 pad_00[0x38];
    u8 actorId;
    u8 pad_39[0xb];
    fx32 posY;
    u8 pad_48[0x30];
    fx32 velocityY;
} FallObject;

extern FallActor *func_02036240(u32 id);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern CollisionShape InitCylinderShape_0203aeac(CollisionCylinder *storage, const VecFx32 *start, const VecFx32 *end,
                                                 const VecFx32 *direction, fx32 length, fx32 radius);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, QueryFilter *filter);
extern BOOL SweepWorldCollision_020364a0(CollisionQuery *query);

static inline QueryFilter MakeFilter(s32 value, s32 mask)
{
    QueryFilter filter;
    filter.unk_00 = value;
    filter.mask = mask;
    return filter;
}

void FallCylinderObject_020831a8(FallObject *object)
{
    CollisionQuery sweep;
    QueryWorkspace workspace;
    SweptShape shapeCopy;
    SweptShape shape;
    CollisionQuery query;
    CollisionCylinder cylinder;
    VecFx32 start;
    VecFx32 end;
    VecFx32 delta;
    VecFx32 startTmp;
    VecFx32 endTmp;
    VecFx32 axis;
    VecFx32 diff;
    CollisionShape built;
    VecFx32 actorDelta;
    FallActor *actor;
    QueryFilter filter;
    fx32 length;

    object->velocityY -= 0x52;
    actor = func_02036240(object->actorId);
    filter = MakeFilter(0, 0x15);
    endTmp.x = actor->body.shape.data->end.x;
    endTmp.y = actor->body.shape.data->end.y + 0xccd;
    endTmp.z = actor->body.shape.data->end.z;
    end = endTmp;
    startTmp.x = actor->body.shape.data->start.x;
    startTmp.y = actor->body.shape.data->start.y - 0xccd;
    startTmp.z = actor->body.shape.data->start.z;
    start = startTmp;
    delta.x = 0;
    delta.y = object->velocityY;
    delta.z = 0;
    VEC_Subtract_01ff9e3c(&end, &start, &diff);
    axis = diff;
    length = func_01ffaff4(&axis, &axis);
    built = InitCylinderShape_0203aeac(&cylinder, &start, &end, &axis, length, 0xccd);
    shape.shape = built;
    shape.delta = delta;
    OffsetBoxByDelta_0203ac70(&shape.shape.bounds, &shape.sweptBounds, &shape.delta);
    shapeCopy = shape;
    actor->sweepPending = 1;
    actorDelta.x = 0;
    actorDelta.y = object->velocityY;
    actorDelta.z = 0;
    actor->body.delta = actorDelta;
    OffsetBoxByDelta_0203ac70(&actor->body.shape.bounds, &actor->body.sweptBounds, &actor->body.delta);
    CollisionQuery_Init_02034c74(&query, 0, actor, 1, 1, 1, &shapeCopy, &workspace, &filter);
    sweep = query;
    if (SweepWorldCollision_020364a0(&sweep)) {
        object->velocityY = 0;
    }
    object->posY = cylinder.start.y;
}
