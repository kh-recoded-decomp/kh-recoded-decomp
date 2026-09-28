#include "nitro/types.h"

extern u32 g_pxiChannel_020bb6a0;
extern void *PXI_Init_0202a638();

void ReleasePxiChannel_020bac10(void)
{
    PXI_Init_0202a638(g_pxiChannel_020bb6a0);
    g_pxiChannel_020bb6a0 = 0xffffffff;
}
