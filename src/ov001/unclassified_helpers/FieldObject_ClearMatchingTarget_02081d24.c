#include "nitro/types.h"

typedef struct ObjectData {
    u8 pad_00[0xbc];
    s8 targetIndex;
} ObjectData;

typedef struct FieldObject {
    u8 pad_00[0x8];
    ObjectData *data;
    u8 pad_0c[0x2e];
    u8 index;
} FieldObject;

extern void func_ov001_0207f20c(FieldObject *object, int arg);

void FieldObject_ClearMatchingTarget_02081d24(FieldObject *object, int arg)
{
    ObjectData *data = object->data;

    if (data->targetIndex == object->index) {
        data->targetIndex = -1;
    }
    func_ov001_0207f20c(object, arg);
}
