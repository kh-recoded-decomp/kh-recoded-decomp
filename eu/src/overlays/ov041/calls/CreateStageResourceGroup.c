#include "src/overlays/ov041/StageResources.h"

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MIi_CpuClearFast(u32 value, void *destination, u32 bytes);
extern void *SND_RegisterSeq(u32 key, int kind);
extern void *func_0202c4a0(u32 key, int kind);
extern void func_0202edb0(void *model, void *record, void *block, int kind);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

/* The cursor visits two resource keys, then returns to its start. */
#define RESOURCE_KEY(c, operation) \
    ((((u32)(c)->header + 0x8000) & 0xfffffc) << 7 | 0x80000000 | \
     ((c)->cursor operation & 0x1ff))

void CreateStageResourceGroup(int category, StageResourceContainer *container)
{
    StageResourceGroup *group;
    StageWork *work = gMovieContextState->stageWork;
    int i;
    int j;

    if (work->groups[category] != NULL ||
        (container->header->recordCount - container->cursor) / 2 == 0) {
        return;
    }
    group = work->groups[category] = NNSi_FndAllocFromDefaultHeap(sizeof(*group));
    MIi_CpuClearFast(0, group, sizeof(*group));
    group->count = (container->header->recordCount - container->cursor) / 2;
    group->lists = NNSi_FndAllocFromDefaultHeap(group->count * sizeof(StageResourceList));
    MIi_CpuClearFast(0, group->lists, group->count * sizeof(StageResourceList));

    for (i = 0; i < group->count; ++i) {
        StageResourceList *list = &group->lists[i];
        list->count = 1;
        switch (category) {
        case 22:
            if (i == 1) {
                list->count = work->primaryCount;
            }
            break;
        case 23:
            list->count = 3;
            break;
        case 26:
            list->count = 4;
            break;
        case 25:
            if (i == 2) {
                list->count = 5;
            }
            break;
        case 24:
            if (i == 2) {
                list->count = 3;
            }
            break;
        case 21:
            if (i == 0) {
                list->count = 10;
            }
            break;
        }
        list->items = NNSi_FndAllocFromDefaultHeap(list->count * sizeof(StageResourceItem));
        MIi_CpuClearFast(0, list->items, list->count * sizeof(StageResourceItem));
    }
    for (i = 0; i < group->count; ++i) {
        StageResourceList *list = &group->lists[i];
        for (j = 0; j < list->count; ++j) {
            void *record = SND_RegisterSeq(RESOURCE_KEY(container, ++), 0x12);
            void *block = func_0202c4a0(RESOURCE_KEY(container, --), 0xf);
            func_0202edb0(&list->items[j].model, record, block, 0x12);
            NNSi_FndFreeFromDefaultHeap(block);
        }
        container->cursor += 2;
    }
}
