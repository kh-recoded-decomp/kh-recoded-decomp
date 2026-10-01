#include "nitro/types.h"
#include "nitro/fx_types.h"

extern int ProjectWorldPositionToScreen_02019f84(const VecFx32 *world, int *x, int *y);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern VecFx32 data_0205ab3c;
extern VecFx32 data_0205ab54;

int ProjectWorldToScreenFx_0206ad34(const VecFx32 *world, fx32 *screen)
{
    VecFx32 toWorld;
    VecFx32 viewDir;
    int x;
    int y;
    int result;
    VecFx32 *cameraPos = &data_0205ab3c;

    result = ProjectWorldPositionToScreen_02019f84(world, &x, &y);
    y -= 8;
    if (result != -1) {
        VEC_Subtract_01ff9e3c(world, cameraPos, &toWorld);
        VEC_Subtract_01ff9e3c(&data_0205ab54, cameraPos, &viewDir);
        if (toWorld.x != 0 || toWorld.y != 0 || toWorld.z != 0) {
            func_01ff9f88(&toWorld, &toWorld);
        }
        if (viewDir.x != 0 || viewDir.y != 0 || viewDir.z != 0) {
            func_01ff9f88(&viewDir, &viewDir);
        }
        if (VEC_DotProduct_01ff9e6c(&viewDir, &toWorld) < 0) {
            result = -1;
        }
    }
    screen[0] = x << 12;
    screen[1] = y << 12;
    return result;
}
