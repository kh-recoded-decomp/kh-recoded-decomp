#include "nitro/types.h"

extern s32 GetLoadedSubsceneMode(void);
extern s32 GetSubsceneReadyValue(void);
extern void LookupChannelEntry_020b62ac(u32 value);
extern void DrawNumberInPanelSlot(void);

void SetPanelListDepthLimitAndRefreshLabel(u32 value)
{
    if (GetLoadedSubsceneMode() == 2 && GetSubsceneReadyValue() != 0) {
        DrawNumberInPanelSlot();
        LookupChannelEntry_020b62ac(value);
    }
}
