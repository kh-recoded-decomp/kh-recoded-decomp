#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_00[0x50];
    s32 type;
} FieldObject;

BOOL IsFieldTypeOneOrTen_020a2bb0(FieldObject *object)
{
    BOOL result = TRUE;
    s16 type = (s16)object->type;
    if (type != 1 && type != 10) {
        result = FALSE;
    }
    return result;
}
