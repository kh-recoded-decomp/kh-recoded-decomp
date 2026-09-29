#include "nitro/types.h"

extern u32 func_ov002_02066fc8(void);
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern void ReleaseRecordSlot_02051dfc(s32 slot);
extern void func_ov002_0206a020(u32 source, s32 *outIds);

s32 CountMatchingSlotIds_02069f9c(u32 other) {
    s32 matchCount = 0;
    u32 current = func_ov002_02066fc8();
    s32 ids[2][16];
    s32 index;

    AcquireRecordSlot_02051d3c(9, 1);
    func_ov002_0206a020(current, ids[0]);
    func_ov002_0206a020(other, ids[1]);
    for (index = 0; index < 16; index++) {
        if (ids[0][index] != -1 && ids[0][index] == ids[1][index]) {
            matchCount++;
        }
    }
    ReleaseRecordSlot_02051dfc(9);
    return matchCount;
}
