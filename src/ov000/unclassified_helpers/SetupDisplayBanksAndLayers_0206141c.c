#include "nitro/types.h"

extern void ResetDisplayHardware_02029bfc(void);
extern void GX_SetBankForTex_02008820(int bank);
extern void GX_BeginLoadOBJExtPltt_02008998(int bank);
extern void GX_SetBankForBG_02008358(int bank);
extern void GX_SetBankForBGExtPltt_0200868c(int bank);
extern void GX_SetBankForOBJExtPltt_02008784(int bank);
extern void GX_SetBankForSubBG_02008a98(int bank);
extern void GX_SetBankForSubOBJ_02008b34(int bank);
extern void GX_SetBankForSubBGExtPltt_02008ba4(int bank);
extern void GX_SetBankForSubOBJExtPltt_02008c24(int bank);
extern void NNS_GfdInitFrmTexVramManager_0201389c(int numSlot, BOOL useAsDefault);
extern void SetFrameProcessingMode_02013bcc(int size, BOOL useAsDefault);
extern void GX_SetGraphicsMode_020066c4(int dispMode, int bgMode, int bg0As);
extern void func_0200672c(int bgMode);
extern void G2x_SetBlendAlpha_02006850(vu32 *reg, int plane1, int plane2, int ev1, int ev2);

#define REG_DISPCNT      (*(vu32 *)0x04000000)
#define REG_BG0CNT       (*(vu16 *)0x04000008)
#define REG_BG1CNT       (*(vu16 *)0x0400000a)
#define REG_DB_DISPCNT   (*(vu32 *)0x04001000)
#define REG_DB_BG1CNT    (*(vu16 *)0x0400100a)
#define REG_DB_BG2CNT    (*(vu16 *)0x0400100c)
#define REG_DB_BG3CNT    (*(vu16 *)0x0400100e)
#define REG_DB_BLDCNT    ((vu32 *)0x04001050)

void SetupDisplayBanksAndLayers_0206141c(void)
{
    ResetDisplayHardware_02029bfc();
    GX_SetBankForTex_02008820(3);
    GX_BeginLoadOBJExtPltt_02008998(0x60);
    GX_SetBankForBG_02008358(0x10);
    GX_SetBankForBGExtPltt_0200868c(0);
    GX_SetBankForOBJExtPltt_02008784(0);
    GX_SetBankForSubBG_02008a98(4);
    GX_SetBankForSubOBJ_02008b34(8);
    GX_SetBankForSubBGExtPltt_02008ba4(0);
    GX_SetBankForSubOBJExtPltt_02008c24(0);
    NNS_GfdInitFrmTexVramManager_0201389c(2, TRUE);
    SetFrameProcessingMode_02013bcc(0x8000, TRUE);
    GX_SetGraphicsMode_020066c4(1, 0, 1);

    REG_BG1CNT = (u16)((REG_BG1CNT & 0x43) | (0 << 14) | (1 << 7) | (0 << 8) | (1 << 2));
    REG_BG0CNT = (u16)((REG_BG0CNT & ~3) | 0);
    REG_BG1CNT = (u16)((REG_BG1CNT & ~3) | 1);
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | (3 << 8);

    func_0200672c(0);

    REG_DB_BG1CNT = (u16)((REG_DB_BG1CNT & 0x43) | (1 << 14) | (1 << 7) | (0 << 8) | (1 << 2));
    REG_DB_BG2CNT = (u16)((REG_DB_BG2CNT & 0x43) | (1 << 14) | (1 << 7) | (2 << 8) | (1 << 2));
    REG_DB_BG3CNT = (u16)((REG_DB_BG3CNT & 0x43) | (0 << 14) | (0 << 7) | (4 << 8) | (1 << 2));
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x300010) | 0x10;
    REG_DB_BG1CNT = (u16)((REG_DB_BG1CNT & ~3) | 3);
    REG_DB_BG2CNT = (u16)((REG_DB_BG2CNT & ~3) | 2);
    REG_DB_BG3CNT = (u16)((REG_DB_BG3CNT & ~3) | 1);

    G2x_SetBlendAlpha_02006850(REG_DB_BLDCNT, 0x10, 0x22, 0, 0x10);
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | (0x12 << 8);
}
