#include "nitro/types.h"

typedef struct CounterPanel {
    u8 pad_00[0x10];
    int posY;
    u8 pad_14[0x34];
    u32 vramAddress;
} CounterPanel;

extern void func_ov001_0207d828(CounterPanel *panel, u32 vramAddress);

void ScrollCounterPanelUp(CounterPanel *panel)
{
    panel->posY -= 0x1e;
    func_ov001_0207d828(panel, panel->vramAddress);
}
