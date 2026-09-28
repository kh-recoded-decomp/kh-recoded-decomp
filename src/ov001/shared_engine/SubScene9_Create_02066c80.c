#include "nitro/types.h"

extern void *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void func_020524e8(void *state);
extern u32 data_ov001_020a0468;

u32 SubScene9_Create_02066c80(void)
{
    u8 *heap;

    heap = (u8 *)NNSi_FndGetCurrentRootHeap_0202a764();
    data_ov001_020a0468 = (u32)heap;
    *heap = 0;
    func_020524e8(heap + 8);
    return 0x2066cb5;
}
