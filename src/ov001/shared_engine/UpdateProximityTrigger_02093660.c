#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ProximityCommand {
    u8 pad_00[0x4];
    u16 unk_04_0 : 1;
    u16 playerOutOfRange : 1;
    u16 unk_04_2 : 4;
    u16 keepMotion : 1;
    u16 unk_04_7 : 9;
    u8 pad_06[0x9 - 0x6];
    u8 kind;
    u8 pad_0a[0x10 - 0xa];
    s16 groupId;
    u16 targetId;
} ProximityCommand;

typedef struct TriggerTarget {
    u16 paramIndex;
    u8 pad_02[0x18 - 0x2];
    u32 alwaysOutOfRange;
    VecFx32 position;
} TriggerTarget;

typedef struct TriggerParams {
    u8 pad_00[0x14];
    u32 tracksPlayer;
    u8 pad_18[0x28 - 0x18];
    fx32 activationRadius;
    fx32 playerRadius;
} TriggerParams;

typedef struct StageManager {
    u8 pad_00000[0x18e5c];
    fx32 minActivationHeight;
} StageManager;

typedef struct ActorModel {
    u8 pad_00[0x5c];
    s32 currentMotion;
} ActorModel;

typedef struct ScriptRunner {
    u16 targetKind;
    u16 targetId;
} ScriptRunner;

typedef struct TriggerActor {
    u8 pad_000[0x90];
    u16 savedAngle;
    u8 pad_092[0xb8 - 0x92];
    VecFx32 savedPosition;
    u8 pad_0c4[0x1d0 - 0xc4];
    ScriptRunner runner;
    u8 pad_1d4[0x1e0 - 0x1d4];
    ActorModel *model;
    u8 pad_1e4[0x248 - 0x1e4];
    s32 motionId;
    s32 idleMotion;
    u8 pad_250[0x288 - 0x250];
    u16 unk_288_0 : 5;
    u16 resetMotionTimer : 1;
    u16 unk_288_6 : 10;
    u16 moveMode : 2;
    u16 unk_28A_2 : 14;
    u16 unk_28C_0 : 11;
    u16 zone : 3;
    u16 unk_28C_14 : 2;
    u8 pad_28e[0x29c - 0x28e];
    u32 motionTimer;
    u8 pad_2a0[0x2c0 - 0x2a0];
    VecFx32 position;
    u8 pad_2cc[0x2e6 - 0x2cc];
    u16 angle;
    u8 pad_2e8[0x3a4 - 0x2e8];
    u16 unk_3A4;
    u8 pad_3a6[2];
    u16 unk_3A8;
} TriggerActor;

extern TriggerActor *func_ov001_0209c040(s16 groupId);
extern TriggerTarget *GetStageObjectHandle_0209c0c4(u32 id);
extern TriggerParams *GetLargeTableEntry_0209c30c(u32 index);
extern u32 func_ov001_0209c584(u32 mask);
extern void func_ov001_0209c59c(u32 mask);
extern StageManager *func_ov001_0209c3c0(void);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern u16 func_ov001_02099328(VecFx32 *position);
extern TriggerActor *func_ov001_0209c2f0(TriggerActor *member);
extern void func_ov001_02098fbc(int playerIndex, VecFx32 *position);
extern void func_ov021_020b4b7c(ScriptRunner *runner);
extern void ClearActorMotionState_02091194(TriggerActor *actor);
extern u16 RunGroupScriptSlot_020925d8(TriggerActor *leader, int slot);

int UpdateProximityTrigger_02093660(ProximityCommand *command)
{
    TriggerActor *actor = func_ov001_0209c040(command->groupId);
    TriggerTarget *target = GetStageObjectHandle_0209c0c4(command->targetId);
    TriggerParams *params = GetLargeTableEntry_0209c30c(target->paramIndex);
    u32 wasOutOfRange = command->playerOutOfRange;
    VecFx32 delta;
    TriggerActor *member;
    VecFx32 playerPosition;

    if (func_ov001_0209c584(1)) {
        if (!func_ov001_0209c584(0x40)) {
            actor->savedPosition = actor->position;
            actor->savedAngle = actor->angle;
            if (command->kind != 4) {
                func_ov001_0209c59c(0x10);
            } else {
                func_ov001_0209c59c(0x20);
            }
            return 9;
        }
        return 0;
    }
    if (func_ov001_0209c584(1)) {
        return 0;
    }
    if (params->activationRadius != 0) {
        StageManager *manager = func_ov001_0209c3c0();

        if (manager != NULL && manager->minActivationHeight != 0 &&
            manager->minActivationHeight > actor->position.y) {
            return 6;
        }
        VEC_Subtract_01ff9e3c(&target->position, &actor->position, &delta);
        if (VEC_Mag_01ff9f28(&delta) > params->activationRadius) {
            return 6;
        }
    }
    member = actor;
    if (actor->zone == 0) {
        u16 zone = func_ov001_02099328(&actor->position);

        for (; member != NULL; member = func_ov001_0209c2f0(member)) {
            member->zone = zone;
        }
    }
    if (actor->motionId != -1 && params->tracksPlayer != 0 &&
        (command->playerOutOfRange || actor->idleMotion == actor->model->currentMotion)) {
        func_ov001_02098fbc(1, &playerPosition);
        VEC_Subtract_01ff9e3c(&playerPosition, &actor->position, &delta);
        delta.y = 0;
        command->playerOutOfRange = VEC_Mag_01ff9f28(&delta) > params->playerRadius;
        if (target->alwaysOutOfRange != 0) {
            command->playerOutOfRange = 1;
        }
        if (command->playerOutOfRange != wasOutOfRange) {
            func_ov021_020b4b7c(&actor->runner);
            ClearActorMotionState_02091194(actor);
            if (command->playerOutOfRange) {
                actor->unk_3A4 = 0;
                actor->unk_3A8 = 0;
            } else if (!command->keepMotion) {
                actor->moveMode = 1;
                actor->unk_3A4 = 0;
                actor->unk_3A8 = 0xffff;
            }
        }
    }
    if (command->playerOutOfRange) {
        if (actor->resetMotionTimer) {
            actor->motionTimer = 0;
        }
        RunGroupScriptSlot_020925d8(actor, 2);
    } else {
        RunGroupScriptSlot_020925d8(actor, 3);
    }
    return 0;
}
