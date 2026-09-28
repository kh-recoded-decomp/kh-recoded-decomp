#include "nitro/types.h"

extern u32 data_ov035_020bc4e0;
extern void func_01ff8740(int value, void *dest, u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void ReleaseMovieResources_020baac4(void) {
    u32 base;
    void *inner;

    base = data_ov035_020bc4e0;
    if (*(void **)(base + 0x50) != 0) {
        inner = *(void **)(*(u32 *)(base + 0x50) + 0x14);
        if (inner != 0) {
            NNSi_FndFreeFromDefaultHeap_0202a1c4(inner);
        }
        NNSi_FndFreeFromDefaultHeap_0202a1c4(*(void **)(base + 0x50));
        *(u32 *)(base + 0x50) = 0;
    }
    if (*(void **)(base + 100) != 0) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(*(void **)(base + 100));
    }
    if (*(void **)(base + 0x68) != 0) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(*(void **)(base + 0x68));
    }
    func_01ff8740(0, (void *)(base + 0x40), 0x30);
    if (*(void **)(base + 0xb8) != 0) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(*(void **)(base + 0xb8));
        *(u32 *)(base + 0xb8) = 0;
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(*(void **)(base + 0x38));
    *(u32 *)(base + 0x38) = 0;
}
