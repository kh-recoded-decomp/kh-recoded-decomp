#include "nitro/types.h"

typedef struct Resource {
    u8 pad_000[0x628];
    s32 ready;
} Resource;

extern void *PXI_Init_020bc8a8();

BOOL IsPxiResourceReadyOrInitialize_020be110(Resource *resource)
{
    if (resource->ready != 0) {
        return TRUE;
    }
    PXI_Init_020bc8a8();
    return TRUE;
}
