#include "nitro/types.h"

extern u32 gSubscenePanelWork;

u8 GetCachedPanelListDepthLimit(void)
{
    return *(u8 *)(gSubscenePanelWork + 0x102);
}
