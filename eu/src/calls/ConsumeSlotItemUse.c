/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 kh-recoded-decomp contributors
 * Adapted from src/arm9/record_management/func_02029468.c.
 */
#include "src/EquipmentSlotWork.h"

typedef struct EquipmentSlotWorkPair {
    EquipmentSlotWork first;
    EquipmentSlotWork second;
} EquipmentSlotWorkPair;

typedef char EquipmentSlotWorkPairIs24Bytes[sizeof(EquipmentSlotWorkPair) == 24 ? 1 : -1];

typedef struct SlotUseSaveData {
    u8 unknown0000[0x28d8];
    u8 itemCounts[0x390];
    u8 extraSlotCount;
    u8 unknown2c69[0x2d84 - 0x2c69];
    u16 slotHandles[30];
    u32 slotUses[15];
} SlotUseSaveData;

typedef char ItemCountsOffset[(u32)&((SlotUseSaveData *)0)->itemCounts == 0x28d8 ? 1 : -1];
typedef char SlotHandlesOffset[(u32)&((SlotUseSaveData *)0)->slotHandles == 0x2d84 ? 1 : -1];
typedef char SlotUsesOffset[(u32)&((SlotUseSaveData *)0)->slotUses == 0x2dc0 ? 1 : -1];

extern SlotUseSaveData *data_0205fe0c;

/* Consume one equipped stack item and return its remaining slot uses. */
int ConsumeSlotItemUse(int slotIndex)
{
    int byteOffset = slotIndex * 4;
    u32 *uses = (u32 *)((u8 *)data_0205fe0c->slotUses + byteOffset);
    EquipmentSlotWorkPair *slotPairs = (EquipmentSlotWorkPair *)gEquipmentSlotWork;
    EquipmentSlotWork *slot = &slotPairs[slotIndex].first;

    if (slot->state == 3 && *uses != 0) {
        u32 itemId = *(u16 *)((u8 *)data_0205fe0c->slotHandles + byteOffset);
        u8 *itemCount = &data_0205fe0c->itemCounts[itemId];
        int remaining;

        --*itemCount;
        remaining = *uses - 1;
        *uses = remaining;
        return remaining;
    }
    return -1;
}
