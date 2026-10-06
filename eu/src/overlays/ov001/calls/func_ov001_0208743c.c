#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern u32 data_ov001_020a04fc;

void func_ov001_0208743c(void) {
    void *ptr = *(void **)(data_ov001_020a04fc + 0x1bc);
    if (ptr != 0) {
        NNSi_FndFreeFromDefaultHeap(ptr);
        *(u32 *)(data_ov001_020a04fc + 0x1bc) = 0;
    }
    ptr = *(void **)(data_ov001_020a04fc + 0x1c4);
    if (ptr != 0) {
        NNSi_FndFreeFromDefaultHeap(ptr);
        *(u32 *)(data_ov001_020a04fc + 0x1c4) = 0;
    }
}
