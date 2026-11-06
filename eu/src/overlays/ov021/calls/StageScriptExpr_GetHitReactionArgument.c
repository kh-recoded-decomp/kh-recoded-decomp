#include "nitro/types.h"

extern u32 gActiveFieldContextStorage;

u32 StageScriptExpr_GetHitReactionArgument(int self)
{
    s32 entry;

    entry = gActiveFieldContextStorage;
    if (gActiveFieldContextStorage == 0) {
        return 0;
    }
    *(u16 *)(self + 0x2c) = 1;
    *(u32 *)(self + 0x30) = (u32)*(u16 *)(entry + 0x1e);
    return 0;
}
