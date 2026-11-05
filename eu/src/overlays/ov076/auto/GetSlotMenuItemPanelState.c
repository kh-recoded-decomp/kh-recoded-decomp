#include "nitro/types.h"

extern u8 *data_ov076_020cd400;

u32 GetSlotMenuItemPanelState(void)
{
    return *(const u32 *)(data_ov076_020cd400 + 0x28);
}
