#include "nitro/types.h"

typedef struct ResourceListener ResourceListener;

typedef struct ResourceListenerVtbl {
    void (*onLoaded)(ResourceListener *listener, int slot, void *record, void *file);
} ResourceListenerVtbl;

struct ResourceListener {
    ResourceListener *next;
    ResourceListenerVtbl *vtbl;
};

typedef struct ResourceEntry {
    s16 id;
    u8 flags;
    u8 pad_03;
    void *record;
    void *file;
} ResourceEntry;

typedef struct ResourceLoader {
    u8 pad_00[5];
    u8 flags;
    u8 pad_06[2];
    ResourceListener *listeners;
    u8 pad_0c[4];
    ResourceEntry *entries[1];
} ResourceLoader;

extern ResourceLoader *data_ov001_020a04dc;
extern const int data_ov001_0209e3a0[];
extern u32 ObjectManager_GetFirstEntryParam_0207ee14(int id);
extern u32 ObjectManager_GetSecondEntryParam_0207ee48(int id);
extern void *RetainOrInitializeSharedRecord_0202c80c(u32 fileId, int flags);
extern void *func_0202c48c(u32 fileId, u32 heapId);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);

BOOL StepResourceSlotLoading_02086d00(void)
{
    ResourceLoader *loader = data_ov001_020a04dc;
    int i;
    int slot;
    ResourceEntry *entry;
    ResourceListener *listener;

    if (loader->flags & 4) {
        for (i = 0; i < 21; i++) {
            slot = data_ov001_0209e3a0[i];
            entry = loader->entries[slot];
            if (entry == NULL || (entry->flags & 4)) {
                continue;
            }
            if (!(entry->flags & 1)) {
                entry->record = RetainOrInitializeSharedRecord_0202c80c(ObjectManager_GetFirstEntryParam_0207ee14(entry->id), 4);
                entry->flags |= 1;
            }
            if (!(entry->flags & 2)) {
                entry->file = func_0202c48c(ObjectManager_GetSecondEntryParam_0207ee48(entry->id), 4);
                entry->flags |= 2;
            }
            if (loader->flags & 8) {
                for (listener = loader->listeners; listener != NULL; listener = listener->next) {
                    listener->vtbl->onLoaded(listener, slot, entry->record, entry->file);
                }
                NNSi_FndFreeFromDefaultHeap_0202a1c4(entry->file);
                entry->file = NULL;
                entry->flags |= 4;
                return FALSE;
            }
        }
    }
    loader->flags |= 4;
    return TRUE;
}
