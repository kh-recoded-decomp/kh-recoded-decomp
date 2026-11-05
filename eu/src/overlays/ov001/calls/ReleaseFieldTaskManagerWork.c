#include "nitro/types.h"

extern void *GetRunningTaskWork(void);
extern void ReleaseAllTaskNodes(void);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern u32 data_ov001_020a0498;

void ReleaseFieldTaskManagerWork(void)
{
    u8 *ctx;

    ctx = (u8 *)GetRunningTaskWork();
    ReleaseAllTaskNodes();
    NNSi_FndFreeFromDefaultHeap((void *)*(u32 *)(ctx + 0x34));
    data_ov001_020a0498 = 0;
}
