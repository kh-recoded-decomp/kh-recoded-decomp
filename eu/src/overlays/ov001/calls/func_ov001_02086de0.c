#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void DestroyAllEffectEntries(int arg);
extern u32 data_ov001_020a04fc;

void func_ov001_02086de0(void) {
    u32 base = data_ov001_020a04fc;
    int i = 0;
    DestroyAllEffectEntries(0);
    do {
        void *entry = *(void **)(base + i * 8 + 0x13c);
        if (entry != 0) {
            NNSi_FndFreeFromDefaultHeap(entry);
        }
        i = i + 1;
    } while (i < 8);
    NNSi_FndFreeFromDefaultHeap((void *)data_ov001_020a04fc);
    data_ov001_020a04fc = 0;
}
