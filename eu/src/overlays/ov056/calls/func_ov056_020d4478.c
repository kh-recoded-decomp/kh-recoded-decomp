#include "nitro/types.h"

extern void UpdateSceneGroupEntries(void);
extern void AdvanceModelSlotAnimations(int target, u32 value);

void func_ov056_020d4478(int actor, u32 value)
{
    UpdateSceneGroupEntries();
    AdvanceModelSlotAnimations(actor + 0x18c, value);
}
