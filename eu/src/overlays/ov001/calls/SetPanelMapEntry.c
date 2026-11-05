#include "nitro/types.h"

extern u32 IsPanelMapUpdateAllowed();
extern void PrepareMenuScreenEntry(u32 x, u32 y);

extern u32 data_ov001_020a04e8;

void SetPanelMapEntry(u32 x, u32 y)
{
    s32 panel;
    u32 ready;

    panel = data_ov001_020a04e8;
    *(u32 *)(data_ov001_020a04e8 + 0x50) = x;
    *(u32 *)(panel + 0x54) = y;
    ready = IsPanelMapUpdateAllowed();
    if (ready != 0) {
        PrepareMenuScreenEntry(x, y);
    }
}
