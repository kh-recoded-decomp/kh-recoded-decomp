#include "src/overlays/ov027/PackedResource.h"

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern PackedResourceHeader *Archive_LoadFile(u32 fileId, u32 heapId);
extern PackedResourceHeader *func_0202c4a0(u32 fileId, u32 heapId);

void LoadPackedFileView(PackedResourceView *view, u32 fileId, BOOL fromTail)
{
    PackedResourceHeader *file;
    u32 offset;

    MI_CpuFill8(view, 0, sizeof(PackedResourceView));
    if (fromTail) {
        view->file = func_0202c4a0(fileId, 14);
    } else {
        view->file = Archive_LoadFile(fileId, 14);
    }
    file = view->file;
    offset = file->payloadOffset;
    view->count = file->count;
    view->payload = (u8 *)file + offset;
}
