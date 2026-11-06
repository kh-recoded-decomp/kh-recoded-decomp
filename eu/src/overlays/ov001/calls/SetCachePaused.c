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

extern EntryCache *gFieldEntryPoolManager;
extern void CacheEntry_SetActive(CacheEntry *entry, BOOL active);

void SetCachePaused(BOOL paused)
{
    CacheEntry *entry;

    if (paused) {
        gFieldEntryPoolManager->flags |= 0x10;
    } else {
        gFieldEntryPoolManager->flags &= ~0x10;
    }
    entry = gFieldEntryPoolManager->head;
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
