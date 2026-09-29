#include "nitro/types.h"

typedef struct CollisionWorld CollisionWorld;
typedef struct CollisionResult CollisionResult;

extern CollisionResult *func_020351cc(CollisionWorld *world, void *params);
extern CollisionWorld *g_collisionWorld_0206083c;

CollisionResult *SweepWorldCollision_020364a0(void *params)
{
    return func_020351cc(g_collisionWorld_0206083c, params);
}
