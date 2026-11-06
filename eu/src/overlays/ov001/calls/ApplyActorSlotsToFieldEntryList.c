#include "nitro/types.h"

extern void FieldObject_ApplyActorSlotIndex(void *node);
extern u32 gFieldEntryPoolManager;

void ApplyActorSlotsToFieldEntryList(void) {
    void **node = *(void ***)(gFieldEntryPoolManager + 8);
    while (node != 0) {
        FieldObject_ApplyActorSlotIndex(node);
        node = *node;
    }
}
