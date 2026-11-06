#include "nitro/types.h"

extern u32 IsPanelMapUpdateAllowed();
extern void PrepareMenuScreenEntry(u32 x, u32 y);

extern u32 gSubscenePanelWork;

void SetPanelMapEntry(u32 x, u32 y)
{
    s32 panel;
    u32 ready;

    panel = gSubscenePanelWork;
    *(u32 *)(gSubscenePanelWork + 0x50) = x;
    *(u32 *)(panel + 0x54) = y;
    ready = IsPanelMapUpdateAllowed();
    if (ready != 0) {
        PrepareMenuScreenEntry(x, y);
    }
}
