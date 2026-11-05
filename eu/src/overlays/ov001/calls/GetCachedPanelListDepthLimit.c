#include "nitro/types.h"

extern u32 data_ov001_020a04e8;

u8 GetCachedPanelListDepthLimit(void)
{
    return *(u8 *)(data_ov001_020a04e8 + 0x102);
}
