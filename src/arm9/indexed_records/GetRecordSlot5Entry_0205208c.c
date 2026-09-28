#include "nitro/types.h"

typedef struct {
    u16 count;
    u16 pad_02;
    u8 entries[0x18];
} Slot5Table;

typedef struct {
    u8 pad_00[0x30];
    Slot5Table *slot5;
} RecordManager;

extern RecordManager *g_recordManager_020613d0;

/* Returns a pointer to record slot 5 entry. */
u8 *GetRecordSlot5Entry_0205208c(int index)
{
    RecordManager *manager = g_recordManager_020613d0;
    Slot5Table *table;

    if (manager == NULL || (table = manager->slot5) == NULL) {
        return NULL;
    }
    if (table->count <= index) {
        return NULL;
    }
    return table->entries + index * 0x18;
}
