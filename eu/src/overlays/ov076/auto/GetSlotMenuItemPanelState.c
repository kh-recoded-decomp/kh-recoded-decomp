#include "nitro/types.h"

extern u8 *gSlotMenuSharedState;

u32 GetSlotMenuItemPanelState(void)
{
    return *(const u32 *)(gSlotMenuSharedState + 0x28);
}
