#include "nitro/types.h"

typedef struct FieldObject FieldObject;

extern u16 FieldObject_GetSavedValue_0207f9a8(FieldObject *object);
extern void FieldObject_SetSavedValue_0207f9c8(FieldObject *object, u32 value);

void SetSavedValueFlag7_02084750(FieldObject *object, int flag)
{
    u32 value = FieldObject_GetSavedValue_0207f9a8(object);

    FieldObject_SetSavedValue_0207f9c8(object, (u16)((flag << 7) | (value & ~0x80)));
}
