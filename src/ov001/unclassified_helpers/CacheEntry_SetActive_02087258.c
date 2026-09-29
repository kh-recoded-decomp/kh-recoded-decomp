#include "nitro/types.h"

typedef struct RegisteredActor {
    u8 pad_00[8];
    u16 flags;
} RegisteredActor;

typedef struct CacheEntry CacheEntry;

typedef struct CacheEntryOps {
    u8 pad_00[0x18];
    void (*onSetActive)(CacheEntry *entry, BOOL active);
} CacheEntryOps;

struct CacheEntry {
    u8 pad_00[4];
    CacheEntryOps *ops;
    RegisteredActor *actor;
    u8 pad_0C[0x24];
    u16 flags;
    u8 bitIndex;
};

typedef struct ResourceCache {
    u8 pad_000[0x178];
    u32 inactiveBits[0x10];
} ResourceCache;

extern ResourceCache *g_resourceCache_020a04dc;
extern void WritePackedBits_0202d560(u32 *base, u32 bitOffset, u32 bitCount, u32 value);
extern void ActorRegistry_Add_02036944(RegisteredActor *actor);
extern void ActorRegistry_Remove_02036994(RegisteredActor *actor);

void CacheEntry_SetActive_02087258(CacheEntry *entry, BOOL active)
{
    WritePackedBits_0202d560(g_resourceCache_020a04dc->inactiveBits, entry->bitIndex, 1, active == FALSE);
    if (entry->flags & 4) {
        if (active) {
            if (!(entry->actor->flags & 0x100)) {
                ActorRegistry_Add_02036944(entry->actor);
            }
        } else {
            if (entry->actor->flags & 0x100) {
                ActorRegistry_Remove_02036994(entry->actor);
            }
        }
    }
    if (entry->ops->onSetActive != NULL) {
        entry->ops->onSetActive(entry, active);
    }
}
