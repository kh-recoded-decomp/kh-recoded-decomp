#include "nitro/types.h"

extern int func_0200c6fc(void *file, u32 index, int wait);

typedef struct FileRequest {
    u8 pad_00[4];
    void *cursor;
    void *object;
    u32 flags;
    u8 pad_10[0x20 - 0x10];
    u8 embedded;
    u8 pad_21[0x30 - 0x21];
    void *dst;
    u16 lengthLo;
    u16 lengthHi;
    s32 length;
} FileRequest;

/* Fills request fields then dispatches it */
int SetupFileRequestAndDispatch_0200c854(void *object, FileRequest *file, u32 packedLength, s32 length)
{
    int result;

    file->lengthLo = (u16)packedLength;
    file->object = object;
    file->dst = object;
    file->lengthHi = (u16)(packedLength >> 16);
    file->length = length;
    result = func_0200c6fc(file, 2, 1);
    if (result != 0) {
        return result;
    }
    file->flags |= 0x20;
    file->flags &= ~0x10;
    file->cursor = &file->embedded;
    file->object = object;
    return result;
}
