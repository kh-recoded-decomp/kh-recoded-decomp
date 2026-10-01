#include "nitro/types.h"

typedef struct EventActor {
    u8 pad_000[0x1d0];
    u16 eventMode;
    u16 eventId;
    u8 pad_1D4[0xa4];
    void *eventTarget;
} EventActor;

typedef struct EventTrigger {
    u8 pad_00[0xd];
    u8 actorId;
} EventTrigger;

extern EventActor *GetStageActor_0209c040(int id);
extern u32 func_ov001_0209c584(u32 mask);
extern s32 *GetStageEventRecord_0209c0ec(u32 id);
extern BOOL IsCommandType8_02096224(s32 *type);
extern void func_ov001_02093eec(s32 *record);

void TryTriggerActorEvent_0209256c(EventTrigger *trigger, BOOL busy)
{
    EventActor *actor = GetStageActor_0209c040(trigger->actorId);
    s32 *record;

    if (actor == NULL || actor->eventTarget == NULL) {
        return;
    }
    if (func_ov001_0209c584(1 << 30) != 0 || busy) {
        return;
    }
    if (actor->eventMode != 1) {
        return;
    }
    record = GetStageEventRecord_0209c0ec(actor->eventId);
    if (record == NULL || IsCommandType8_02096224(record)) {
        return;
    }
    func_ov001_02093eec(record);
}
