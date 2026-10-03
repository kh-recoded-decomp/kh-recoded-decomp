#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    VecFx32 *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBounds;
} SweptShape;

typedef struct {
    u8 data[0x28];
} SegmentStorage;

typedef struct {
    u8 data[0x2c];
} CylinderStorage;

typedef struct {
    u8 pad_000[0x1a4];
} QueryWorkspace;

typedef struct {
    void (*func)(void);
    void *arg;
} QueryCallback;

typedef struct {
    u32 words[0x12];
    QueryCallback filter;
    QueryCallback callback;
    u32 tail[2];
} CollisionQuery;

typedef union {
    u32 raw;
    struct {
        u32 matchFlag : 1;
        u32 enabled : 1;
    } bits;
} SweepFilterArg;

typedef struct {
    u8 pad_00[8];
    fx32 width;
    fx32 depth;
} StageExtent;

typedef struct {
    u8 pad_00[4];
    fx32 floorY;
} StageFloor;

extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern CollisionShape func_0203adcc(SegmentStorage *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length);
extern CollisionShape func_0203aeac(CylinderStorage *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length, fx32 radius);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);
extern void *func_02036240(u16 actorId);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, void *filter);
extern void *SweepWorldCollision_020364a0(CollisionQuery *query);
extern s32 func_ov001_02063a38(void);
extern StageExtent *func_ov042_020bd590(void);
extern StageFloor *func_ov021_020af5b4(void);
extern void func_ov021_020a9230(void);
extern void func_ov021_020a9268(void);

#define FIXED_ABS(x) ((x) < 0 ? -(x) : (x))

void SweepDropToGround_020ae3f0(VecFx32 *out, u32 actorId, const VecFx32 *position, const VecFx32 *delta, fx32 radius, u32 matchFlag)
{
    CollisionQuery sweep;
    QueryWorkspace workspace;
    SweptShape sweptCopy;
    CollisionQuery segmentQuery;
    SweptShape swept;
    CollisionQuery cylinderQuery;
    VecFx32 start;
    VecFx32 end;
    VecFx32 result;
    SegmentStorage segment;
    CollisionShape segmentShape;
    CylinderStorage cylinder;
    VecFx32 dropDelta;
    CollisionShape segmentResult;
    VecFx32 segmentDiff;
    VecFx32 segmentAxis;
    VecFx32 cylinderAxis;
    VecFx32 cylinderDiff;
    CollisionShape cylinderShape;
    SweepFilterArg filterArg;
    QueryCallback segmentCallback;
    QueryCallback cylinderCallback;
    void *actor;
    fx32 lift;
    fx32 depth;

    start = *position;
    VEC_Add_01ff9e0c(&start, delta, &end);
    VEC_Subtract_01ff9e3c(&end, &start, &segmentDiff);
    segmentAxis = segmentDiff;
    segmentResult = func_0203adcc(&segment, &start, &end, &segmentAxis, func_01ffaff4(&segmentAxis, &segmentAxis));
    segmentShape = segmentResult;
    actor = func_02036240(actorId);
    CollisionQuery_Init_02034c74(&segmentQuery, 0, actor, 2, 1, 0, &segmentShape, &workspace, NULL);
    sweep = segmentQuery;
    segmentCallback.func = func_ov021_020a9230;
    segmentCallback.arg = NULL;
    sweep.callback = segmentCallback;
    if (SweepWorldCollision_020364a0(&sweep) != NULL) {
        start = segmentShape.data[1];
    } else {
        VEC_Add_01ff9e0c(position, delta, &start);
    }
    result = start;
    lift = 0x4000;
    depth = 0x18000;
    if (func_ov001_02063a38() == 4) {
        StageExtent *extent = func_ov042_020bd590();
        StageFloor *floor = func_ov021_020af5b4();

        lift = FIXED_ABS(extent->width);
        lift += floor->floorY - start.y;
        depth = FIXED_ABS(extent->width) + FIXED_ABS(extent->depth);
    }
    start.y += lift;
    end = start;
    end.y -= 0x19a;
    dropDelta.x = 0;
    dropDelta.y = -depth;
    dropDelta.z = 0;
    VEC_Subtract_01ff9e3c(&end, &start, &cylinderDiff);
    cylinderAxis = cylinderDiff;
    cylinderShape = func_0203aeac(&cylinder, &start, &end, &cylinderAxis, func_01ffaff4(&cylinderAxis, &cylinderAxis), radius);
    swept.shape = cylinderShape;
    swept.delta = dropDelta;
    OffsetBoxByDelta_0203ac70(&swept.shape.bounds, &swept.sweptBounds, &swept.delta);
    sweptCopy = swept;
    actor = func_02036240(actorId);
    CollisionQuery_Init_02034c74(&cylinderQuery, 0, actor, 9, 1, 1, &sweptCopy, &workspace, NULL);
    sweep = cylinderQuery;
    filterArg.raw = 0;
    filterArg.bits.matchFlag = matchFlag;
    filterArg.bits.enabled = 1;
    cylinderCallback.func = func_ov021_020a9268;
    cylinderCallback.arg = &filterArg;
    sweep.callback = cylinderCallback;
    if (SweepWorldCollision_020364a0(&sweep) != NULL) {
        result = sweptCopy.shape.data[1];
    } else {
        result.y -= depth;
    }
    *out = result;
}
