#include "nitro/types.h"

extern u32 gSubscenePanelWork;

u32 IsSubscenePanelState6(void)
{
    if (*(u32 *)(gSubscenePanelWork + 0x30) == 6) {
        return 1;
    }
    return 0;
}
