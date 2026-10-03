#include "nitro/types.h"

typedef struct FieldDef {
    u8 pad_00[0x5a];
    u8 kind;
} FieldDef;

typedef struct FieldObject {
    u8 pad_00[4];
    FieldDef *def;
} FieldObject;

extern u32 IsFieldFlagBit1Set_020a3d40(FieldObject *object);
extern u32 func_ov017_020a5dd0(FieldObject *object);

u32 IsFieldObjectActive_020a3d50(FieldObject *object)
{
    switch (object->def->kind) {
    case 4:
        return IsFieldFlagBit1Set_020a3d40(object);
    case 7:
        return func_ov017_020a5dd0(object);
    case 8:
        break;
    }
    return 0;
}
