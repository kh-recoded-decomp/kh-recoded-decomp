#include "nitro/types.h"

extern s32 func_ov002_02069504(u32 target, s32 category, s32 flag);
extern void func_ov002_020682c4(u32 param1, u32 param2, s32 category, u32 param4);

void SyncMismatchedCategoryEntries_020683bc(u32 param1, u32 param2, u32 param3, u32 param4) {
    s32 category = 3;
    s32 valueA;
    s32 valueB;

    do {
        valueA = func_ov002_02069504(*(u32 *)(param2 + 0x18), category, 1);
        valueB = func_ov002_02069504(param3, category, 1);
        if (valueA != 0 && valueA != valueB) {
            func_ov002_020682c4(param1, param2, category, param4);
        }
        category = category + 1;
    } while (category < 0x16);
}
