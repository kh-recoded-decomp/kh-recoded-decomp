#include "nitro/types.h"

typedef struct CacheEntry CacheEntry;

typedef struct CacheEntryOps {
    u8 pad_00[4];
    void (*onRelease)(CacheEntry *entry);
} CacheEntryOps;

struct CacheEntry {
    CacheEntry *next;
    CacheEntryOps *ops;
    u8 pad_08[0x2A];
    u8 actorIndex;
};

typedef struct CacheSlot {
    u32 key;
    void *block;
} CacheSlot;

typedef struct ResourceCache {
    u8 pad_000[5];
    u8 flags;
    u8 pad_006[2];
    CacheEntry *entries;
    u8 pad_00C[0x12C];
    CacheSlot slots[8];
} ResourceCache;

extern ResourceCache *g_resourceCache_020a04dc;
extern void *GetActorByIndex_02036810(u32 actorIndex);
extern void *Actor_SetUpdateCallback_02036a90(void *actor, void (*callback)(int, int));
extern void func_ov001_02086aec(int actor, int useCallback);
extern BOOL IsGameFlagSet_020645c8(u32 flagIndex);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void ResourceCache_Shutdown_02087190(void)
{
    ResourceCache *cache = g_resourceCache_020a04dc;
    CacheEntry *entry;
    int i;

    for (entry = cache->entries; entry != NULL; entry = entry->next) {
        void *actor;

        if (entry->ops->onRelease != NULL) {
            entry->ops->onRelease(entry);
        }
        actor = GetActorByIndex_02036810(entry->actorIndex);
        if (actor != NULL) {
            Actor_SetUpdateCallback_02036a90(actor, func_ov001_02086aec);
        }
    }
    if (!IsGameFlagSet_020645c8(0x3614)) {
        for (i = 0; i < 8; i++) {
            if (cache->slots[i].block != NULL) {
                NNSi_FndFreeFromDefaultHeap_0202a1c4(cache->slots[i].block);
                cache->slots[i].block = NULL;
            }
        }
    }
    cache->flags &= 0xF5;
}
