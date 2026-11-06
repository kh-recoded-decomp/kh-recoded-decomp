#include "nitro/types.h"

extern u32 gManagedActorGlobals;

int GetFieldEntryGroupId(int index)
{
    return (int)*(short *)(gManagedActorGlobals + index * 2 + 0xa0);
}
