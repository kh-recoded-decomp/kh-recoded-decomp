#include "nitro/types.h"

extern u32 IsSessionFlagSet(u32 id);
extern void SetSessionFlag(u32 id);
extern u32 GetScriptHandlerSlot7Index(void);
extern u32 GetLoadedSubsceneMode(void);
extern u32 GetSubsceneReadyValue(void);
extern void ScrollMenuListDownOneRow(void);

extern u32 gSubscenePanelWork;

void RequestTemporaryPanelListDisplay(void)
{
    s32 panel;
    u32 fault;

    panel = gSubscenePanelWork;
    fault = GetScriptHandlerSlot7Index();
    if ((fault == 0) && (fault = IsSessionFlagSet(0x3709), fault == 0)) {
        SetSessionFlag(0x3709);
    }
    fault = GetLoadedSubsceneMode();
    if (fault == 2) {
        fault = GetSubsceneReadyValue();
        if (fault != 0) {
            ScrollMenuListDownOneRow();
        }
        *(u16 *)(panel + 0x100) = 2;
        return;
    }
    *(u16 *)(panel + 0x100) = 1;
}
