#ifndef OV011_SPAWN_COLLISION_OWNER_H
#define OV011_SPAWN_COLLISION_OWNER_H

#include "nitro/types.h"
#include "nitro/fx_types.h"

/* Partial views used by the spawn commands and their clearance query. */
typedef struct SpawnCollisionBody {
    u8 reserved00[0x10];
    u8 collisionBody[0xa8];
    VecFx32 center;
} SpawnCollisionBody;

typedef struct SpawnOwner {
    u8 reserved00[0xc];
    SpawnCollisionBody *body;
    u8 reserved10[0x30];
    VecFx32 position;
} SpawnOwner;

#endif
