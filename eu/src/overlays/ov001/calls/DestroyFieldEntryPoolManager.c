#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void DestroyAllEffectEntries(int arg);
extern u32 gFieldEntryPoolManager;

void DestroyFieldEntryPoolManager(void) {
    u32 base = gFieldEntryPoolManager;
    int i = 0;
    DestroyAllEffectEntries(0);
    do {
        void *entry = *(void **)(base + i * 8 + 0x13c);
        if (entry != 0) {
            NNSi_FndFreeFromDefaultHeap(entry);
        }
        i = i + 1;
    } while (i < 8);
    NNSi_FndFreeFromDefaultHeap((void *)gFieldEntryPoolManager);
    gFieldEntryPoolManager = 0;
}
