#include "nitro/types.h"

extern u32 GetLoadedSubsceneMode(void);
extern u32 GetSubsceneReadyValue(void);
extern void ResetMenuListToFirstEntry(void);

void ResetPanelListToFirstEntryIfReady(void)
{
    u32 fault;

    fault = GetLoadedSubsceneMode();
    if ((fault == 2) && (fault = GetSubsceneReadyValue(), fault != 0)) {
        ResetMenuListToFirstEntry();
    }
}
