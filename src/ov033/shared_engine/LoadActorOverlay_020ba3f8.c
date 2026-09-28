#include "nitro/types.h"

typedef u32 FSOverlayID;

extern u32 OVERLAY_107_ID[1];
#define FS_OVERLAY_ID_ov107 ((FSOverlayID)(u32) & (OVERLAY_107_ID))

extern void LoadOverlaySync(int target, FSOverlayID id);

void LoadActorOverlay_020ba3f8(void)
{
    LoadOverlaySync(0, FS_OVERLAY_ID_ov107);
}
