#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x18de6];
    u16 slotCount;
} StageManager;

typedef struct {
    u8 pad_00[9];
    u8 active : 1;
    u8 pending : 1;
} StageSlot;

extern StageManager *g_stageManager_020a0508;
extern StageSlot *func_ov001_0209c0c4(u32 id);

void ActivateStageSlot_0209caa8(u32 index)
{
    StageSlot *slot;

    if (index < g_stageManager_020a0508->slotCount) {
        slot = func_ov001_0209c0c4((index + 1) & 0xffff);
        slot->active = 1;
        slot->pending = 0;
    }
}
