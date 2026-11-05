#include "nitro/types.h"

extern u32 data_ov001_020a04e8;

u32 IsSubscenePanelState6(void)
{
    if (*(u32 *)(data_ov001_020a04e8 + 0x30) == 6) {
        return 1;
    }
    return 0;
}
