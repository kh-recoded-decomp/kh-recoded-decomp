#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef struct {
    u8 data[0x40];
} BoxStorage;

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

typedef struct {
    u32 mask;
    u32 flags;
} QueryFilter;

typedef struct {
    u8 pad_00[0xc8];
    u16 angle;
    u8 pad_ca[2];
    fx32 slopeX;
    fx32 slopeY;
    fx32 slopeZ;
} MotionState;

typedef struct {
    u8 pad_000[0x230];
    void *body;
    u8 pad_234[0x9b8 - 0x234];
    int character;
    u8 pad_9bc[0xa54 - 0x9bc];
    MotionState motion;
} ClearanceActor;

extern const s16 data_0205356c[];
extern void GetTableValuePair_020a91e8(s32 *outFirst, s32 *outSecond, int index);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sin, fx32 cos);
extern void MTX_RotX33_01ff9220(MtxFx33 *mtx, fx32 sin, fx32 cos);
extern void func_01ff9258(MtxFx33 *mtx, fx32 sin, fx32 cos);
extern void MTX_Concat33_01ff9270(const MtxFx33 *a, const MtxFx33 *b, MtxFx33 *out);
extern u16 FixedPointAtan2_020062bc(fx32 y, fx32 x);
extern void InitBoxShape_0203ad54(CollisionShape *shape, BoxStorage *storage, const VecFx32 *center, const VecFx32 *halfExtents, const MtxFx33 *rotation);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, QueryFilter *filter);
extern void *SweepWorldCollision_020364a0(CollisionQuery *query);
extern void func_ov021_020a9268(void);

BOOL IsLedgeClimbSpaceClear_020c9274(ClearanceActor *actor, VecFx32 *position)
{
    CollisionQuery sweep;
    QueryWorkspace workspace;
    CollisionShape shape;
    CollisionQuery headQuery;
    CollisionQuery bodyQuery;
    VecFx32 center;
    VecFx32 forward;
    BoxStorage storage;
    VecFx32 extent;
    MtxFx33 rotation;
    MtxFx33 tilt;
    CollisionShape headShape;
    CollisionShape bodyShape;
    QueryFilter filter;
    s32 height;
    s32 width;
    u32 hit;
    QueryFilter filterInit;
    QueryCallback headCallback;
    QueryCallback bodyCallback;
    int index;
    MotionState *motion = &actor->motion;
    u16 slope;

    forward.x = forward.y = forward.z = 0;
    index = motion->angle >> 4;
    forward.x = -data_0205356c[index];
    forward.z = -data_0205356c[(0x400 - index) & 0xfff];
    GetTableValuePair_020a91e8(&height, &width, actor->character);
    filterInit.mask = 0;
    filterInit.flags = 0x20;
    filter = filterInit;
    center = *position;
    center.y += height - 0x800;
    VEC_MultAdd_01ffa09c(0x100, &forward, &center, &center);
    extent.x = 0x700;
    extent.y = 0x1600;
    extent.z = 0x480;
    index = motion->angle >> 4;
    MTX_RotY33_01ff923c(&rotation, data_0205356c[index], data_0205356c[(0x400 - index) & 0xfff]);
    InitBoxShape_0203ad54(&headShape, &storage, &center, &extent, &rotation);
    shape = headShape;
    CollisionQuery_Init_02034c74(&headQuery, 3, actor->body, 0xf, 2, 0, &shape, &workspace, &filter);
    sweep = headQuery;
    hit = 0;
    headCallback.func = func_ov021_020a9268;
    headCallback.arg = &hit;
    sweep.callback = headCallback;
    if (SweepWorldCollision_020364a0(&sweep) != NULL) {
        return FALSE;
    }
    center = *position;
    center.y += height;
    VEC_MultAdd_01ffa09c(0x780, &forward, &center, &center);
    center.y += 0x800;
    extent.y = 0x600;
    extent.z = 0x900;
    extent.x = 0x700;
    if (motion->slopeZ != 0) {
        slope = FixedPointAtan2_020062bc(motion->slopeZ, motion->slopeY);
        MTX_RotX33_01ff9220(&tilt, data_0205356c[slope >> 4], data_0205356c[(0x400 - (slope >> 4)) & 0xfff]);
        MTX_Concat33_01ff9270(&rotation, &tilt, &rotation);
    }
    if (motion->slopeX != 0) {
        slope = FixedPointAtan2_020062bc(motion->slopeY, motion->slopeX);
        func_01ff9258(&tilt, -data_0205356c[(0x400 - (slope >> 4)) & 0xfff], data_0205356c[slope >> 4]);
        MTX_Concat33_01ff9270(&rotation, &tilt, &rotation);
    }
    InitBoxShape_0203ad54(&bodyShape, &storage, &center, &extent, &rotation);
    shape = bodyShape;
    CollisionQuery_Init_02034c74(&bodyQuery, 3, actor->body, 0xe, 2, 0, &shape, &workspace, &filter);
    sweep = bodyQuery;
    bodyCallback.func = func_ov021_020a9268;
    bodyCallback.arg = &hit;
    sweep.callback = bodyCallback;
    if (SweepWorldCollision_020364a0(&sweep) != NULL) {
        return FALSE;
    }
    return TRUE;
}
