#include "nitro/types.h"

typedef struct ControllerOwner {
    u8 pad_00[0xd];
    u8 actorId;
} ControllerOwner;

typedef struct ControlledActor {
    u8 pad_000[0x1d0];
    u16 controlMode;
    u16 controllerIndex;
    u8 pad_1d4[0x278 - 0x1d4];
    void *controlData;
} ControlledActor;

extern ControlledActor *func_ov001_0209c040(s16 actorId);
extern u32 func_ov001_0209c584(u32 mask);
extern u8 *GetStageEventRecord_0209c0ec(u32 id);
extern void func_ov001_02094714(u8 *eventRecord);

void UpdateActorStageEvent_0209252c(ControllerOwner *owner)
{
    ControlledActor *actor = func_ov001_0209c040(owner->actorId);
    u8 *eventRecord;

    if (actor != NULL && actor->controlData != NULL && func_ov001_0209c584(0x40000000) == 0 &&
        actor->controlMode == 1) {
        eventRecord = GetStageEventRecord_0209c0ec(actor->controllerIndex);
        if (eventRecord != NULL) {
            func_ov001_02094714(eventRecord);
        }
    }
}
