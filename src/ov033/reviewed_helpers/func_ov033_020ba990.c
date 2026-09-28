#include "nitro/types.h"

extern int data_020baa80;
extern void *PXI_Init_0202a638(int argument0);

void func_ov033_020ba990(void)
{
    PXI_Init_0202a638(data_020baa80);
    data_020baa80 = -1;
}
