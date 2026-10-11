#include "nitro/types.h"

extern void *PXI_Init_0202a64c();

extern u32 gScreenFadeTaskHandle;

void func_ov001_0206a714(void)
{
    PXI_Init_0202a64c(gScreenFadeTaskHandle);
    gScreenFadeTaskHandle = 0xffffffff;
}
