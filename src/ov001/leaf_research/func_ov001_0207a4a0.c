#include "nitro/types.h"

extern void func_ov001_020715ac(void);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

extern u32 g_activeContext_020a04c4;

void func_ov001_0207a4a0(void)
{
    u32 context;

    context = g_activeContext_020a04c4;
    if (*(u32 *)(g_activeContext_020a04c4 + 0xd4) != 0) {
        func_ov001_020715ac();
        *(u32 *)(context + 0xd4) = 0;
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4((void *)*(u32 *)(context + 0xd0));
    g_activeContext_020a04c4 = 0;
}
