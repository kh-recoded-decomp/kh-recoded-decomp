#include "nitro/types.h"

extern u32 g_mobiClipSrcHandle_020bcf80;
extern void PXI_Init_0202a638(u32 handle);
extern void func_0204f98c(void);
extern void func_0204fabc(void);

void MobiClip_CloseDecoder_020bac28(void)
{
    PXI_Init_0202a638(g_mobiClipSrcHandle_020bcf80);
    g_mobiClipSrcHandle_020bcf80 = 0xffffffff;
    func_0204f98c();
    func_0204fabc();
}
