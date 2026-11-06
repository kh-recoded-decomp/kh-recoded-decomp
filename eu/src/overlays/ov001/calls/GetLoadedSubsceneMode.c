#include "nitro/types.h"

extern u32 gSubscenePanelWork;

u32 GetLoadedSubsceneMode(void)
{
    if (gSubscenePanelWork == 0) {
        return 0xffffffff;
    }
    return *(u32 *)(gSubscenePanelWork + 0xdc);
}
