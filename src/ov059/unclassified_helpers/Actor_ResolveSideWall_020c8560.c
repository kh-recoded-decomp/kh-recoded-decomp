#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Box {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct CollisionShape {
    VecFx32 *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct SweptShape {
    CollisionShape shape;
    VecFx32 offset;
    Box swept;
} SweptShape;

typedef struct SegmentStorage {
    VecFx32 hit;
    u8 pad_0c[0x28 - 0xc];
} SegmentStorage;

typedef struct QueryWorkspace {
    u8 pad_000[0x1a4];
} QueryWorkspace;

typedef struct QueryCallback {
    void *func;
    void *arg;
} QueryCallback;

typedef struct QueryFilter {
    s32 mask;
    s32 kind;
} QueryFilter;

typedef struct SweepContext {
    s32 hit;
    QueryFilter filter;
} SweepContext;

typedef struct FilterTemplate {
    s32 unused;
    QueryFilter filter;
} FilterTemplate;

typedef struct CollisionQuery {
    u32 words[9];
    SweptShape *shape;
    u8 pad_28[0x3c - 0x28];
    u8 unk3C;
    u8 unk3D;
    u8 pad_3e[0x48 - 0x3e];
    QueryCallback filter;
    QueryCallback callback;
    u32 tail[2];
} CollisionQuery;

typedef struct Actor {
    u8 pad_000[0x230];
    void *model;
} Actor;

extern VecFx32 *Actor_GetModelPosition_020cd0d8(Actor *actor);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Normalize_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern CollisionShape InitAxisCylinderShape_0203adcc(SegmentStorage *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, QueryFilter *filter);
extern void *SweepWorldCollision_020364a0(CollisionQuery *query);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);
extern void SetShapePosition_0203afa0(SweptShape *shape, const VecFx32 *position);
extern void func_ov059_020c8548(void);
extern void func_ov059_020c8558(void);

void Actor_ResolveSideWall_020c8560(Actor *actor, VecFx32 *delta)
{
    QueryWorkspace workspace;
    CollisionQuery sweep;
    SweptShape probe;
    CollisionQuery query;
    SweptShape side;
    SegmentStorage segment;
    VecFx32 start;
    VecFx32 end;
    CollisionShape shape;
    SegmentStorage sideSegment;
    VecFx32 rise;
    VecFx32 moved;
    VecFx32 riseTemplate;
    VecFx32 raised;
    CollisionShape shapeResult;
    VecFx32 diff;
    VecFx32 axis;
    VecFx32 sideOffset;
    VecFx32 sideAxis;
    VecFx32 sideDiff;
    CollisionShape sideResult;
    VecFx32 otherOffset;
    SweepContext context;
    FilterTemplate filterTemplate;
    QueryCallback filterCallback;
    QueryCallback hitCallback;
    fx32 best;
    fx32 shift;
    fx32 distance;

    VEC_Add_01ff9e0c(Actor_GetModelPosition_020cd0d8(actor), delta, &moved);
    start = moved;
    riseTemplate.x = 0;
    riseTemplate.y = 0xa000;
    riseTemplate.z = 0;
    rise = riseTemplate;
    VEC_Add_01ff9e0c(&start, &rise, &raised);
    end = raised;
    VEC_Subtract_01ff9e3c(&end, &start, &diff);
    axis = diff;
    shapeResult = InitAxisCylinderShape_0203adcc(&segment, &start, &end, &axis, VEC_Normalize_01ffaff4(&axis, &axis));
    shape = shapeResult;
    filterTemplate.filter.mask = 0;
    filterTemplate.filter.kind = 0x11;
    context.filter = filterTemplate.filter;
    CollisionQuery_Init_02034c74(&query, 0, actor->model, 8, 0, 0, &shape, &workspace, &context.filter);
    sweep = query;
    context.hit = 0;
    filterCallback.func = func_ov059_020c8548;
    filterCallback.arg = NULL;
    sweep.filter = filterCallback;
    hitCallback.arg = &context.hit;
    hitCallback.func = func_ov059_020c8558;
    sweep.callback = hitCallback;
    if (SweepWorldCollision_020364a0(&sweep) != NULL || context.hit != 0) {
        return;
    }
    sideOffset.x = 0xa000;
    sideOffset.y = 0;
    sideOffset.z = 0;
    best = 0x7fffffff;
    VEC_Subtract_01ff9e3c(&end, &start, &sideDiff);
    sideAxis = sideDiff;
    sideResult = InitAxisCylinderShape_0203adcc(&sideSegment, &start, &end, &sideAxis, VEC_Normalize_01ffaff4(&sideAxis, &sideAxis));
    side.shape = sideResult;
    side.offset = sideOffset;
    OffsetBoxByDelta_0203ac70(&side.shape.bounds, &side.swept, &side.offset);
    probe = side;
    sweep.shape = &probe;
    sweep.unk3D = 1;
    sweep.unk3C = 1;
    sweep.callback.func = NULL;
    if (SweepWorldCollision_020364a0(&sweep) != NULL) {
        shift = sideSegment.hit.x - start.x;
        best = shift < 0 ? -shift : shift;
    }
    SetShapePosition_0203afa0(&probe, &start);
    OffsetBoxByDelta_0203ac70(&probe.shape.bounds, &probe.swept, &probe.offset);
    otherOffset.x = -0xa000;
    otherOffset.y = 0;
    otherOffset.z = 0;
    probe.offset = otherOffset;
    OffsetBoxByDelta_0203ac70(&probe.shape.bounds, &probe.swept, &probe.offset);
    if (SweepWorldCollision_020364a0(&sweep) != NULL) {
        fx32 other = sideSegment.hit.x - start.x;

        distance = other < 0 ? -other : other;
        if (distance < best) {
            shift = other;
            best = distance;
        }
    }
    if (best != 0x7fffffff) {
        delta->x += shift;
    } else {
        delta->x = 0;
    }
}
