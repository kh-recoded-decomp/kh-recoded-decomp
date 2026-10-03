#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x47];
    s8 carryState;
    u8 pad_48[0x77 - 0x48];
    u8 mode;
    u8 pad_78[0xc0 - 0x78];
    u32 flags;
    u8 pad_c4[0xc8 - 0xc4];
    int soundId;
    VecFx32 velocity;
} FieldObject;

extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern fx32 func_01ff9cfc(fx32 value);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *v, fx32 scale);

BOOL PushFieldObject_020a3258(FieldObject *obj, const VecFx32 *push)
{
    VecFx32 velocity;
    VecFx32 impulse;
    VecFx32 sum;
    VecFx32 direction;
    VecFx32 scaled;
    BOOL pushable;
    fx32 speed;
    fx32 impulseSq;

    if (obj->mode == 9 || (u8)(obj->mode + 0xf4) <= 3) {
        pushable = TRUE;
    } else {
        pushable = FALSE;
    }
    if (pushable && obj->carryState != 2) {
        obj->flags |= 8;
        obj->flags |= 0x400;
        velocity = obj->velocity;
        impulse = *push;
        velocity.y = 0;
        impulse.y = 0;
        VEC_Add_01ff9e0c(&velocity, &impulse, &sum);
        if (sum.x != 0 || sum.y != 0 || sum.z != 0) {
            func_01ff9f88(&sum, &direction);
            impulseSq = VEC_DotProduct_01ff9e6c(&impulse, &impulse);
            speed = VEC_DotProduct_01ff9e6c(&velocity, &velocity);
            speed = func_01ff9cfc(speed + impulseSq);
            if (speed > 0xccd) {
                speed = 0xccd;
            }
            scaled = direction;
            ScaleVecFx32InPlace_0204a5e4(&scaled, speed);
            sum = scaled;
            obj->velocity.x = sum.x;
            obj->velocity.z = sum.z;
        }
        obj->soundId = 0x333;
        return TRUE;
    }
    return FALSE;
}
