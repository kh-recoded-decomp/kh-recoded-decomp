#include "nitro/types.h"

extern void *PXI_Init_0202a64c();

extern u32 data_ov001_0209eb08;

void func_ov001_0206a714(void)
{
    PXI_Init_0202a64c(data_ov001_0209eb08);
    data_ov001_0209eb08 = 0xffffffff;
}
