#include "nitro/types.h"

extern void *PXI_Init_0202a638();

extern u32 g_pxiChannel_0209eae8;

void func_ov001_0206a714(void)
{
    PXI_Init_0202a638(g_pxiChannel_0209eae8);
    g_pxiChannel_0209eae8 = 0xffffffff;
}
