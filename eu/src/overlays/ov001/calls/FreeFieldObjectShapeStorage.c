#include "nitro/types.h"

extern u32 NNSi_FndFreeFromDefaultHeap();

void
FreeFieldObjectShapeStorage(int self)
{
    if (*(int *)(self + 0x18) != 0) {
        NNSi_FndFreeFromDefaultHeap();
        *(u32 *)(self + 0x18) = 0;
    }
}
