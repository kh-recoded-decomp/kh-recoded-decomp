#include "nitro/types.h"

typedef struct ResourceSlot {
    u8 pad00[0x90];
} ResourceSlot;

typedef struct ResourceOwner {
    u8 pad00[0x44];
    void *buffer;
    u8 pad48[0x6c - 0x48];
    ResourceSlot *slots;
    s32 slotCount;
} ResourceOwner;

extern void FreeResourceAt0x44_020aa8f8(ResourceSlot *slot, int mode);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *memory);

void FreeResourceSlots_020ade38(ResourceOwner *owner, int mode)
{
    int i;

    for (i = 0; i < owner->slotCount; i++) {
        FreeResourceAt0x44_020aa8f8(&owner->slots[i], mode);
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(owner->buffer);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(owner->slots);
}
