#include "nitro/types.h"
#include "nitro/fx_types.h"

extern VecFx32 data_0205ab3c;
extern VecFx32 data_0205ab54;
extern int ProjectWorldPositionToScreen_02019f84(const VecFx32 *position, int *screenX, int *screenY);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);

BOOL Camera_GetScreenEdgeMask_020c28d0(u32 *edgeMask, const VecFx32 *position, int marginX, int marginY)
{
    int result;
    int screenX;
    int screenY;
    u32 mask = 0;
    VecFx32 toPosition;
    VecFx32 viewDirection;

    result = ProjectWorldPositionToScreen_02019f84(position, &screenX, &screenY);
    VEC_Subtract_01ff9e3c(position, &data_0205ab3c, &toPosition);
    VEC_Subtract_01ff9e3c(&data_0205ab54, &data_0205ab3c, &viewDirection);
    func_01ffaff4(&toPosition, &toPosition);
    func_01ffaff4(&viewDirection, &viewDirection);
    if (VEC_DotProduct_01ff9e6c(&viewDirection, &toPosition) < 0) {
        result = -1;
        screenX = -screenX;
        screenY = -screenY;
    }
    if (0xff - marginX < screenX) {
        mask |= 2;
        result = -1;
    }
    if (marginX > screenX) {
        mask |= 1;
        result = -1;
    }
    if (marginY > screenY) {
        mask |= 4;
        result = -1;
    }
    if (0xc0 - marginY < screenY) {
        mask |= 8;
        mask |= screenX < 0x80 ? 1 : 2;
        result = -1;
    }
    *edgeMask = mask;
    return result != -1;
}

