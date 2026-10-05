#include "nitro/types.h"

typedef struct {
    u32 unk_00;
    u8 resource[0x138];
} ResourceItem;

typedef struct {
    ResourceItem *items;
    u8 count;
} ResourceList;

typedef struct {
    ResourceList *lists;
    u8 count;
} ResourceGroup;

typedef struct {
    u8 pad_000[0x354];
    u32 heapHandle;
    ResourceList *lists[0x3e];
    ResourceGroup *groups[0x1b];
} Work;

extern int data_ov035_020bc4e0;
extern void ReleaseResourceAndDetach(void *resource);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void ZeroHalfThenFree(u32 value);

void FreeResourceLists(void) {
    ResourceGroup *group;
    ResourceList *list;
    Work *work;
    int i;
    int j;
    int k;

    work = *(Work **)(data_ov035_020bc4e0 + 0xb8);
    for (i = 0; i < 0x3e; i++) {
        list = work->lists[i];
        if (list != NULL) {
            for (j = 0; j < list->count; j++) {
                ReleaseResourceAndDetach(list->items[j].resource);
            }
            NNSi_FndFreeFromDefaultHeap(list->items);
            NNSi_FndFreeFromDefaultHeap(list);
            work->lists[i] = NULL;
        }
    }
    ZeroHalfThenFree(work->heapHandle);
    for (i = 0; i < 0x1b; i++) {
        group = work->groups[i];
        if (group != NULL) {
            for (j = 0; j < group->count; j++) {
                list = &group->lists[j];
                for (k = 0; k < list->count; k++) {
                    ReleaseResourceAndDetach(list->items[k].resource);
                }
                NNSi_FndFreeFromDefaultHeap(list->items);
            }
            NNSi_FndFreeFromDefaultHeap(group->lists);
            NNSi_FndFreeFromDefaultHeap(group);
            work->groups[i] = NULL;
        }
    }
}
