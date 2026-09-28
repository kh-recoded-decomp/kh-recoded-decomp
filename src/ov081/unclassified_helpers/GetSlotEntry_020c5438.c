#include "nitro/types.h"

typedef struct Ov081State {
    u8 pad_00[0x6120];
    void *entries[110];
    u8 slotEntryIndices[16];
} Ov081State;

extern Ov081State *g_ov081State_020c5d80;

void *GetSlotEntry_020c5438(int slot)
{
    return g_ov081State_020c5d80->entries[g_ov081State_020c5d80->slotEntryIndices[slot]];
}
