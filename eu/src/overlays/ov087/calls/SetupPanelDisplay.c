#include "nitro/types.h"

#define REG_DISP3DCNT (*(vu16 *)0x04000060)

extern void ResetDisplayHardware(void);
extern void GX_SetBankForTex(int bank);
extern void GX_SetBankForTexPltt(int bank);
extern void NNS_GfdInitFrmTexVramManager(int numSlot, BOOL useAsDefault);
extern void NNS_GfdInitFrmPlttVramManager(u32 size, BOOL useAsDefault);
extern void GX_SetBankForBG(int bank);
extern void GX_SetBankForOBJ(int bank);
extern void GX_SetBankForSubBG(int bank);
extern void GX_SetBankForSubOBJ(int bank);
extern void GX_SetGraphicsMode(int dispMode, int bgMode, int bg0As);
extern void GX_SetBankForBGExtPltt(int bank);

void SetupPanelDisplay(void)
{
    ResetDisplayHardware();
    GX_SetBankForTex(0xc);
    GX_SetBankForTexPltt(0x60);
    NNS_GfdInitFrmTexVramManager(2, TRUE);
    NNS_GfdInitFrmPlttVramManager(0x8000, TRUE);

    REG_DISP3DCNT = (u16)(REG_DISP3DCNT & ~0x3002);
    REG_DISP3DCNT &= ~0x3004;
    REG_DISP3DCNT = (u16)((REG_DISP3DCNT & ~0x3000) | 8);

    GX_SetBankForBG(2);
    GX_SetBankForOBJ(1);
    GX_SetBankForSubBG(0x80);
    GX_SetBankForSubOBJ(0x100);
    GX_SetGraphicsMode(1, 0, 1);
    GX_SetBankForBGExtPltt(0);
}
