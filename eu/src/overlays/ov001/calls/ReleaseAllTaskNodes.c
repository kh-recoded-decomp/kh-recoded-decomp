#include "nitro/types.h"

extern u32 gFieldTaskManagerWork;
extern void ReleaseLowIdTaskNodes(void);
extern void ReleaseHighIdTaskNodes(void);

void ReleaseAllTaskNodes(void)
{
    u32 ctx;

    ctx = gFieldTaskManagerWork;
    ReleaseLowIdTaskNodes();
    ReleaseHighIdTaskNodes();
    *(u8 *)(ctx + 0x11) = 0;
}
