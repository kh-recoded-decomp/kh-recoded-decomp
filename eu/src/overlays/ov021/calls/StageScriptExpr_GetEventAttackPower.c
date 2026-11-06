#include "nitro/types.h"

extern u32 gActiveFieldContextStorage;
extern s32 ResolveTaggedValueRef();
extern u32 GetEntryScaledValue();

u32 StageScriptExpr_GetEventAttackPower(int self, int args)
{
    s32 entry;
    s32 resolved;
    u32 value;

    resolved = ResolveTaggedValueRef(self, args + 8);
    entry = gActiveFieldContextStorage;
    if (gActiveFieldContextStorage == 0) {
        return 0;
    }
    *(u16 *)(self + 0x2c) = 0x10;
    value = GetEntryScaledValue(entry, *(s32 *)(resolved + 4) + 1U & 0xffff);
    *(u32 *)(self + 0x30) = value;
    return 0;
}
