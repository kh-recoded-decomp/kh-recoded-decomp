#include "nitro/types.h"

extern u8 *data_ov001_020a04e8;

u32 GetPanelInputActive(void)
{
    return *(const u32 *)(data_ov001_020a04e8 + 0x40);
}
