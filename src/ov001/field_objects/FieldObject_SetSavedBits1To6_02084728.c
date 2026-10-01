#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_00[0x7e];
    u8 savedBits;
} FieldObject;

extern u16 FieldObject_GetSavedValue_0207f9a8(FieldObject *object);
extern void FieldObject_SetSavedValue_0207f9c8(FieldObject *object, u16 value);

void FieldObject_SetSavedBits1To6_02084728(FieldObject *object, int bits)
{
    u32 value = FieldObject_GetSavedValue_0207f9a8(object);

    object->savedBits = bits;
    FieldObject_SetSavedValue_0207f9c8(object, (bits << 1) | (value & ~0x7e));
}
