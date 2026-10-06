#include "nitro/types.h"

extern void *ObjectManager_GetSecondEntryParam();
extern void func_0202c38c(void *ptr, u32 value);

void func_ov001_0207f0d0(u32 param1, u32 value)
{
    void *ptr;

    ptr = ObjectManager_GetSecondEntryParam();
    func_0202c38c(ptr, value);
}
