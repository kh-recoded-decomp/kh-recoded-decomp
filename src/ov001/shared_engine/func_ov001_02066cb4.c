#include "nitro/types.h"

extern void *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void func_ov001_02066da4(u32 param);
extern void func_0204d8d0(u32 param1, u32 param2);

u32 func_ov001_02066cb4(void)
{
    s8 *state;
    u32 result;

    state = (s8 *)NNSi_FndGetCurrentRootHeap_0202a764();
    result = 0;
    if (*state == 1) {
        *state = 2;
        func_ov001_02066da4(1);
        func_0204d8d0(0, 0x19);
        result = 0x2066ce1;
    }
    return result;
}
