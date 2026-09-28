#include "nitro/types.h"

extern u32 g_mobiClipSrcHandle_020bcf80;
extern u32 func_0202a78c(u32 handle);

u32 MobiClip_IsDecoderReady_020bac0c(void)
{
    u32 ready;

    ready = func_0202a78c(g_mobiClipSrcHandle_020bcf80);
    if (ready != 0) {
        return 1;
    }
    return 0;
}
