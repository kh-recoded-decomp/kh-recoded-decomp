#include "nitro/types.h"

extern s32 g_stageEventsState;
extern void ResetGroupRows(u32 groupIndex);
extern void RestoreStageSlotDefault(u32 groupIndex);

void func_ov001_02087e24(u32 groupIndex)
{
    if (g_stageEventsState != -1) {
        ResetGroupRows(groupIndex);
        RestoreStageSlotDefault(groupIndex);
    }
}
