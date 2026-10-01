#include "nitro/types.h"

typedef struct Handle {
    void *target;
    u8 active;
} Handle;

extern void DetachHandle_0204fdf8(Handle *handle);

void ReleaseHandle_0204fdc8(Handle *handle)
{
    if (handle->active && handle->target != NULL) {
        DetachHandle_0204fdf8(handle);
    }
    handle->active = 0;
    handle->target = NULL;
}
