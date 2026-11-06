#include "nitro/types.h"

extern u32 gActiveFieldContextStorage;
extern u32 GetStageMotionRecord();

u32 func_ov021_020b0edc(int self)
{
    s32 member;

    if (gActiveFieldContextStorage == 0) {
        return 0;
    }
    member = GetStageMotionRecord(*(u16 *)(gActiveFieldContextStorage + 0x16));
    if (member == 0) {
        return 0;
    }
    *(u16 *)(self + 0x2c) = 1;
    *(u32 *)(self + 0x30) = *(u32 *)(member + 0x18);
    return 0;
}
