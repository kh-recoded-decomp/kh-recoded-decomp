#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SlotPosition {
    VecFx32 position;
    u32 extra[2];
} SlotPosition;

extern VecFx32 *func_ov001_0206dc4c(int context);
extern int IsStageEventReady_02087c78(u32 id);
extern BOOL StageRecord_GetSlotPosition_02087c4c(u16 eventId, u16 slot, SlotPosition *outPosition);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);

BOOL IsEventSlotInRange_0206b800(int context, int eventId, int slot, fx32 range)
{
    VecFx32 *origin = func_ov001_0206dc4c(context);
    SlotPosition slotPosition;

    if (!IsStageEventReady_02087c78((u16)eventId)) {
        return FALSE;
    }
    if (!StageRecord_GetSlotPosition_02087c4c(eventId, slot, &slotPosition)) {
        return FALSE;
    }
    if (func_01ffa0f4(&slotPosition.position, origin) > range) {
        return FALSE;
    }
    return TRUE;
}
