#include "nitro/types.h"

extern void ResetDisplayHardware_02029bfc(void);
extern void GX_SetBankForLCDC_02008a74(int bank);
extern void MIi_CpuClearFast_01ff8740(u32 data, void *dest, u32 size);
extern void func_02008ef4(void);
extern void GX_SetBankForBG_02008358(int bank);
extern void GX_SetBankForBGExtPltt_0200868c(int bank);
extern void GX_SetBankForOBJ_0200855c(int bank);
extern void GX_SetBankForOBJExtPltt_02008784(int bank);
extern void GX_SetGraphicsMode_020066c4(int dispMode, int bgMode, int bg0As);
extern void GX_SetBankForSubOBJ_02008b34(int bank);

#define REG_DISPCNT (*(vu32 *)0x04000000)

void SetupOverlayVramBanks_020c2df8(void)
{
    ResetDisplayHardware_02029bfc();
    GX_SetBankForLCDC_02008a74(0x1ff);
    MIi_CpuClearFast_01ff8740(0, (void *)0x06800000, 0xa4000);
    func_02008ef4();
    GX_SetBankForBG_02008358(8);
    GX_SetBankForBGExtPltt_0200868c(0);
    GX_SetBankForOBJ_0200855c(0x10);
    GX_SetBankForOBJExtPltt_02008784(0);
    REG_DISPCNT = (REG_DISPCNT & 0xffcfffef) | 0x100010;
    GX_SetGraphicsMode_020066c4(1, 0, 1);
    GX_SetBankForSubOBJ_02008b34(0x100);
}
