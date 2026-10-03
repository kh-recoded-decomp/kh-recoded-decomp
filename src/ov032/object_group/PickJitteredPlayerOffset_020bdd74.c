#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x38];
    VecFx32 position;
} WanderObject;

extern void *func_ov001_0206dc4c(int index);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern u32 random_next_scaled_0202aa04(u32 upperBound);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void func_01ffaff4(VecFx32 *in, VecFx32 *out);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);

void PickJitteredPlayerOffset_020bdd74(WanderObject *object, VecFx32 *out)
{
    VecFx32 diff;
    u32 range;

    VEC_Subtract_01ff9e3c(func_ov001_0206dc4c(0), &object->position, &diff);
    range = 0x3666;
    diff.x += random_next_scaled_0202aa04(range) - (range >> 1);
    diff.z += random_next_scaled_0202aa04(range) - (range >> 1);
    if (VEC_Mag_01ff9f28(&diff) > (fx32)(range >> 1)) {
        VecFx32 dir = diff;
        func_01ffaff4(&dir, &dir);
        ScaleVecFx32InPlace_0204a5e4(&dir, range >> 1);
        *out = dir;
    } else {
        *out = diff;
    }
}
