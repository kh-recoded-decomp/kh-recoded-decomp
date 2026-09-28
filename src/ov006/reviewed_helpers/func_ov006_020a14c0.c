#include "nitro/types.h"

typedef struct {
    u8 value;
    u8 pad_01[3];
} Entry;

typedef struct {
    u8 pad_00[0x24];
    Entry *entries;
} EntryTable;

u8 func_ov006_020a14c0(EntryTable *table, int index)
{
    return table->entries[index].value;
}
