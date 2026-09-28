#include "nitro/types.h"

extern u32 g_ov038Context_020bd144;
extern void ReleaseOv038SlotPools_020bb0c0(void);
extern void FreeOv038ContextSlots_020baf7c(void);
extern void FreeOv038ContextBuffers_020bae2c(void);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void ReleaseOv038Context_020bbcb8(void)
{
    u32 context;

    context = g_ov038Context_020bd144;
    ReleaseOv038SlotPools_020bb0c0();
    FreeOv038ContextSlots_020baf7c();
    FreeOv038ContextBuffers_020bae2c();
    NNSi_FndFreeFromDefaultHeap_0202a1c4((void *)context);
    g_ov038Context_020bd144 = 0;
}
