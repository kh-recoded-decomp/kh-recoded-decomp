#include "src/overlays/ov001/StageSlotState.h"

extern StageSlotState *GetStageObjectHandle(u32 id);
extern void SpawnStageEventGroups(StageSlotState *slot);

void ReleaseStageSlotLocks(u32 index, u32 mask)
{
    StageSlotState *slot;

    if (index < gStageSlotManager->slotCount) {
        slot = GetStageObjectHandle((u16)(index + 1));
        if (slot != NULL) {
            slot->lockMask &= (u8)~mask;
            if (slot->lockMask == 0 && slot->state == 6) {
                SpawnStageEventGroups(slot);
                slot->state = 2;
                slot->released = 1;
            }
        }
    }
}
