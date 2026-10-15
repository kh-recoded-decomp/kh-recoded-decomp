#include "nitro/types.h"

typedef struct SlotPair {
    u16 first;
    u16 second;
} SlotPair;

typedef struct SaveData {
    u8 unknown0000[0x2c68];
    u8 extraSlotCount;
    u8 unknown2c69[0x2d84 - 0x2c69];
    SlotPair slotPairs[8];
} SaveData;

typedef char SlotPairIsFourBytes[sizeof(SlotPair) == 4 ? 1 : -1];
typedef char ExtraSlotCountOffset[
    (u32)&((SaveData *)0)->extraSlotCount == 0x2c68 ? 1 : -1];
typedef char SlotPairsOffset[
    (u32)&((SaveData *)0)->slotPairs == 0x2d84 ? 1 : -1];

extern SaveData *data_0205fe0c;
extern u16 GetPrimaryRecordCount(void);

static inline BOOL IsPrimaryHandle(u32 handle)
{
    BOOL valid = FALSE;
    if (handle >= 0x200 && handle < 0x458) {
        valid = TRUE;
    }
    return valid;
}

static inline int ReadPairHandle(SaveData *save, int slot, BOOL secondary)
{
    if (secondary) {
        return save->slotPairs[slot].second;
    }
    return save->slotPairs[slot].first;
}

static inline void AccumulateSlotPair(u32 first, u32 second,
                                     int *occupiedCount, BOOL *unpaired)
{
    *occupiedCount += IsPrimaryHandle(first) ? 1 : 0;
    *occupiedCount += IsPrimaryHandle(second) ? 1 : 0;
    if (first != 0xffff && second == 0xffff) {
        *unpaired = TRUE;
    }
}

/* An unpaired slot needs another primary record that is not already equipped. */
BOOL SlotMenu_HasUnpairedSlotAndStock(void *unusedMenu)
{
    SaveData *save = data_0205fe0c;
    int occupiedCount;
    int slotCount;
    int slot;
    BOOL unpaired;

    slotCount = save->extraSlotCount + 3;
    unpaired = FALSE;
    occupiedCount = slot = 0;

    for (; slot < slotCount; slot++) {
        AccumulateSlotPair(ReadPairHandle(save, slot, FALSE),
                           ReadPairHandle(save, slot, TRUE),
                           &occupiedCount, &unpaired);
    }
    if (unpaired) {
        unpaired = occupiedCount < GetPrimaryRecordCount() ? TRUE : FALSE;
    }
    return unpaired;
}
