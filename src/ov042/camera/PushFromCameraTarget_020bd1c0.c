#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u8 *data_ov042_020be5c0;
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_ov042_020bd178(VecFx32 *offset);

void PushFromCameraTarget_020bd1c0(const VecFx32 *pos) {
    VecFx32 offset;
    VecFx32 delta;
    VEC_Subtract_01ff9e3c(pos, (VecFx32 *)(data_ov042_020be5c0 + 0x88), &delta);
    offset = delta;
    func_ov042_020bd178(&offset);
}
