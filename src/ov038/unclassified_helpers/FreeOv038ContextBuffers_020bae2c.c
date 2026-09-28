#include "nitro/types.h"

extern u32 g_ov038Context_020bd144;
extern int ZeroHalfThenFree_0202cd78(void *arg0);

void FreeOv038ContextBuffers_020bae2c(void)
{
    u32 context;
    s32 index;

    context = g_ov038Context_020bd144;
    index = 0;
    do {
        ZeroHalfThenFree_0202cd78((void *)*(u32 *)(context + index * 4 + 4));
        index = index + 1;
    } while (index < 3);
}
