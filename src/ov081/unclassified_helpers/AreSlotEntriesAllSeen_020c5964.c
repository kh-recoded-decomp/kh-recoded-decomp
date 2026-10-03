#include "nitro/types.h"

typedef struct Ov081State {
    u8 pad_00[0x6348];
    u8 *bitIndexTable;
} Ov081State;

typedef struct EntryList {
    u8 kind;
    u8 count;
    u8 pad_02[2];
    u8 *ids;
} EntryList;

extern Ov081State *data_020c5d80;
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern u16 *func_ov081_020c5be4(int id);
extern EntryList *GetSlotEntry_020c5438(int slot);

static inline BOOL IsListEntryUnlocked(u8 id)
{
    u16 *entry;
    BOOL ok;

    if (IsGlobalPackedBitSet_02027304(data_020c5d80->bitIndexTable[id - 2] + 0xf50)
        && (entry = func_ov081_020c5be4(id)) != NULL
        && !(*entry == 0x30 && *entry == 0x2e && *entry == 0x30)
        && !(*entry == 0x2f && *entry == 0x2f)) {
        ok = TRUE;
    } else {
        ok = FALSE;
    }
    return ok;
}

BOOL AreSlotEntriesAllSeen_020c5964(int slot)
{
    EntryList *list;
    int i;
    u8 id;

    list = GetSlotEntry_020c5438(slot);
    if (list->kind == 1) {
        for (i = 0; i < list->count; i++) {
            id = list->ids[i];
            if (IsListEntryUnlocked(id)
                && !IsGlobalPackedBitSet_02027304(data_020c5d80->bitIndexTable[id - 2] + 0x1010)) {
                return FALSE;
            }
        }
    } else {
        id = list->count;
        if (IsListEntryUnlocked(id)
            && !IsGlobalPackedBitSet_02027304(data_020c5d80->bitIndexTable[id - 2] + 0x1010)) {
            return FALSE;
        }
    }
    return TRUE;
}