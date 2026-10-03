#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x64];
    VecFx32 velocity;
} Obj;

extern const VecFx32 data_02053438;

extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern int FixedPointMultiply12(int left, int right);
extern void VEC_MultAdd_01ffa09c(int scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);

void BounceVelocityOffNormal_020a3134(void *unused, const VecFx32 *normal, Obj *obj)
{
    fx32 dot;

    if (obj->velocity.x != 0 || obj->velocity.y != 0 || obj->velocity.z != 0) {
        dot = VEC_DotProduct_01ff9e6c(&obj->velocity, normal);
        VEC_MultAdd_01ffa09c(-(dot + FixedPointMultiply12(dot, 0x4cd)), normal, &obj->velocity, &obj->velocity);
        if (VEC_Mag_01ff9f28(&obj->velocity) <= 0x80) {
            obj->velocity = data_02053438;
        }
    }
}
