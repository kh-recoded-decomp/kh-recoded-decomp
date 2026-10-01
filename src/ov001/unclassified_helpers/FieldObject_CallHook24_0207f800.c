#include "nitro/types.h"

struct FieldObject;

typedef struct FieldObjectClass {
    u8 pad_00[0x24];
    void (*hook24)(struct FieldObject *object, int argument);
} FieldObjectClass;

typedef struct FieldObject {
    u8 pad_00[0x8];
    FieldObjectClass *objectClass;
} FieldObject;

void FieldObject_CallHook24_0207f800(FieldObject *object, int argument)
{
    void (*hook)(FieldObject *object, int argument) = object->objectClass->hook24;

    if (hook != NULL) {
        hook(object, argument);
    }
}
