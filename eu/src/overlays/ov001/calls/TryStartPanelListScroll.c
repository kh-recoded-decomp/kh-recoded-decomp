#include "nitro/types.h"

extern s32 GetLoadedSubsceneMode(void);
extern s32 IsSubscenePanelState6(void);
extern void ActivatePanelEntity(void);

u32 TryStartPanelListScroll(void)
{
    if (GetLoadedSubsceneMode() != 2) {
        return 0;
    }
    if (IsSubscenePanelState6() == 0) {
        return 0;
    }
    ActivatePanelEntity();
    return 1;
}
