#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

extern u8 data_0205a970[];
extern s16 data_0205356c[];
extern void func_01ff913c(const void *src, MtxFx33 *dst);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

VecFx32 GetCameraOrbitOffset_020af8d4(fx32 radians)
{
    MtxFx33 camera;
    VecFx32 offset;
    MtxFx33 fetched;
    VecFx32 axis;
    VecFx32 sum;
    VecFx32 result;
    int index;

    func_01ff913c(data_0205a970, &fetched);
    camera = fetched;
    index = (int)((((s64)radians << 16) / 0x6488) & 0xffff) >> 4;
    axis = *(VecFx32 *)&camera._00;
    ScaleVecFx32InPlace_0204a5e4(&axis, data_0205356c[(0x400 - index) & 0xfff]);
    offset = axis;
    VEC_MultAdd_01ffa09c(data_0205356c[index], (VecFx32 *)&camera._10, &offset, &sum);
    result = sum;
    offset = result;
    return result;
}
