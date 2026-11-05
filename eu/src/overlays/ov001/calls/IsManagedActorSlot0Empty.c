#include "nitro/types.h"

extern int GetBoundedEntryField(int index);

BOOL IsManagedActorSlot0Empty(void)
{
    int result;

    result = GetBoundedEntryField(0);
    return result == 0;
}
