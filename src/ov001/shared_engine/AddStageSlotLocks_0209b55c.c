#include "nitro/types.h"

typedef struct StageManager {
    u8 pad_00000[0x18de6];
    u16 slotCount;
} StageManager;

typedef struct StageSlot {
    u8 pad_00[2];
    u16 state;
    u8 pad_04[5];
    u8 active : 1;
    u8 pending : 1;
    u8 lockMask : 2;
    u8 flag4 : 1;
    u8 released : 1;
} StageSlot;

extern StageManager *g_stageManager_020a0508;
extern StageSlot *GetStageObjectHandle_0209c0c4(u32 id);

void AddStageSlotLocks_0209b55c(u32 index, u32 mask)
{
    StageSlot *slot;

    if (index < g_stageManager_020a0508->slotCount) {
        slot = GetStageObjectHandle_0209c0c4((u16)(index + 1));
        if (slot != NULL) {
            slot->lockMask |= mask;
            if (slot->state == 2) {
                slot->active = 0;
                slot->pending = 1;
            }
        }
    }
}
