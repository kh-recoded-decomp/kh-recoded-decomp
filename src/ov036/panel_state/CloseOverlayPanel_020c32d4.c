#include "nitro/types.h"

#define REG_DISPCNT (*(vu32 *)0x04000000)

extern void func_ov036_020c31c8(void);
extern void ClosePanelAndResume_0202874c(int panel);
extern void SelectActiveEntry_020011a4(int index);
extern void G2x_SetBlendAlpha_02006850(unsigned int *reg, unsigned int plane1, unsigned int plane2, unsigned int ev1, unsigned int ev2);

BOOL CloseOverlayPanel_020c32d4(int panel)
{
    u32 planes;

    func_ov036_020c31c8();
    ClosePanelAndResume_0202874c(panel);
    SelectActiveEntry_020011a4(0);
    planes = (REG_DISPCNT & 0x1f00) >> 8;
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | ((planes | 0x10) << 8);
    G2x_SetBlendAlpha_02006850((unsigned int *)0x04000050, 1, 0x22, 0, 0x10);
    return TRUE;
}
