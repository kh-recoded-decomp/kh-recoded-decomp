#include "nitro/types.h"

#define REG_DISP3DCNT (*(vu16 *)0x04000060)

extern void ResetDisplayHardware_02029bfc(void);
extern void GX_SetBankForTex_02008820(int bank);
extern void GX_BeginLoadOBJExtPltt_02008998(int bank);
extern void NNS_GfdInitFrmTexVramManager_0201389c(int numSlot, BOOL useAsDefault);
extern void SetFrameProcessingMode_02013bcc(u32 size, BOOL useAsDefault);
extern void GX_SetBankForBG_02008358(int bank);
extern void GX_SetBankForOBJ_0200855c(int bank);
extern void GX_SetBankForSubBG_02008a98(int bank);
extern void GX_SetBankForSubOBJ_02008b34(int bank);
extern void GX_SetGraphicsMode_020066c4(int dispMode, int bgMode, int bg0As);
extern void GX_SetBankForBGExtPltt_0200868c(int bank);

void SetupPanelDisplay_020c64d8(void)
{
    ResetDisplayHardware_02029bfc();
    GX_SetBankForTex_02008820(0xc);
    GX_BeginLoadOBJExtPltt_02008998(0x60);
    NNS_GfdInitFrmTexVramManager_0201389c(2, TRUE);
    SetFrameProcessingMode_02013bcc(0x8000, TRUE);

    REG_DISP3DCNT = (u16)(REG_DISP3DCNT & ~0x3002);
    REG_DISP3DCNT &= ~0x3004;
    REG_DISP3DCNT = (u16)((REG_DISP3DCNT & ~0x3000) | 8);

    GX_SetBankForBG_02008358(2);
    GX_SetBankForOBJ_0200855c(1);
    GX_SetBankForSubBG_02008a98(0x80);
    GX_SetBankForSubOBJ_02008b34(0x100);
    GX_SetGraphicsMode_020066c4(1, 0, 1);
    GX_SetBankForBGExtPltt_0200868c(0);
}
