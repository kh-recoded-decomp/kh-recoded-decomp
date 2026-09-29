#include "nitro/types.h"

typedef struct NamedEntry {
    char name[0xc];
    u32 value;
    void *data;
} NamedEntry;

typedef struct CollisionWorld {
    u8 pad_00[0x820];
    NamedEntry *namedEntries;
    int namedEntryCount;
} CollisionWorld;

extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern CollisionWorld *g_collisionWorld_0206083c;

void AllocWorldNamedEntries_02036310(int count)
{
    g_collisionWorld_0206083c->namedEntries = NNSi_FndAllocFromDefaultHeap_0202a178(count * sizeof(NamedEntry));
    g_collisionWorld_0206083c->namedEntryCount = count;
}
