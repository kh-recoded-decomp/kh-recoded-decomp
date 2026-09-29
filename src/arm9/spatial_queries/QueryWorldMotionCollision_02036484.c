#include "nitro/types.h"

typedef struct CollisionWorld CollisionWorld;
typedef struct CollisionResult CollisionResult;

extern CollisionResult *QueryModelMotionCollision_01ffce6c(CollisionWorld *world, void *query);
extern CollisionWorld *g_collisionWorld_0206083c;

CollisionResult *QueryWorldMotionCollision_02036484(void *query)
{
    return QueryModelMotionCollision_01ffce6c(g_collisionWorld_0206083c, query);
}
