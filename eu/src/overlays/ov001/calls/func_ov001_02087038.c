#include "nitro/types.h"

extern void FieldObject_ApplyActorSlotIndex(void *node);
extern u32 data_ov001_020a04fc;

void func_ov001_02087038(void) {
    void **node = *(void ***)(data_ov001_020a04fc + 8);
    while (node != 0) {
        FieldObject_ApplyActorSlotIndex(node);
        node = *node;
    }
}
