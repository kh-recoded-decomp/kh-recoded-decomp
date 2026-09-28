#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

typedef struct {
    u8 pad_000[0x44];
    void *resource;
} SomeObj;

void FreeResourceAt0x44_020aa8f8(SomeObj *obj)
{
    if (obj->resource != 0) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(obj->resource);
    }
}
