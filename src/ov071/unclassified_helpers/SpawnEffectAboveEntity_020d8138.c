#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

extern const s16 data_0205356c[];
extern int GetLinkedAngleOffset_020ceb7c(int entity);
extern VecFx32 *func_ov052_020ceb54(int entity);
extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec33_01ff9404(const VecFx32 *vec, const MtxFx33 *mtx, VecFx32 *dst);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void func_ov046_020c13e0(VecFx32 *pos, int kind, int arg);

void SpawnEffectAboveEntity_020d8138(int entity, int arg)
{
    MtxFx33 rotation;
    VecFx32 offset;
    int cosAngle = GetLinkedAngleOffset_020ceb7c(entity);
    int sinAngle = GetLinkedAngleOffset_020ceb7c(entity);

    MTX_RotY33_01ff923c(&rotation, data_0205356c[sinAngle >> 4], data_0205356c[(0x400 - (cosAngle >> 4)) & 0xfff]);
    offset.x = 0;
    offset.y = 0;
    offset.z = FX32_ONE * 4;
    MTX_MultVec33_01ff9404(&offset, &rotation, &offset);
    VEC_Add_01ff9e0c(func_ov052_020ceb54(entity), &offset, &offset);
    offset.y += FX32_ONE * 4;
    func_ov046_020c13e0(&offset, 3, arg);
}
