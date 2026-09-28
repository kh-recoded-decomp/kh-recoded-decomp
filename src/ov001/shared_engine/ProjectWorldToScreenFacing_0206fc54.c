#include "nitro/types.h"
#include "nitro/fx_types.h"

extern int ProjectWorldPositionToScreen_02028c24(const VecFx32 *world, int *x, int *y);
extern const VecFx32 *func_02028c0c(void);
extern const VecFx32 *func_02028c18(void);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);

void ProjectWorldToScreenFacing_0206fc54(const VecFx32 *world, int *x, int *y)
{
    VecFx32 viewDir;
    VecFx32 toWorld;
    const VecFx32 *cameraPos;

    ProjectWorldPositionToScreen_02028c24(world, x, y);
    cameraPos = func_02028c0c();
    VEC_Subtract_01ff9e3c(func_02028c18(), cameraPos, &viewDir);
    VEC_Subtract_01ff9e3c(world, cameraPos, &toWorld);
    if (VEC_DotProduct_01ff9e6c(&viewDir, &viewDir) != 0 && VEC_DotProduct_01ff9e6c(&toWorld, &toWorld) != 0) {
        func_01ff9f88(&viewDir, &viewDir);
        func_01ff9f88(&toWorld, &toWorld);
        if (VEC_DotProduct_01ff9e6c(&viewDir, &toWorld) < 0) {
            *x = 255 - *x;
            *y = 191 - *y;
        }
    }
}
