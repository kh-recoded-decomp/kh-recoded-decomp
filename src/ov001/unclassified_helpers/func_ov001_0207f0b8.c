#include "nitro/types.h"

extern void *func_ov001_0207ee14();
extern void AcquireSharedRecord_0202c764(void *ptr, u32 param2, u32 param3);

u32 func_ov001_0207f0b8(u32 param1, u32 param2, u32 param3)
{
    void *ptr;

    ptr = func_ov001_0207ee14();
    AcquireSharedRecord_0202c764(ptr, param2, param3);
    return 1;
}
