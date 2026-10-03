#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_00[4];
    void *owner;
    u8 pad_08[0x48];
    s8 state;
    u8 pad_51[5];
    s16 parentIndex;
} FieldObject;

extern FieldObject *func_ov001_0208635c(void *owner, int index);
extern u32 func_ov017_020a5ddc(FieldObject *object);

BOOL IsActiveAncestorChain_020a50e4(FieldObject *object)
{
    BOOL active;

    if (func_ov017_020a5ddc(object)) {
        return TRUE;
    }
    for (;;) {
        active = TRUE;
        if (object->state != 2 && object->state != 1) {
            active = FALSE;
        }
        if (!active) {
            return FALSE;
        }
        if (object->parentIndex < 0) {
            break;
        }
        object = func_ov001_0208635c(object->owner, object->parentIndex);
    }
    return TRUE;
}
