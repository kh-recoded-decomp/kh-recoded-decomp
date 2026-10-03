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
    u8 data[0x28];
} SegmentStorage;

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
    u8 active;
    u8 pad_01[3];
    s32 unk04;
    VecFx32 anchor;
    VecFx32 prevAnchor;
    s16 heading;
    u8 pad_22[2];
    s32 arrived;
    s32 unk28;
    u8 pad_2c[0x3c - 0x2c];
    u8 model[0x778 - 0x3c];
    s16 slotGroups[3][4];
    s16 slots[4];
    u8 cameraPath[4];
} OverlayState;

extern OverlayState data_ov058_020d8a24;
extern const VecFx32 data_ov058_020d89a8;

extern void RotateOffsetAroundY_020a9160(VecFx32 *out, const VecFx32 *origin, u16 angle, const VecFx32 *offset);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern CollisionShape func_0203adcc(SegmentStorage *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, void *filter);
extern void *SweepWorldCollision_020364a0(CollisionQuery *query);
extern void func_ov021_020a9268(void);
extern void SettleAnchorOnGround_020d7054(fx32 step);
extern void SelectAnimationById_020ac8f4(void *model, int id);
extern void CameraPath_Start_020c2f44(void *path);
extern void func_ov058_020d720c(int mode);

void StartAnchorSequence_020d7f60(const VecFx32 *pos, s16 angle)
{
    CollisionQuery sweep;
    QueryWorkspace workspace;
    CollisionQuery query;
    VecFx32 offset;
    VecFx32 anchor;
    SegmentStorage segment;
    CollisionShape shape;
    VecFx32 top;
    VecFx32 end;
    VecFx32 dir;
    CollisionShape shapeResult;
    VecFx32 diff;
    VecFx32 axis;
    u32 filterArg;
    QueryCallback callback;
    OverlayState *state = &data_ov058_020d8a24;
    int heading;
    int i;
    int j;

    state->unk04 = 0;
    state->active = 1;
    state->arrived = 0;
    state->unk28 = 0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            state->slotGroups[i][j] = -1;
        }
    }
    for (i = 0; i < 4; i++) {
        state->slots[i] = -1;
    }
    heading = (u16)(angle + 0x8000);
    offset = data_ov058_020d89a8;
    RotateOffsetAroundY_020a9160(&anchor, pos, heading, &offset);
    top = *pos;
    top.y += 0x400;
    end = anchor;
    end.y = top.y;
    VEC_Subtract_01ff9e3c(&end, &top, &diff);
    axis = diff;
    shapeResult = func_0203adcc(&segment, &top, &end, &axis, func_01ffaff4(&axis, &axis));
    shape = shapeResult;
    CollisionQuery_Init_02034c74(&query, 7, NULL, 0xa, 1, 0, &shape, &workspace, NULL);
    sweep = query;
    filterArg = 0;
    callback.func = func_ov021_020a9268;
    callback.arg = &filterArg;
    sweep.callback = callback;
    if (SweepWorldCollision_020364a0(&sweep) != NULL) {
        VEC_Subtract_01ff9e3c(&shape.data[1], pos, &dir);
        func_01ff9f88(&dir, &dir);
        VEC_MultAdd_01ffa09c(0x800, &dir, pos, &anchor);
        anchor.y = pos->y;
    }
    state->anchor = anchor;
    state->heading = heading;
    SettleAnchorOnGround_020d7054(0x1000);
    SelectAnimationById_020ac8f4(state->model, -1);
    CameraPath_Start_020c2f44(state->cameraPath);
    func_ov058_020d720c(1);
}
