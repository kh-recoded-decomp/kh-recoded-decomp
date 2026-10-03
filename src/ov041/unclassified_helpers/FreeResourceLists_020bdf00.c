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
extern void ReleaseResourceAndDetach_0202eee8(void *resource);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void ZeroHalfThenFree_0202cd78(u32 value);

void FreeResourceLists_020bdf00(void) {
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
                ReleaseResourceAndDetach_0202eee8(list->items[j].resource);
            }
            NNSi_FndFreeFromDefaultHeap_0202a1c4(list->items);
            NNSi_FndFreeFromDefaultHeap_0202a1c4(list);
            work->lists[i] = NULL;
        }
    }
    ZeroHalfThenFree_0202cd78(work->heapHandle);
    for (i = 0; i < 0x1b; i++) {
        group = work->groups[i];
        if (group != NULL) {
            for (j = 0; j < group->count; j++) {
                list = &group->lists[j];
                for (k = 0; k < list->count; k++) {
                    ReleaseResourceAndDetach_0202eee8(list->items[k].resource);
                }
                NNSi_FndFreeFromDefaultHeap_0202a1c4(list->items);
            }
            NNSi_FndFreeFromDefaultHeap_0202a1c4(group->lists);
            NNSi_FndFreeFromDefaultHeap_0202a1c4(group);
            work->groups[i] = NULL;
        }
    }
}
