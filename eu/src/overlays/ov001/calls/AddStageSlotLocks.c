#include "src/overlays/ov001/StageSlotState.h"

extern StageSlotState *GetStageObjectHandle(u32 id);

void AddStageSlotLocks(u32 index, u32 mask)
{
    StageSlotState *slot;

    if (index < gStageSlotManager->slotCount) {
        slot = GetStageObjectHandle((u16)(index + 1));
        if (slot != NULL) {
            slot->lockMask |= (u8)mask;
            if (slot->state == 2) {
                slot->active = 0;
                slot->pending = 1;
            }
        }
    }
}
