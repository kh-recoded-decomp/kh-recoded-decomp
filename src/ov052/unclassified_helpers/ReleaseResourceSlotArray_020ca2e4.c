#include "nitro/types.h"

extern void ReleaseResourceAndDetach_0202eee8(u8 *object);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

/* Releases four resource slots and frees the array */
void ReleaseResourceSlotArray_020ca2e4(int entity)
{
    int slotIndex;

    for (slotIndex = 0; slotIndex < 4; slotIndex++) {
        ReleaseResourceAndDetach_0202eee8(*(u8 **)(entity + 0x106c) + slotIndex * 0x104);
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(*(u8 **)(entity + 0x106c));
}
