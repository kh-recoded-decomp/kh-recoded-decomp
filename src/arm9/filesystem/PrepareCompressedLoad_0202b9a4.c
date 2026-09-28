#include "nitro/types.h"

typedef struct LoaderRequest {
    u8 pad_00[0x14];
    u8 uncompressContext[0x28 - 0x14];
    u8 *dest;
    s32 size;
} LoaderRequest;

extern s32 ReadFileSync_0200b674(void *file, void *buffer, s32 length);
extern void *AllocFromHeapOrDefaultEx_0202a210(u32 size, int align, void **heap);
extern void func_02005750(void *context, u8 *dest, const void *header);

u8 *PrepareCompressedLoad_0202b9a4(LoaderRequest *request, void *file, u8 *dest, s32 maxSize, void **heap,
                                   BOOL alignFromEnd)
{
    u32 header;
    s32 size;

    ReadFileSync_0200b674(file, &header, 4);
    size = header >> 8;
    if (dest == NULL) {
        if (alignFromEnd) {
            dest = AllocFromHeapOrDefaultEx_0202a210(size, -0x20, heap);
        } else {
            dest = AllocFromHeapOrDefaultEx_0202a210(size, 0x20, heap);
        }
    } else if (size > maxSize) {
        return NULL;
    }
    request->dest = dest;
    request->size = size;
    func_02005750(request->uncompressContext, dest, &header);
    return dest;
}
