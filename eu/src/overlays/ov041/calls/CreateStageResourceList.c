#include "src/overlays/ov041/StageResources.h"

#define RetainOrInitializeSharedRecord SND_RegisterSeq
#define LoadResourceBlock func_0202c4a0
#define InitStageResourceModel func_0202edb0

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MIi_CpuClearFast(u32 value, void *destination, u32 bytes);
extern void *RetainOrInitializeSharedRecord(u32 key, int kind);
extern void *LoadResourceBlock(u32 key, int kind);
extern void InitStageResourceModel(void *model, void *record, void *block, int kind);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

static inline StageResourceList *ReadStageResourceListSlot(StageResourceWork *work, int index)
{
    /* Keep the indexed read separate from the writable slot used after allocation. */
    u8 *slot = (u8 *)work + index * sizeof(StageResourceList *);
    return *(StageResourceList **)(slot + (u32)&((StageResourceWork *)0)->lists);
}

void CreateStageResourceList(int index, int count, void *archive, u8 modelIndex, u8 blockIndex)
{
    StageResourceWork *work = gMovieContextState->stageWork;
    StageResourceList *list;
    StageResourceItem *items;
    int i;

    if (ReadStageResourceListSlot(work, index) != NULL) {
        return;
    }
    StageResourceList **slot = &work->lists[index];
    list = *slot = NNSi_FndAllocFromDefaultHeap(sizeof(*list));
    MIi_CpuClearFast(0, list, sizeof(*list));
    list->count = count;
    items = list->items = NNSi_FndAllocFromDefaultHeap(list->count * sizeof(*items));
    MIi_CpuClearFast(0, items, list->count * sizeof(*items));
    i = 0;
    if (i < list->count) {
        u32 archiveKey = ((((u32)archive + 0x8000) & 0xfffffc) << 7) | 0x80000000;
        u32 modelKey = archiveKey | (modelIndex & 0x1ff);
        u32 blockKey = archiveKey | (blockIndex & 0x1ff);
        do {
            void *record = RetainOrInitializeSharedRecord(modelKey, 0x12);
            void *block = LoadResourceBlock(blockKey, 0xf);
            InitStageResourceModel(items[i].model, record, block, 0x12);
            NNSi_FndFreeFromDefaultHeap(block);
            i++;
        } while (i < list->count);
    }
}
