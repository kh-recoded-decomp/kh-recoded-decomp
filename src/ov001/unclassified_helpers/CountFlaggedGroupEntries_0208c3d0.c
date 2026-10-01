#include "nitro/types.h"

typedef struct SaveData {
    u8 pad_0000[0x2888];
    u16 groupMasks[1];
} SaveData;

extern SaveData *data_0205fe0c;
extern BOOL IsGroupEntryFlagged_0208c36c(int group, int index);

int CountFlaggedGroupEntries_0208c3d0(int group)
{
    u32 index;
    int count = 0;

    for (index = 0; index < 16; index++) {
        if ((1 << index) & data_0205fe0c->groupMasks[group]) {
            if (IsGroupEntryFlagged_0208c36c(group, index)) {
                count++;
            }
        }
    }
    return count;
}
