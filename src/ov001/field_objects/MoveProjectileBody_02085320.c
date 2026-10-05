#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Box {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct CollisionShape {
    VecFx32 *position;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct SweptShape {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBounds;
} SweptShape;

typedef struct ShapeStorage {
    u8 data[0x28];
} ShapeStorage;

typedef struct QueryWorkspace {
    u8 pad_000[0x1a4];
} QueryWorkspace;

typedef struct QueryFilter {
    s32 unk_00;
    s32 mask;
} QueryFilter;

typedef struct QueryHandler {
    void *func;
    void *arg;
} QueryHandler;

typedef struct CollisionQuery {
    u32 words[0x12];
    QueryHandler surface;
    QueryHandler contact;
    QueryHandler bounce;
} CollisionQuery;

typedef struct HitResult {
    u8 pad_00[0x38];
    VecFx32 point;
} HitResult;

typedef struct Matrix33 {
    VecFx32 row[3];
} Matrix33;

typedef struct SceneNode {
    u16 flags;
    u8 pad_02[0x80 - 0x02];
    Matrix33 rotation;
    VecFx32 translation;
} SceneNode;

typedef struct ProjectileBody {
    u8 pad_000[0x10];
    u8 anchor[4];
    SceneNode node;
    u8 pad_0c4[0x11c - 0xc4];
    u8 collider[0x140 - 0x11c];
    SweptShape sweep;
} ProjectileBody;

typedef struct Projectile {
    u8 pad_00[0xc];
    ProjectileBody *body;
    u8 pad_10[4];
    void *update;
    u8 pad_18[0x40 - 0x18];
    VecFx32 position;
    u8 pad_4c[0x58 - 0x4c];
    s32 state;
    u8 pad_5c[0x70 - 0x5c];
    VecFx32 drift;
    VecFx32 velocity;
    s32 heading;
    s32 pitch;
    u8 pad_90[0xa0 - 0x90];
    Box cached;
} Projectile;

extern const VecFx32 data_02053438;
extern const s16 data_0205356c[];
extern BOOL CheckSurfaceFacing_02085734(void);
extern BOOL HandleContactHit_02085888(void);
extern void BounceProjectileOffWall_020858e0(void);
extern int UpdateFallingObject_02085218(Projectile *projectile);

extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern int FixedPointMultiply12(int left, int right);
extern void SetCollisionObjectPosition_02033f48(void *object, const VecFx32 *position);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, QueryFilter *filter);
extern void func_020350d4(CollisionQuery *query, Box *cached);
extern HitResult *SweepWorldCollision_020364a0(CollisionQuery *query);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);
extern CollisionShape func_0203adcc(ShapeStorage *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length);
extern void SetShapePosition_0203afa0(CollisionShape *shape, const VecFx32 *position);
extern void SpawnSoundSlot_0204da8c(int soundId, int mode, const VecFx32 *position, int flags);
extern void ProbeWorldAlongVelocity_02085278(Projectile *probe, QueryFilter *filter);

#define ANGLE_INDEX(angle) ((s32)((((s64)(angle) << 16) / 0x6488) & 0xffff) >> 4)
#define SIN_AT(index) data_0205356c[index]
#define COS_AT(index) data_0205356c[(0x400 - (index)) & 0xfff]

static inline QueryFilter MakeFilter(s32 unk, s32 mask)
{
    QueryFilter filter;
    filter.unk_00 = unk;
    filter.mask = mask;
    return filter;
}

static inline QueryHandler MakeHandler(void *func, void *arg)
{
    QueryHandler handler;
    handler.func = func;
    handler.arg = arg;
    return handler;
}

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

static inline void UpdateSweptBounds(SweptShape *sweep)
{
    OffsetBoxByDelta_0203ac70(&sweep->shape.bounds, &sweep->sweptBounds, &sweep->delta);
}

static inline void SetSweepDelta(SweptShape *sweep, const VecFx32 *delta)
{
    sweep->delta = *delta;
    UpdateSweptBounds(sweep);
}

static inline void TranslateSweep(SweptShape *sweep, const VecFx32 *delta)
{
    VecFx32 position;
    VecFx32 sum;

    VEC_Add_01ff9e0c(sweep->shape.position, delta, &sum);
    position = sum;
    SetShapePosition_0203afa0(&sweep->shape, &position);
    UpdateSweptBounds(sweep);
}

static inline void SetNodeRotation(SceneNode *node, const Matrix33 *rotation)
{
    node->rotation = *rotation;
    node->flags &= ~0x20;
}

static inline void BuildSegmentShape(CollisionShape *shape, ShapeStorage *storage, const VecFx32 *position, const VecFx32 *top)
{
    VecFx32 axis;
    VecFx32 delta;
    fx32 length;
    VEC_Subtract_01ff9e3c(top, position, &delta);
    axis = delta;
    length = func_01ffaff4(&axis, &axis);
    *shape = func_0203adcc(storage, position, top, &axis, length);
}

void MoveProjectileBody_02085320(Projectile *projectile, BOOL collide)
{
    QueryWorkspace workspace;
    CollisionQuery sweep;
    QueryWorkspace groundWorkspace;
    CollisionQuery query;
    CollisionQuery groundQuery;
    ShapeStorage storage;
    CollisionShape shape;
    Matrix33 rotation;
    QueryFilter filter;
    HitResult *hit;

    if (collide) {

        filter = MakeFilter(0, 0x12);
        CollisionQuery_Init_02034c74(&query, 0, projectile->body->anchor, 3, 0, 1, &projectile->body->sweep, &workspace, &filter);
        sweep = query;
        SetSweepDelta(&projectile->body->sweep, &projectile->drift);
        sweep.surface = MakeHandler((void *)CheckSurfaceFacing_02085734, NULL);
        sweep.contact = MakeHandler((void *)HandleContactHit_02085888, projectile);
        sweep.bounce = MakeHandler((void *)BounceProjectileOffWall_020858e0, projectile);
        SetCollisionObjectPosition_02033f48(projectile->body->collider, &projectile->position);
        ProbeWorldAlongVelocity_02085278(projectile, &filter);
        func_020350d4(&sweep, &projectile->cached);
        hit = SweepWorldCollision_020364a0(&sweep);
        if (hit == NULL && projectile->state == 1) {
            VecFx32 top = MakeVec(0, -0x3000, 0);

            BuildSegmentShape(&shape, &storage, &data_02053438, &top);
            CollisionQuery_Init_02034c74(&groundQuery, 0, projectile->body->anchor, 1, 2, 0, &shape, &groundWorkspace, NULL);
            sweep = groundQuery;
            SetShapePosition_0203afa0(&shape, &projectile->position);
            if (!SweepWorldCollision_020364a0(&sweep)) {
                projectile->state = 3;
                projectile->update = (void *)UpdateFallingObject_02085218;
                SpawnSoundSlot_0204da8c(0x1a1, 2, &projectile->position, 0);
            }
            VEC_Add_01ff9e0c(&projectile->position, &projectile->drift, &projectile->position);
        } else if (hit != NULL) {
            projectile->position = hit->point;
        } else {
            VEC_Add_01ff9e0c(&projectile->position, &projectile->drift, &projectile->position);
        }
    } else {
        VEC_Add_01ff9e0c(&projectile->position, &projectile->drift, &projectile->position);
        SetSweepDelta(&projectile->body->sweep, &projectile->drift);
        TranslateSweep(&projectile->body->sweep, &projectile->body->sweep.delta);
    }
    projectile->body->node.translation = projectile->position;
    rotation.row[0] = MakeVec(FixedPointMultiply12(COS_AT(ANGLE_INDEX(projectile->heading)), COS_AT(ANGLE_INDEX(projectile->pitch))),
                              SIN_AT(ANGLE_INDEX(projectile->pitch)),
                              FixedPointMultiply12(SIN_AT(ANGLE_INDEX(projectile->heading)), COS_AT(ANGLE_INDEX(projectile->pitch))));
    rotation.row[1] = MakeVec(FixedPointMultiply12(COS_AT(ANGLE_INDEX(projectile->heading)), COS_AT(ANGLE_INDEX(projectile->pitch + 0x6488 / 4))),
                              SIN_AT(ANGLE_INDEX(projectile->pitch + 0x6488 / 4)),
                              FixedPointMultiply12(SIN_AT(ANGLE_INDEX(projectile->heading)), COS_AT(ANGLE_INDEX(projectile->pitch + 0x6488 / 4))));
    VEC_CrossProduct_01ff9ea8(&rotation.row[0], &rotation.row[1], &rotation.row[2]);
    SetNodeRotation(&projectile->body->node, &rotation);
}
