#include "nitro/types.h"

typedef struct SlotEntry {
    s16 id;
    u8 pad_02[2];
    u8 turnsLeft;
    u8 level;
} SlotEntry;

extern SlotEntry *GetPlayerFlagRecord_0205036c(int id);

int TickSlotTimer_0205031c(int id)
{
    SlotEntry *entry = GetPlayerFlagRecord_0205036c(id);

    if (entry == NULL) {
        return -1;
    }
    if (entry->id == -1) {
        return -1;
    }
    if (entry->turnsLeft != 0) {
        entry->turnsLeft--;
    }
    if (entry->turnsLeft == 0) {
        entry->id = -1;
    }
    return entry->turnsLeft;
}
