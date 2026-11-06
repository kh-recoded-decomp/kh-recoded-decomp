#include "nitro/types.h"

extern u32 gStageEventContext;
extern void ResetStageEventContext(void);
extern void ReleaseRecordSlot(s32 mode);
extern void ReleaseServiceInstance_020876a0(void);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void DestroyStageEventContext(void)
{
    u32 *ctx;

    ctx = (u32 *)gStageEventContext;
    ResetStageEventContext();
    ReleaseRecordSlot(4);
    ReleaseServiceInstance_020876a0();
    if (*ctx != 0) {
        NNSi_FndFreeFromDefaultHeap((void *)*ctx);
    }
    NNSi_FndFreeFromDefaultHeap((void *)gStageEventContext);
    gStageEventContext = 0;
}
