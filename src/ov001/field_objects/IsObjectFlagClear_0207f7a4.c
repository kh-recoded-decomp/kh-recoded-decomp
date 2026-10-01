#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_00[0x50];
    u16 id;
    u8 kind;
} FieldObject;

extern u32 func_ov001_02064574(u16 id, u8 kind);

BOOL IsObjectFlagClear_0207f7a4(FieldObject *object)
{
    return (func_ov001_02064574(object->id, object->kind) & 1) == 0;
}
