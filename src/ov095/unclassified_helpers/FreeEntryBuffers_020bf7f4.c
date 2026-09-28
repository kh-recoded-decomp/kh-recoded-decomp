#include "nitro/types.h"

typedef struct {
    void *data;
    u8 pad_04[0xC];
} EntryBuffer;

typedef struct {
    u8 pad_000[0x130];
    EntryBuffer buffers[5];
} EntryViewer;

extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void FreeEntryBuffers_020bf7f4(EntryViewer *viewer)
{
    int bufferIndex;

    for (bufferIndex = 0; bufferIndex < 5; bufferIndex++) {
        if (viewer->buffers[bufferIndex].data != NULL) {
            NNSi_FndFreeFromDefaultHeap_0202a1c4(viewer->buffers[bufferIndex].data);
        }
    }
}
