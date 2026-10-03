#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 active : 1;
    u8 airborne : 1;
    u8 flagsHigh : 6;
    u8 phase;
    u16 timer;
    VecFx32 origin;
    VecFx32 velocity;
    fx32 scale;
    int angle;
} LaunchMotion;

typedef struct {
    u8 pad_00[0x8c];
    int count;
    s8 alpha[16];
    s8 fade[16];
} WanderDef;

typedef struct {
    u8 pad_00[0x8];
    WanderDef *def;
    u8 pad_0c[0x2c];
    u8 actorId;
    u8 pad_39;
    u8 index;
    u8 pad_3b[0x5];
    VecFx32 position;
    u8 pad_4c[0x2];
    u16 drawFlags;
    u8 pad_50[0x8];
    VecFx32 drawPosition;
    LaunchMotion motion[2];
    s16 heading;
    u8 facing;
    s8 state;
    u8 flags;
    u8 pad_b1;
    s8 mode;
    u8 pad_b3;
    u16 waitId;
} WanderObject;

typedef struct EventTargetInfo {
    u16 header;
    u16 kind;
    u16 pad_04[2];
    VecFx32 position;
    s32 width;
    s32 height;
    s32 displayWidth;
    s32 displayHeight;
} EventTargetInfo;

typedef struct StageObject StageObject;

typedef struct {
    u8 pad_00[0x30];
    BOOL (*isBusy)(StageObject *object);
} StageObjectVtable;

struct StageObject {
    u32 unk_00;
    StageObjectVtable *vtable;
    u8 pad_08[0x30];
    VecFx32 position;
};

extern const VecFx32 data_02053438;
extern BOOL func_ov001_02063838(void);
extern void func_ov007_020a0908(WanderObject *object);
extern BOOL StageEvents_CheckEvent_02087824(u16 eventIndex);
extern int func_ov001_0208775c(int objectIndex, u32 entryIndex);
extern BOOL GetStageEventTargetInfo_02087960(u16 id, EventTargetInfo *out);
extern int func_ov035_020bafb4(void);
extern StageObject *func_ov001_02087224(u32 group, u32 index);
extern void StartLaunchMotion_020a0e58(WanderObject *object, const VecFx32 *velocity);
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable);
extern BOOL func_ov007_020a098c(WanderObject *owner, const VecFx32 *from, const VecFx32 *delta, VecFx32 *out);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern BOOL StepBounceBody_020a0afc(WanderObject *owner, LaunchMotion *motion);
extern BOOL SteerHomingParticle_020a0b84(WanderObject *owner, LaunchMotion *motion);
extern BOOL StepHomingBounceBody_020a0d24(WanderObject *owner, LaunchMotion *motion);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

BOOL UpdateWanderActor_020a1118(WanderObject *object)
{
    WanderDef *def = object->def;
    int i;

    if (object->index == 0) {
        for (i = 0; i < def->count; i++) {
            if (def->fade[i] & 1) {
                def->alpha[i] += 4;
                if (def->alpha[i] >= 0x1f) {
                    def->alpha[i] = 0x1f;
                    def->fade[i] &= ~1;
                }
            } else if (def->fade[i] & 2) {
                def->alpha[i] -= 4;
                if (def->alpha[i] <= 0) {
                    def->alpha[i] = 0;
                    def->fade[i] &= ~2;
                }
            }
        }
    }
    if (object->state == 6) {
        return FALSE;
    }
    if (!func_ov001_02063838() && object->state == 0) {
        func_ov007_020a0908(object);
    }
    switch (object->state) {
    case 1: {
        BOOL found = FALSE;
        VecFx32 dest;
        EventTargetInfo info;

        if (object->mode == 2) {
            if (StageEvents_CheckEvent_02087824(object->waitId)) {
                dest = object->motion[0].origin;
                found = TRUE;
            } else {
                GetStageEventTargetInfo_02087960(func_ov001_0208775c(object->waitId, 0), &info);
                object->motion[0].origin = info.position;
                object->motion[0].origin.y += 0x800;
            }
        } else if (object->mode == 1) {
            StageObject *target = func_ov001_02087224(func_ov035_020bafb4(), object->waitId);
            BOOL busy;

            if (target->vtable->isBusy == NULL) {
                busy = FALSE;
            } else {
                busy = target->vtable->isBusy(target);
            }
            if (busy) {
                dest = target->position;
                found = TRUE;
                dest.y += 0xc00;
            }
        } else if (object->mode == 3 && object->waitId != 0) {
            StartLaunchMotion_020a0e58(object, &object->motion[1].velocity);
            ActorSlot_SetFlag8ByIndex_02036120(object->actorId, TRUE);
            object->motion[0].active = FALSE;
            object->motion[0].airborne = FALSE;
            goto step_motion;
        }
        if (!found) {
            break;
        }
        object->motion[0].active = TRUE;
        object->motion[0].airborne = TRUE;
        object->motion[0].origin = dest;
        object->motion[0].velocity.y = 0x400;
        object->state = 0;
        object->flags |= 1;
        object->position = dest;
        object->drawPosition = dest;
        object->drawFlags &= ~0x10;
        ActorSlot_SetFlag8ByIndex_02036120(object->actorId, TRUE);
        break;
    }
    case 0:
        if (!(object->flags & 1)) {
            VecFx32 hit;
            VecFx32 down = MakeVec(0, -0x64000, 0);

            func_ov007_020a098c(object, &object->motion[0].origin, &down, &hit);
            if (hit.y < object->motion[0].origin.y) {
                object->flags |= 1;
                object->drawFlags &= ~0x10;
            }
        }
        if (object->flags & 1) {
            object->motion[0].velocity.y -= 0x7b;
        }
        if (VEC_Mag_01ff9f28(&object->motion[0].velocity) > 0 && !StepBounceBody_020a0afc(object, &object->motion[0])) {
            object->flags &= ~1;
            object->drawFlags |= 0x10;
        }
        break;
    case 2:
    case 4:
    step_motion:
        if (object->motion[0].active && SteerHomingParticle_020a0b84(object, &object->motion[0])) {
            object->motion[0].active = FALSE;
            object->motion[0].airborne = FALSE;
            object->motion[0].velocity = data_02053438;
        }
        if (object->motion[1].active) {
            if (!StepHomingBounceBody_020a0d24(object, &object->motion[1])) {
                object->motion[1].velocity.y -= 0x7b;
            } else {
                object->motion[1].active = FALSE;
                object->motion[1].velocity = data_02053438;
            }
        }
        if (!object->motion[0].active && !object->motion[1].active) {
            object->state++;
        }
        break;
    case 5:
        object->state = 0;
        object->drawFlags |= 0x10;
        object->motion[0].active = TRUE;
        object->motion[0].origin = object->motion[1].origin;
        object->motion[0].scale = 0x1000;
        object->motion[0].angle = 0;
        object->motion[0].airborne = TRUE;
        object->motion[1].airborne = FALSE;
        break;
    case 3:
        object->state = 6;
        ActorSlot_SetFlag8ByIndex_02036120(object->actorId, FALSE);
        break;
    }
    return FALSE;
}
