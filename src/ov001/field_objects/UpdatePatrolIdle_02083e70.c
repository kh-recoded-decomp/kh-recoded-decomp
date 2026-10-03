#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef int (*PatrolStateFunc)(void *object);

typedef struct PatrolModel {
    u8 pad_00[0x14];
    u16 anim[1];
} PatrolModel;

typedef struct PatrolObject {
    u8 pad_00[0x0c];
    PatrolModel *model;
    u8 pad_10[0x04];
    PatrolStateFunc state;
    u8 pad_18[0x20];
    u8 actorId;
    u8 pad_39[0x07];
    VecFx32 position;
    u8 pad_4c[0x0c];
    s32 moving;
    fx32 idleTime;
    u8 pad_60[0x04];
    VecFx32 heading;
    VecFx32 up;
    u8 pad_7c[0x05];
    s8 visits;
    u8 paused;
} PatrolObject;

extern BOOL DetachFromLeaderQuadTree_020836d8(PatrolObject *object);
extern int Anim_GetFrame_0202f4a0(u16 *anim, int index);
extern u32 SpawnSoundSlot_0204da8c(u32 owner, u32 kind, VecFx32 *position, u32 flags);
extern u32 func_ov001_02063a4c(void);
extern void UpdateFieldPointActivation_02083dbc(PatrolObject *object);
extern BOOL ActorSlot_IsFlag8SetByIndex_02036164(int index);
extern signed char GetCtxModeByte_02068084(void);
extern int func_ov001_02083f9c(void *object);
extern void ChooseNextPatrolPoint_02083c68(PatrolObject *object);
extern void SetSavedValueFlag7_02084750(PatrolObject *object, int flag);
extern void SetPackedStateLowBit_02084774(PatrolObject *object, u16 lowBit);
extern void func_0204b1fc(VecFx32 *current, const VecFx32 *target, fx32 rate);
extern void func_ov001_02083d2c(PatrolObject *object);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

int UpdatePatrolIdle_02083e70(PatrolObject *object)
{
    int frame;
    fx32 limit;
    VecFx32 flat;
    VecFx32 up;

    if (DetachFromLeaderQuadTree_020836d8(object)) {
        frame = (Anim_GetFrame_0202f4a0(object->model->anim, 0) >> 12) - 1;
        if (frame == 3 || frame == 14 || frame == 26 || frame == 39) {
            SpawnSoundSlot_0204da8c(0xe7, 4, &object->position, 2);
        }
    }
    if (func_ov001_02063a4c() != 4 || object->paused != 0) {
        if (func_ov001_02063a4c() != 4 && object->paused != 0) {
            object->paused = 0;
        }
        SetSavedValueFlag7_02084750(object, 0);
        SetPackedStateLowBit_02084774(object, 0);
    } else {
        UpdateFieldPointActivation_02083dbc(object);
        if (ActorSlot_IsFlag8SetByIndex_02036164(object->actorId) && object->idleTime != 0x7fffffff) {
            object->idleTime += FX32_ONE;
            if (GetCtxModeByte_02068084() == 7) {
                limit = 0x96000;
            } else {
                limit = 0x12c000;
            }
            if (object->idleTime >= limit) {
                object->moving = 1;
                object->state = func_ov001_02083f9c;
                object->visits++;
                ChooseNextPatrolPoint_02083c68(object);
            }
        }
    }
    flat = object->heading;
    flat.y = 0;
    func_0204b1fc(&object->heading, &flat, 0x595);
    up = MakeVec(0, FX32_ONE, 0);
    func_0204b1fc(&object->up, &up, 0x595);
    func_ov001_02083d2c(object);
    return 0;
}
