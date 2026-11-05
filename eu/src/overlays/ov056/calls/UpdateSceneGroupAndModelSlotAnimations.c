#include "nitro/types.h"

extern void UpdateSceneGroupEntries(void);
extern void AdvanceModelSlotAnimations(int target, u32 value);

void UpdateSceneGroupAndModelSlotAnimations(int actor, u32 value)
{
    UpdateSceneGroupEntries();
    AdvanceModelSlotAnimations(actor + 0x18c, value);
}
