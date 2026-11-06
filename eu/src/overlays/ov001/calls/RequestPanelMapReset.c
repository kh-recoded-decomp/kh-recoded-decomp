#include "nitro/types.h"

extern u32 IsPanelMapUpdateAllowed();
extern void ResetMapMenuScreen(void);

extern u32 gSubscenePanelWork;

void RequestPanelMapReset(void)
{
    u32 ready;

    *(u32 *)(gSubscenePanelWork + 0x50) = 0xfffffffe;
    ready = IsPanelMapUpdateAllowed();
    if (ready != 0) {
        ResetMapMenuScreen();
    }
}
