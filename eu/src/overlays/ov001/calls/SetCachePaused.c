#include "nitro/types.h"

typedef struct CacheEntry {
    struct CacheEntry *next;
} CacheEntry;

typedef struct EntryCache {
    u8 pad_00[5];
    u8 flags;
    u8 pad_06[2];
    CacheEntry *head;
} EntryCache;

extern EntryCache *data_ov001_020a04fc;
extern void CacheEntry_SetActive(CacheEntry *entry, BOOL active);

void SetCachePaused(BOOL paused)
{
    CacheEntry *entry;

    if (paused) {
        data_ov001_020a04fc->flags |= 0x10;
    } else {
        data_ov001_020a04fc->flags &= ~0x10;
    }
    entry = data_ov001_020a04fc->head;
    if (entry != NULL) {
        BOOL active = TRUE;

        if (paused) {
            active = FALSE;
        }
        do {
            CacheEntry_SetActive(entry, active);
            entry = entry->next;
        } while (entry != NULL);
    }
}
