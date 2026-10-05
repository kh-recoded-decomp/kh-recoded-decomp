#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x6c];
    s32 kind;
} ContactObject;

typedef struct {
    ContactObject *object;
    s32 type;
    s32 pad_08;
} Contact;

typedef struct {
    Contact entries[32];
    u8 count;
} ContactList;

typedef struct {
    u8 pad_00[8];
    fx32 damping;
    u8 pad_0c[0x12];
    s16 tilt;
    u8 pad_20[0x24];
} DragMotion;

typedef struct {
    u8 pad_00[0xce];
    s16 animId;
} ActorModel;

typedef struct {
    fx32 bonus[2];
} SpeedBonusTable;

typedef struct DragActor DragActor;

struct DragActor {
    u8 pad_000[0x1f0];
    void (*onDrop)(DragActor *actor, int a, int b, int c);
    u8 pad_1f4[4];
    void (*onMoved)(DragActor *actor, int result, int extra);
    u8 pad_1fc[0x210 - 0x1fc];
    void (*onTurn)(DragActor *actor, u16 yaw);
    u8 pad_214[0x230 - 0x214];
    ActorModel *model;
    u32 moveFlags;
    u8 pad_238[0x344 - 0x238];
    ContactList contactList;
    u8 pad_4c8[0x75c - 0x4c8];
    s32 state;
    u8 pad_760[0x768 - 0x760];
    s32 motionActive;
    u8 pad_76c[0x9ac - 0x76c];
    u64 flags;
    u8 entryId;
    u8 pad_9b5[0x9c8 - 0x9b5];
    VecFx32 offset;
    u8 pad_9d4[0x9ec - 0x9d4];
    s32 tiltSpeed;
    u8 pad_9f0[0xa10 - 0x9f0];
    DragMotion motion;
    u8 pad_a54[0xb2c - 0xa54];
    u8 grabState[0x10ec - 0xb2c];
    void (*setState)(DragActor *actor, int state);
};

extern SpeedBonusTable data_ov030_020bcf44;
extern void *func_ov001_0206db78(int index);
extern int UpdateActorReactionState_020bbe00(DragActor *actor, DragMotion *motion);
extern BOOL AlarmCallback_020a7504(void *entry);
extern fx32 func_ov052_020d0e80(DragMotion *motion);
extern BOOL IsPlayerEntryFlagSet_02050014(int entryId, int flag);
extern int GetPlayerEntryCount_02050050(int entryId, int flag);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern void ApplyTimeScaledSpeed_020c7d28(DragActor *actor, fx32 scale);
extern int func_ov052_020cebbc(DragActor *actor, VecFx32 *dir);
extern VecFx32 *func_ov042_020bd324(void);
extern void ResetIfIdMatches_020a8178(void *state, int id);

void UpdateDraggedActorState_020bb5a0(DragActor *actor)
{
    VecFx32 dir;
    SpeedBonusTable table;
    void *entry = func_ov001_0206db78(actor->entryId);
    int result = -1;
    BOOL found;
    fx32 speed;
    fx32 bonus;
    int yaw;
    DragMotion *motion;
    VecFx32 *drift;
    int i;
    ContactList *list;
    int count;
    Contact *contact;

    if (actor->flags & 0x400000) {
        actor->setState(actor, 9);
        return;
    }
    if (actor->flags & 0x80) {
        actor->setState(actor, 8);
        return;
    }
    if (!(actor->moveFlags & 4)) {
        if (actor->offset.y > 0) {
            actor->flags |= 0x1000;
            actor->setState(actor, 3);
            return;
        }
        actor->setState(actor, 4);
        return;
    }
    if (UpdateActorReactionState_020bbe00(actor, &actor->motion)) {
        return;
    }
    dir.z = 0;
    dir.y = 0;
    dir.x = 0;
    if (AlarmCallback_020a7504(entry)) {
        speed = func_ov052_020d0e80(&actor->motion);
        if (IsPlayerEntryFlagSet_02050014(0, 0x10)) {
            table = data_ov030_020bcf44;
            bonus = table.bonus[GetPlayerEntryCount_02050050(0, 0x10) - 1];
            speed += FixedPointMultiply12(speed, bonus);
            ApplyTimeScaledSpeed_020c7d28(actor, bonus + 0x1000);
        }
        yaw = func_ov052_020cebbc(actor, &dir);
        dir.x = FixedPointMultiply12(dir.x, speed);
        dir.z = FixedPointMultiply12(dir.z, speed);
        if (actor->onTurn != NULL) {
            actor->onTurn(actor, yaw);
        }
        result = 1;
        actor->offset.x += dir.x;
        actor->offset.z += dir.z;
    } else {
        motion = &actor->motion;
        drift = func_ov042_020bd324();
        motion->damping = 0;
        found = FALSE;
        if (drift->x > 0) {
            list = &actor->contactList;
            count = list->count;
            for (i = 0; i < count; i++) {
                contact = &list->entries[i];
                if (contact->type == 4 && contact->object->kind == 3) {
                    found = TRUE;
                    break;
                }
            }
        }
        if (!found) {
            motion->tilt += (s16)actor->tiltSpeed;
            if (motion->tilt >= 0x2000) {
                result = 0;
                ApplyTimeScaledSpeed_020c7d28(actor, 0x1000);
                if (actor->state != 0) {
                    actor->flags |= 0x2000000;
                }
            }
        } else {
            result = 1;
            if (actor->onTurn != NULL) {
                actor->onTurn(actor, 0x8000);
            }
        }
    }
    if (result != -1 && actor->onMoved != NULL) {
        actor->onMoved(actor, result, -1);
    }
    if (result == 1 && actor->motionActive != 0) {
        ResetIfIdMatches_020a8178(actor->grabState, 1);
    }
    if ((actor->flags & 0x2000000) && actor->state == 0 && actor->model->animId == -1) {
        if (actor->onDrop != NULL) {
            actor->onDrop(actor, 4, 4, 0);
        }
        actor->flags &= ~0x2000000;
    }
}
