#include "nitro/types.h"

extern u8 *gSubscenePanelWork;

void *GetPanelMessageView(void)
{
    return gSubscenePanelWork + 0x20;
}
