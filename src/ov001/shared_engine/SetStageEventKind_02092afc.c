#include "nitro/types.h"

typedef struct StageActor StageActor;

typedef struct StageEvent {
    u8 pad_000[0xc];
    u8 kind;
    u8 pad_00d[3];
    s16 actorId;
    u8 pad_012[0x1a4 - 0x12];
    int progress;
    int speed;
    int elapsed;
} StageEvent;

extern void AddSessionCounter_02063a80(int index, int amount);
extern void func_ov001_02091ac0(StageActor *actor, u32 firstId, u32 secondId, int flags);
extern void ClearActorGroupFlagsAndNotify_02092ad0(StageEvent *event);
extern StageActor *GetStageActor_0209c040(int id);
extern StageActor *GetLinkedStageActor_0209c2f0(StageActor *actor);

void SetStageEventKind_02092afc(StageEvent *event, u32 kind)
{
    StageActor *actor;

    if (kind != 0 && event->kind == kind) {
        return;
    }
    event->kind = kind;
    event->progress = 0;
    event->elapsed = 0;
    event->speed = 1;
    if (kind == 2) {
        event->speed = 0x4000;
    }
    if (kind == 9) {
        event->speed = 0x2000;
    }
    if (kind == 4) {
        event->speed = 0x4000;
    }
    if (kind == 9 || kind == 2 || kind == 7 || kind == 4 || kind == 8) {
        ClearActorGroupFlagsAndNotify_02092ad0(event);
    }
    for (actor = GetStageActor_0209c040(event->actorId); actor != NULL; actor = GetLinkedStageActor_0209c2f0(actor)) {
        func_ov001_02091ac0(actor, 0xffff, 0xffff, 0);
    }
    switch (kind) {
    case 1:
        AddSessionCounter_02063a80(0x15, 1);
        break;
    case 2:
        AddSessionCounter_02063a80(0x16, 1);
        break;
    case 3:
        AddSessionCounter_02063a80(0x17, 1);
        break;
    case 4:
        AddSessionCounter_02063a80(0x18, 1);
        break;
    }
}
