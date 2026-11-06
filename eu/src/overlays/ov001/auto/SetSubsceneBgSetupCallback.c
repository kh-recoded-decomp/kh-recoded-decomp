#include "nitro/types.h"

extern u8 *gSubscenePanelWork;

void SetSubsceneBgSetupCallback(u32 value)
{
    *(u32 *)(gSubscenePanelWork + 0x2c) = value;
}
