#include "nitro/types.h"

extern void *func_0202e09c(void *dst, u32 len, const char *fmt, void *args);

void *func_0202e060(void *dst, const char *fmt, ...)
{
    return func_0202e09c(dst, 0x7fffffff, fmt, (void *)(((u32)&fmt & ~3u) + 4));
}
