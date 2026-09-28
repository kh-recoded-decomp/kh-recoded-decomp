#include "nitro/types.h"

extern int func_0200c6fc(void *file, u32 unused1, int unused2);

typedef struct BufferInfo {
    u8 pad_00[8];
    s32 capacity;
    s32 used;
} BufferInfo;

typedef struct FileRequest {
    u8 pad_00[4];
    BufferInfo *buffer;
    u8 pad_08[0x28];
    void *dst;
    s32 requestedLength;
    s32 length;
} FileRequest;

/* Clamps requested length then dispatches request */
int ClampLengthAndDispatch_0200c7cc(void *unused, FileRequest *file, void *dst, u32 *length)
{
    BufferInfo *buffer = file->buffer;
    u32 requested = *length;
    u32 remaining = buffer->capacity - buffer->used;

    if (requested > remaining) {
        *length = remaining;
    }
    file->requestedLength = requested;
    file->dst = dst;
    file->length = *length;
    return func_0200c6fc(file, 0, 0);
}
