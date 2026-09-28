#include "nitro/types.h"

extern void func_01ff8830(void *dst, int value, u32 size);

void ClearBuffer_0208f02c(void *dst, u32 size)
{
    func_01ff8830(dst, 0, size);
}
