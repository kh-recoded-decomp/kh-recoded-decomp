#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct WorldObject WorldObject;

typedef struct CollisionWorld {
    u8 pad_00[0x20];
    WorldObject *objects[1];
} CollisionWorld;

extern void SetObjectProbeSphere_020361b8(WorldObject *object, BOOL enable, fx32 radius);
extern CollisionWorld *g_collisionWorld_0206083c;

void SetWorldObjectProbeSphere_02036198(int index, BOOL enable, fx32 radius)
{
    SetObjectProbeSphere_020361b8(g_collisionWorld_0206083c->objects[index], enable, radius);
}
