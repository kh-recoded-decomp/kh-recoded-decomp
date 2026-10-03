#pragma opt_propagation off
#include "nitro/types.h"

typedef struct {
    u8 data[0x104];
} ResourceSlot;

typedef struct {
    u8 pad_00[0x3c];
    void *bufferA;
    void *bufferB;
    u8 pad_44[4];
    ResourceSlot slots[6];
} EffectSet;

extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *memory);
extern void ReleaseResourceAndDetach_0202eee8(ResourceSlot *slot);
extern void ReleaseCallbackOwnedBuffer_020aafac(EffectSet *set);

void EffectSet_Release_020cf1d8(EffectSet *set)
{
    int i;

    NNSi_FndFreeFromDefaultHeap_0202a1c4(set->bufferA);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(set->bufferB);
    for (i = 0; i < 6; i++) {
        ReleaseResourceAndDetach_0202eee8(&set->slots[i]);
    }
    ReleaseCallbackOwnedBuffer_020aafac(set);
}
