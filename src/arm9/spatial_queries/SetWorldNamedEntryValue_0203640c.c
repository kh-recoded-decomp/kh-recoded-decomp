#include "nitro/types.h"

typedef struct NamedEntry {
    char name[0xc];
    u32 value;
    void *data;
} NamedEntry;

typedef struct CollisionWorld {
    u8 pad_00[0x820];
    NamedEntry *namedEntries;
} CollisionWorld;

extern CollisionWorld *g_collisionWorld_0206083c;

void SetWorldNamedEntryValue_0203640c(int index, const u32 *value)
{
    NamedEntry *entries = g_collisionWorld_0206083c->namedEntries;
    if (entries != NULL) {
        entries[index].value = *value;
    }
}
