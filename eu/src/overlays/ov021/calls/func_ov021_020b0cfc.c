#include "nitro/types.h"

extern u32 data_ov021_020b56c4;
extern u32 GetStageMotionRecord();
extern u32 SlotTable_FindNearestFree();
extern u32 ResolveTaggedValueRef();
extern u32 TaggedValueToFixed();

u32 func_ov021_020b0cfc(int self, int args)
{
    u32 resolved;
    s32 member;
    u32 value;

    resolved = ResolveTaggedValueRef(self, args + 8);
    if (data_ov021_020b56c4 == 0) {
        return 0;
    }
    member = GetStageMotionRecord(*(u16 *)(data_ov021_020b56c4 + 0x16));
    if (member == 0) {
        return 0;
    }
    *(u16 *)(self + 0x2c) = 1;
    value = TaggedValueToFixed(resolved);
    value = SlotTable_FindNearestFree(member, value, 0, 0xffffffff);
    *(u32 *)(self + 0x30) = value;
    return 0;
}
