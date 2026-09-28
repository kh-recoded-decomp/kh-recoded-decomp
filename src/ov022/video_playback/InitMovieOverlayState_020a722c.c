#include "nitro/types.h"

extern void *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void PXI_Init_020a8a44(void *arg);
extern void func_02001474(void *arg);
extern void func_020257e4(void *arg);
extern void StoreGlobalArrayEntry_02025668(s32 index, s32 value);
extern s32 data_020b7be0;
extern void *data_020b7d80;
extern void func_02028bcc(void);

void InitMovieOverlayState_020a722c(void)
{
    u8 *state = (u8 *)NNSi_FndGetCurrentRootHeap_0202a764();

    PXI_Init_020a8a44(state + 0x830);
    func_02001474(state + 0x824);
    func_020257e4(state + 4);
    StoreGlobalArrayEntry_02025668(3, 0);
    data_020b7be0 = -1;
    data_020b7d80 = 0;
    func_02028bcc();
}
