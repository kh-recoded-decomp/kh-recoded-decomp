#include "nitro/types.h"

extern void *GetRecordTableBEntry_02052238(s32 index);
extern s32 func_02051ea8(s32 id);
extern void func_02051d3c(s32 id, s32 value);
extern void func_02051dfc(s32 id);
extern void func_ov002_020663d0(u32 dst, u32 value, u32 maxLen);

void CopyRecordTableBField_02069d04(s32 index, u32 dst) {
    s32 wasLocked = func_02051ea8(9);
    u32 entry;

    if (wasLocked == 0) {
        func_02051d3c(9, 1);
    }
    entry = (u32)GetRecordTableBEntry_02052238(index);
    func_ov002_020663d0(dst, *(u32 *)(entry + 0x14), 0x3f);
    if (wasLocked != 0) {
        return;
    }
    func_02051dfc(9);
}
