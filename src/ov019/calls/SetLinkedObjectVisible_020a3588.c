#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_000[0x5a];
    u16 flags;
} FieldObject;

void SetLinkedObjectVisible_020a3588(FieldObject *object, BOOL visible)
{
    u16 visibilityFlags;

    object->flags &= 0xcfff;
    visibilityFlags = visible ? 0x1000 : 0x2000;
    object->flags |= visibilityFlags;
}
