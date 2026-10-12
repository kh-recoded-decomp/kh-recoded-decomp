#include "src/overlays/ov041/StageResources.h"

extern void ReleaseResourceAndDetach(void *resource);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void ZeroHalfThenFree(u32 handle);

void FreeResourceLists(void)
{
    StageResourceGroup *group;
    StageResourceList *list;
    StageResourceWork *work;
    int i;
    int j;
    int k;

    work = gMovieContextState->stageWork;
    for (i = 0; i < 0x3e; ++i) {
        list = work->lists[i];
        if (list != NULL) {
            for (j = 0; j < list->count; ++j) {
                ReleaseResourceAndDetach(list->items[j].model);
            }
            NNSi_FndFreeFromDefaultHeap(list->items);
            NNSi_FndFreeFromDefaultHeap(list);
            work->lists[i] = NULL;
        }
    }
    ZeroHalfThenFree((u32)work->messages);
    for (i = 0; i < 0x1b; ++i) {
        group = work->groups[i];
        if (group != NULL) {
            for (j = 0; j < group->count; ++j) {
                list = &group->lists[j];
                for (k = 0; k < list->count; ++k) {
                    ReleaseResourceAndDetach(list->items[k].model);
                }
                NNSi_FndFreeFromDefaultHeap(list->items);
            }
            NNSi_FndFreeFromDefaultHeap(group->lists);
            NNSi_FndFreeFromDefaultHeap(group);
            work->groups[i] = NULL;
        }
    }
}
