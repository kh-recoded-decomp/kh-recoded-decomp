#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_00[0x54];
    u32 flags;
} RenderState;

typedef struct {
    u8 pad_00[0x24];
    VecFx32 direction;
    u8 pad_30[0x20];
    u8 transform[0x84];
    u8 material[0xc];
    u8 model[4];
} OrientedModel;

extern const VecFx32 data_ov021_020b4fbc;
extern u8 data_0205a9b8[];
extern RenderState data_0205a9a4;
extern void func_01ff90ec(MtxFx33 *mtx);
extern void func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_0201931c(void *model);
extern void func_01ff87c4(const MtxFx33 *src, void *dst);
extern void func_020192ec(void *material);
extern void FlushGeometryStateVariant_020191b8(void);
extern void func_01ffe1bc(void *transform);

void DrawOrientedModel_020ab370(OrientedModel *model)
{
    MtxFx33 rotation;
    VecFx32 side;
    VecFx32 up;
    VecFx32 forward;

    func_01ff90ec(&rotation);
    if (model->direction.x != 0 || model->direction.y != 0 || model->direction.z != 0) {
        func_01ffaff4(&model->direction, &forward);
        VEC_CrossProduct_01ff9ea8(&data_ov021_020b4fbc, &forward, &side);
        func_01ffaff4(&side, &side);
        VEC_CrossProduct_01ff9ea8(&forward, &side, &up);
        rotation._00 = side.x;
        rotation._01 = side.y;
        rotation._02 = side.z;
        rotation._10 = up.x;
        rotation._11 = up.y;
        rotation._12 = up.z;
        rotation._20 = forward.x;
        rotation._21 = forward.y;
        rotation._22 = forward.z;
    }
    func_0201931c(model->model);
    func_01ff87c4(&rotation, data_0205a9b8);
    data_0205a9a4.flags &= ~0xa4;
    func_020192ec(model->material);
    FlushGeometryStateVariant_020191b8();
    func_01ffe1bc(model->transform);
}
