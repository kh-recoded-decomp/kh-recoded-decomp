#include "nitro/types.h"

extern u32 data_ov001_020a0490;

void QueueStageEventRequestIfEmpty(u8 byteValue, u16 wordValue)
{
    u8 *ctx;

    ctx = (u8 *)data_ov001_020a0490;
    if (*(s8 *)(ctx + 6) < 0) {
        ctx[6] = byteValue;
        *(u16 *)(ctx + 4) = wordValue;
    }
}
