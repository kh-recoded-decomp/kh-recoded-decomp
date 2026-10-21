#include "nitro/types.h"

#define REG_DISPCNT    (*(vu32 *)0x04000000)
#define REG_BG0CNT     (*(vu16 *)0x04000008)
#define REG_BG1CNT     (*(vu16 *)0x0400000a)
#define REG_BG2CNT     (*(vu16 *)0x0400000c)
#define REG_BG3CNT     (*(vu16 *)0x0400000e)
#define REG_WIN0H      (*(vu16 *)0x04000040)
#define REG_WIN0V      (*(vu16 *)0x04000044)
#define REG_WININ      (*(vu16 *)0x04000048)
#define REG_WINOUT     (*(vu16 *)0x0400004a)
#define REG_DISP3DCNT  (*(vu16 *)0x04000060)
#define REG_POWCNT     (*(vu16 *)0x04000304)
#define REG_DB_DISPCNT (*(vu32 *)0x04001000)
#define REG_DB_BG0CNT  (*(vu16 *)0x04001008)
#define REG_DB_BG1CNT  (*(vu16 *)0x0400100a)
#define REG_DB_BG2CNT  (*(vu16 *)0x0400100c)
#define REG_DB_BG3CNT  (*(vu16 *)0x0400100e)

extern void ResetDisplayHardware(void);
extern void SetSecondaryBrightness(int brightness);
extern void SetBrightnessAndSyncMain(int brightness);
extern void GX_SetBankForLCDC(int bank);
extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);
extern void GX_DisableBankForLCDC(void);
extern void TaskManager_SetEnabled(int enabled);
extern void GXS_SetGraphicsMode(int bgMode);
extern void GX_SetBankForSubBG(int bank);
extern void GX_SetBankForSubBGExtPltt(int bank);
extern void GX_SetBankForSubOBJ(int bank);
extern void GX_SetGraphicsMode(int dispMode, int bgMode, int bg0As);
extern void GX_SetBankForTex(int bank);
extern void GX_SetBankForTexPltt(int bank);
extern void GX_SetBankForBG(int bank);
extern void GX_SetBankForBGExtPltt(int bank);
extern void GX_SetBankForOBJ(int bank);

/* Merge new field bits into the bits kept from a display register. */
static inline int MergeRegisterBits(int kept, int bits)
{
    return kept | bits;
}

/* Reset the display and clear VRAM, then set up the sub screen (text BGs, 1D OBJ) and the main
 * screen (3D on BG0, text BG1-BG3, 1D OBJ, window 0 framing the menu). */
void SetupMenuDisplay_020bf46c(void)
{
    ResetDisplayHardware();
    SetSecondaryBrightness(-16);
    SetBrightnessAndSyncMain(-16);
    GX_SetBankForLCDC(0x1ff);
    MIi_CpuClearFast(0, (void *)0x06800000, 0xa4000);
    GX_DisableBankForLCDC();
    REG_POWCNT &= ~0x8000;
    TaskManager_SetEnabled(0);

    GXS_SetGraphicsMode(0);
    GX_SetBankForSubBG(4);
    GX_SetBankForSubBGExtPltt(0x80);
    GX_SetBankForSubOBJ(0x100);
    REG_DB_DISPCNT = (REG_DB_DISPCNT & 0xffcfffef) | 0x100010;
    REG_DB_BG0CNT = (u16)MergeRegisterBits(REG_DB_BG0CNT & 0x43, 0x1d88);
    REG_DB_BG1CNT = (u16)MergeRegisterBits(REG_DB_BG1CNT & 0x43, 0x1e00);
    REG_DB_BG2CNT = (u16)((REG_DB_BG2CNT & 0x43) | 0x1f00);
    REG_DB_BG1CNT = (u16)MergeRegisterBits(REG_DB_BG1CNT & ~3, 1);
    REG_DB_BG0CNT = (u16)(REG_DB_BG0CNT & ~3);
    REG_DB_BG2CNT = (u16)((REG_DB_BG2CNT & ~3) | 2);
    REG_DB_BG3CNT = (u16)((REG_DB_BG3CNT & ~3) | 3);
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | 0x1700;

    GX_SetGraphicsMode(1, 0, 1);
    REG_DISP3DCNT = (u16)(REG_DISP3DCNT & ~0x3002);
    REG_DISP3DCNT &= (u16)~0x3004;
    REG_DISP3DCNT = (u16)((REG_DISP3DCNT & ~0x3000) | 8);
    GX_SetBankForTex(3);
    GX_SetBankForTexPltt(0x60);
    GX_SetBankForBG(8);
    GX_SetBankForBGExtPltt(0);
    GX_SetBankForOBJ(0x10);
    REG_DISPCNT = MergeRegisterBits(REG_DISPCNT & 0xffcfffef, 0x100010);
    REG_BG1CNT = (u16)((REG_BG1CNT & 0x43) | 0x1e00);
    REG_BG2CNT = (u16)((REG_BG2CNT & 0x43) | 0x1f00);
    REG_BG1CNT = (u16)(REG_BG1CNT & ~3);
    REG_BG0CNT = (u16)((REG_BG0CNT & ~3) | 1);
    REG_BG2CNT = (u16)((REG_BG2CNT & ~3) | 2);
    REG_BG3CNT = (u16)((REG_BG3CNT & ~3) | 3);
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0x1700;
    REG_WININ = (u16)((REG_WININ & ~0x3f) | 0x17);
    REG_WINOUT = (u16)((REG_WINOUT & ~0x3f) | 0x16);
    REG_WIN0H = 0x01ff;
    REG_WIN0V = 0x26b0;
    REG_DISPCNT = (REG_DISPCNT & ~0xe000) | 0x2000;
}
