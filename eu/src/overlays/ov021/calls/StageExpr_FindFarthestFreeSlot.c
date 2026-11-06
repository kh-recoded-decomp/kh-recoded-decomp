#include "nitro/types.h"

extern u32 gActiveFieldContextStorage;
extern u32 GetStageMotionRecord();
extern u32 SlotTable_FindNearestFree();
extern u32 ResolveTaggedValueRef();
extern u32 TaggedValueToFixed();

u32 StageExpr_FindFarthestFreeSlot(int self, int args)
{
    u32 resolved;
    s32 member;
    u32 value;

    resolved = ResolveTaggedValueRef(self, args + 8);
    if (gActiveFieldContextStorage == 0) {
        return 0;
    }
    member = GetStageMotionRecord(*(u16 *)(gActiveFieldContextStorage + 0x16));
    if (member == 0) {
        return 0;
    }
    *(u16 *)(self + 0x2c) = 1;
    value = TaggedValueToFixed(resolved);
    value = SlotTable_FindNearestFree(member, value, 0, 1);
    *(u32 *)(self + 0x30) = value;
    return 0;
}
