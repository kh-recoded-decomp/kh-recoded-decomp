#include "nitro/types.h"

typedef struct {
    u8 data[0x154];
} GroupEntry;

typedef struct {
    u8 pad_00[8];
    GroupEntry *entries;
    u8 pad_0C[9];
    u8 count;
} EntryGroup;

extern void ReleaseNestedObjectAt0x30_020aaac8(GroupEntry *entry);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);

void ReleaseEntryGroup_020aaf10(EntryGroup *group) {
    int i;

    for (i = 0; i < group->count; i++) {
        ReleaseNestedObjectAt0x30_020aaac8(&group->entries[i]);
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(group->entries);
}
