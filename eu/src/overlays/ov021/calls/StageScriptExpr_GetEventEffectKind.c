#include "nitro/types.h"

extern u32 gActiveFieldContextStorage;

u32 StageScriptExpr_GetEventEffectKind(int self)
{
    s32 entry;

    entry = gActiveFieldContextStorage;
    if (gActiveFieldContextStorage == 0) {
        return 0;
    }
    *(u16 *)(self + 0x2c) = 1;
    *(u32 *)(self + 0x30) = (u32)*(u8 *)(entry + 0xc);
    return 0;
}
