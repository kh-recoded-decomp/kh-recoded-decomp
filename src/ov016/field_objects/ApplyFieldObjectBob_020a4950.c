#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0xc0];
    u32 flags;
    u8 pad_c4[0xcc - 0xc4];
    VecFx32 velocity;
} FieldObject;

extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *v, fx32 scale);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);

void ApplyFieldObjectBob_020a4950(FieldObject *obj, VecFx32 *position, fx32 *drop)
{
    VecFx32 offset;
    VecFx32 direction;
    VecFx32 scaled;
    fx32 amount;
    fx32 scale;

    if (obj->flags & 0x20000) {
        amount = VEC_Mag_01ff9f28(&obj->velocity);
        func_01ff9f88(&obj->velocity, &direction);
        amount = amount * 0x99a / 0x119a;
        if (amount < 0x4cd) {
            scale = amount * 2;
        } else {
            scale = (0x99a - amount) * 2;
        }
        scaled = direction;
        ScaleVecFx32InPlace_0204a5e4(&scaled, scale);
        offset = scaled;
        VEC_Add_01ff9e0c(position, &offset, position);
        if (*drop < 0) {
            *drop -= offset.y;
        }
    }
}
