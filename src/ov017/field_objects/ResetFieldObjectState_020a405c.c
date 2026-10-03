#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_00[0x4a];
    s8 state;
    u8 flags : 7;
    u8 pad_4c[0x24];
    u8 queue[4];
} FieldObject;

extern void func_ov017_020a3e10(FieldObject *object);
extern void func_ov017_020a3c78(FieldObject *object, int mode);
extern void func_ov017_020a5048(void *queue, FieldObject *object);

void ResetFieldObjectState_020a405c(FieldObject *object)
{
    if ((u8)(s8)(object->state - 1) <= 1) {
        func_ov017_020a3e10(object);
    }
    func_ov017_020a3c78(object, 0);
    object->flags &= ~0x20;
    func_ov017_020a5048(object->queue, object);
}
