#include "nitro/types.h"

typedef struct CacheSlot {
    u32 key;
    void *block;
} CacheSlot;

typedef struct ResourceCache {
    u8 pad_000[0x138];
    CacheSlot slots[8];
    u8 extraSlots[0x40];
} ResourceCache;

extern ResourceCache *g_resourceCache_020a04dc;
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void func_01ff86fc(u32 value, void *destination, u32 size);

void ResourceCache_FreeAll_02086df0(void)
{
    int i;
    ResourceCache *cache = g_resourceCache_020a04dc;

    for (i = 0; i < 8; i++) {
        if (cache->slots[i].block != NULL) {
            NNSi_FndFreeFromDefaultHeap_0202a1c4(cache->slots[i].block);
        }
    }
    func_01ff86fc(0, cache->slots, sizeof(cache->slots));
    func_01ff86fc(0, cache->extraSlots, sizeof(cache->extraSlots));
}
