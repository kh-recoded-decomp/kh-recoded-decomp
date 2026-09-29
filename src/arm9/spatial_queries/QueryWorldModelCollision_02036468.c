#include "nitro/types.h"

typedef struct CollisionWorld CollisionWorld;
typedef struct CollisionResult CollisionResult;

extern CollisionResult *QueryModelCollision_01ffce24(CollisionWorld *world, void *query);
extern CollisionWorld *g_collisionWorld_0206083c;

CollisionResult *QueryWorldModelCollision_02036468(void *query)
{
    return QueryModelCollision_01ffce24(g_collisionWorld_0206083c, query);
}
