#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_00[0x50];
    u16 saveBitOffset;
    u8 saveBitCount;
} FieldObject;

extern u32 func_ov001_02064574(int bitOffset, u32 bitCount);

u16 FieldObject_GetSavedValue_0207f9a8(FieldObject *object)
{
    u32 saved = func_ov001_02064574(object->saveBitOffset, object->saveBitCount);

    return (u16)((saved & 0xfffe) >> 1);
}
