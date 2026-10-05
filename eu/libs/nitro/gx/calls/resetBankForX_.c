#include "libs/nitro/gx/gx_state_internal.h"

extern void GX_VRAMCNT_SetLCDC_(u32 banks);

int resetBankForX_(u16 *assignment)
{
    int banks = *assignment;

    *assignment = 0;
    gGXState.vram.lcdc |= (u16)banks;
    GX_VRAMCNT_SetLCDC_(banks);
    return banks;
}
