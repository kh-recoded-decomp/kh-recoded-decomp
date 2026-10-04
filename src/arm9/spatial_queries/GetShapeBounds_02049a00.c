#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ShapeData {
    VecFx32 center;
    VecFx32 halfExtent;
    VecFx32 axes[3];
    u8 flags;
} ShapeData;

typedef struct CollisionShape {
    ShapeData *data;
} CollisionShape;

typedef struct ShapeBounds {
    VecFx32 max;
    VecFx32 min;
} ShapeBounds;

extern int abs_02049b60(int value);
extern void func_0204abf4(VecFx32 *vec, int (*transform)(int));
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void NegateVecFx32_0204aa40(VecFx32 *vec);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

static inline VecFx32 AbsVec(VecFx32 vec)
{
    func_0204abf4(&vec, abs_02049b60);
    return vec;
}

static inline VecFx32 ScaledVec(VecFx32 vec, fx32 scale)
{
    ScaleVecFx32InPlace_0204a5e4(&vec, scale);
    return vec;
}

static inline VecFx32 NegatedVec(VecFx32 vec)
{
    NegateVecFx32_0204aa40(&vec);
    return vec;
}

void GetShapeBounds_02049a00(const CollisionShape *shape, ShapeBounds *bounds)
{
    ShapeData *data = shape->data;
    VecFx32 extentY;
    VecFx32 extentZ;

    if (data->flags & 1) {
        bounds->max = data->halfExtent;
    } else {
        bounds->max = ScaledVec(AbsVec(data->axes[0]), data->halfExtent.x);
        extentY = ScaledVec(AbsVec(data->axes[1]), data->halfExtent.y);
        VEC_Add_01ff9e0c(&bounds->max, &extentY, &bounds->max);
        extentZ = ScaledVec(AbsVec(data->axes[2]), data->halfExtent.z);
        VEC_Add_01ff9e0c(&bounds->max, &extentZ, &bounds->max);
    }
    bounds->min = NegatedVec(bounds->max);
    VEC_Add_01ff9e0c(&bounds->max, &data->center, &bounds->max);
    VEC_Add_01ff9e0c(&bounds->min, &data->center, &bounds->min);
}
