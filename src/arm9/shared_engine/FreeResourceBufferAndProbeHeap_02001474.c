#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    void *buffer;
} FreeableResource;

extern void **data_0206039c;
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern int findLargestAlignedHeapBlock_02013304(void *heap, int alignmentInput);

BOOL FreeResourceBufferAndProbeHeap_02001474(FreeableResource *resource)
{
    NNSi_FndFreeFromDefaultHeap_0202a1c4(resource->buffer);
    findLargestAlignedHeapBlock_02013304(*data_0206039c, 4);
    return TRUE;
}
