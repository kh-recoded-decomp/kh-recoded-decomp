#include "nitro/types.h"

extern u8 *gSubscenePanelWork;

u32 GetSubsceneReadyValue(void)
{
    return *(const u32 *)(gSubscenePanelWork + 0x38);
}
