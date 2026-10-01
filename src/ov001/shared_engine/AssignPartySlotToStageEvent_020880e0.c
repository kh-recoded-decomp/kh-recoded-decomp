#include "nitro/types.h"

typedef struct StageEventRecord {
    u8 pad_000[4];
    u16 active : 1;
    u16 unk_04_1 : 15;
    u16 unk_06_0 : 8;
    u16 partyBound : 1;
    u16 claimed : 1;
    u16 unk_06_10 : 6;
    u8 pad_008[6];
    u16 kind;
    u8 pad_010[0x1a7];
    u8 partyMode : 2;
    u8 partyParam : 6;
} StageEventRecord;

typedef struct PartySlot {
    u16 kind;
    u16 eventId;
    u8 pad_04[0x28];
} PartySlot;

extern int data_ov001_0209f2c8;
extern void func_ov001_0209c3c0(void);
extern u16 FindFirstActiveStageEvent_0209c940(void);
extern u32 func_ov001_0209c99c(int startHandle);
extern StageEventRecord *GetStageEventRecord_0209c0ec(u32 id);
extern PartySlot *GetStagePartySlot_0209c1d4(u32 slot);
extern void func_01ff8830(void *dst, int value, u32 size);

void AssignPartySlotToStageEvent_020880e0(u32 slotIndex, u8 mode, u8 param)
{
    u32 id;
    StageEventRecord *record;
    PartySlot *slot;

    if (data_ov001_0209f2c8 == -1) {
        return;
    }
    func_ov001_0209c3c0();
    for (id = FindFirstActiveStageEvent_0209c940(); id != 0; id = func_ov001_0209c99c(id)) {
        record = GetStageEventRecord_0209c0ec(id);
        if (record != NULL && record->kind == 99 && !record->claimed) {
            slot = GetStagePartySlot_0209c1d4(slotIndex);
            record->active = 1;
            record->claimed = 1;
            record->partyBound = 1;
            record->partyMode = mode;
            record->partyParam = param;
            func_01ff8830(slot, 0, sizeof(PartySlot));
            slot->kind = 99;
            slot->eventId = id;
            return;
        }
    }
}
