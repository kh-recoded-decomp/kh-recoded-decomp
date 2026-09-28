#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    void *bufferA;
    void *bufferB;
} Resource;

extern void func_0202a1c4(void *block);

/* Frees a resource and its two buffers. */
void ReleaseResourceWithBuffers_0205206c(Resource **resourceHandle)
{
    Resource *resource = *resourceHandle;

    func_0202a1c4(resource->bufferA);
    func_0202a1c4(resource->bufferB);
    func_0202a1c4(resource);
    *resourceHandle = 0;
}
