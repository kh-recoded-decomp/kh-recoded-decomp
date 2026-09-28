#include "nitro/types.h"

extern void GX_VRAMCNT_SetLCDC__020082c0(int lcdc);
extern u16 data_02056f48;

void GX_SetBankForLCDC_02008a74(int bank)
{
    u16 mask = (u16)bank;
    data_02056f48 = (u16)(data_02056f48 | mask);
    GX_VRAMCNT_SetLCDC__020082c0(bank);
}
