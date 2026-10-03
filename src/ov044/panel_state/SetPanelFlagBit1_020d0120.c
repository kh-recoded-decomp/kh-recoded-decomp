#include "nitro/types.h"

extern u32 g_panel_020d0ea0;

void SetPanelFlagBit1_020d0120(BOOL enable)
{
    u32 panel = g_panel_020d0ea0;

    if (enable) {
        *(u32 *)(panel + 0x38) |= 2;
    } else {
        *(u32 *)(panel + 0x38) &= ~2;
    }
}
