#include "nitro/types.h"

extern u32 data_ov001_0209efd4;
extern void OS_SNPrintf_02002468(void *buffer, u32 size, const char *format, ...);
extern u32 func_0202cc6c(void *buffer, u32 arg1, u32 arg2);

void func_ov001_0207b7bc(u32 *out, u32 value, u32 unused, u32 pad)
{
    char buffer[32];
    u32 padStack;

    padStack = pad;
    OS_SNPrintf_02002468(buffer, 0x20, (const char *)&data_ov001_0209efd4, value);
    *out = func_0202cc6c(buffer, 0xe, 0);
}
