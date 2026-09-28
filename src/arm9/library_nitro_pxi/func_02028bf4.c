#include "nitro/types.h"

extern void *PXI_Init_0202a638(u32 unused);
extern u8 data_0205fea8[];

void func_02028bf4(void)
{
    PXI_Init_0202a638(*(u32 *)(data_0205fea8 + 0x14));
    PXI_Init_0202a638(*(u32 *)(data_0205fea8 + 0x18));
}
