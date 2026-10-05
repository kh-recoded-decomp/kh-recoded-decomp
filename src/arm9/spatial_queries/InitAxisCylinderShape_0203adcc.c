#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct AxisCylinder {
    VecFx32 base;
    VecFx32 top;
    VecFx32 axis;
    fx32 radius;
} AxisCylinder;

typedef struct CollisionShape {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef void (*ComputeBoundsFunc)(CollisionShape *shape, s32 *bounds);

extern const ComputeBoundsFunc data_020559c0[];

void InitAxisCylinderShape_0203adcc(CollisionShape *shape, AxisCylinder *cylinder, const VecFx32 *base, const VecFx32 *top,
                                    const VecFx32 *axis, fx32 radius)
{
    shape->data = cylinder;
    cylinder->axis = *axis;
    cylinder->radius = radius;
    cylinder->top = *top;
    shape->kind = 2;
    ((AxisCylinder *)shape->data)->base = *base;
    data_020559c0[2](shape, shape->bounds);
}
