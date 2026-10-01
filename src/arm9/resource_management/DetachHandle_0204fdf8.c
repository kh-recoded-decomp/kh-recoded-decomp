#include "nitro/types.h"

typedef struct Handle {
    void *target;
    u8 active;
} Handle;

typedef struct HandleOwner {
    u32 unk_00;
    void *current;
} HandleOwner;

extern HandleOwner data_020608c8;
extern void ReleaseHandle_0204fdc8(Handle *handle);

void DetachHandle_0204fdf8(Handle *handle)
{
    if (handle->active && handle->target != NULL) {
        handle->active = 0;
        handle->target = NULL;
        data_020608c8.current = NULL;
    }
    ReleaseHandle_0204fdc8(handle);
}
