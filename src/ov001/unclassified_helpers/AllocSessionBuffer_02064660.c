#include "nitro/types.h"

typedef struct {
    void *data;
    u32 size;
} SessionBuffer;

extern u32 data_ov001_020a0460;
extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);

void *AllocSessionBuffer_02064660(int index, u32 size)
{
    SessionBuffer *buffers = (SessionBuffer *)(data_ov001_020a0460 + 0x283c);
    SessionBuffer *entry = &buffers[index];

    buffers[index].data = NNSi_FndAllocFromDefaultHeapEx_0202a19c(size, -4);
    entry->size = size;
    return buffers[index].data;
}
