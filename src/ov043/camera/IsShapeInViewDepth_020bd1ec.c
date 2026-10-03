#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionShape CollisionShape;

extern VecFx32 GetShapeCenter_0203b43c(const CollisionShape *shape);
extern fx32 func_0203b2cc(const CollisionShape *shape, const VecFx32 *axis);
extern s32 func_ov031_020bc700(void);
extern BOOL func_0203e958(const CollisionShape *shape, s32 margin);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z) {
    VecFx32 out;
    out.x = x;
    out.y = y;
    out.z = z;
    return out;
}

BOOL IsShapeInViewDepth_020bd1ec(const CollisionShape *shape, s32 margin) {
    VecFx32 center = GetShapeCenter_0203b43c(shape);
    BOOL result = FALSE;
    VecFx32 axis = MakeVec(0, 0, 0x1000);
    s32 depth = func_ov031_020bc700();
    if (center.z >= -(margin + (depth + func_0203b2cc(shape, &axis)))) {
        result = func_0203e958(shape, margin);
    }
    return result;
}
