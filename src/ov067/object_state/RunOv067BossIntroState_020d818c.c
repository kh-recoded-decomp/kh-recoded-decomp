#include "nitro/types.h"

typedef struct Actor Actor;
typedef void (*ActorStateFunc)(Actor *actor);

typedef struct {
    ActorStateFunc func;
    int id;
    int arg;
} ActorState;

typedef struct {
    u8 pad_00[0xe4];
    ActorState saved;
    u8 pad_f0[4];
    int phase;
} BossObject;

struct Actor {
    u8 pad_000[0x1f8];
    void (*notify)(Actor *actor, int arg1, int arg2);
    u8 pad_1fc[0x234 - 0x1fc];
    u32 modeFlags;
    u8 pad_238[0x9b4 - 0x238];
    u8 player;
    u8 pad_9b5[7];
    ActorState state;
    u8 pad_9c8[0xa51 - 0x9c8];
    u8 dashLocked;
    u8 pad_a52[0xb2c - 0xa52];
    u8 sound[0x1078 - 0xb2c];
    BossObject *boss;
    u8 pad_107c[0x10ec - 0x107c];
    void (*setMode)(Actor *actor, int mode);
};

extern void *func_ov001_0206db78(int player);
extern BOOL func_ov001_02072040(void);
extern BOOL UpdateIdleTimeout_0206e1c8(void);
extern u16 GetId10_020a755c(void *unit);
extern int GetFieldAt0x12_020a7560(void *unit);
extern BOOL CameraPath_ConsumeSkipRequest_020c2fd4(void);
extern void RestartScriptSound_020a818c(void *sound, int arg);
extern void ApplyTimeScaledSpeed_020c7d28(Actor *actor, int speed);
extern void func_ov052_020d1170(Actor *actor, int arg);
extern void func_ov056_020d33f8(Actor *actor);
void RunOv067BossIntroState_020d818c(Actor *actor);

void RunOv067BossIntroState_020d818c(Actor *actor)
{
    BossObject *boss = actor->boss;
    void *unit = func_ov001_0206db78(actor->player);
    u32 hasMode;

    switch (boss->phase) {
    default:
        boss->phase = 0;
        return;
    case 0:
        return;
    case 1:
        hasMode = actor->modeFlags & 4;
        actor->state.id = 0;
        if (hasMode) {
            actor->setMode(actor, 1);
            if (actor->notify != NULL) {
                actor->notify(actor, 0, -1);
            }
        } else {
            actor->setMode(actor, 4);
        }
        boss->saved = actor->state;
        boss->phase = 2;
    case 2:
        if (func_ov001_02072040() && !UpdateIdleTimeout_0206e1c8()) {
            if (GetId10_020a755c(unit) == 5 && GetFieldAt0x12_020a7560(unit) == 4) {
                boss->phase = 3;
            }
        } else {
            boss->phase = 4;
        }
        break;
    case 3:
        boss->phase = 0;
        CameraPath_ConsumeSkipRequest_020c2fd4();
        RestartScriptSound_020a818c(actor->sound, 0);
        ApplyTimeScaledSpeed_020c7d28(actor, 0x1000);
        actor->dashLocked = 0;
        func_ov052_020d1170(actor, 0);
        actor->state.func = func_ov056_020d33f8;
        actor->state.id = 0x18;
        actor->state.func(actor);
        return;
    case 4:
        switch (boss->saved.id) {
        case 0xb:
            actor->state.func = boss->saved.func;
            actor->state.id = 0x18;
            actor->state.func(actor);
            return;
        case 0xc:
            goto resume;
        }
        if (actor->modeFlags & 4) {
            actor->setMode(actor, 1);
            if (actor->notify != NULL) {
                actor->notify(actor, 0, -1);
            }
        } else {
            actor->setMode(actor, 4);
        }
        return;
    }
resume:
    actor->state.id = boss->saved.id;
    boss->saved.func(actor);
    if (actor->boss != NULL) {
        if (boss->saved.id != actor->state.id) {
            boss->saved = actor->state;
        }
        actor->state.func = RunOv067BossIntroState_020d818c;
        actor->state.id = 0x18;
    }
}
