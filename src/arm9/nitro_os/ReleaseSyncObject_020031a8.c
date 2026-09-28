#include "nitro/types.h"

extern void func_02003294(void *obj, u32 tag);

void ReleaseSyncObject_020031a8(void *obj)
{
    func_02003294(obj, 0x10000000);
}
