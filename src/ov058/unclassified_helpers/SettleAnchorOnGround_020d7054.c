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
    u8 data[0x2c];
} CapsuleStorage;

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
    u8 pad_00[8];
    VecFx32 anchor;
    VecFx32 prevAnchor;
} OverlayState;

extern OverlayState data_ov058_020d8a24;
extern u8 data_ov058_020d8a60[];

extern void AdvanceModelAnimation_020ac9a4(void *model, fx32 step, VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern CollisionShape InitCapsuleShape_0203ae34(CapsuleStorage *capsule, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length, fx32 radius);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, void *filter);
extern void *SweepWorldCollision_020364a0(CollisionQuery *query);
extern void func_ov021_020a94b0(void);

void SettleAnchorOnGround_020d7054(fx32 step)
{
    CollisionQuery sweep;
    QueryWorkspace workspace;
    CollisionQuery query;
    VecFx32 motion;
    CapsuleStorage capsule;
    CollisionShape shape;
    VecFx32 top;
    VecFx32 bottom;
    VecFx32 offset;
    CollisionShape shapeResult;
    VecFx32 diff;
    VecFx32 axis;
    QueryCallback callback;
    OverlayState *state = &data_ov058_020d8a24;

    AdvanceModelAnimation_020ac9a4(data_ov058_020d8a60, step, &motion);
    state->prevAnchor = state->anchor;
    bottom = state->anchor;
    top = bottom;
    top.y += 0xe66;
    VEC_Subtract_01ff9e3c(&bottom, &top, &diff);
    axis = diff;
    shapeResult = InitCapsuleShape_0203ae34(&capsule, &top, &bottom, &axis, func_01ffaff4(&axis, &axis), 0xccd);
    shape = shapeResult;
    CollisionQuery_Init_02034c74(&query, 7, NULL, 0xf, 0, 0, &shape, &workspace, NULL);
    sweep = query;
    callback.func = func_ov021_020a94b0;
    callback.arg = NULL;
    sweep.callback = callback;
    if (SweepWorldCollision_020364a0(&sweep) == NULL) {
        return;
    }
    offset.z = 0;
    offset.y = 0;
    offset.x = 0;
    VEC_Subtract_01ff9e3c(&shape.data[1], &state->anchor, &offset);
    if (VEC_Mag_01ff9f28(&offset) > 0x400) {
        func_01ffaff4(&offset, &offset);
        VEC_MultAdd_01ffa09c(0x400, &offset, &state->anchor, &state->anchor);
    } else {
        VEC_Add_01ff9e0c(&offset, &state->anchor, &state->anchor);
    }
}
