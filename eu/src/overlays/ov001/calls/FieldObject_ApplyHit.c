#include "src/overlays/ov001/FieldObjectCallbacks.h"

u32 FieldObject_ApplyHit(FieldObject *object,
                       const FieldObjectHitMessage *message)
{
    u32 (*callback)(FieldObject *, const FieldObjectHitMessage *);

    if (IsObjectFlagClear(object) &&
        (callback = object->callbacks->applyHit) != NULL) {
        return callback(object, message);
    }
    return 0;
}
