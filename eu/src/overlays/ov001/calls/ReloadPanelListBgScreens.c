#include "nitro/types.h"

extern u32 GetLoadedSubsceneMode(void);
extern void ResetMenuLayerTransforms(void);

void ReloadPanelListBgScreens(void)
{
    u32 fault;

    fault = GetLoadedSubsceneMode();
    if (fault == 2) {
        ResetMenuLayerTransforms();
    }
}
