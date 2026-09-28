#include "nitro/types.h"

extern u32 g_moviePlayerCtx_020bd000;
extern void func_0204df9c(u32 arg);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void PXI_Init_0202a638(u32 channel);
extern void func_ov001_020667b4(void);
extern void func_ov001_0206a714(void);
extern void ArmObject_0206c6f4(void);
extern void func_ov001_02063c54(void);

void MoviePlayer_Close_020ba518(void)
{
    func_0204df9c(0);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(*(void **)(g_moviePlayerCtx_020bd000 + 0x30));
    PXI_Init_0202a638(*(u32 *)(g_moviePlayerCtx_020bd000 + 0x18));
    PXI_Init_0202a638(*(u32 *)(g_moviePlayerCtx_020bd000 + 0x1c));
    func_ov001_020667b4();
    if (*(s32 *)(g_moviePlayerCtx_020bd000 + 0x14) != -1) {
        func_ov001_0206a714();
        *(u32 *)(g_moviePlayerCtx_020bd000 + 0x14) = 0xffffffff;
    }
    ArmObject_0206c6f4();
    func_ov001_02063c54();
    g_moviePlayerCtx_020bd000 = 0;
}
