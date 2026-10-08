#include "nitro/types.h"

#define REG_DISPCNT    (*(vu32 *)0x04000000)
#define REG_BG0CNT     (*(vu16 *)0x04000008)
#define REG_BG1CNT     (*(vu16 *)0x0400000a)
#define REG_BG2CNT     (*(vu16 *)0x0400000c)
#define REG_BG3CNT     (*(vu16 *)0x0400000e)
#define REG_DISP3DCNT  (*(vu16 *)0x04000060)
#define REG_DB_DISPCNT (*(vu32 *)0x04001000)

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

void SetupEntryMenuDisplay(void)
{
    ResetDisplayHardware();
    GX_SetBankForTex(7);
    GX_SetBankForTexPltt(0x20);
    NNS_GfdInitFrmTexVramManager(3, TRUE);
    NNS_GfdInitFrmPlttVramManager(0x4000, TRUE);

    REG_DISP3DCNT = (u16)(REG_DISP3DCNT & ~0x3002);
    REG_DISP3DCNT &= ~0x3004;
    REG_DISP3DCNT = (u16)((REG_DISP3DCNT & ~0x3000) | 8);

    GX_SetBankForBG(8);
    GX_SetBankForOBJ(0x10);
    GX_SetBankForSubBG(0x80);
    GX_SetBankForSubOBJ(0x100);
    GX_SetGraphicsMode(1, 0, 1);
    GX_SetBankForBGExtPltt(0);

    REG_BG2CNT = (u16)((REG_BG2CNT & 0x43) | 0x1e08);
    REG_BG3CNT = (u16)((REG_BG3CNT & 0x43) | 0x1f00);
    REG_BG3CNT = (u16)((REG_BG3CNT & ~3) | 3);
    REG_BG0CNT = (u16)((REG_BG0CNT & ~3) | 2);
    REG_BG2CNT = (u16)((REG_BG2CNT & ~3) | 1);
    REG_BG1CNT = (u16)(REG_BG1CNT & ~3);
    REG_DISPCNT = (REG_DISPCNT & 0xffcfffef) | 0x10;
    REG_DB_DISPCNT = (REG_DB_DISPCNT & 0xffcfffef) | 0x10;
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0x1d00;
}
