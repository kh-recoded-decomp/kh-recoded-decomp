#include "nitro/types.h"

extern u32 g_pxiFifoTag_020bc780;
extern void PXI_Init_0202a638(u32 tag);
extern void func_0204f98c(void);
extern void func_0204fabc(void);

void ReleasePxiFifoTag_020bb4f8(void)
{
    PXI_Init_0202a638(g_pxiFifoTag_020bc780);
    g_pxiFifoTag_020bc780 = 0xffffffff;
    func_0204f98c();
    func_0204fabc();
}
