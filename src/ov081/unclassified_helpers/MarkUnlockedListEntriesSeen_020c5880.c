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
extern void SetGlobalPackedBit_02027320(int bitIndex);
extern u16 *func_ov081_020c5be4(int id);
extern EntryList *FX_Div_020c542c(Ov081State *state);

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

void MarkUnlockedListEntriesSeen_020c5880(Ov081State *state)
{
    EntryList *list;
    int i;
    u8 id;

    list = FX_Div_020c542c(state);
    if (list->kind == 1) {
        for (i = 0; i < list->count; i++) {
            id = list->ids[i];
            if (IsListEntryUnlocked(id)) {
                SetGlobalPackedBit_02027320(data_020c5d80->bitIndexTable[id - 2] + 0x1010);
            }
        }
    } else {
        id = list->count;
        if (IsListEntryUnlocked(id)) {
            SetGlobalPackedBit_02027320(data_020c5d80->bitIndexTable[id - 2] + 0x1010);
        }
    }
}
