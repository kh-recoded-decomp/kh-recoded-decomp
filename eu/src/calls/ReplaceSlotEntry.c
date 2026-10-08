#include "nitro/types.h"

typedef struct SlotEntry {
    s16 id;
    u8 pad02[2];
    u8 count;
    u8 maxCount;
    u8 pad06[2];
    u32 extra;
} SlotEntry;

SlotEntry *GetPlayerFlagRecord(int index);

SlotEntry ReplaceSlotEntry(const SlotEntry *update, int index)
{
    SlotEntry *slot = GetPlayerFlagRecord(index);
    SlotEntry previous;
    u8 limit;

    previous.id = -1;
    previous.count = 0;
    if (slot->id != -1) {
        previous = *slot;
        slot->id = update->id;
        {
            int count = update->count;
            slot->count = count;
            count &= 0xff;
            if (count == 0)
                slot->count = count + 1;
        }
        limit = slot->maxCount;
        if (slot->count <= limit)
            limit = slot->count;
        slot->count = limit;
    }
    return previous;
}
