#include "nitro/types.h"

typedef struct BufferArrayOwner {
    u8 pad_000[0x10c];
    int count;
    void **buffers;
} BufferArrayOwner;

extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void FreeBufferArray_0207aadc(BufferArrayOwner *owner)
{
    int i;

    for (i = 0; i < owner->count; i++) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(owner->buffers[i]);
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(owner->buffers);
}
