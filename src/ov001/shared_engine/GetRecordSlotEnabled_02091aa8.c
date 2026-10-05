#include "nitro/types.h"

typedef struct RecordSlot {
    u8 pad_00[0xd];
    u8 enabled;
} RecordSlot;

extern RecordSlot *func_02036810(int index);

u8 GetRecordSlotEnabled_02091aa8(int index)
{
    RecordSlot *slot = func_02036810(index);

    if (slot == NULL) {
        return 0;
    }
    if (slot->enabled == 0) {
        return 0;
    }
    return slot->enabled;
}
