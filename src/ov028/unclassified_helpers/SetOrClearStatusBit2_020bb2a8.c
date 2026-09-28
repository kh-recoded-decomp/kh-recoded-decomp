#include "nitro/types.h"

extern u32 g_fieldContext_020bb380;

void SetOrClearStatusBit2_020bb2a8(s32 enable)
{
    if (enable != 0) {
        *(u16 *)(g_fieldContext_020bb380 + 6) = *(u16 *)(g_fieldContext_020bb380 + 6) | 4;
        return;
    }
    *(u16 *)(g_fieldContext_020bb380 + 6) = *(u16 *)(g_fieldContext_020bb380 + 6) & 0xfffb;
}
