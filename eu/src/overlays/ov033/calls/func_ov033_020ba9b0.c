#include "nitro/types.h"

extern int data_ov033_020baaa0;
extern void *PXI_Init_0202a64c(int argument0);

void func_ov033_020ba9b0(void)
{
    PXI_Init_0202a64c(data_ov033_020baaa0);
    data_ov033_020baaa0 = -1;
}
