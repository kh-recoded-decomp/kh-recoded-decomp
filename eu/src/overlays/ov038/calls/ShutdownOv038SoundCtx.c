#include "nitro/types.h"

extern char OVERLAY_27_ID[];
extern void *data_ov038_020bd160;
extern void SetSoundListenersEnabled(int enabled);
extern void func_02029fac(int processor, int overlayId);

void ShutdownOv038SoundCtx(void)
{
    SetSoundListenersEnabled(0);
    func_02029fac(0, (int)OVERLAY_27_ID);
    data_ov038_020bd160 = NULL;
}
