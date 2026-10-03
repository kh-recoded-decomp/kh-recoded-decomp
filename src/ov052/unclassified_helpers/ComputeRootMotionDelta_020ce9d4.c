#include "nitro/types.h"
#include "nitro/fx.h"

extern s16 data_0205356c[];
extern u16 func_ov052_020ceb7c(int entity);
extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void AdvanceModelAnimation_020ac9a4(void *model, fx32 step, VecFx32 *out);
extern int FX_Div_01ff9c84(int numer, int denom);
extern void ScaleVecFx32_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern void MTX_MultVec33_01ff9404(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst);

void ComputeRootMotionDelta_020ce9d4(int entity, VecFx32 *out)
{
    MtxFx33 rotation;
    VecFx32 motion;
    int index = func_ov052_020ceb7c(entity) >> 4;
    int scale;
    MTX_RotY33_01ff923c(&rotation, -data_0205356c[index], -data_0205356c[(0x400 - index) & 0xfff]);
    AdvanceModelAnimation_020ac9a4((void *)(entity + 0x874), *(fx32 *)(entity + 0x9ec), &motion);
    scale = FX_Div_01ff9c84(0x1000, *(int *)(entity + 0x340));
    if (scale != 0x1000) {
        fx32 height = motion.y;
        ScaleVecFx32_01ffafb4(scale, &motion, &motion);
        motion.y = height;
    }
    MTX_MultVec33_01ff9404(&motion, &rotation, out);
}
