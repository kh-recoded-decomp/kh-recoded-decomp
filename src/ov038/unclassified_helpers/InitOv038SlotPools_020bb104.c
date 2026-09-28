#include "nitro/types.h"

extern u32 g_ov038Context_020bd144;
extern void NNS_FndInitListWithOffset0_0204f11c(void *list);

void InitOv038SlotPools_020bb104(void)
{
    u32 pool;
    s32 index;

    index = 0;
    pool = g_ov038Context_020bd144 + 0x40;
    do {
        NNS_FndInitListWithOffset0_0204f11c((void *)(index * 0x6434 + pool));
        index = index + 1;
    } while (index < 2);
}
