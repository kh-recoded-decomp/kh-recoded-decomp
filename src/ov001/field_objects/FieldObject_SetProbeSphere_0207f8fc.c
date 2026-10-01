#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct WorldObject {
    u8 pad_00[8];
    u16 flags;
    u8 pad_0a[0x82];
    void *model;
} WorldObject;

typedef struct FieldObject {
    u8 pad_00[0xc];
    WorldObject *world;
    u8 pad_10[0x2c];
    s16 probeRadius;
    u8 pad_3e[0x10];
    u16 stateFlags;
} FieldObject;

extern void SetObjectProbeSphere_020361b8(WorldObject *object, BOOL enable, fx32 radius);
extern void Model_SetAllPolygonIds_0201a8c0(void *model, int polygonId);
extern void SetAllMaterialsPolyAttrMask_0201a3c4(void *model, BOOL enable, u32 mask);

void FieldObject_SetProbeSphere_0207f8fc(FieldObject *object, BOOL enable, s16 radius, BOOL updateModel)
{
    WorldObject *world = object->world;

    if (world == NULL) {
        return;
    }
    if (enable) {
        object->stateFlags |= 8;
        object->probeRadius = radius;
    } else {
        object->stateFlags &= 0xfff7;
        object->probeRadius = 0;
    }
    if (updateModel) {
        object->stateFlags |= 0x80;
    } else {
        object->stateFlags &= 0xff7f;
    }
    if (world->flags & 4) {
        SetObjectProbeSphere_020361b8(object->world, enable, object->probeRadius);
        if (updateModel) {
            if (enable) {
                Model_SetAllPolygonIds_0201a8c0(object->world->model, 0x3f);
                return;
            }
            SetAllMaterialsPolyAttrMask_0201a3c4(object->world->model, TRUE, 0x3f000000);
        }
    }
}
