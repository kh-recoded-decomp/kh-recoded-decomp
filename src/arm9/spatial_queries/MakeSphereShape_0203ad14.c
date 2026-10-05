#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollBox {
    VecFx32 max;
    VecFx32 min;
} CollBox;

typedef struct CollShape {
    void *geometry;
    CollBox box;
    s32 kind;
} CollShape;

typedef struct CollSphere {
    VecFx32 center;
    fx32 radius;
} CollSphere;

typedef void (*ShapeBoundsFn)(CollShape *shape, CollBox *box);

extern const ShapeBoundsFn g_shapeBoundsTable_020559c0[];

static inline void SetShapeCenter(CollShape *shape, const VecFx32 *center)
{
    ((CollSphere *)shape->geometry)->center = *center;
}

void MakeSphereShape_0203ad14(CollShape *shape, CollSphere *sphere, const VecFx32 *center, fx32 radius)
{
    shape->geometry = sphere;
    sphere->radius = radius;
    shape->kind = 0;
    SetShapeCenter(shape, center);
    g_shapeBoundsTable_020559c0[0](shape, &shape->box);
}
