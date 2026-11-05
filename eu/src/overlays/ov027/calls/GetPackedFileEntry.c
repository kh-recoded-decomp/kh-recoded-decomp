#include "src/overlays/ov027/PackedResource.h"

void *GetPackedFileEntry(const PackedResourceView *view, s32 index)
{
    u32 count = view->count;
    u8 *entry = view->payload;
    int i;

    if ((u32)index >= count) {
        return NULL;
    }
    for (i = 0; i < index; i++) {
        entry += *(s32 *)entry;
    }
    return entry + 4;
}
