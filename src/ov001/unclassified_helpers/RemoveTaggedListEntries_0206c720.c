#include "nitro/types.h"

typedef struct NNSFndList {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;

typedef struct TaggedEntry {
    int tag;
} TaggedEntry;

typedef struct TaggedEntryPool {
    u32 unk_00;
    NNSFndList list;
} TaggedEntryPool;

extern TaggedEntryPool data_ov001_020a0488;
extern void *NNS_FndGetNextListObject_02012a38(void *list, void *obj);
extern void RemoveIntrusiveListObject_020129d8(NNSFndList *list, void *object);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);

void RemoveTaggedListEntries_0206c720(int tag)
{
    TaggedEntryPool *pool = &data_ov001_020a0488;
    TaggedEntry *entry = NNS_FndGetNextListObject_02012a38(&pool->list, NULL);

    while (entry != NULL) {
        TaggedEntry *next = NNS_FndGetNextListObject_02012a38(&pool->list, entry);

        if (entry->tag == tag || tag == 0) {
            RemoveIntrusiveListObject_020129d8(&pool->list, entry);
            NNSi_FndFreeFromDefaultHeap_0202a1c4(entry);
            if (tag != 0) {
                return;
            }
        }
        entry = next;
    }
}
