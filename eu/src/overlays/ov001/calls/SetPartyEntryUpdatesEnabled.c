#include "nitro/types.h"

extern u32 gManagedActorGlobals;

void SetPartyEntryUpdatesEnabled(u32 value)
{
    if (gManagedActorGlobals != 0) {
        *(u32 *)(gManagedActorGlobals + 0x8c) = value;
    }
}
