#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct WaitTarget {
    u8 kind;
    u8 pad_01[3];
    struct SceneActor *target;
} WaitTarget;

typedef struct StateSlot {
    void *handler;
    int id;
    int timer;
} StateSlot;

typedef struct ActorControl {
    u64 flags;
    u8 pad_08[4];
    int linkKind;
    StateSlot slot;
} ActorControl;

typedef struct SceneActor SceneActor;
struct SceneActor {
    u8 pad_000[0x1f8];
    void (*onEvent)(SceneActor *actor, int event, int value);
    u8 pad_1fc[0x200 - 0x1fc];
    void (*onReset)(SceneActor *actor, int value);
    u8 pad_204[0x210 - 0x204];
    void (*setAngle)(SceneActor *actor, int angle);
    u8 pad_214[0x9ac - 0x214];
    ActorControl control;
    u8 pad_9c8[0xb2c - 0x9c8];
    u8 linkWork[4];
    u8 pad_b30[0x1048 - 0xb30];
    WaitTarget wait;
};

typedef struct SceneGlobals {
    u8 pad_0000[0x1258];
    unsigned int linkResult;
    SceneActor *target;
    u8 pad_1260[0x1274 - 0x1260];
    int selectedItem;
} SceneGlobals;

extern SceneGlobals *data_ov054_020d3700;

extern void AddSessionCounter_02063a80(int index, int amount);
extern void *SelectFallStateHandler_020d1238(SceneActor *actor, int *nextState);
extern BOOL ExitActorState_020ccfa4(SceneActor *actor, int cmd, int arg);
extern BOOL IsWaitTargetReady_0206c3a4(WaitTarget *target);
extern VecFx32 *func_ov052_020ceb54(SceneActor *actor);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern unsigned short FixedPointAtan2_020062bc(int vertical, int horizontal);
extern unsigned int func_ov021_020a81b8(void *work, unsigned int value, unsigned int *resultSlot);
extern u16 GetLinkedAngleOffset_020ceb7c(SceneActor *actor);
extern void StartAnchorSequence_020d7f60(VecFx32 *pos, u16 angle);
extern int func_ov001_0206dc38(void);
extern u32 GetBoundedEntryField_0206db5c(int index);
extern void TryRequestEnemyAction_020d64dc(u32 entry, int mode, int arg);
extern void PlaySoundChecked_0204d8d0(int id, int arg);
extern void func_ov001_0206df78(void);
extern void SetManagerEnabled_0206e160(u32 enabled);
extern int EnterActorState_020cd338(SceneActor *actor, int cmd);
extern int func_ov052_020d083c(SceneActor *actor, int cmd, int arg2, int arg3);
extern int UpdateRewardApproach_020d2f8c(SceneActor *actor, int cmd, int arg2, int arg3);
extern int UpdateRewardCharge_020d3078(SceneActor *actor, int cmd, int arg2, int arg3);
extern int ReleaseActiveDisplay_020d31b0(SceneActor *actor, int cmd, int arg2, int arg3);
extern int func_ov054_020d3230(SceneActor *actor, int cmd, int arg2, int arg3);

static inline int SetActorState(StateSlot *slot, void *handler, int id)
{
    slot->handler = handler;
    slot->id = id;
    slot->timer = 0;
    return id;
}

int HandleRewardActorCommand_020d2774(SceneActor *actor, int cmd)
{
    SceneGlobals *globals = data_ov054_020d3700;
    StateSlot *slot = &actor->control.slot;
    int result = slot->id;
    int i;
    int nextState;
    VecFx32 targetPos;
    VecFx32 diff;

    switch (cmd) {
    case 0x20:
        switch (globals->selectedItem) {
        case 0xb7:
        case 0xb8:
        case 0xbb:
        case 0xbc:
        case 0xbd:
            AddSessionCounter_02063a80(5, 1);
            break;
        }
        if (SelectFallStateHandler_020d1238(actor, &nextState)) {
            void *handler;
            if (nextState != 2) {
                handler = UpdateRewardApproach_020d2f8c;
            } else {
                handler = func_ov052_020d083c;
            }
            slot->handler = handler;
            slot->id = nextState;
            slot->timer = 0;
            return slot->id;
        }
        if (actor->onEvent != NULL) {
            actor->onEvent(actor, 0x1e, -1);
        }
        result = SetActorState(slot, UpdateRewardCharge_020d3078, 0x19);
        break;
    case 0x1e:
        if (ExitActorState_020ccfa4(actor, cmd, 0)) {
            break;
        }
        if (!IsWaitTargetReady_0206c3a4(&actor->wait)) {
            break;
        }
        if (actor->wait.kind != 4) {
            break;
        }
        globals->target = actor->wait.target;
        targetPos = *func_ov052_020ceb54(globals->target);
        VEC_Subtract_01ff9e3c(&targetPos, func_ov052_020ceb54(actor), &diff);
        {
            int angle = (u16)(FixedPointAtan2_020062bc(diff.x, diff.z) + 0x8000);
            if (actor->setAngle != NULL) {
                actor->setAngle(actor, (u16)angle);
            }
        }
        if (globals->target->control.linkKind == 1) {
            func_ov021_020a81b8(actor->linkWork, 3, &globals->linkResult);
        } else if (globals->target->control.linkKind == 2) {
            func_ov021_020a81b8(actor->linkWork, 4, &globals->linkResult);
        }
        if (actor->onEvent != NULL) {
            actor->onEvent(actor, 0x15, -1);
        }
        result = SetActorState(slot, ReleaseActiveDisplay_020d31b0, 0x1e);
        break;
    case 0x1f:
        if (ExitActorState_020ccfa4(actor, cmd, 0)) {
            break;
        }
        StartAnchorSequence_020d7f60(func_ov052_020ceb54(actor), GetLinkedAngleOffset_020ceb7c(actor));
        for (i = 1; i < func_ov001_0206dc38(); i++) {
            TryRequestEnemyAction_020d64dc(GetBoundedEntryField_0206db5c(i), 3, 0);
        }
        actor->control.flags &= ~0x400090ULL;
        actor->control.flags |= 0x1000000;
        if (actor->onEvent != NULL) {
            actor->onEvent(actor, 0x16, -1);
        }
        result = SetActorState(slot, func_ov054_020d3230, 0x18);
        PlaySoundChecked_0204d8d0(0xc2, 2);
        if (actor->onReset != NULL) {
            actor->onReset(actor, 0);
        }
        func_ov001_0206df78();
        AddSessionCounter_02063a80(3, 1);
        SetManagerEnabled_0206e160(1);
        break;
    default:
        result = EnterActorState_020cd338(actor, cmd);
        break;
    }
    return result;
}

