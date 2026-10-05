#include "nitro/types.h"

typedef struct StageHeap {
    u8 pad_00[0x34];
    void *heap;
    void *savedHeap;
} StageHeap;

typedef struct StageData {
    u8 pad_00000[0x18e14];
    StageHeap heapContext;
} StageData;

extern StageData *data_ov001_020a0508;
extern void *func_0202a158(void);
extern void *SetDefaultHeap_0202a134(void *heap);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);

static inline void PushStageHeap(void)
{
    StageData *stage = data_ov001_020a0508;

    if (stage != NULL && &stage->heapContext != NULL && stage->heapContext.savedHeap == NULL) {
        stage->heapContext.savedHeap = func_0202a158();
        SetDefaultHeap_0202a134(stage->heapContext.heap);
    }
}

static inline void PopStageHeap(void)
{
    StageData *stage = data_ov001_020a0508;

    if (stage != NULL && &stage->heapContext != NULL && stage->heapContext.savedHeap != NULL) {
        SetDefaultHeap_0202a134(stage->heapContext.savedHeap);
        stage->heapContext.savedHeap = NULL;
    }
}

void *AllocFromStageHeap_0209cee4(u32 size)
{
    u32 alignedSize;
    void *block;

    if (size == 0) {
        size = 0x200;
    }
    PushStageHeap();
    alignedSize = size & ~0x1ff;
    if (size & 0x1ff) {
        alignedSize += 0x200;
    }
    block = NNSi_FndAllocFromDefaultHeap_0202a178(alignedSize);
    PopStageHeap();
    if (block == NULL) {
        return NULL;
    }
    return block;
}
