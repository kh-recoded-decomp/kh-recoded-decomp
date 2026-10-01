#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ClassInstance {
    u16 flags;
    u8 pad_02[0x76];
    void *model;
    u16 angle;
    u8 pad_7e[0x26];
    VecFx32 position;
    u8 pad_b0[0x54];
} ClassInstance;

typedef struct FieldObjectClass {
    u8 pad_00[0x84];
    ClassInstance instances[1];
} FieldObjectClass;

typedef struct FieldObject {
    u8 pad_00[0x08];
    FieldObjectClass *objectClass;
    u8 pad_0c[0x34];
    VecFx32 position;
    u8 pad_4c[0xc];
    u32 unk_58_0 : 27;
    u32 alpha : 5;
    int slot;
    u32 unk_60;
    fx32 rotation;
} FieldObject;

extern void Model_SetAllMaterialAlpha_0201a900(void *model, int alpha);
extern void SceneNode_Draw_01ffb12c(void *node);

void FieldObject_DrawInstance_020823a0(FieldObject *object)
{
    FieldObjectClass *objectClass = object->objectClass;
    ClassInstance *instance;

    if (object->alpha != 0) {
        objectClass->instances[object->slot].position = object->position;
        instance = &objectClass->instances[object->slot];
        instance->angle = (((s64)object->rotation << 16) / 0x6488) & 0xffff;
        instance->flags |= 0x20;
        Model_SetAllMaterialAlpha_0201a900(objectClass->instances[object->slot].model, object->alpha);
        SceneNode_Draw_01ffb12c(&objectClass->instances[object->slot]);
        Model_SetAllMaterialAlpha_0201a900(objectClass->instances[object->slot].model, 0x1f);
    }
}
