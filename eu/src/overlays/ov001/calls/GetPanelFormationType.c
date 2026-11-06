#include "nitro/types.h"

extern u32 gSubscenePanelWork;

u8 GetPanelFormationType(void)
{
    if (gSubscenePanelWork == 0) {
        return 0;
    }
    return *(u8 *)(gSubscenePanelWork + 0x103);
}
