#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x18de6];
    u16 slotCount;
} StageManager;

typedef struct {
    u8 pad_00[8];
    s8 currentValue;
    u8 pad_09[6];
    s8 defaultValue;
} StageSlot;

extern StageManager *g_stageManager_020a0508;
extern StageSlot *func_ov001_0209c0c4(u32 id);

void RestoreStageSlotDefault_0209ca7c(u32 index)
{
    StageSlot *slot;

    if (index < g_stageManager_020a0508->slotCount) {
        slot = func_ov001_0209c0c4((index + 1) & 0xffff);
        if (slot != NULL) {
            slot->currentValue = slot->defaultValue;
        }
    }
}
