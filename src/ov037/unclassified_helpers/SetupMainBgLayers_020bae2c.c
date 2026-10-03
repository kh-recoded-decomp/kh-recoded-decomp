#include "nitro/types.h"

typedef struct GfxRegs {
    u32 dispcnt;
    u8 pad_04[4];
    u16 bg0cnt;
    u16 bg1cnt;
    u16 bg2cnt;
    u16 bg3cnt;
} GfxRegs;

extern void GX_SetBankForBG_02008358(int bank);
extern void GX_SetGraphicsMode_020066c4(int dispMode, int bgMode, int bg0As3d);
extern void GX_SetBankForBGExtPltt_0200868c(int bank);

void SetupMainBgLayers_020bae2c(void)
{
    volatile GfxRegs *regs;

    GX_SetBankForBG_02008358(0x10);
    regs = (volatile GfxRegs *)0x04000000;
    regs->dispcnt = (regs->dispcnt & ~0x1f00) | 0xd00;
    GX_SetGraphicsMode_020066c4(1, 0, 1);
    GX_SetBankForBGExtPltt_0200868c(0);
    regs->bg2cnt = (regs->bg2cnt & 0x43) | 0x1e08;
    regs->bg3cnt = (regs->bg3cnt & 0x43) | 0x1f00;
    regs->bg0cnt = (regs->bg0cnt & ~3) | 3;
    regs->bg2cnt = regs->bg2cnt & ~3;
    regs->bg3cnt = (regs->bg3cnt & ~3) | 1;
}
