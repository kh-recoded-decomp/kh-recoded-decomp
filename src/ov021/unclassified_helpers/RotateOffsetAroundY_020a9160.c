#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

extern const s16 data_0205356c[];
extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec33_01ff9404(const VecFx32 *vec, const MtxFx33 *mtx, VecFx32 *dst);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);

void RotateOffsetAroundY_020a9160(VecFx32 *out, const VecFx32 *origin, int angle, const VecFx32 *offset)
{
    VecFx32 point = *offset;
    MtxFx33 rotation;
    int index = angle >> 4;

    MTX_RotY33_01ff923c(&rotation, data_0205356c[index], data_0205356c[(0x400 - index) & 0xfff]);
    MTX_MultVec33_01ff9404(&point, &rotation, &point);
    VEC_Add_01ff9e0c(&point, origin, &point);
    *out = point;
}

