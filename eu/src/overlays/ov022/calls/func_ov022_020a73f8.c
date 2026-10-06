#include "nitro/types.h"

extern void *NNSi_FndGetCurrentRootHeap(void);

BOOL func_ov022_020a73f8(void)
{
    u8 *state = (u8 *)NNSi_FndGetCurrentRootHeap();

    return *(s32 *)(state + 0x8b0) == 2;
}
