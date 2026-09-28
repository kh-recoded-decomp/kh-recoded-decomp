#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x28];
    fx32 margin;
} Source;

extern void func_02049b6c(void);
extern void Vec3AddScalar_0204a534(VecFx32 *v, fx32 amount);
extern void Vec3SubScalar_0204a55c(VecFx32 *v, fx32 amount);

void AdjustAabbMarginByField_02049c1c(Source **handle, VecFx32 *bounds)
{
    Source *source = *handle;

    func_02049b6c();
    Vec3AddScalar_0204a534(bounds, source->margin);
    Vec3SubScalar_0204a55c(bounds + 1, source->margin);
}
