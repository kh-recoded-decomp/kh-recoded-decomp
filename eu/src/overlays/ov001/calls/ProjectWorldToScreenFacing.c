#include "src/graphics/CameraState.h"

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);

void ProjectWorldToScreenFacing(const VecFx32 *world, int *x, int *y)
{
    VecFx32 viewDir;
    VecFx32 toWorld;
    const VecFx32 *cameraPos;

    ProjectWorldPositionWithSavedCamera(world, x, y);
    cameraPos = GetSavedCameraPosition();
    VEC_Subtract(GetSavedCameraTarget(), cameraPos, &viewDir);
    VEC_Subtract(world, cameraPos, &toWorld);
    if (VEC_DotProduct(&viewDir, &viewDir) != 0 && VEC_DotProduct(&toWorld, &toWorld) != 0) {
        VEC_Normalize(&viewDir, &viewDir);
        VEC_Normalize(&toWorld, &toWorld);
        if (VEC_DotProduct(&viewDir, &toWorld) < 0) {
            *x = 255 - *x;
            *y = 191 - *y;
        }
    }
}
