#include "src/collision/CollisionContacts.h"

typedef struct CollisionQuery {
    u8 reserved00[0xe];
    u16 id;
    void *actor;
    s32 unknown14;
    u8 reserved18[0xc];
    void *shape;
    CollisionContacts *workspace;
    fx32 unknown2c;
    s32 unknown30;
    s32 unknown34;
    s32 unknown38;
    u8 option3c;
    u8 option3d;
    u8 option3e;
    u8 reserved3f;
    u8 kind;
    u8 reserved41[3];
    s32 unknown44;
    s32 unknown48;
    u8 reserved4c[4];
    s32 unknown50;
    u8 reserved54[4];
    s32 unknown58;
    u8 reserved5c[4];
} CollisionQuery;

typedef char CollisionQuerySizeCheck[sizeof(CollisionQuery) == 0x60 ? 1 : -1];

/* Initialize the active query fields; reserved bytes and callback contexts survive. */
void CollisionQuery_Init(CollisionQuery *query, u16 id, void *actor, u8 kind,
                          u8 option3c, u8 option3d, void *shape,
                          CollisionContacts *workspace, s32 unknown44)
{
    query->id = id;
    query->actor = actor;
    query->kind = kind;
    query->option3c = option3c;
    query->option3d = option3d;
    query->option3e = 1;
    query->unknown2c = 0x3000;
    query->shape = shape;
    query->workspace = workspace;
    query->unknown44 = unknown44;
    query->unknown14 = 0;
    query->unknown30 = -1;
    query->unknown34 = -1;
    query->unknown38 = -1;
    query->unknown48 = 0;
    query->unknown50 = 0;
    query->unknown58 = 0;
    workspace->count = 0;
    workspace->projectionMode = 0;
}
