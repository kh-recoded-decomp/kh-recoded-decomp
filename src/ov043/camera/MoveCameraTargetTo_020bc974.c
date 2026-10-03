#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u8 *data_ov043_020bd2c0;
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_ov043_020bc90c(VecFx32 *offset);

void MoveCameraTargetTo_020bc974(const VecFx32 *pos) {
    VecFx32 offset;
    VecFx32 delta;
    VEC_Subtract_01ff9e3c(pos, (VecFx32 *)(data_ov043_020bd2c0 + 0x94), &delta);
    offset = delta;
    func_ov043_020bc90c(&offset);
}
