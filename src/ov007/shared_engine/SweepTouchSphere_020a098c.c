#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    void *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBounds;
} SweptShape;

typedef struct {
    VecFx32 center;
    fx32 radius;
} CollisionSphere;

typedef struct {
    void *callback;
    void *owner;
} CollisionFilter;

typedef struct {
    u8 pad_00[0x48];
    CollisionFilter filter;
    u8 pad_50[0x10];
} CollisionQuery;

typedef struct {
    u8 data[0x1a4];
} QueryWorkspace;

typedef struct {
    u8 pad_00[0xc];
    u8 *model;
} TouchActor;

extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern CollisionShape MakeSphereShape_0203ad14(CollisionSphere *sphere, const VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *owner, u8 kind, u8 unk3C, u8 unk3D, SweptShape *shape, QueryWorkspace *workspace, s32 unk44);
extern void *SweepWorldCollision_020364a0(CollisionQuery *query);
extern BOOL CanTouchedObjectAct_020a08a8();

BOOL SweepTouchSphere_020a098c(TouchActor *actor, VecFx32 *pos, const VecFx32 *motion, VecFx32 *out)
{
    fx32 x, y, z;
    CollisionQuery query;
    QueryWorkspace workspace;
    SweptShape shapeCopy;
    SweptShape shape;
    CollisionQuery setup;
    VecFx32 center;
    CollisionSphere sphere;
    CollisionFilter filter;

    x = pos->x;
    y = pos->y;
    z = pos->z;
    center.x = x;
    center.y = y;
    center.z = z;
    shape.shape = MakeSphereShape_0203ad14(&sphere, &center, 0x200);
    shape.delta = *motion;
    OffsetBoxByDelta_0203ac70(&shape.shape.bounds, &shape.sweptBounds, &shape.delta);
    shapeCopy = shape;
    CollisionQuery_Init_02034c74(&setup, 0xf, actor->model + 0x10, 9, 1, 1, &shapeCopy, &workspace, 0);
    query = setup;
    filter.callback = CanTouchedObjectAct_020a08a8;
    filter.owner = NULL;
    query.filter = filter;
    if (SweepWorldCollision_020364a0(&query)) {
        *out = sphere.center;
        return TRUE;
    }
    VEC_Add_01ff9e0c(pos, motion, out);
    return FALSE;
}
