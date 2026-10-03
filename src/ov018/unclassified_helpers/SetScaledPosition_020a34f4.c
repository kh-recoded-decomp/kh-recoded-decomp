#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x38];
    VecFx32 position;
} Obj;

extern u8 GetCtxModeByte_02068084(void);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void func_ov018_020a3530(Obj *obj, VecFx32 *position);

void SetScaledPosition_020a34f4(Obj *obj, const VecFx32 *position)
{
    obj->position = *position;
    if (GetCtxModeByte_02068084() != 6) {
        ScaleVecFx32InPlace_0204a5e4(&obj->position, FX_Div_01ff9c84(0x1000, 0x1800));
    }
    func_ov018_020a3530(obj, &obj->position);
}
