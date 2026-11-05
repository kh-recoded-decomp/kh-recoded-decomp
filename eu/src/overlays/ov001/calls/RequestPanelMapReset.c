#include "nitro/types.h"

extern u32 IsPanelMapUpdateAllowed();
extern void ResetMapMenuScreen(void);

extern u32 data_ov001_020a04e8;

void RequestPanelMapReset(void)
{
    u32 ready;

    *(u32 *)(data_ov001_020a04e8 + 0x50) = 0xfffffffe;
    ready = IsPanelMapUpdateAllowed();
    if (ready != 0) {
        ResetMapMenuScreen();
    }
}
