#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ModelSlot {
    u8 pad_000[0x130];
    void *node;
} ModelSlot;

typedef struct ModelSlotList {
    ModelSlot *slots;
    s8 count;
} ModelSlotList;

extern u16 AdvanceAnimationTracks_0202ef24(ModelSlot *state, fx32 delta);

void AdvanceModelSlotAnimations_020d7e74(ModelSlotList *list, fx32 delta)
{
    int i;
    for (i = 0; i < list->count; i++) {
        ModelSlot *slot = &list->slots[i];
        if (slot->node != NULL && AdvanceAnimationTracks_0202ef24(slot, delta)) {
            slot->node = NULL;
        }
    }
}
