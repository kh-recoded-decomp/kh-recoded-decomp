#include "nitro/types.h"

typedef struct {
    u8 pad_000[4];
    u16 value;
    u8 pad_006[0x132];
} SlotEntry;

typedef struct {
    SlotEntry *entries;
} SlotTable;

extern void *data_ov021_020b5608;

extern SlotTable *func_ov021_020a8810(void *owner, void *manager);

void SetSlotEntryValue_020a8f4c(void *owner, int slot, u16 value) {
    SlotTable *table;

    if (data_ov021_020b5608 != NULL && (table = func_ov021_020a8810(owner, data_ov021_020b5608)) != NULL) {
        table->entries[slot].value = value;
    }
}
