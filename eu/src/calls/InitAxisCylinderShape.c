#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct AxisCylinder {
    VecFx32 base;
    VecFx32 top;
    VecFx32 axis;
    fx32 radius;
} AxisCylinder;

typedef struct CollisionShape {
    void *geometry;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef void (*ShapeBoundsFunc)(CollisionShape *shape, s32 *bounds);

extern const ShapeBoundsFunc gCollisionBoundsDispatch[];

void InitAxisCylinderShape(CollisionShape *shape, AxisCylinder *cylinder, const VecFx32 *base, const VecFx32 *top,
                           const VecFx32 *axis, fx32 radius)
{
    shape->geometry = cylinder;
    cylinder->axis = *axis;
    cylinder->radius = radius;
    cylinder->top = *top;
    shape->kind = 2;
    ((AxisCylinder *)shape->geometry)->base = *base;
    gCollisionBoundsDispatch[2](shape, shape->bounds);
}
