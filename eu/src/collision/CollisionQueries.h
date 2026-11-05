#ifndef KH_RECODED_COLLISION_QUERIES_H
#define KH_RECODED_COLLISION_QUERIES_H

#include "nitro/fx_types.h"

typedef struct CollisionScene CollisionScene;
typedef struct CollisionResult CollisionResult;

typedef struct MoverCastParams {
    const VecFx32 *start;
    const VecFx32 *delta;
    fx32 radius;
    u16 flags;
    u16 groupMask;
    u32 ownerId;
} MoverCastParams;

typedef char MoverCastRadiusOffset[(u32)&((MoverCastParams *)0)->radius == 8 ? 1 : -1];
typedef char MoverCastNativeSize[sizeof(MoverCastParams) == 0x14 ? 1 : -1];

/* Mutates radius to zero; returns borrowed shared result or NULL. */
CollisionResult *QueryModelSegmentCollision(CollisionScene *scene,
                                           MoverCastParams *params);

#endif
