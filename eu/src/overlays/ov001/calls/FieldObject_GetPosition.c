#include "src/overlays/ov001/FieldObjectCallbacks.h"

VecFx32 *FieldObject_GetPosition(FieldObject *object)
{
    VecFx32 *(*callback)(FieldObject *) = object->callbacks->getPosition;

    if (callback != NULL) {
        return callback(object);
    }
    return NULL;
}
