#include "nitro/types.h"

extern u32 gManagedActorGlobals;
extern void SetBrightnessAndSyncMain(u32 callerId);

void ResetTrackedMainBrightness(void)
{
    u32 ctx;

    ctx = gManagedActorGlobals;
    SetBrightnessAndSyncMain(0);
    if (gManagedActorGlobals != 0) {
        *(u32 *)(ctx + 0xf4) = 0;
        *(u8 *)(ctx + 0xf0) = 0;
    }
}
