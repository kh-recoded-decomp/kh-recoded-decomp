#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CollisionShape CollisionShape;

extern MtxFx43 data_0205a970;
extern const VecFx32 *func_ov042_020bd290(void);
extern const fx32 *func_ov042_020bd590(void);
extern VecFx32 GetShapeCenter_0203b43c(const CollisionShape *shape);
extern fx32 func_0203b2cc(const CollisionShape *shape, const VecFx32 *axis);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void MTX_Copy43To33_01ff913c(const MtxFx43 *src, MtxFx33 *dst);

static inline VecFx32 SubtractVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 out;
    VEC_Subtract_01ff9e3c(a, b, &out);
    return out;
}

static inline MtxFx33 GetViewRotation(void)
{
    MtxFx33 rotation;
    MTX_Copy43To33_01ff913c(&data_0205a970, &rotation);
    return rotation;
}

BOOL IsShapeInViewBounds_0203eab0(const CollisionShape *shape, fx32 margin)
{
    VecFx32 delta;
    MtxFx33 rotation;
    const VecFx32 *origin = func_ov042_020bd290();
    VecFx32 center = GetShapeCenter_0203b43c(shape);
    const fx32 *extent;
    fx32 radius;
    fx32 distance;

    delta = SubtractVec(&center, origin);
    rotation = GetViewRotation();
    extent = func_ov042_020bd590();
    radius = func_0203b2cc(shape, (const VecFx32 *)rotation.m[0]);
    distance = VEC_DotProduct_01ff9e6c((const VecFx32 *)rotation.m[0], &delta);
    if (distance < 0)
        distance = -distance;
    if (distance > margin + (extent[1] + radius))
        return FALSE;
    radius = func_0203b2cc(shape, (const VecFx32 *)rotation.m[1]);
    distance = VEC_DotProduct_01ff9e6c((const VecFx32 *)rotation.m[1], &delta);
    if (distance < 0)
        distance = -distance;
    if (distance > margin + (extent[2] + radius))
        return FALSE;
    return TRUE;
}
