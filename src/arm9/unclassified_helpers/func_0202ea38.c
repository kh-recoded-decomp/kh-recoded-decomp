#include "nitro/types.h"

extern int func_0202c940(void *info, int textureId, int flag, void *extra);
extern void func_0202e854(void *dst, void *src, int result, u16 field);

BOOL func_0202ea38(void *dst, void *src, void *info, void *extra)
{
    int result = func_0202c940(info, 0, 1, extra);
    u16 field = *(u16 *)((u8 *)info + 6);
    func_0202e854(dst, src, result, field);
    return TRUE;
}
