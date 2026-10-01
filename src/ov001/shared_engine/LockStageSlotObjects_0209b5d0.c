#include "nitro/types.h"

typedef struct StageObject {
    u8 pad0[6];
    u16 flags;
    u8 pad8[0x1c0];
} StageObject;

typedef struct StageManager {
    u8 pad_00000[0x210];
    StageObject *objects;
    u8 pad_00214[0x18bd2];
    u16 slotCount;
} StageManager;

typedef struct StageSlot {
    u8 pad_00[0xa];
    s16 firstObject;
    s16 lastObject;
} StageSlot;

extern StageManager *g_stageManager_020a0508;
extern StageSlot *GetStageObjectHandle_0209c0c4(u32 id);
extern void ReleaseStageSlotLocks_0209b4f8(u32 index, u32 mask);

void LockStageSlotObjects_0209b5d0(u32 index) {
    int i;
    StageSlot *slot;

    if (index < g_stageManager_020a0508->slotCount) {
        slot = GetStageObjectHandle_0209c0c4((u16)(index + 1));
        if (slot != NULL) {
            for (i = slot->firstObject; i <= slot->lastObject; i++) {
                g_stageManager_020a0508->objects[i].flags |= 0x2000;
            }
            ReleaseStageSlotLocks_0209b4f8(index, 1);
        }
    }
}
