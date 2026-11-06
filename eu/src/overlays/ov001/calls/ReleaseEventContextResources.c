#include "nitro/types.h"

extern int ZeroHalfThenFree(void *arg0);

extern u32 gManagedActorGlobals;

void ReleaseEventContextResources(void)
{
    int base;
    int i;

    base = gManagedActorGlobals;
    i = 0;
    do {
        ZeroHalfThenFree(*(void **)(base + i * 4 + 0xb8));
        i = i + 1;
    } while (i < 9);
}
