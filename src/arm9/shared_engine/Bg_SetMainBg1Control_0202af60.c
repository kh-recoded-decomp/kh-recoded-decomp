#include "nitro/types.h"

extern int GX_GetBankForBGExtPltt_02008f80(void);
extern void GX_SetGraphicsMode_020066c4(int dispMode, int bgMode, int bg0As3d);

void Bg_SetMainBg1Control_0202af60(int screenSize, int colorMode, int screenBase, int charBase)
{
    int bank = GX_GetBankForBGExtPltt_02008f80();
    int extPalette;
    int bg0Is3d;
    int bg0As3d;
    int bgMode;

    if (bank == 0x20 || bank == 0x10 || bank == 0x60) {
        extPalette = 0;
    } else {
        extPalette = 1;
    }
    bg0Is3d = (*(volatile u32 *)0x04000000 & 8) ? 1 : 0;
    bg0As3d = bg0Is3d ? 1 : 0;
    bgMode = *(volatile u32 *)0x04000000 & 7;
    GX_SetGraphicsMode_020066c4(1, bgMode, bg0As3d);
    {
        volatile u16 *bg1Control = (volatile u16 *)0x0400000a;
        *bg1Control = (*bg1Control & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) |
                      (charBase << 2) | (extPalette << 13);
    }
}
