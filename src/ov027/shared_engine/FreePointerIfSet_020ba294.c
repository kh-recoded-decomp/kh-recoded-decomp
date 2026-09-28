#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void FreePointerIfSet_020ba294(void **ptr) {
    if (*ptr != 0) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(*ptr);
        *ptr = 0;
    }
}
