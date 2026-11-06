#include "nitro/types.h"

extern u32 gActiveFieldContextStorage;

u32 StageScriptExpr_GetEventCountdown(int self)
{
    s32 entry;

    entry = gActiveFieldContextStorage;
    if (gActiveFieldContextStorage == 0) {
        return 0;
    }
    *(u16 *)(self + 0x2c) = 0x10;
    *(u32 *)(self + 0x30) = *(u32 *)(entry + 0x1a0);
    return 0;
}
