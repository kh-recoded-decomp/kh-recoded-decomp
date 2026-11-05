#include "nitro/types.h"

typedef struct CounterPanel {
    u8 pad_00[0x10];
    int posY;
    u8 pad_14[0x34];
    u32 vramAddress;
} CounterPanel;

extern void QueueArrowPromptFlashTiles(CounterPanel *panel, u32 vramAddress);

void ScrollCounterPanelUp(CounterPanel *panel)
{
    panel->posY -= 0x1e;
    QueueArrowPromptFlashTiles(panel, panel->vramAddress);
}
