#include "nitro/types.h"

extern int GX_GetBankForBGExtPltt_02008f80(void);
extern void GX_SetGraphicsMode_020066c4(int dispMode, int bgMode, int bg0As3d);

void Bg_SetMainBg0Control_0202af04(int screenSize, int colorMode, int screenBase, int charBase)
{
    int bank = GX_GetBankForBGExtPltt_02008f80();
    int extPalette;
    int bgMode;

    if (bank == 0x20 || bank == 0x10 || bank == 0x60) {
        extPalette = 0;
    } else {
        extPalette = 1;
    }
    bgMode = *(volatile u32 *)0x04000000 & 7;
    GX_SetGraphicsMode_020066c4(1, bgMode, 0);
    {
        volatile u16 *bg0Control = (volatile u16 *)0x04000008;
        *bg0Control = (*bg0Control & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) |
                      (charBase << 2) | (extPalette << 13);
    }
}
