#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x194];
    void *slotBuffers;
} ShotEntity;

extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void FreeSlotBuffers_020d63fc(ShotEntity *entity)
{
    NNSi_FndFreeFromDefaultHeap_0202a1c4(entity->slotBuffers);
}
