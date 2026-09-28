#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void ReleaseResourceAndDetach_0202eee8(void *object);

void DestroyDisplayObject_020c37b4(int owner) {
    int object;

    object = *(int *)(owner + 0x3a4);
    if (object != 0) {
        if (*(int *)(object + 0x58) == 0) {
            *(u32 *)(object + 0x20) = *(u32 *)(object + 0x20) & 0xfffffffe;
        }
        *(u32 *)(object + 0x54) = 0;
        NNSi_FndFreeFromDefaultHeap_0202a1c4(*(void **)(object + 0x104));
        ReleaseResourceAndDetach_0202eee8((void *)object);
        NNSi_FndFreeFromDefaultHeap_0202a1c4((void *)object);
        *(u32 *)(owner + 0x3a4) = 0;
    }
}
