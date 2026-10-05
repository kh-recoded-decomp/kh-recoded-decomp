#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct GeometryState {
    u8 pad_00[0x88];
    u32 polygonAttr;
    u8 pad_8c[0x38];
    VecFx32 scale;
    u8 pad_d0[4];
    u32 flags;
} GeometryState;

typedef struct ModelDrawObject {
    u8 pad_00[0x78];
    void *model;
    u8 pad_7c[0x28];
    VecFx32 translation;
} ModelDrawObject;

extern void MI_Copy36B_01ff87c4(const void *src, void *dst);
extern u32 GetMaterialPolygonId_0201a7a0(void *model, u32 materialIndex);
extern u32 GetMaterialLightMask_0201a6c4(void *model, u32 materialIndex);
extern u32 GetMaterialPolygonMode_0201a730(void *model, u32 materialIndex);
extern void func_02019188(void);
extern MtxFx33 data_0205a9b8;
extern VecFx32 data_0205a9dc;
extern GeometryState data_0205a924;

void SetupModelDrawState_01fff810(ModelDrawObject *object, fx32 scale, const MtxFx33 *rotation, u32 alpha) {
    u32 polygonId;
    u32 lightMask;
    u32 polygonMode;
    void *model;

    MI_Copy36B_01ff87c4(rotation, &data_0205a9b8);
    data_0205a9dc = object->translation;
    data_0205a924.scale.x = scale;
    data_0205a924.scale.y = scale;
    data_0205a924.scale.z = scale;
    model = object->model;
    data_0205a924.flags &= ~0xa4;
    polygonId = GetMaterialPolygonId_0201a7a0(model, 0);
    lightMask = GetMaterialLightMask_0201a6c4(object->model, 0);
    polygonMode = GetMaterialPolygonMode_0201a730(object->model, 0);
    data_0205a924.polygonAttr = lightMask | (polygonMode << 4) | 0xc0 | (polygonId << 24) | (alpha << 16);
    func_02019188();
}
