#include "nitro/types.h"

typedef struct StagePartySlot {
    u16 unk_00;
    u16 recordId;
} StagePartySlot;

typedef struct StageRecord {
    u8 pad_00[0x6];
    u16 flags;
} StageRecord;

extern s32 g_stageEventsState;
extern void func_ov001_0209c3e8(void);
extern u16 FindFirstActiveStageEvent(void);
extern u16 func_ov001_0209c9c4(u16 recordId);
extern StagePartySlot *GetStagePartySlot(u32 slot);
extern StageRecord *GetStageEventRecord(u32 id);
extern void MI_CpuFill8(void *dst, s32 value, u32 size);

void func_ov001_020881a8(u32 slotIndex)
{
    u16 recordId;
    StagePartySlot *slot;
    StageRecord *record;

    if (g_stageEventsState == -1) {
        return;
    }
    func_ov001_0209c3e8();
    for (recordId = FindFirstActiveStageEvent(); recordId != 0; recordId = func_ov001_0209c9c4(recordId)) {
        slot = GetStagePartySlot(slotIndex);
        if (slot != NULL && slot->recordId != 0) {
            record = GetStageEventRecord(slot->recordId);
            if (record != NULL) {
                record->flags = record->flags & ~0x200;
            }
            MI_CpuFill8(slot, 0, 0x2c);
        }
    }
}
