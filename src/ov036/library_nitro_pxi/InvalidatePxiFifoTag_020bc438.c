#include "nitro/types.h"

extern u32 g_pxiFifoTag_020c36c0;
extern void func_0202a638(u32 tag);

void InvalidatePxiFifoTag_020bc438(void)
{
    func_0202a638(g_pxiFifoTag_020c36c0);
    g_pxiFifoTag_020c36c0 = 0xffffffff;
}
