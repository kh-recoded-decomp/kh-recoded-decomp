#include "nitro/types.h"

extern void *RetainOrInitializeSharedRecord_0202c80c(int a, int b);
extern void func_0202eb84(void *dst, int flags, void *info, int zero, int b);

void func_0202edd8(void *dst, int a, void *info, int b)
{
    void *record = RetainOrInitializeSharedRecord_0202c80c(a, b);
    *(void **)((u8 *)dst + 0x74) = record;
    func_0202eb84(dst, 0, info, 0, b);
}
