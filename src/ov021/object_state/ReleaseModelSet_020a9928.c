#include "nitro/types.h"

typedef struct SubModel {
    u8 resource[0x104];
    u8 slots[0xc];
} SubModel;

typedef struct ModelSet {
    u32 flags;
    u32 field4;
    u8 resource[0x104];
    int field10c;
    u8 pad110[4];
    u8 records[6][0x2c];
    u8 slots[0xc];
    SubModel *sub;
} ModelSet;

extern void ReleaseSharedRecordState_020a9084(void *record);
extern void FreeSlotTable_020a90e4(void *table);
extern void ReleaseResourceAndDetach_0202eee8(void *resource);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void ReleaseModelSet_020a9928(ModelSet *set)
{
    int i;
    SubModel *sub;

    if (!(set->flags & 1)) {
        return;
    }
    for (i = 0; i < 6; i++) {
        ReleaseSharedRecordState_020a9084(set->records[i]);
    }
    FreeSlotTable_020a90e4(set->slots);
    ReleaseResourceAndDetach_0202eee8(set->resource);
    sub = set->sub;
    if (sub != NULL) {
        FreeSlotTable_020a90e4(sub->slots);
        ReleaseResourceAndDetach_0202eee8(sub);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(set->sub);
    }
    set->field10c = 0;
    set->flags = 0;
}
