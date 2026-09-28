#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x1c];
    int flag;
    void *opFunc;
} StreamOps;

typedef struct {
    u8 pad_00[8];
    int innerObject;
    u8 pad_0c[0x14];
    StreamOps *ops;
} Handle;

typedef struct {
    Handle *handle;
    const void *position;
} Cursor;

typedef int (*StreamOpFunc)(Handle *handle, void *buffer, const void *position, u32 size);

extern void MI_CpuCopy8_01ff89a8(const void *src, void *dst, u32 size);
extern int func_0200a2a4(int object, int result);

int RunStreamOp_0200be04(Cursor *cursor, void *buffer, u32 size) {
    Handle *handle = cursor->handle;
    StreamOps *ops = handle->ops;
    int result;

    if (ops->flag != 0) {
        MI_CpuCopy8_01ff89a8(cursor->position, buffer, size);
        result = 0;
    } else {
        StreamOpFunc opFunc = (StreamOpFunc)ops->opFunc;
        result = opFunc(handle, buffer, cursor->position, size);
        result = func_0200a2a4(handle->innerObject, result);
    }
    cursor->position = (const u8 *)cursor->position + size;
    return result;
}
