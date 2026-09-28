#include "nitro/types.h"

typedef struct PairRecord {
    u8 pad_00[0x4];
    s32 firstId;
    s32 secondId;
} PairRecord;

typedef struct SlotMenu {
    u8 pad_00000[0x49868];
    int pairBits[128][4];
} SlotMenu;

extern PairRecord *GetRecordSlot6Entry_02052108(int index);
extern void SetPackedBit(int *bitWords, int bitIndex);

void SlotMenu_BuildPairMatrix_020c6c40(SlotMenu *menu)
{
    PairRecord *pair;
    int i;

    for (i = 0; i < 333; i++) {
        pair = GetRecordSlot6Entry_02052108(i);
        SetPackedBit(menu->pairBits[pair->firstId], pair->secondId);
        SetPackedBit(menu->pairBits[pair->secondId], pair->firstId);
    }
}
