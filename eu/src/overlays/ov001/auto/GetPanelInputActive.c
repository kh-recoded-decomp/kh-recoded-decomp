#include "nitro/types.h"

extern u8 *gSubscenePanelWork;

u32 GetPanelInputActive(void)
{
    return *(const u32 *)(gSubscenePanelWork + 0x40);
}
