#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern u32 gFieldEntryPoolManager;

void ReleaseFieldEntryRewardTables(void) {
    void *ptr = *(void **)(gFieldEntryPoolManager + 0x1bc);
    if (ptr != 0) {
        NNSi_FndFreeFromDefaultHeap(ptr);
        *(u32 *)(gFieldEntryPoolManager + 0x1bc) = 0;
    }
    ptr = *(void **)(gFieldEntryPoolManager + 0x1c4);
    if (ptr != 0) {
        NNSi_FndFreeFromDefaultHeap(ptr);
        *(u32 *)(gFieldEntryPoolManager + 0x1c4) = 0;
    }
}
