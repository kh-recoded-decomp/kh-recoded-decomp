#include "nitro/types.h"

extern void *NNSi_FndGetCurrentRootHeap_0202a764(void);

BOOL func_ov022_020a73d8(void)
{
    u8 *state = (u8 *)NNSi_FndGetCurrentRootHeap_0202a764();

    return *(s32 *)(state + 0x8b0) == 2;
}
