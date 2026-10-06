#include "nitro/types.h"

extern s32 data_ov001_0209f2e8;
extern void ResetGroupRows(u32 groupIndex);
extern void RestoreStageSlotDefault(u32 groupIndex);

void func_ov001_02087e24(u32 groupIndex)
{
    if (data_ov001_0209f2e8 != -1) {
        ResetGroupRows(groupIndex);
        RestoreStageSlotDefault(groupIndex);
    }
}
