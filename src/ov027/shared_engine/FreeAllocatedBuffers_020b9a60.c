#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

struct Owner {
    void *primary;
    u8 pad_04[0xc];
    void *secondary;
};

void FreeAllocatedBuffers_020b9a60(struct Owner *owner) {
    NNSi_FndFreeFromDefaultHeap_0202a1c4(owner->secondary);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(owner->primary);
}
