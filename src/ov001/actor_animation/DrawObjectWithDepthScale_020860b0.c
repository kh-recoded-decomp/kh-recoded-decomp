#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ProjMatrix {
    fx32 m[16];
} ProjMatrix;

typedef struct GlobalStateTail {
    u8 pad_00[0x54];
    u32 flags;
} GlobalStateTail;

typedef struct ObjectModel {
    u8 pad_00[0x14];
    u8 sceneNode[0xa4];
} ObjectModel;

typedef struct DepthObject {
    u8 pad_00[0xc];
    ObjectModel *model;
    u8 pad_10[0x38];
    fx32 depth;
} DepthObject;

extern ProjMatrix data_0205a92c;
extern GlobalStateTail data_0205a9a4;
extern s16 data_020536ac[];
extern void func_ov042_020bd0f0(void);
extern int func_02006450(int left, int right);
extern fx32 FX_Div_01ff9c84(fx32 numerator, fx32 denominator);
extern void func_01ff878c(const void *src, void *dst, u32 size);
extern void SceneNode_Draw_01ffb12c(void *node);
extern void func_02019188(void);

static inline void SetProjection(const ProjMatrix *matrix)
{
    func_01ff878c(matrix, &data_0205a92c, sizeof(ProjMatrix));
    data_0205a9a4.flags &= ~0x50;
}

void DrawObjectWithDepthScale_020860b0(DepthObject *object)
{
    ProjMatrix scaled;
    ProjMatrix saved;
    fx32 scale;

    func_ov042_020bd0f0();
    scale = FX_Div_01ff9c84(0x1000, func_02006450(-object->depth, data_020536ac[10]) + 0x1000);
    scaled = data_0205a92c;
    saved = scaled;
    scaled.m[0] = func_02006450(scaled.m[0], scale);
    scaled.m[5] = func_02006450(scaled.m[5], scale);
    SetProjection(&scaled);
    SceneNode_Draw_01ffb12c(object->model->sceneNode);
    SetProjection(&saved);
    func_02019188();
}
