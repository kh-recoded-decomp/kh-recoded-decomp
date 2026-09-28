#include "nitro/types.h"

extern void *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void func_01ff8740(u32 value, void *dest, u32 size);
extern u32 data_ov001_020a0474;

u32 SubScene9_Create_02068c0c(u32 *cfg)
{
    u32 *state;

    state = (u32 *)NNSi_FndGetCurrentRootHeap_0202a764();
    data_ov001_020a0474 = (u32)state;
    func_01ff8740(0, state, 0x2c);
    *state = *cfg;
    *(u16 *)((u8 *)state + 0x22) = 0x1000;
    return 0x2068c51;
}
