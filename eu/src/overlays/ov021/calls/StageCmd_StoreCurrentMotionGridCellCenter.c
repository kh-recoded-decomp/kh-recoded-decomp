#include "nitro/types.h"

extern u32 gActiveFieldContextStorage;
extern u32 GetStageMotionRecord();
extern u32 GetGridCellCenter();

u32 StageCmd_StoreCurrentMotionGridCellCenter(int self)
{
    s32 member;

    member = GetStageMotionRecord(*(u16 *)(gActiveFieldContextStorage + 0x16));
    if (member != 0) {
        GetGridCellCenter(member, **(u32 **)(member + 0x20), self + 0x34);
    }
    return 0;
}
