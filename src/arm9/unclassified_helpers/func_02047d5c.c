#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void func_0204774c(s32 param1, fx32 dot, const VecFx32 *param3, s32 param4, s32 param5, s32 param6, s32 param7);

void func_02047d5c(s32 param1, const VecFx32 *param2, const VecFx32 *param3, s32 param4, s32 param5, s32 param6, s32 param7) {
    fx32 dot = VEC_DotProduct_01ff9e6c(param3, param2);
    func_0204774c(param1, dot, param3, param4, param5, param6, param7);
}
