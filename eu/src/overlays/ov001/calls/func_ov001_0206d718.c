#include "nitro/types.h"

extern int ZeroHalfThenFree(void *arg0);

extern u32 data_ov001_020a04bc;

void func_ov001_0206d718(void)
{
    int base;
    int i;

    base = data_ov001_020a04bc;
    i = 0;
    do {
        ZeroHalfThenFree(*(void **)(base + i * 4 + 0xb8));
        i = i + 1;
    } while (i < 9);
}
