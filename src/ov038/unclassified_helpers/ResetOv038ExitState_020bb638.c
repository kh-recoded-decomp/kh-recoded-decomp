#include "nitro/types.h"

extern u32 g_ov038Context_020bd144;

void ResetOv038ExitState_020bb638(u32 mode)
{
    u32 context;

    context = g_ov038Context_020bd144;
    *(u32 *)(context + 0xd0a0) = mode;
    *(u32 *)(context + 0xd0a4) = 0;
    *(u32 *)(context + 0xd0a8) = 0;
}
