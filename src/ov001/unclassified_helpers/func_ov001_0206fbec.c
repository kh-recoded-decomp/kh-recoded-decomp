#include "nitro/types.h"

extern void PXI_Init_0202a638();

void func_ov001_0206fbec(u32 context)
{
    PXI_Init_0202a638(*(u32 *)(context + 0x418));
    PXI_Init_0202a638(*(u32 *)(context + 0x414));
    PXI_Init_0202a638(*(u32 *)(context + 0x41c));
    PXI_Init_0202a638(*(u32 *)(context + 0x420));
    PXI_Init_0202a638(*(u32 *)(context + 0x424));
    PXI_Init_0202a638(*(u32 *)(context + 0x428));
    if (*(s32 *)(context + 0x430) != 0) {
        PXI_Init_0202a638();
    }
    if (*(s32 *)(context + 0x434) != 0) {
        PXI_Init_0202a638();
    }
    PXI_Init_0202a638(*(u32 *)(context + 0x438));
}
