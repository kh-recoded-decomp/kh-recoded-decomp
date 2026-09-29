#include "nitro/types.h"

typedef struct CollisionWorld CollisionWorld;

extern void TestQueryAgainstMeshList_02035270(CollisionWorld *world, void *params);
extern CollisionWorld *g_collisionWorld_0206083c;

void TestQueryAgainstWorldMeshes_020364d8(void *params)
{
    TestQueryAgainstMeshList_02035270(g_collisionWorld_0206083c, params);
}
