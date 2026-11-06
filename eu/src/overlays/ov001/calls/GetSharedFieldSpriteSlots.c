#include "nitro/types.h"

extern u32 gManagedActorGlobals;

u32 GetSharedFieldSpriteSlots(void)
{
    if (gManagedActorGlobals == 0) {
        return 0;
    }
    return *(u32 *)(gManagedActorGlobals + 0xfc);
}
