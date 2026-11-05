#include "nitro/types.h"

extern void *data_ov033_020baae0;
extern void SetSoundListenersEnabled(int enabled);
extern void UnloadOverlayAfterGeometryTransfer(int processor, int overlayId);
extern char OVERLAY_39_ID[];

void ShutdownResumeModeContext(void)
{
    SetSoundListenersEnabled(0);
    UnloadOverlayAfterGeometryTransfer(0, (int)OVERLAY_39_ID);
    data_ov033_020baae0 = NULL;
}
