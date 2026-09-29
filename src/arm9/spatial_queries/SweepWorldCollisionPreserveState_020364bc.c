#include "nitro/types.h"

typedef struct CollisionWorld CollisionWorld;
typedef struct CollisionResult CollisionResult;

extern CollisionResult *func_02035264(CollisionWorld *world, void *params);
extern CollisionWorld *g_collisionWorld_0206083c;

CollisionResult *SweepWorldCollisionPreserveState_020364bc(void *params)
{
    return func_02035264(g_collisionWorld_0206083c, params);
}
