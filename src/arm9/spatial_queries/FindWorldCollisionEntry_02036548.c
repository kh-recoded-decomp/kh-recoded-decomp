#include "nitro/types.h"

typedef struct CollisionWorld CollisionWorld;

extern char *CollModel_FindEntry_020352cc(CollisionWorld *world, void *name);
extern CollisionWorld *g_collisionWorld_0206083c;

char *FindWorldCollisionEntry_02036548(void *name)
{
    return CollModel_FindEntry_020352cc(g_collisionWorld_0206083c, name);
}
