#pragma opt_propagation off
#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u32 count;
    u32 stride;
    u8 *items;
} LinkArray;

typedef struct {
    u8 pad_00[0x84];
    LinkArray paths;
    u8 pad_90[0x54];
    LinkArray slots;
} LinkTable;

typedef struct {
    u8 pad_00[8];
    LinkTable *table;
} LinkData;

typedef struct {
    u32 pad_00;
    LinkData *data;
} StageLink;

typedef struct {
    u32 pathIndex;
} LinkSlot;

typedef struct {
    u32 pad_00;
    s32 nodeNameIndex;
    VecFx32 offset;
    u8 pad_14[0x10];
    s32 objectId;
    s32 spawnArg;
} LinkPath;

typedef struct {
    u8 pad_00[0xe];
    u16 kind;
    s16 actorId;
} StageEvent;

typedef struct {
    u8 pad_00[0xc];
    s16 actorId;
} StageController;

typedef struct {
    u16 pad_00;
    u16 objectId;
    u16 spawnArg;
    u8 pad_06[0xa];
} SpawnParams;

typedef struct {
    u8 pad_000[0xac];
    VecFx32 up;
    u8 pad_0b8[0x1b4];
    u32 moveFlags : 31;
    u32 moveFlag31 : 1;
    u16 spawnArg;
    u8 pad_272[0xe];
    u16 animId;
    u8 pad_282[8];
    u16 moveMode : 2;
    u16 pad_bits : 3;
    u16 moveState : 3;
    u16 rest : 8;
    u8 pad_28c[0x2c];
    s32 moveSpeed;
    u8 pad_2bc[4];
    VecFx32 position;
    u8 pad_2cc[0x1a];
    u16 yaw;
    u16 prevYaw;
    u16 pitch;
    u16 prevPitch;
    u8 pad_2ee[0xba];
    u16 motionId;
} StageActor;

typedef struct {
    u8 pad_00[0x18edc];
    VecFx32 targetPos;
    VecFx32 direction;
    u8 pad_18ef4[0x10];
    fx32 speed;
    s32 actorSpeed;
    s32 turnLimit;
    u8 pad_18f10[0xc];
    u16 aimMode;
    u8 pad_18f1e[2];
    s32 pitchDeg;
    s32 yawDeg;
} LinkMoveManager;

typedef struct {
    u16 pad_00;
    u16 animId;
    u16 motionId;
    u8 pad_06[2];
    VecFx32 target;
    u8 pad_14[0xc];
    s32 frames;
    s32 extra;
    fx32 moveSpeed;
} LinkMoveCommand;

extern const s16 data_0205356c[];

extern LinkMoveManager *func_ov001_0209c3c0(void);
extern StageLink *FindStageLink_02099584(u32 id);
extern void func_01ff8830(void *dst, int value, u32 size);
extern int SpawnStageObjectActor_02096ae0(StageEvent *record, SpawnParams *params, VecFx32 *position);
extern StageActor *GetStageActor_0209c040(int id);
extern StageController *GetStageController_0209c120(u32 id);
extern void SetActorGridCell_0209191c(StageActor *actor, int column, int row);
extern const char *func_ov001_0208f018(LinkData *data, int index);
extern u16 FindActorResourceIndexByName_02091248(StageActor *actor, const char *name);
extern void GetNodePosition_02091600(StageActor *owner, u32 nodeId, VecFx32 *out);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_NormalizeUnchecked_01ff9f88(const VecFx32 *input, VecFx32 *output);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern fx32 VEC_Normalize_01ffaff4(const VecFx32 *source, VecFx32 *destination);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern int FixedPointMultiply12(int left, int right);
extern void func_01ff90ec(MtxFx33 *mtx);
extern void MTX_RotX33_01ff9220(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_Concat33_01ff9270(const MtxFx33 *a, const MtxFx33 *b, MtxFx33 *ab);
extern void VecToYawPitch_0209d3c4(VecFx32 *dir, u16 *pitch, u16 *yaw);
extern void WarpWalkerTo_02090f0c(StageActor *walker, const VecFx32 *position);
extern void BeginWalkerMove_020910c4(StageActor *walker, const VecFx32 *target, int frames, int extra);
extern void UpdateActorController_020980fc(StageController *controller);

static inline u32 GetSlotCount(StageLink *link)
{
    if (link == NULL) {
        return 0;
    }
    if (link->data == NULL) {
        return 0;
    }
    return link->data->table->slots.count;
}

static inline LinkSlot *GetLinkSlot(StageLink *link, u16 index)
{
    u32 count;
    LinkData *data;
    LinkTable *table;
    u8 *items;
    if (link == NULL) {
        return NULL;
    }
    data = link->data;
    if (data == NULL) {
        return NULL;
    }
    count = GetSlotCount(link);
    table = data->table;
    items = table->slots.items;
    if (count == 0) {
        return NULL;
    }
    if (index >= count) {
        return NULL;
    }
    return (LinkSlot *)(items + index * table->slots.stride);
}

static inline u32 GetPathCount(StageLink *link)
{
    if (link == NULL) {
        return 0;
    }
    if (link->data == NULL) {
        return 0;
    }
    return link->data->table->paths.count;
}

static inline LinkPath *GetLinkPath(StageLink *link, u16 index)
{
    u32 count;
    LinkData *data;
    LinkTable *table;
    u8 *items;
    if (link == NULL) {
        return NULL;
    }
    data = link->data;
    if (data == NULL) {
        return NULL;
    }
    count = GetPathCount(link);
    table = data->table;
    items = table->paths.items;
    if (count == 0) {
        return NULL;
    }
    if (index >= count) {
        return NULL;
    }
    return (LinkPath *)(items + index * table->paths.stride);
}

void MoveLinkedActor_020afda8(StageEvent *record, int unused, s16 column, s16 row, LinkMoveCommand *cmd)
{
    LinkMoveManager *manager = func_ov001_0209c3c0();
    int spawned;
    StageActor *owner;
    StageController *controller;
    StageLink *link;
    int frames;
    int extra;
    int pitch;
    u16 mode;
    int pitchIndex;
    LinkSlot *slot;
    LinkPath *path;
    StageActor *actor;
    const char *nodeName;
    int yaw;
    int yawIndex;
    fx32 dist;
    fx32 limit;
    SpawnParams params;
    MtxFx33 rotX;
    MtxFx33 rotY;
    MtxFx33 rot;
    VecFx32 aim;
    VecFx32 offset;
    VecFx32 dir;
    VecFx32 up;
    VecFx32 side;
    VecFx32 start;
    VecFx32 end;
    VecFx32 delta;

    link = FindStageLink_02099584(record->kind);
    if (link == NULL) {
        return;
    }
    slot = GetLinkSlot(link, column);
    if (slot == NULL) {
        return;
    }
    path = GetLinkPath(link, slot->pathIndex);
    if (path == NULL) {
        return;
    }
    func_01ff8830(&params, 0, sizeof(SpawnParams));
    params.objectId = path->objectId;
    params.spawnArg = path->spawnArg;
    spawned = SpawnStageObjectActor_02096ae0(record, &params, NULL);
    if (spawned == 0) {
        return;
    }
    owner = GetStageActor_0209c040(record->actorId);
    if (owner == NULL) {
        return;
    }
    controller = GetStageController_0209c120(spawned);
    if (controller == NULL) {
        return;
    }
    actor = GetStageActor_0209c040(controller->actorId);
    if (actor == NULL) {
        return;
    }
    SetActorGridCell_0209191c(actor, column, row);
    if (path->nodeNameIndex != 0) {
        nodeName = func_ov001_0208f018(link->data, path->nodeNameIndex);
        if (nodeName != NULL) {
            GetNodePosition_02091600(owner, FindActorResourceIndexByName_02091248(owner, nodeName), &actor->position);
            VEC_Add_01ff9e0c(&path->offset, &actor->position, &actor->position);
        }
    }
    mode = manager->aimMode;
    switch (mode) {
    case 0:
        cmd->target = manager->targetPos;
        if (manager->speed != 0) {
            VEC_Subtract_01ff9e3c(&cmd->target, &actor->position, &aim);
            VEC_NormalizeUnchecked_01ff9f88(&aim, &aim);
            VEC_MultAdd_01ffa09c(manager->speed, &aim, &actor->position, &cmd->target);
        }
        break;
    case 1:
        VEC_MultAdd_01ffa09c(manager->speed, &manager->direction, &actor->position, &cmd->target);
        break;
    case 2:
    case 3:
        pitch = (u16)(((s64)manager->pitchDeg * 0xb60b60b60bLL + 0x80000000000LL) >> 44);
        yaw = (u16)(((s64)manager->yawDeg * 0xb60b60b60bLL + 0x80000000000LL) >> 44);
        if (mode == 3) {
            pitch += owner->pitch;
            yaw += owner->yaw;
        }
        pitchIndex = (pitch + 0xffff) % 0xffff;
        yawIndex = (yaw + 0xffff) % 0xffff;
        func_01ff90ec(&rotX);
        func_01ff90ec(&rotY);
        MTX_RotX33_01ff9220(&rotX, data_0205356c[pitchIndex >> 4], data_0205356c[(0x400 - (pitchIndex >> 4)) & 0xfff]);
        MTX_RotY33_01ff923c(&rotY, data_0205356c[yawIndex >> 4], data_0205356c[(0x400 - (yawIndex >> 4)) & 0xfff]);
        MTX_Concat33_01ff9270(&rotX, &rotY, &rot);
        VEC_MultAdd_01ffa09c(manager->speed, (VecFx32 *)rot.m[2], &actor->position, &cmd->target);
        break;
    }
    if (cmd->motionId != 0) {
        actor->motionId = cmd->motionId;
        actor->moveState |= 1;
        actor->moveFlags |= 0x10;
        actor->moveMode = 1;
    }
    frames = cmd->frames;
    extra = cmd->extra;
    actor->moveSpeed = manager->actorSpeed;
    if (frames == 0 && cmd->moveSpeed != 0) {
        VEC_Subtract_01ff9e3c(&cmd->target, &actor->position, &offset);
        frames = FX_Div_01ff9c84(VEC_Mag_01ff9f28(&offset), cmd->moveSpeed);
        extra = 0;
    }
    VEC_Subtract_01ff9e3c(&cmd->target, &actor->position, &dir);
    if (VEC_Mag_01ff9f28(&dir) != 0) {
        dist = VEC_Mag_01ff9f28(&dir);
        VEC_NormalizeUnchecked_01ff9f88(&dir, &dir);
        if (manager->turnLimit != 0) {
            limit = FixedPointMultiply12(dist, data_0205356c[(u16)(((s64)manager->turnLimit * 0xb60b60b60bLL + 0x80000000000LL) >> 44) >> 4]);
            up = owner->up;
            VEC_Normalize_01ffaff4(&up, &up);
            VEC_MultAdd_01ffa09c(dist, &up, &actor->position, &start);
            VEC_NormalizeUnchecked_01ff9f88(&dir, &side);
            VEC_MultAdd_01ffa09c(dist, &side, &actor->position, &end);
            VEC_MultAdd_01ffa09c(FixedPointMultiply12(0x1000 - VEC_DotProduct_01ff9e6c(&up, &side), dist), &up, &end, &end);
            VEC_Subtract_01ff9e3c(&end, &start, &delta);
            if (VEC_Mag_01ff9f28(&delta) > limit) {
                VEC_NormalizeUnchecked_01ff9f88(&delta, &side);
                VEC_MultAdd_01ffa09c(limit, &side, &start, &cmd->target);
                VEC_Subtract_01ff9e3c(&cmd->target, &actor->position, &dir);
                VEC_NormalizeUnchecked_01ff9f88(&dir, &dir);
            } else {
                cmd->target = end;
            }
        }
        VecToYawPitch_0209d3c4(&dir, &actor->pitch, &actor->yaw);
        actor->prevPitch = actor->pitch;
        actor->prevYaw = actor->yaw;
    }
    WarpWalkerTo_02090f0c(actor, &actor->position);
    BeginWalkerMove_020910c4(actor, &cmd->target, frames, extra);
    actor->spawnArg = params.spawnArg;
    if (cmd->animId != 0) {
        actor->animId = cmd->animId;
    }
    UpdateActorController_020980fc(controller);
}
