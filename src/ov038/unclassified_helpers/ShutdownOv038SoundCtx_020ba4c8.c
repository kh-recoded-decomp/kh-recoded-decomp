#include "nitro/types.h"

extern char OVERLAY_27_ID_0000001b[];
extern void *g_ov038SoundCtx_020bd140;
extern void SetSoundListenersEnabled_0204df9c(int enabled);
extern void func_02029f98(int processor, int overlayId);

void ShutdownOv038SoundCtx_020ba4c8(void)
{
    SetSoundListenersEnabled_0204df9c(0);
    func_02029f98(0, (int)OVERLAY_27_ID_0000001b);
    g_ov038SoundCtx_020bd140 = NULL;
}
