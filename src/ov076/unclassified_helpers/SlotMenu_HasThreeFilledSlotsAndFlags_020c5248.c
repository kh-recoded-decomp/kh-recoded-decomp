#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00000[0x49818];
    u16 slotPoints[8];
} SlotMenu;

typedef struct SaveData {
    u8 pad_0000[0x2c68];
    u8 extraSlotCount;
} SaveData;

extern SaveData *data_0205fe0c;
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);

BOOL SlotMenu_HasThreeFilledSlotsAndFlags_020c5248(SlotMenu *menu)
{
    int slotCount = data_0205fe0c->extraSlotCount + 3;
    int slot = 0;
    int filledCount = 0;

    for (; slot < slotCount; slot++) {
        if (menu->slotPoints[slot] != 0 && ++filledCount == 3) {
            if (IsGlobalPackedBitSet_02027304(0xf74) && IsGlobalPackedBitSet_02027304(0xf75) &&
                IsGlobalPackedBitSet_02027304(0xf7a) && IsGlobalPackedBitSet_02027304(0xf78) &&
                IsGlobalPackedBitSet_02027304(0xf79) && IsGlobalPackedBitSet_02027304(0xf7d)) {
                return TRUE;
            }
            return FALSE;
        }
    }
    return FALSE;
}
