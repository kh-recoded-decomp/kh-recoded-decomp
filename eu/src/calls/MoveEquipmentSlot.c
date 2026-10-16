#include "nitro/types.h"

typedef struct EquipmentRecordEntry {
    u16 kind : 2;
    u16 flags : 3;
    u16 levelProgress : 11;
    u16 active : 1;
    u16 level : 7;
    u16 category : 8;
} EquipmentRecordEntry;

typedef struct EquipmentSlotWork {
    s32 state;
    u32 limit;
    EquipmentRecordEntry entry;
} EquipmentSlotWork;

typedef union SlotHandlePair {
    u32 packed;
    struct {
        u16 first;
        u16 second;
    } handles;
} SlotHandlePair;

typedef struct InventorySlotData {
    u8 itemCounts[0x390];
    u8 extraSlotCount;
    u8 unknown391[0x4ac - 0x391];
    SlotHandlePair slotHandles[8];
} InventorySlotData;

typedef struct SlotSaveData {
    u8 unknown0000[0x28d8];
    InventorySlotData inventory;
} SlotSaveData;

typedef char EquipmentSlotIs12Bytes[sizeof(EquipmentSlotWork) == 12 ? 1 : -1];
typedef char SlotHandlesAreFourBytes[sizeof(SlotHandlePair) == 4 ? 1 : -1];
typedef char InventoryOffset[(u32)&((SlotSaveData *)0)->inventory == 0x28d8 ? 1 : -1];
typedef char SlotHandleOffset[(u32)&((InventorySlotData *)0)->slotHandles == 0x4ac ? 1 : -1];

extern SlotSaveData *data_0205fe0c;
extern EquipmentSlotWork gEquipmentSlotWork[];
extern void func_01ff8dc8(const void *source, void *destination, u32 size);

/* Move a command pair and its cached records, preserving intervening order. */
void MoveEquipmentSlot(int sourceSlot, int destinationSlot)
{
    if (sourceSlot == destinationSlot) {
        return;
    }

    InventorySlotData *inventory = &data_0205fe0c->inventory;
    int distance = sourceSlot < destinationSlot
        ? destinationSlot - sourceSlot : sourceSlot - destinationSlot;
    int sourceWorkIndex = sourceSlot * 2;
    int destinationWorkIndex = destinationSlot * 2;
    u32 savedHandles = inventory->slotHandles[sourceSlot].packed;
    u32 sourceWorkByteOffset = sourceWorkIndex * sizeof(EquipmentSlotWork);
    EquipmentSlotWork savedFirst = *(EquipmentSlotWork *)(
        (u8 *)gEquipmentSlotWork + sourceWorkByteOffset);
    EquipmentSlotWork savedSecond = *(EquipmentSlotWork *)(
        (u8 *)gEquipmentSlotWork + sourceWorkByteOffset + sizeof(EquipmentSlotWork));
    u32 *moveHandles;
    EquipmentSlotWork *moveWork;
    int direction;

    if (sourceSlot < destinationSlot) {
        moveHandles = &inventory->slotHandles[sourceSlot + 1].packed;
        moveWork = &gEquipmentSlotWork[sourceWorkIndex + 2];
        direction = -1;
    } else {
        moveHandles = &inventory->slotHandles[destinationSlot].packed;
        moveWork = &gEquipmentSlotWork[destinationWorkIndex];
        direction = 1;
    }

    func_01ff8dc8(moveHandles, moveHandles + direction, distance * sizeof(u32));
    func_01ff8dc8(moveWork, moveWork + direction * 2,
                 distance * (2 * sizeof(EquipmentSlotWork)));

    const EquipmentSlotWork *savedFirstSource = &savedFirst;
    inventory->slotHandles[destinationSlot].packed = savedHandles;
    u32 destinationWorkByteOffset = destinationWorkIndex * sizeof(EquipmentSlotWork);
    *(EquipmentSlotWork *)((u32)gEquipmentSlotWork + destinationWorkByteOffset) = *savedFirstSource;
    destinationWorkByteOffset += sizeof(EquipmentSlotWork);
    *(EquipmentSlotWork *)(destinationWorkByteOffset + (u32)gEquipmentSlotWork) = savedSecond;
}
