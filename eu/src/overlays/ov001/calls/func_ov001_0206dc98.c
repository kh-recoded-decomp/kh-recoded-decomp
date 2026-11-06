#include "nitro/types.h"

extern u32 gManagedActorGlobals;

void func_ov001_0206dc98(void)
{
    if (gManagedActorGlobals != 0) {
        *(u32 *)(gManagedActorGlobals + 0xf8) = 0;
    }
}
