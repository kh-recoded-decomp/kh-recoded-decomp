#include "nitro/types.h"

extern u32 data_ov001_020a0498;
extern void ReleaseLowIdTaskNodes(void);
extern void ReleaseHighIdTaskNodes(void);

void ReleaseAllTaskNodes(void)
{
    u32 ctx;

    ctx = data_ov001_020a0498;
    ReleaseLowIdTaskNodes();
    ReleaseHighIdTaskNodes();
    *(u8 *)(ctx + 0x11) = 0;
}
