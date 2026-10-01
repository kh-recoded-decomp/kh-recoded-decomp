#include "nitro/types.h"

typedef struct EffectEntry {
    u8 pad_00[0x34];
    void (*onDestroy)(struct EffectEntry *entry);
} EffectEntry;

typedef struct EffectList {
    EffectEntry **entries;
    s8 count;
} EffectList;

extern EffectList *data_ov001_020a04dc;

extern void func_ov001_02086298(EffectEntry *entry);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);

void DestroyAllEffectEntries_020868d0(BOOL notify)
{
    EffectList *list = data_ov001_020a04dc;
    int i;
    EffectEntry *entry;

    for (i = 0; i < list->count; i++) {
        entry = list->entries[i];
        if (entry != NULL) {
            if (notify && entry->onDestroy != NULL) {
                entry->onDestroy(entry);
            }
            func_ov001_02086298(entry);
            list->entries[i] = NULL;
        }
    }
    list->count = 0;
    if (list->entries != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(list->entries);
        list->entries = NULL;
    }
}
