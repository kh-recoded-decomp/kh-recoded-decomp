#include "nitro/types.h"

typedef struct {
    u32 index;
    u8 pad_04[0x34];
    u32 nameAddress;
    u32 descriptionAddress;
} Entry;

typedef struct {
    u32 baseA;
    u32 baseB;
    u8 pad_08[0x5c];
    Entry *entries;
    u32 nameTable;
    u32 descriptionTable;
} State;

extern State *data_020613d0;
extern u32 func_0202c478(u32 fileId, u32 param2);
extern u32 func_0202c48c(u32 fileId, u32 param2);

void LoadNamedRecordTables_020519d8(int useAlt)
{
    State *state = data_020613d0;
    int i;
    u32 *nameTable;
    u32 *descriptionTable;

    if (useAlt != 0) {
        state->entries = (Entry *)func_0202c48c(((state->baseA + 0x8000) & 0xfffffc) << 7 | 0x80000009, 0x11);
        state->nameTable = func_0202c48c(((state->baseB + 0x8000) & 0xfffffc) << 7 | 0x80000004, 0x11);
        state->descriptionTable = func_0202c48c(((state->baseB + 0x8000) & 0xfffffc) << 7 | 0x80000006, 0x11);
    } else {
        state->entries = (Entry *)func_0202c478(((state->baseA + 0x8000) & 0xfffffc) << 7 | 0x80000009, 0x11);
        state->nameTable = func_0202c478(((state->baseB + 0x8000) & 0xfffffc) << 7 | 0x80000004, 0x11);
        state->descriptionTable = func_0202c478(((state->baseB + 0x8000) & 0xfffffc) << 7 | 0x80000006, 0x11);
    }
    nameTable = (u32 *)state->nameTable;
    descriptionTable = (u32 *)state->descriptionTable;
    for (i = 0; i < 100; i++) {
        Entry *entry = &state->entries[i];

        entry->nameAddress = state->nameTable + nameTable[entry->index];
        entry->descriptionAddress = state->descriptionTable + descriptionTable[entry->index];
    }
}
