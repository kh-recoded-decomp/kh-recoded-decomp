#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SlotPosition {
    VecFx32 position;
    u32 extra[2];
} SlotPosition;

typedef struct WaitSubject {
    u8 pad_00[0xbc];
    VecFx32 position;
} WaitSubject;

typedef struct WaitTarget {
    u8 kind;
    u8 pad_01[3];
    union {
        struct {
            u16 eventId;
            u16 slot;
        } event;
        int entry;
        WaitSubject *subject;
    } u;
    VecFx32 position;
} WaitTarget;

extern int IsStageEventReady_02087c78(u32 id);
extern BOOL StageRecord_GetSlotPosition_02087c4c(u32 id, u32 slot, SlotPosition *outPosition);
extern VecFx32 *func_ov001_0207f870(int entry);
extern VecFx32 *func_ov001_020863f4(int entry);

VecFx32 *GetWaitTargetPosition_0206c3f4(WaitTarget *target)
{
    SlotPosition slot;
    VecFx32 *source;

    switch (target->kind) {
    case 1:
        if (IsStageEventReady_02087c78(target->u.event.eventId)) {
            StageRecord_GetSlotPosition_02087c4c(target->u.event.eventId, target->u.event.slot, &slot);
            target->position = slot.position;
        }
        break;
    case 2:
        source = func_ov001_0207f870(target->u.entry);
        if (source != NULL) {
            target->position = *source;
        }
        break;
    case 3:
        source = func_ov001_020863f4(target->u.entry);
        if (source != NULL) {
            target->position = *source;
        }
        break;
    case 4:
        source = &target->u.subject->position;
        if (source != NULL) {
            target->position = *source;
        }
        break;
    }
    return &target->position;
}
