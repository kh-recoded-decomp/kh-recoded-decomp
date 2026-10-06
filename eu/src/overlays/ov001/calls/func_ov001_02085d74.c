#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void func_ov001_02085d74(int state) {
    void *handle = *(void **)(state + 0x74);
    NNSi_FndFreeFromDefaultHeap(handle);
    *(void **)(state + 0x74) = 0;
}
