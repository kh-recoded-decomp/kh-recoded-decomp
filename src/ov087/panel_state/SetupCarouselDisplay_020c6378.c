#include "nitro/types.h"

#define REG_DISPCNT    (*(vu32 *)0x04000000)
#define REG_BG0CNT     (*(vu16 *)0x04000008)
#define REG_BG1CNT     (*(vu16 *)0x0400000a)
#define REG_BG2CNT     (*(vu16 *)0x0400000c)
#define REG_BG3CNT     (*(vu16 *)0x0400000e)
#define REG_DISP3DCNT  (*(vu16 *)0x04000060)
#define REG_DB_DISPCNT (*(vu32 *)0x04001000)

extern void ResetDisplayHardware_02029bfc(void);
extern void GX_SetBankForTex_02008820(int bank);
extern void GX_BeginLoadOBJExtPltt_02008998(int bank);
extern void GX_SetBankForBG_02008358(int bank);
extern void GX_SetBankForOBJ_0200855c(int bank);
extern void GX_SetBankForSubBG_02008a98(int bank);
extern void GX_SetBankForSubOBJ_02008b34(int bank);
extern void NNS_GfdInitFrmTexVramManager_0201389c(u16 numSlot, BOOL useAsDefault);
extern void SetFrameProcessingMode_02013bcc(int processingMode, int installCallbacks);
extern void GX_SetGraphicsMode_020066c4(int dispMode, int bgMode, int bg0As);
extern void GX_SetBankForBGExtPltt_0200868c(int bank);

static inline void SetBGPriority(vu16 *reg, int priority)
{
    *reg = (u16)((*reg & ~3) | priority);
}

void SetupCarouselDisplay_020c6378(void)
{
    ResetDisplayHardware_02029bfc();
    GX_SetBankForTex_02008820(0xb);
    GX_BeginLoadOBJExtPltt_02008998(0x40);
    GX_SetBankForBG_02008358(0x10);
    GX_SetBankForOBJ_0200855c(0x20);
    GX_SetBankForSubBG_02008a98(4);
    GX_SetBankForSubOBJ_02008b34(0x100);
    NNS_GfdInitFrmTexVramManager_0201389c(3, 1);
    SetFrameProcessingMode_02013bcc(0x4000, 1);
    REG_DISP3DCNT = (u16)(REG_DISP3DCNT & ~0x3002);
    REG_DISP3DCNT = (u16)(REG_DISP3DCNT & 0xcffb);
    REG_DISP3DCNT = (u16)((REG_DISP3DCNT & ~0x3000) | 8);
    GX_SetGraphicsMode_020066c4(1, 0, 1);
    GX_SetBankForBGExtPltt_0200868c(0);

    REG_BG2CNT = (u16)((REG_BG2CNT & 0x43) | 0x1e00);
    REG_BG3CNT = (u16)((REG_BG3CNT & 0x43) | 0x1f00);
    SetBGPriority(&REG_BG0CNT, 3);
    SetBGPriority(&REG_BG3CNT, 2);
    SetBGPriority(&REG_BG2CNT, 1);
    SetBGPriority(&REG_BG1CNT, 0);
    REG_DISPCNT = (REG_DISPCNT & 0xffcfffef) | 0x10;
    REG_DB_DISPCNT = (REG_DB_DISPCNT & 0xffcfffef) | 0x10;
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0x1d00;
}