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

extern EntryCache *data_ov001_020a04dc;
extern void CacheEntry_SetActive_02087258(CacheEntry *entry, BOOL active);

void SetCachePaused_02087078(BOOL paused)
{
    CacheEntry *entry;

    if (paused) {
        data_ov001_020a04dc->flags |= 0x10;
    } else {
        data_ov001_020a04dc->flags &= ~0x10;
    }
    entry = data_ov001_020a04dc->head;
    if (entry != NULL) {
        BOOL active = TRUE;

        if (paused) {
            active = FALSE;
        }
        do {
            CacheEntry_SetActive_02087258(entry, active);
            entry = entry->next;
        } while (entry != NULL);
    }
}
