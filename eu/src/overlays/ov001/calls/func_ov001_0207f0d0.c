#include "nitro/types.h"

extern void *ObjectManager_GetSecondEntryParam();
extern void RequestFileLoadFromHeapTail(void *ptr, u32 value);

void func_ov001_0207f0d0(u32 param1, u32 value)
{
    void *ptr;

    ptr = ObjectManager_GetSecondEntryParam();
    RequestFileLoadFromHeapTail(ptr, value);
}
