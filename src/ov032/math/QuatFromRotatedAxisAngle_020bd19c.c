#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    fx32 w;
    fx32 x;
    fx32 y;
    fx32 z;
} Quaternion;

extern const VecFx32 data_02053438;
extern const fx16 g_sinTable_0205356c[];

extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec33_01ff9404(const VecFx32 *vec, const MtxFx33 *mtx, VecFx32 *dst);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);

void QuatFromRotatedAxisAngle_020bd19c(Quaternion *out, const VecFx32 *axis, int angle)
{
    Quaternion quat;
    VecFx32 dir;
    MtxFx33 rot;
    int index;
    fx32 sinHalf;

    if (axis->x == 0 && axis->y == 0 && axis->z == 0) {
        dir = data_02053438;
    } else {
        func_01ff9f88(axis, &dir);
    }
    MTX_RotY33_01ff923c(&rot, g_sinTable_0205356c[0x400], g_sinTable_0205356c[0]);
    MTX_MultVec33_01ff9404(&dir, &rot, &dir);
    index = (u16)angle;
    index = (index / 2) >> 4;
    sinHalf = g_sinTable_0205356c[index];
    quat.w = g_sinTable_0205356c[(0x400 - index) & 0xfff];
    quat.x = FixedPointMultiply12(sinHalf, dir.x);
    quat.y = FixedPointMultiply12(sinHalf, dir.y);
    quat.z = FixedPointMultiply12(sinHalf, dir.z);
    *out = quat;
}
