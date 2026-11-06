#include "nitro/types.h"

extern u32 gManagedActorGlobals;

u32 GetFieldActorUpdateStepFx12(void)
{
    if (gManagedActorGlobals == 0) {
        return 0x1000;
    }
    return *(u32 *)(gManagedActorGlobals + 0x9c);
}
