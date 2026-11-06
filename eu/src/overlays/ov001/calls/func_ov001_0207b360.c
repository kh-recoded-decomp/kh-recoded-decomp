#include "nitro/types.h"

extern u32 IsSessionFlagSet(u32 id);
extern u32 GetScriptHandlerSlot7Index(void);
extern void RequestPanelModeChange(u32 arg);

extern u32 gSubscenePanelWork;

void func_ov001_0207b360(u32 arg)
{
    u32 fault;

    fault = GetScriptHandlerSlot7Index();
    if ((fault == 0) && (fault = IsSessionFlagSet(0x370b), fault != 0)) {
        *(u32 *)(gSubscenePanelWork + 0x108) = 2;
    }
    RequestPanelModeChange(arg);
}
