#include "nitro/types.h"

extern char OVERLAY_27_ID_0000001b_00000026[];
extern void *g_ov038SoundCtx_020baac0;
extern void SetSoundListenersEnabled_0204df9c(int enabled);
extern void func_02029f98(int processor, int overlayId);

void func_ov033_020ba5b4(void)
{
    SetSoundListenersEnabled_0204df9c(0);
    func_02029f98(0, (int)OVERLAY_27_ID_0000001b_00000026);
    g_ov038SoundCtx_020baac0 = NULL;
}
