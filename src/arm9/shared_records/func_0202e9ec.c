#include "nitro/types.h"

extern void *RetainOrInitializeSharedRecord_0202c80c(int a, int b);
extern int func_0202c940(void *info, int flags, int one);
extern void func_0202e854(void *dst, void *src, int result, int b);

BOOL func_0202e9ec(void *dst, void *src, int a, int b)
{
    void *record = RetainOrInitializeSharedRecord_0202c80c(a, b);
    *(void **)((u8 *)dst + 0xc) = record;
    int result = func_0202c940(record, 0, 1);
    func_0202e854(dst, src, result, b);
    return TRUE;
}
