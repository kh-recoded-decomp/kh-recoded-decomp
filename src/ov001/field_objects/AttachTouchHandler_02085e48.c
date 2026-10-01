#include "nitro/types.h"

typedef struct TouchHandler {
    u32 words[5];
} TouchHandler;

typedef struct FieldObjectWork {
    u8 pad_000[0x494];
    s32 interactRange;
} FieldObjectWork;

typedef struct FieldObject {
    u8 pad_00[8];
    FieldObjectWork *work;
    u8 pad_0c[0x5c];
    void (*onTouchStart)(struct FieldObject *object);
    void (*onTouchEnd)(struct FieldObject *object);
    s32 touchState;
    TouchHandler *touchHandler;
} FieldObject;

extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern TouchHandler func_ov031_020bc5b0(void (*callback)(FieldObject *), FieldObject *owner, int mode, int flags);
extern void func_ov001_02085d4c(FieldObject *object);
extern void func_ov001_02085d5c(FieldObject *object);
extern void func_ov001_02085d74(FieldObject *object);

void AttachTouchHandler_02085e48(FieldObject *object)
{
    object->work->interactRange = 0x1800;
    if (object->touchHandler == NULL) {
        object->touchHandler = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(TouchHandler));
    }
    object->onTouchStart = func_ov001_02085d4c;
    object->onTouchEnd = func_ov001_02085d5c;
    object->touchState = 0;
    *object->touchHandler = func_ov031_020bc5b0(func_ov001_02085d74, object, 2, 0);
}
