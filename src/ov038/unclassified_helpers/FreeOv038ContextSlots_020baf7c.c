#include "nitro/types.h"

extern u32 g_ov038Context_020bd144;
extern int NNSi_FndFreeFromDefaultHeap_0202a1c4();

void FreeOv038ContextSlots_020baf7c(void)
{
    u32 context;
    s32 index;

    context = g_ov038Context_020bd144;
    index = 0;
    do {
        if (*(s32 *)(context + index * 0x10 + 0x10) != 0) {
            NNSi_FndFreeFromDefaultHeap_0202a1c4();
        }
        index = index + 1;
    } while (index < 3);
}
