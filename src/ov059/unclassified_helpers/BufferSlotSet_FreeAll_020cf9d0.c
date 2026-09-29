#include "nitro/types.h"

typedef struct BufferSlot {
    u8 data[0x30];
} BufferSlot;

typedef struct BufferSlotSet {
    BufferSlot mainSlots[2];
    BufferSlot extraSlot;
    BufferSlot pairSlots[2];
} BufferSlotSet;

extern BOOL FreeBufferAndClearStatus_0206a918(BufferSlot *slot);
extern void BufferSlots_FreePair_020cf2e8(BufferSlot *slots);

void BufferSlotSet_FreeAll_020cf9d0(BufferSlotSet *set)
{
    u32 i;

    BufferSlots_FreePair_020cf2e8(set->pairSlots);
    for (i = 0; i < 2; i++) {
        FreeBufferAndClearStatus_0206a918(&set->mainSlots[i]);
    }
    FreeBufferAndClearStatus_0206a918(&set->extraSlot);
}
