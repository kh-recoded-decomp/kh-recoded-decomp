#include "nitro/types.h"
#include "nitro/gx.h"

#define REG_DISPCNT (*(vu32 *)0x04000000)
#define REG_BGCNT ((vu16 *)0x04000008)
#define REG_POWCNT1 (*(vu16 *)0x04000304)

extern void SetBrightnessAndSyncMain_02029e7c(int value);
extern void SetSecondaryBrightness_02029ed0(int value);
extern void ResetDisplayHardware_02029bfc(void);
extern void SetupMovieScreenHardware_020a831c(int useMainScreen);
extern void GX_SetGraphicsMode_020066c4(GXDispMode dispMode, GXBGMode bgMode, GXBG0As bg0As);
extern void GX_SetBankForBG_02008358(GXVRamBG bank);
extern void GX_SetBankForBGExtPltt_0200868c(GXVRamBGExtPltt bank);

void MoviePlayer_SetupDisplay_02063ae0(void)
{
    SetBrightnessAndSyncMain_02029e7c(-16);
    SetSecondaryBrightness_02029ed0(-16);
    ResetDisplayHardware_02029bfc();
    SetupMovieScreenHardware_020a831c(FALSE);
    GX_SetGraphicsMode_020066c4(GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BG0_AS_2D);
    GX_SetBankForBG_02008358(GX_VRAM_BG_256_AB);
    GX_SetBankForBGExtPltt_0200868c(GX_VRAM_BGEXTPLTT_NONE);

    REG_BGCNT[0] = REG_BGCNT[0] & 0x43 | 0x84;
    REG_BGCNT[1] = REG_BGCNT[1] & 0x43 | 0x290;
    REG_BGCNT[2] = REG_BGCNT[2] & 0x43 | 0x4a0;
    REG_DISPCNT &= ~0x1f00;
    REG_BGCNT[0] = REG_BGCNT[0] & ~3;
    REG_BGCNT[1] = REG_BGCNT[1] & ~3 | 1;
    REG_BGCNT[2] = REG_BGCNT[2] & ~3 | 2;
    REG_POWCNT1 = (u16)(REG_POWCNT1 & ~0x8000);
}
