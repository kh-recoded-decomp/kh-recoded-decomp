#include "nitro/types.h"

extern s32 GetLoadedSubsceneMode(void);
extern s32 GetSubsceneReadyValue(void);
extern u32 LookupChannelEntry_020b62c8(u32 value);

u32 GetPanelListPathNodeId(u32 value)
{
    u32 result;

    result = 0xffff;
    if (GetLoadedSubsceneMode() == 2 && GetSubsceneReadyValue() != 0) {
        result = LookupChannelEntry_020b62c8(value);
    }
    return result;
}
