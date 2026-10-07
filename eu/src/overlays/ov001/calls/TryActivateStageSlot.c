#include "nitro/types.h"

extern s32 g_stageEventsState;
extern void ActivateStageSlot(u32 slotIndex);

void TryActivateStageSlot(u32 slotIndex)
{
    if (g_stageEventsState != -1) {
        ActivateStageSlot(slotIndex);
    }
}
