#include "nitro/types.h"

extern u32 gStageEventContext;

void QueueStageEventRequestIfEmpty(u8 byteValue, u16 wordValue)
{
    u8 *ctx;

    ctx = (u8 *)gStageEventContext;
    if (*(s8 *)(ctx + 6) < 0) {
        ctx[6] = byteValue;
        *(u16 *)(ctx + 4) = wordValue;
    }
}
