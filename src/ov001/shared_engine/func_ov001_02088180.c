#include "nitro/types.h"

typedef struct StagePartySlot {
    u16 unk_00;
    u16 recordId;
} StagePartySlot;

typedef struct StageRecord {
    u8 pad_00[0x6];
    u16 flags;
} StageRecord;

extern s32 g_activeService_0209f2c8;
extern void func_ov001_0209c3c0(void);
extern u16 func_ov001_0209c940(void);
extern u16 func_ov001_0209c99c(u16 recordId);
extern StagePartySlot *GetStagePartySlot_0209c1d4(u32 slot);
extern StageRecord *GetStageEventRecord_0209c0ec(u32 id);
extern void func_01ff8830(void *dst, s32 value, u32 size);

void func_ov001_02088180(u32 slotIndex)
{
    u16 recordId;
    StagePartySlot *slot;
    StageRecord *record;

    if (g_activeService_0209f2c8 == -1) {
        return;
    }
    func_ov001_0209c3c0();
    for (recordId = func_ov001_0209c940(); recordId != 0; recordId = func_ov001_0209c99c(recordId)) {
        slot = GetStagePartySlot_0209c1d4(slotIndex);
        if (slot != NULL && slot->recordId != 0) {
            record = GetStageEventRecord_0209c0ec(slot->recordId);
            if (record != NULL) {
                record->flags = record->flags & ~0x200;
            }
            func_01ff8830(slot, 0, 0x2c);
        }
    }
}
