#include "nitro/types.h"

extern void *func_ov001_0207ee48();
extern void func_0202c378(void *ptr, u32 value);

void func_ov001_0207f0a8(u32 param1, u32 value)
{
    void *ptr;

    ptr = func_ov001_0207ee48();
    func_0202c378(ptr, value);
}
