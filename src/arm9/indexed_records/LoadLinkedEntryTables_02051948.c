#include "nitro/types.h"

typedef struct {
    u32 index;
    u32 pad[11];
    u32 address;
} LinkedEntry;

typedef struct {
    u32 baseA;
    u32 baseB;
    u32 pad[21];
    LinkedEntry *entries;
    u32 table;
} TableState;

extern TableState *data_020613d0;
extern u32 func_0202c478(u32 fileId, u32 param2);
extern u32 func_0202c48c(u32 fileId, u32 param2);

void LoadLinkedEntryTables_02051948(int useAlt)
{
    TableState *TableState = data_020613d0;
    int i;
    u32 *table;

    if (useAlt != 0) {
        TableState->entries = (LinkedEntry *)func_0202c48c(((TableState->baseA + 0x8000) & 0xfffffc) << 7 | 0x8000000a, 0x11);
        TableState->table = func_0202c48c(((TableState->baseB + 0x8000) & 0xfffffc) << 7 | 0x80000005, 0x11);
    } else {
        TableState->entries = (LinkedEntry *)func_0202c478(((TableState->baseA + 0x8000) & 0xfffffc) << 7 | 0x8000000a, 0x11);
        TableState->table = func_0202c478(((TableState->baseB + 0x8000) & 0xfffffc) << 7 | 0x80000005, 0x11);
    }
    table = (u32 *)TableState->table;
    for (i = 0; i < 0x5d; i++) {
        TableState->entries[i].address = TableState->table + table[TableState->entries[i].index];
    }
}
