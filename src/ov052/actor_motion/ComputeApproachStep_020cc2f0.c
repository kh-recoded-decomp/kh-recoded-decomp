#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_00[8];
    VecFx32 position;
    u8 pad_14[0x24 - 0x14];
} EventTargetInfo;

typedef struct {
    VecFx32 position;
    fx32 width;
    fx32 depth;
} SlotPosition;

typedef struct {
    VecFx32 offset;
    fx32 radius;
} SlotShape;

typedef struct {
    u8 pad_00[0x22];
    u8 kind : 3;
    u8 pad_23;
    SlotShape shape;
    u8 pad_34[0x54 - 0x34];
} MotionSlot;

typedef struct {
    u8 pad_00[0x28];
    int noClamp;
    int noLift;
    u8 pad_30[0xc];
    u32 flags;
    s16 slotIndex;
    u8 pad_42[2];
    MotionSlot *slots;
    u8 pad_48[4];
    u16 pad_bits : 4;
    u16 noPull : 1;
} MotionState;

typedef struct {
    u8 kind;
    u8 pad_01[3];
    u16 eventId;
    u16 slotId;
} WaitTarget;

typedef struct {
    u8 pad_0000[0x2878];
    u32 pad_bits : 20;
    u32 autoFace : 1;
} GameState;

typedef struct Actor Actor;
typedef void (*TurnCallback)(Actor *actor, u16 angle);
typedef int (*QueryCallback)(Actor *actor, int arg);

struct Actor {
    u8 pad_0000[0x210];
    TurnCallback onTurn;
    u8 pad_0214[0x228 - 0x214];
    QueryCallback isApproaching;
    u8 pad_022c[0x9b4 - 0x22c];
    u8 player;
    u8 pad_09b5[0x9c4 - 0x9b5];
    int power;
    u8 pad_09c8[0xa04 - 0x9c8];
    fx32 height;
    u8 pad_0a08[0x1048 - 0xa08];
    WaitTarget wait;
};

extern GameState *data_0205fe0c;
extern s16 data_0205356c[];
extern void *func_ov001_0206db78(int player);
extern BOOL func_ov021_020a7504(void *unit);
extern u16 func_ov021_020a7544(void *unit);
extern u16 FixedPointAtan2_020062bc(fx32 y, fx32 x);
extern VecFx32 *GetWaitTargetPosition_0206c3f4(WaitTarget *wait);
extern VecFx32 *func_ov052_020ceb54(Actor *actor);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern u16 GetLinkedAngleOffset_020ceb7c(Actor *actor);
extern BOOL GetStageEventTargetInfo_02087960(u32 id, EventTargetInfo *out);
extern BOOL StageRecord_GetSlotPosition_02087c4c(u32 id, u32 slot, SlotPosition *out);
extern void ScaleVecFx32_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec33_01ff9404(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

VecFx32 ComputeApproachStep_020cc2f0(Actor *actor, VecFx32 *input, MotionState *motion, BOOL adjust)
{
    int slotOffset;
    MotionSlot *slots;
    VecFx32 original;
    BOOL faced;
    VecFx32 dir;
    EventTargetInfo info;
    SlotPosition slotPos;
    VecFx32 offset;
    VecFx32 move;
    VecFx32 rotated;
    MtxFx33 rotation;
    VecFx32 result;
    int facing;
    fx32 distance;
    VecFx32 *selfPos;
    VecFx32 *targetPos;
    int index;

    slots = motion->slots;
    slotOffset = motion->slotIndex * sizeof(MotionSlot);
    original = *input;
    faced = FALSE;
    if (data_0205fe0c->autoFace && actor->power <= 0x2000) {
        void *unit = func_ov001_0206db78(actor->player);
        if (func_ov021_020a7504(unit)) {
            int heading = func_ov021_020a7544(unit);
            u16 turn;
            dir.x = -data_0205356c[heading >> 4];
            dir.z = -data_0205356c[(0x400 - (heading >> 4)) & 0xfff];
            turn = FixedPointAtan2_020062bc(dir.x, dir.z) + 0x8000;
            if (actor->onTurn != NULL) {
                actor->onTurn(actor, turn);
            }
            faced = TRUE;
        }
    }
    if ((actor->isApproaching != NULL ? actor->isApproaching(actor, 0) : 0) == 0 || faced) {
        return original;
    }
    targetPos = GetWaitTargetPosition_0206c3f4(&actor->wait);
    selfPos = func_ov052_020ceb54(actor);
    VEC_Subtract_01ff9e3c(targetPos, selfPos, &dir);
    dir.y = 0;
    distance = func_01ffaff4(&dir, &dir);
    if (actor->power <= 0x2000) {
        u16 turn = FixedPointAtan2_020062bc(dir.x, dir.z) + 0x8000;
        if (actor->onTurn != NULL) {
            actor->onTurn(actor, turn);
        }
    }
    facing = GetLinkedAngleOffset_020ceb7c(actor);
    if (((MotionSlot *)((u8 *)slots + slotOffset))->kind != 0 || !(motion->flags & 8)) {
        return original;
    }
    if (actor->wait.kind == 1 && GetStageEventTargetInfo_02087960(actor->wait.eventId, &info)
        && StageRecord_GetSlotPosition_02087c4c(actor->wait.eventId, actor->wait.slotId, &slotPos)) {
        fx32 half = slotPos.width / 2;
        if (half < distance) {
            distance -= half;
        }
    }
    {
        SlotShape *shape = &((MotionSlot *)((u8 *)slots + slotOffset))->shape;
        fx32 radius;
        fx32 reach;
        u16 moveAngle;
        fx32 lift;

        move = *input;
        ScaleVecFx32_01ffafb4(FX32_ONE, &move, &move);
        result = move;
        offset = shape->offset;
        radius = shape->radius;
        index = facing >> 4;
        MTX_RotY33_01ff923c(&rotation, -data_0205356c[index], -data_0205356c[(0x400 - index) & 0xfff]);
        MTX_MultVec33_01ff9404(&offset, &rotation, &rotated);
        lift = 0;
        rotated.y = 0;
        reach = radius + VEC_Mag_01ff9f28(&rotated);
        if (reach > distance) {
            fx32 scaled;
            moveAngle = FixedPointAtan2_020062bc(rotated.x, rotated.z) + 0x8000;
            index = (u16)((u16)(FixedPointAtan2_020062bc(dir.x, dir.z) + 0x8000) - moveAngle) >> 4;
            MTX_RotY33_01ff923c(&rotation, data_0205356c[index], data_0205356c[(0x400 - index) & 0xfff]);
            MTX_MultVec33_01ff9404(&move, &rotation, &move);
            if (adjust && motion->noLift == 0) {
                fx32 gap = targetPos->y - (actor->height + move.y);
                fx32 limit = actor->height - selfPos->y;
                if (gap > limit) {
                    lift = 0x100;
                } else if (gap < -limit) {
                    lift = -0x100;
                }
                move.y += lift;
            }
            if (adjust && !motion->noPull) {
                ScaleVecFx32_01ffafb4(FixedPointMultiply12(FX32_ONE, 0x100), &dir, &dir);
                VEC_Add_01ff9e0c(&dir, &move, &move);
            }
            scaled = FixedPointMultiply12(reach, FX32_ONE);
            result = move;
            if (motion->noClamp == 0 && (VEC_Mag_01ff9f28(&move) > distance || scaled > distance)) {
                result.z = 0;
                result.x = 0;
            }
        } else if (adjust && !motion->noPull) {
            ScaleVecFx32_01ffafb4(FixedPointMultiply12(FX32_ONE, 0x100), &dir, &dir);
            VEC_Add_01ff9e0c(&dir, &move, &move);
            result = move;
        }
    }
    return result;
}
