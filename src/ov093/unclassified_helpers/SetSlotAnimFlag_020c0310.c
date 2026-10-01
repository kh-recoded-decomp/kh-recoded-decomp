#include "nitro/types.h"

typedef struct {
    int animIndex;
    u8 pad_04[0x18];
} SlotEntry;

typedef struct {
    u8 pad_0000[0x200];
    u8 animSets[2][0x6434];
    SlotEntry leftSlots[13];
    SlotEntry rightSlots[13];
} SceneWork;

extern void func_0204f378(void *animSet, int index, int value);

void SetSlotAnimFlag_020c0310(int side, int slotIndex, int value, SceneWork *work)
{
    SlotEntry *entry = side == 0 ? &work->leftSlots[slotIndex] : &work->rightSlots[slotIndex];
    func_0204f378(work->animSets[side], entry->animIndex, value);
}
