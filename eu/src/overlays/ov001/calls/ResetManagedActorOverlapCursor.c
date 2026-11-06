#include "nitro/types.h"

extern u32 gManagedActorGlobals;

void ResetManagedActorOverlapCursor(void)
{
    if (gManagedActorGlobals != 0) {
        *(u32 *)(gManagedActorGlobals + 0xf8) = 0;
    }
}
