#include "nitro/fx_types.h"

extern void func_02049b6c(void);
extern void Vec3AddScalar_0204a534(VecFx32 *v, fx32 amount);
extern void Vec3SubScalar_0204a55c(VecFx32 *v, fx32 amount);

void AdjustAabbMargin_02049bf0(u32 unused, VecFx32 *bounds)
{
    func_02049b6c();
    Vec3AddScalar_0204a534(bounds, 0x10);
    Vec3SubScalar_0204a55c(bounds + 1, 0x10);
}
