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

extern int g_stageEventsState;
extern void func_ov001_0209c3e8(void);
extern u16 FindFirstActiveStageEvent(void);
extern u32 func_ov001_0209c9c4(int startHandle);
extern StageEventRecord *GetStageEventRecord(u32 id);
extern PartySlot *GetStagePartySlot(u32 slot);
extern void MI_CpuFill8(void *dst, int value, u32 size);

void AssignPartySlotToStageEvent(u32 slotIndex, u8 mode, u8 param)
{
    u32 id;
    StageEventRecord *record;
    PartySlot *slot;

    if (g_stageEventsState == -1) {
        return;
    }
    func_ov001_0209c3e8();
    for (id = FindFirstActiveStageEvent(); id != 0; id = func_ov001_0209c9c4(id)) {
        record = GetStageEventRecord(id);
        if (record != NULL && record->kind == 99 && !record->claimed) {
            slot = GetStagePartySlot(slotIndex);
            record->active = 1;
            record->claimed = 1;
            record->partyBound = 1;
            record->partyMode = mode;
            record->partyParam = param;
            MI_CpuFill8(slot, 0, sizeof(PartySlot));
            slot->kind = 99;
            slot->eventId = id;
            return;
        }
    }
}
