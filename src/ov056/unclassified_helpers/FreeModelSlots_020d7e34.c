#include "nitro/types.h"

typedef struct ModelSlot {
    u8 pad_000[0x104];
    u8 recordState[0x134 - 0x104];
} ModelSlot;

typedef struct ModelSlotList {
    ModelSlot *slots;
    s8 count;
} ModelSlotList;

extern void ReleaseResourceAndDetach_0202eee8(u8 *object);
extern void ReleaseSharedRecordState_020a9084(void *state);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void FreeModelSlots_020d7e34(ModelSlotList *list)
{
    int i;
    for (i = 0; i < list->count; i++) {
        ModelSlot *slot = &list->slots[i];
        ReleaseResourceAndDetach_0202eee8((u8 *)slot);
        ReleaseSharedRecordState_020a9084(slot->recordState);
    }
    if (list->slots != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(list->slots);
    }
}
