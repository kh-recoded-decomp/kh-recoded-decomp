#include "nitro/types.h"

extern void *ObjectManager_GetSecondEntryParam();
extern void RequestFileLoadFromHeapTail(void *ptr, u32 value);

void RequestFieldObjectAnimationBuffer(u32 param1, u32 value)
{
    void *ptr;

    ptr = ObjectManager_GetSecondEntryParam();
    RequestFileLoadFromHeapTail(ptr, value);
}
