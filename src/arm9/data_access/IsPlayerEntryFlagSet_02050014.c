#include "nitro/types.h"

typedef struct IdEntry {
    u32 id : 18;
    u32 flags : 13;
    u32 isSet : 1;
} IdEntry;

typedef struct IdList {
    IdEntry *entries;
    u8 count;
} IdList;

typedef struct PlayerRecords {
    u8 pad_000[0x13c];
    IdList list;
} PlayerRecords;

extern PlayerRecords data_02060b50[];
extern IdEntry *FindEntryById_0204f6a4(IdList *list, u32 id);

BOOL IsPlayerEntryFlagSet_02050014(int player, u32 id)
{
    IdEntry *entry;

    if (player != 0) {
        return FALSE;
    }
    entry = FindEntryById_0204f6a4(&data_02060b50[player].list, id);
    return entry != NULL ? entry->isSet : FALSE;
}
