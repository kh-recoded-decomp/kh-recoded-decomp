#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct Sphere {
    VecFx32 center;
    fx32 radius;
} Sphere;

typedef struct CollisionShape {
    void *data;
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

typedef struct FallingObject {
    u8 pad_00[0x38];
    u8 actorId;
    u8 pad_39[0x7];
    VecFx32 position;
    u8 pad_4c[0x14];
    fx32 velocityY;
} FallingObject;

extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern CollisionShape func_0203ad14(Sphere *storage, const VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, QueryFilter *filter);
extern BOOL SweepWorldCollision_020364a0(CollisionQuery *query);
extern u8 *func_02036240(u32 id);
extern void SetShapePosition_0203afa0(void *shape, const VecFx32 *position);
extern void SetCollisionObjectPosition_02033f48(void *object, const VecFx32 *position);
extern void FieldObject_SetPhaseMode_02082714(FallingObject *object, int mode);
extern int AdvanceWrappedPhase_02082440(FallingObject *object);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

static inline VecFx32 AddVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 out;
    VEC_Add_01ff9e0c(a, b, &out);
    return out;
}

static inline QueryFilter MakeFilter(s32 value, s32 mask)
{
    QueryFilter filter;
    filter.unk_00 = value;
    filter.mask = mask;
    return filter;
}

int FallFieldObject_02082468(FallingObject *object)
{
    CollisionQuery sweep;
    QueryWorkspace workspace;
    SweptShape shapeCopy;
    SweptShape shape;
    CollisionQuery query;
    Sphere sphere;
    VecFx32 center;
    VecFx32 offset;
    VecFx32 top;
    VecFx32 up;
    VecFx32 delta;
    u8 *actor;
    QueryFilter filter;

    object->velocityY -= 0x7b;
    offset = MakeVec(0, 0, 0);
    center = AddVec(&object->position, &offset);
    delta.x = 0;
    delta.y = object->velocityY;
    delta.z = 0;
    shape.shape = func_0203ad14(&sphere, &center, 0x59a);
    shape.delta = delta;
    OffsetBoxByDelta_0203ac70(&shape.shape.bounds, &shape.sweptBounds, &shape.delta);
    shapeCopy = shape;
    actor = func_02036240(object->actorId);
    filter = MakeFilter(0, 0x21);
    CollisionQuery_Init_02034c74(&query, 0, actor, 1, 1, 1, &shapeCopy, &workspace, &filter);
    sweep = query;
    if (SweepWorldCollision_020364a0(&sweep)) {
        FieldObject_SetPhaseMode_02082714(object, 0);
    }
    VEC_Add_01ff9e0c(&object->position, &shapeCopy.delta, &object->position);
    SetShapePosition_0203afa0(actor + 0x130, &object->position);
    up = MakeVec(0, 0xa66, 0);
    top = AddVec(&object->position, &up);
    SetCollisionObjectPosition_02033f48(actor + 0x10c, &top);
    AdvanceWrappedPhase_02082440(object);
    return 0;
}
