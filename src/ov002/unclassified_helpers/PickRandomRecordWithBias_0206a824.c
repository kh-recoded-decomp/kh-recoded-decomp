#include "nitro/types.h"

extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern void ReleaseRecordSlot_02051dfc(s32 slot);
extern unsigned int func_0202a9d0(unsigned int range);
extern void func_ov002_0206aaa0(s32 *itemIds);
extern s32 PickRandomAvailableRecord_0206a888(s32 category, s32 *preferredItemIds);

s32 PickRandomRecordWithBias_0206a824(s32 category)
{
    s32 preferred[6];
    s32 result;

    AcquireRecordSlot_02051d3c(9, 1);
    if (func_0202a9d0(100) < 70) {
        func_ov002_0206aaa0(preferred);
        result = PickRandomAvailableRecord_0206a888(category, preferred);
    } else {
        result = PickRandomAvailableRecord_0206a888(category, NULL);
    }
    ReleaseRecordSlot_02051dfc(9);
    return result;
}
