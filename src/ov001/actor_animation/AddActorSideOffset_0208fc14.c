#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldActor {
    u8 pad_000[0x2a4];
    fx32 sideSpeed;
} FieldActor;

extern const VecFx32 data_ov001_020a0234;
extern fx32 ApplyActorScaleFactors_02091818(FieldActor *actor);
extern int FixedPointMultiply12(int left, int right);
extern fx32 func_01ffaff4(const VecFx32 *source, VecFx32 *dest);
extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

void AddActorSideOffset_0208fc14(FieldActor *actor, VecFx32 *position, const VecFx32 *direction)
{
    VecFx32 forward = *direction;
    VecFx32 side;
    fx32 scale = ApplyActorScaleFactors_02091818(actor);

    if (actor->sideSpeed != 0) {
        scale = FixedPointMultiply12(actor->sideSpeed, scale);
        func_01ffaff4(&forward, &forward);
        VEC_CrossProduct_01ff9ea8(&forward, &data_ov001_020a0234, &side);
        VEC_MultAdd_01ffa09c(scale, &side, position, position);
    }
}
