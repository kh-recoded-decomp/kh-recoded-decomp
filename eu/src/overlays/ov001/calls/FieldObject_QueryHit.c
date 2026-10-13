#include "src/overlays/ov001/FieldObjectCallbacks.h"

BOOL FieldObject_QueryHit(FieldObject *object, const void *shape,
                         FieldObjectHitContact *contact)
{
    BOOL (*callback)(FieldObject *, const void *, FieldObjectHitContact *);

    if (IsObjectFlagClear(object) &&
        (callback = object->callbacks->queryHit) != NULL) {
        return callback(object, shape, contact);
    }
    return FALSE;
}
