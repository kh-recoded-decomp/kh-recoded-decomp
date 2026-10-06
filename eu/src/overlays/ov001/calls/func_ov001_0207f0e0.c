#include "nitro/types.h"

extern void *ObjectManager_GetFirstEntryParam();
extern void AcquireSharedRecord(void *ptr, u32 param2, u32 param3);

u32 func_ov001_0207f0e0(u32 param1, u32 param2, u32 param3)
{
    void *ptr;

    ptr = ObjectManager_GetFirstEntryParam();
    AcquireSharedRecord(ptr, param2, param3);
    return 1;
}
