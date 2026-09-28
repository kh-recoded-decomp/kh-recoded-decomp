#include "nitro/types.h"

extern int func_0200b850(void *buffer, u32 a, u32 b);
extern int func_0200ba34(void *buffer);
extern void func_0200bb74(void *buffer);

BOOL func_0200bd64(u32 a, u32 b) {
    int ok;
    BOOL result;
    u8 buffer[44];

    result = 0;
    ok = func_0200b850(buffer, a, b);
    if ((ok != 0) && (ok = func_0200ba34(buffer), ok != 0)) {
        func_0200bb74(buffer);
        result = 1;
    }
    return result;
}
