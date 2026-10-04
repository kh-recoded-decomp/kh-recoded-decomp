#include "nitro/types.h"

typedef struct {
    u8 kind;
    u8 count;
    u8 pad_02[2];
    u8 *ids;
} EntryList;

typedef struct {
    u8 pad_00[0x6120];
    EntryList *entries[110];
    u8 slotEntryIndices[0x70];
    u8 *bitIndexTable;
} Ov081State;

extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);

void FreeEntryLists_020c523c(Ov081State *state)
{
    int i;

    for (i = 0; i < 110; i++) {
        switch (state->entries[i]->kind) {
        case 0:
            break;
        case 1:
            NNSi_FndFreeFromDefaultHeap_0202a1c4(state->entries[i]->ids);
            break;
        case 2:
            break;
        }
        NNSi_FndFreeFromDefaultHeap_0202a1c4(state->entries[i]);
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(state->bitIndexTable);
}
