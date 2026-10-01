#include "nitro/types.h"

typedef struct {
    void *data;
    u8 pad[4];
} Buffer;

typedef struct {
    u8 pad_00[0xc];
    u8 *owner;
    u8 pad_10[0x60 - 0x10];
    Buffer *buffers;
    u8 pad_64[0x7c - 0x64];
    s8 bufferCount;
} Loader;

extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern int DefaultStepDone_02036b7c(void *task);
extern void func_ov001_0207f244(Loader *self);

void FreeLoaderBuffers_02083a4c(Loader *loader) {
    s8 count = loader->bufferCount;
    s8 i;
    for (i = 0; i < count; i++) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(loader->buffers[i].data);
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(loader->buffers);
    DefaultStepDone_02036b7c(loader->owner + 0x1a8);
    func_ov001_0207f244(loader);
}
