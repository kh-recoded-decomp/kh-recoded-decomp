#include "nitro/types.h"

extern u32 IsSessionFlagSet(u32 id);
extern void SetSessionFlag(u32 id);
extern u32 func_ov001_02064784(void);
extern u32 GetLoadedSubsceneMode(void);
extern u32 GetSubsceneReadyValue(void);
extern void func_ov025_020b6184(void);

extern u32 data_ov001_020a04e8;

void RequestTemporaryPanelListDisplay(void)
{
    s32 panel;
    u32 fault;

    panel = data_ov001_020a04e8;
    fault = func_ov001_02064784();
    if ((fault == 0) && (fault = IsSessionFlagSet(0x3709), fault == 0)) {
        SetSessionFlag(0x3709);
    }
    fault = GetLoadedSubsceneMode();
    if (fault == 2) {
        fault = GetSubsceneReadyValue();
        if (fault != 0) {
            func_ov025_020b6184();
        }
        *(u16 *)(panel + 0x100) = 2;
        return;
    }
    *(u16 *)(panel + 0x100) = 1;
}
