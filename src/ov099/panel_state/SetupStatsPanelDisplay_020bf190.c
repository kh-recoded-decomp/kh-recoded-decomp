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
extern void NNS_GfdInitFrmTexVramManager_0201389c(u16 numSlot, BOOL useAsDefault);
extern void SetFrameProcessingMode_02013bcc(int processingMode, int installCallbacks);
extern void GX_SetBankForBG_02008358(int bank);
extern void GX_SetBankForOBJ_0200855c(int bank);
extern void GX_SetBankForSubBG_02008a98(int bank);
extern void GX_SetBankForSubBGExtPltt_02008ba4(int bank);
extern void GX_SetBankForSubOBJ_02008b34(int bank);

static inline void SetBGPriority(vu16 *reg, int priority)
{
    *reg = (u16)((*reg & ~3) | priority);
}

void SetupStatsPanelDisplay_020bf190(void)
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
    GX_SetBankForTex_02008820(1);
    GX_BeginLoadOBJExtPltt_02008998(0x10);
    NNS_GfdInitFrmTexVramManager_0201389c(1, 1);
    SetFrameProcessingMode_02013bcc(0x4000, 1);
    REG_DISP3DCNT = (u16)(REG_DISP3DCNT & ~0x3002);
    REG_DISP3DCNT = (u16)(REG_DISP3DCNT & 0xcffb);
    REG_DISP3DCNT = (u16)((REG_DISP3DCNT & ~0x3000) | 8);

    GX_SetBankForBG_02008358(2);
    GX_SetBankForOBJ_0200855c(0x60);
    REG_DISPCNT = (REG_DISPCNT & 0xffcfffef) | 0x100010;
    REG_BG1CNT = (u16)((REG_BG1CNT & 0x43) | 0x1e00);
    REG_BG2CNT = (u16)((REG_BG2CNT & 0x43) | 0x1f00);
    SetBGPriority(&REG_BG0CNT, 0);
    SetBGPriority(&REG_BG1CNT, 1);
    SetBGPriority(&REG_BG2CNT, 2);
    SetBGPriority(&REG_BG3CNT, 3);
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0x1700;
    REG_WININ = (u16)((REG_WININ & ~0x3f) | 0x17);
    REG_WINOUT = (u16)((REG_WINOUT & ~0x3f) | 0x16);
    REG_WIN0H = 0x8dfb;
    REG_WIN0V = 0x1dbb;
    REG_DISPCNT = (REG_DISPCNT & ~0xe000) | 0x2000;

    GX_SetBankForSubBG_02008a98(4);
    GX_SetBankForSubBGExtPltt_02008ba4(0x80);
    GX_SetBankForSubOBJ_02008b34(8);
    REG_DB_DISPCNT = (REG_DB_DISPCNT & 0xffcfffef) | 0x100010;
    REG_DB_BG1CNT = (u16)((REG_DB_BG1CNT & 0x43) | 0x5c00);
    REG_DB_BG2CNT = (u16)((REG_DB_BG2CNT & 0x43) | 0x5e00);
    SetBGPriority(&REG_DB_BG0CNT, 0);
    SetBGPriority(&REG_DB_BG1CNT, 1);
    SetBGPriority(&REG_DB_BG2CNT, 2);
    SetBGPriority(&REG_DB_BG3CNT, 3);
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | 0x1600;
}
