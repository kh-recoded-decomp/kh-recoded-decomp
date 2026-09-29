#include "nitro/types.h"

typedef struct CollisionWorld CollisionWorld;

extern void func_020351b8(CollisionWorld *world, void *query);
extern CollisionWorld *g_collisionWorld_0206083c;

void ResetAndQueryWorldCollision_0203644c(void *query)
{
    func_020351b8(g_collisionWorld_0206083c, query);
}
