#include "nitro/types.h"

typedef struct PackedFileHeader {
    u32 payloadOffset;
    u32 count;
} PackedFileHeader;

typedef struct PackedFileView {
    PackedFileHeader *file;
    u32 count;
    u8 *payload;
} PackedFileView;

extern void func_01ff8830(void *dst, u8 value, u32 size);
extern PackedFileHeader *func_0202c478(u32 fileId, u32 heapId);
extern PackedFileHeader *func_0202c48c(u32 fileId, u32 heapId);

void LoadPackedFileView_020ba25c(PackedFileView *view, u32 fileId, BOOL fromTail)
{
    PackedFileHeader *file;
    u32 offset;

    func_01ff8830(view, 0, sizeof(PackedFileView));
    if (fromTail) {
        view->file = func_0202c48c(fileId, 14);
    } else {
        view->file = func_0202c478(fileId, 14);
    }
    file = view->file;
    offset = file->payloadOffset;
    view->count = file->count;
    view->payload = (u8 *)file + offset;
}
