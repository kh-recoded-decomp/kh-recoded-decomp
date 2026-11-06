#include "nitro/types.h"

extern u32 GetLoadedSubsceneMode(void);
extern u32 GetSubsceneReadyValue(void);
extern u32 LookupChannelEntry(s32 index);

extern u32 gSubscenePanelWork;

u32 GetSubsceneSlotValue(s32 index)
{
    u32 fault;
    u32 result;

    fault = GetLoadedSubsceneMode();
    if ((fault == 2) && (fault = GetSubsceneReadyValue(), fault != 0)) {
        result = LookupChannelEntry(index);
        return result;
    }
    return *(u32 *)(gSubscenePanelWork + index * 4 + 0xe4);
}
