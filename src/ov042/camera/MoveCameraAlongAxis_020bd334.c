#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u8 *data_ov042_020be5c0;
extern void func_01ffaff4(const void *src, VecFx32 *out);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void func_ov042_020bd2a0(VecFx32 *offset);

void MoveCameraAlongAxis_020bd334(fx32 distance) {
    VecFx32 offset;
    VecFx32 axis;
    VecFx32 scaled;
    func_01ffaff4(data_ov042_020be5c0 + 0x11c, &axis);
    scaled = axis;
    ScaleVecFx32InPlace_0204a5e4(&scaled, distance);
    offset = scaled;
    func_ov042_020bd2a0(&offset);
}
