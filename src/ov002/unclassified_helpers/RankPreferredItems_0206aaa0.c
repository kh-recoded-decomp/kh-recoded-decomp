#include "nitro/types.h"

typedef struct RecordB {
    u8 pad_00[0x8];
    s32 itemId;
    u8 pad_0C[0xc];
} RecordB;

typedef struct ItemIdList {
    s32 ids[6];
} ItemIdList;

extern const ItemIdList data_ov002_0206ae0c;
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern void ReleaseRecordSlot_02051dfc(s32 slot);
extern RecordB *GetRecordTableBEntry_02052238(s32 index);
extern int IsRecordFlagBitSet_0206991c(s32 i);
extern void func_01ff8830(void *dest, int value, u32 size);

void RankPreferredItems_0206aaa0(s32 *itemIds)
{
    u16 counts[6];
    ItemIdList defaults = data_ov002_0206ae0c;
    int slot;
    int index;
    int i;
    RecordB *record;
    u16 count;
    s32 swapId;

    AcquireRecordSlot_02051d3c(9, 1);
    for (i = 0; i < 6; i++) {
        itemIds[i] = defaults.ids[i];
    }
    func_01ff8830(counts, 0, sizeof(counts));
    for (index = 0x60; index < 0x5a1; index++) {
        if (IsRecordFlagBitSet_0206991c(index) > 0) {
            record = GetRecordTableBEntry_02052238(index);
            if (record != NULL && record->itemId != -1) {
                counts[defaults.ids[record->itemId]]++;
            }
        }
    }
    ReleaseRecordSlot_02051dfc(10);
    for (index = 0; index < 6; index++) {
        for (slot = 0; slot < 5; slot++) {
            if (counts[slot] < counts[slot + 1]) {
                count = counts[slot];
                counts[slot] = counts[slot + 1];
                counts[slot + 1] = count;
                swapId = itemIds[slot];
                itemIds[slot] = itemIds[slot + 1];
                itemIds[slot + 1] = swapId;
            }
        }
    }
}
