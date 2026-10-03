#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u8 *data_ov043_020bd2c0;
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern u16 FixedPointAtan2_020062bc(int vertical_component, int horizontal_component);

u16 GetCameraYaw_020bcacc(void) {
    VecFx32 direction;
    VecFx32 delta;
    VEC_Subtract_01ff9e3c((VecFx32 *)(data_ov043_020bd2c0 + 0x58), (VecFx32 *)(data_ov043_020bd2c0 + 0x64), &delta);
    direction = delta;
    return FixedPointAtan2_020062bc(direction.x, direction.z);
}
