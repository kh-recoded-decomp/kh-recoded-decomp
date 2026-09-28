#include "nitro/types.h"

extern int ZeroHalfThenFree_0202cd78(void *arg0);

extern u32 g_manager_020a049c;

void func_ov001_0206d718(void)
{
    int base;
    int i;

    base = g_manager_020a049c;
    i = 0;
    do {
        ZeroHalfThenFree_0202cd78(*(void **)(base + i * 4 + 0xb8));
        i = i + 1;
    } while (i < 9);
}
