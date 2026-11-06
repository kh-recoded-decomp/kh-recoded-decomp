#include "nitro/types.h"

extern void SetGroupSlotsVisible(int screenBase, int paletteBase, int mode);
extern void SetPanelPhase(int index);
extern int gOv013PanelGlobals;

/* Sets MAIN layers, clears pending panel flags and selects phase 0. */
void ResetOv013PlayerCardPageDisplay(void) {
    *(vu32 *)0x4000000 = (*(vu32 *)0x4000000 & ~0x1f00) | 0xd00;
    *(vu8 *)(gOv013PanelGlobals + 0x99) |= 0x40;
    SetGroupSlotsVisible(gOv013PanelGlobals + 0x39c, gOv013PanelGlobals + 0xcc94, 0);
    {
        int flags = *(u8 *)(gOv013PanelGlobals + 0x99);
        flags = flags & ~8;
        *(u8 *)(gOv013PanelGlobals + 0x99) = (u8)flags;
    }
    {
        int flags = *(u8 *)(gOv013PanelGlobals + 0xd259);
        flags = flags & ~1;
        *(u8 *)(gOv013PanelGlobals + 0xd259) = (u8)flags;
    }
    *(u32 *)(gOv013PanelGlobals + 0x2e8) = 0xffffffff;
    SetPanelPhase(0);
}
