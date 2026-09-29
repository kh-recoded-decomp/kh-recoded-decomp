#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x34];
    void *heap;
    void *savedHeap;
} HeapScope;

typedef struct {
    u8 pad_00[0x18e14];
    HeapScope heapScope;
} StageManager;

extern StageManager *g_stageManager_020a0508;
extern void *func_0202a158(void);
extern void *SetDefaultHeap_0202a134(void *heap);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void FreeFromStageHeap_0209cf68(void *block)
{
    StageManager *manager;

    manager = g_stageManager_020a0508;
    if (manager != NULL && &manager->heapScope != NULL && manager->heapScope.savedHeap == NULL) {
        manager->heapScope.savedHeap = func_0202a158();
        SetDefaultHeap_0202a134(manager->heapScope.heap);
    }
    if (block != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(block);
    }
    manager = g_stageManager_020a0508;
    if (manager != NULL && &manager->heapScope != NULL && manager->heapScope.savedHeap != NULL) {
        SetDefaultHeap_0202a134(manager->heapScope.savedHeap);
        manager->heapScope.savedHeap = NULL;
    }
}
