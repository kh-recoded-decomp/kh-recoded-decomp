#include "nitro/types.h"

extern u32 NNSi_FndFreeFromDefaultHeap();

void
FreeFieldObjectClassAnimationBuffers(int self)
{
    int work = *(int *)(self + 8);

    if (*(int *)(work + 0x58) != 0) {
        NNSi_FndFreeFromDefaultHeap();
        *(u32 *)(work + 0x58) = 0;
    }
    if (*(int *)(work + 0x60) != 0) {
        NNSi_FndFreeFromDefaultHeap();
        *(u32 *)(work + 0x60) = 0;
    }
}
