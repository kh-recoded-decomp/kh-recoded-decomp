#include "nitro/types.h"

#define REG_DISPCNT    (*(vu32 *)0x04000000)
#define REG_BG0CNT     (*(vu16 *)0x04000008)
#define REG_BG1CNT     (*(vu16 *)0x0400000a)
#define REG_BG2CNT     (*(vu16 *)0x0400000c)
#define REG_BG3CNT     (*(vu16 *)0x0400000e)
#define REG_BG0HOFS    (*(vu32 *)0x04000010)
#define REG_BG1HOFS    (*(vu32 *)0x04000014)
#define REG_BG2HOFS    (*(vu32 *)0x04000018)
#define REG_BG3HOFS    (*(vu32 *)0x0400001c)
#define REG_WIN0H      (*(vu16 *)0x04000040)
#define REG_WIN0V      (*(vu16 *)0x04000044)
#define REG_WININ      (*(vu16 *)0x04000048)
#define REG_WINOUT     (*(vu16 *)0x0400004a)
#define REG_DISP3DCNT  (*(vu16 *)0x04000060)
#define REG_DB_BG0HOFS (*(vu32 *)0x04001010)
#define REG_DB_BG1HOFS (*(vu32 *)0x04001014)
#define REG_DB_BG2HOFS (*(vu32 *)0x04001018)
#define REG_DB_BG3HOFS (*(vu32 *)0x0400101c)
#define REG_POWCNT     (*(vu16 *)0x04000304)
#define REG_DB_DISPCNT (*(vu32 *)0x04001000)
#define REG_DB_BG0CNT  (*(vu16 *)0x04001008)
#define REG_DB_BG1CNT  (*(vu16 *)0x0400100a)
#define REG_DB_BG2CNT  (*(vu16 *)0x0400100c)
#define REG_DB_BG3CNT  (*(vu16 *)0x0400100e)

extern void ResetDisplayHardware_02029bfc(void);
extern void SetBrightnessAndSyncMain_02029e7c(int brightness);
extern void SetSecondaryBrightness_02029ed0(int brightness);
extern void GX_SetBankForLCDC_02008a74(int bank);
extern void MIi_CpuClearFast_01ff8740(u32 data, void *dest, u32 size);
extern void func_02008ef4(void);
extern void func_0202a794(int value);
extern void GX_SetGraphicsMode_020066c4(int dispMode, int bgMode, int bg0As);
extern void GX_SetBankForTex_02008820(int bank);
extern void GX_BeginLoadOBJExtPltt_02008998(int bank);
extern void GX_SetBankForBGExtPltt_0200868c(int bank);
extern void GX_SetBankForBG_02008358(int bank);
extern void GX_SetBankForOBJ_0200855c(int bank);
extern void GX_SetBankForSubBG_02008a98(int bank);
extern void GX_SetBankForSubBGExtPltt_02008ba4(int bank);
extern void GX_SetBankForSubOBJ_02008b34(int bank);

static inline void SetBGPriority(vu16 *reg, int priority)
{
    *reg = (u16)((*reg & ~3) | priority);
}

void SetupGridMenuDisplay_020bf084(void)
{
    ResetDisplayHardware_02029bfc();
    SetBrightnessAndSyncMain_02029e7c(-16);
    SetSecondaryBrightness_02029ed0(-16);
    GX_SetBankForLCDC_02008a74(0x1ff);
    MIi_CpuClearFast_01ff8740(0, (void *)0x06800000, 0xa4000);
    func_02008ef4();
    REG_POWCNT |= 0x8000;
    func_0202a794(0);

    GX_SetGraphicsMode_020066c4(1, 0, 1);
    REG_DISP3DCNT = (u16)(REG_DISP3DCNT & ~0x3002);
    REG_DISP3DCNT = (u16)(REG_DISP3DCNT & 0xcffb);
    REG_DISP3DCNT = (u16)((REG_DISP3DCNT & ~0x3000) | 8);
    GX_SetBankForTex_02008820(3);
    GX_BeginLoadOBJExtPltt_02008998(0x60);

    GX_SetBankForBG_02008358(8);
    GX_SetBankForBGExtPltt_0200868c(0);
    GX_SetBankForOBJ_0200855c(0x10);
    REG_DISPCNT = (REG_DISPCNT & 0xffcfffef) | 0x100010;
    REG_BG1CNT = (u16)((REG_BG1CNT & 0x43) | 0x1a00);
    REG_BG2CNT = (u16)((REG_BG2CNT & 0x43) | 0x9c00);
    REG_BG3CNT = (u16)((REG_BG3CNT & 0x43) | 0x9e00);
    SetBGPriority(&REG_BG1CNT, 0);
    SetBGPriority(&REG_BG2CNT, 1);
    SetBGPriority(&REG_BG0CNT, 2);
    SetBGPriority(&REG_BG3CNT, 3);
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0x1f00;
    REG_BG0HOFS = 0;
    REG_BG1HOFS = 0;
    REG_BG2HOFS = 0;
    REG_BG3HOFS = 0;

    GX_SetBankForSubBG_02008a98(4);
    GX_SetBankForSubBGExtPltt_02008ba4(0x80);
    GX_SetBankForSubOBJ_02008b34(0);
    REG_DB_DISPCNT = (REG_DB_DISPCNT & 0xffcfffef) | 0x100010;
    REG_DB_BG0CNT = (u16)((REG_DB_BG0CNT & 0x43) | 0x1f00);
    REG_DB_BG1CNT = (u16)((REG_DB_BG1CNT & 0x43) | 0x1e00);
    REG_DB_BG2CNT = (u16)((REG_DB_BG2CNT & 0x43) | 0x1d00);
    SetBGPriority(&REG_DB_BG1CNT, 0);
    SetBGPriority(&REG_DB_BG2CNT, 1);
    SetBGPriority(&REG_DB_BG0CNT, 2);
    SetBGPriority(&REG_DB_BG3CNT, 3);
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | 0x700;
    REG_DB_BG0HOFS = 0;
    REG_DB_BG1HOFS = 0;
    REG_DB_BG2HOFS = 0;
    REG_DB_BG3HOFS = 0;
}
