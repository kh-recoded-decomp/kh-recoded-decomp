#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CollisionBox {
    VecFx32 center;
    VecFx32 halfExtents;
    MtxFx33 axes;
    u8 flags;
} CollisionBox;

typedef struct CollisionShape {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef struct ShapeFuncs {
    void (*unused)(void);
    void (*computeBounds)(CollisionShape *shape, s32 *bounds);
} ShapeFuncs;

extern ShapeFuncs data_020559c0;
void UpdateBoxAxisAlignedFlag_0203b1c0(CollisionBox *box);

/* Fills the shape returned by value to callers */
void InitBoxShape_0203ad54(CollisionShape *shape, void *storage, const VecFx32 *center, const VecFx32 *halfExtents, const MtxFx33 *rotation)
{
    CollisionBox *box = (CollisionBox *)storage;
    shape->data = box;
    box->halfExtents = *halfExtents;
    box->axes = *rotation;
    UpdateBoxAxisAlignedFlag_0203b1c0(box);
    shape->kind = 1;
    ((CollisionBox *)shape->data)->center = *center;
    data_020559c0.computeBounds(shape, shape->bounds);
}


