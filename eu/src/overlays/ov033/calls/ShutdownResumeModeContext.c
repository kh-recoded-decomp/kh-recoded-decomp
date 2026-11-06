#include "nitro/types.h"

extern void *gResumeModeWorkStorage;
extern void SetSoundListenersEnabled(int enabled);
extern void UnloadOverlayAfterGeometryTransfer(int processor, int overlayId);
extern char OVERLAY_39_ID[];

void ShutdownResumeModeContext(void)
{
    SetSoundListenersEnabled(0);
    UnloadOverlayAfterGeometryTransfer(0, (int)OVERLAY_39_ID);
    gResumeModeWorkStorage = NULL;
}
