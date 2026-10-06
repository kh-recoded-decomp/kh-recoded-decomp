#include "nitro/types.h"

extern u32 data_ov021_020b56c4;
extern u32 GetStageMotionRecord();
extern u32 GetGridCellCenter();

u32 func_ov021_020b1af4(int self)
{
    s32 member;

    member = GetStageMotionRecord(*(u16 *)(data_ov021_020b56c4 + 0x16));
    if (member != 0) {
        GetGridCellCenter(member, **(u32 **)(member + 0x20), self + 0x34);
    }
    return 0;
}
