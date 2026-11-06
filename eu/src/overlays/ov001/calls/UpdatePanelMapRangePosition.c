#include "nitro/types.h"

extern u32 IsPanelMapUpdateAllowed(s32 panel);
extern void UpdateMenuRangePosition(u32 a, u32 b, u32 c);

extern u32 gSubscenePanelWork;

void UpdatePanelMapRangePosition(u32 a, u32 b, u32 c)
{
    u32 ready;

    ready = IsPanelMapUpdateAllowed(gSubscenePanelWork);
    if (ready != 0) {
        UpdateMenuRangePosition(a, b, c);
    }
}
