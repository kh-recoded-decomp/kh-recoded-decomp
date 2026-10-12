#include "src/overlays/ov001/StageManagerMemory.h"

extern void RemoveTaggedListEntries(void (*callback)(void));
extern void DrawVisibleStageQuads(void);
extern void ShutdownStageManager(void);
extern HeapRecord *Heap_GetCurrent(void);
extern HeapRecord *SetDefaultHeap(HeapRecord *heap);
extern void FreeDefaultHeapBlockIfSet(void *pool);
extern void ZeroHalfThenFree(void *file);
extern void NNSi_FndFreeFromDefaultHeap(void *memory);

static inline void PushStageHeap(void)
{
    StageManagerMemory *manager = gStageManager;
    if (manager != NULL && &manager->heapScope != NULL && manager->heapScope.savedHeap == NULL) {
        manager->heapScope.savedHeap = Heap_GetCurrent();
        SetDefaultHeap(manager->heapScope.blocks[0].activeRecord);
    }
}

static inline void PopStageHeap(void)
{
    StageManagerMemory *manager = gStageManager;
    if (manager != NULL && &manager->heapScope != NULL && manager->heapScope.savedHeap != NULL) {
        SetDefaultHeap(manager->heapScope.savedHeap);
        manager->heapScope.savedHeap = NULL;
    }
}

void DestroyStageManager(void)
{
    StageManagerMemory *manager = gStageManager;
    s32 i;
    if (manager == NULL) {
        return;
    }
    if (manager->flags & 0x80000000) {
        RemoveTaggedListEntries(DrawVisibleStageQuads);
        manager->flags &= 0x7fffffff;
    }
    /* Release live actors before discarding their backing pools. */
    ShutdownStageManager();
    PushStageHeap();
    FreeDefaultHeapBlockIfSet(manager->eventPool);
    FreeDefaultHeapBlockIfSet(manager->pools[0]);
    FreeDefaultHeapBlockIfSet(manager->pools[1]);
    FreeDefaultHeapBlockIfSet(manager->pools[2]);
    FreeDefaultHeapBlockIfSet(manager->pools[4]);
    FreeDefaultHeapBlockIfSet(manager->pools[5]);
    FreeDefaultHeapBlockIfSet(manager->pools[6]);
    FreeDefaultHeapBlockIfSet(manager->pools[7]);
    PopStageHeap();
    if (manager->messageA != NULL) {
        ZeroHalfThenFree(manager->messageA);
        manager->messageA = NULL;
    }
    if (manager->messageB != NULL) {
        ZeroHalfThenFree(manager->messageB);
        manager->messageB = NULL;
    }
    if (manager->messageC != NULL) {
        ZeroHalfThenFree(manager->messageC);
        manager->messageC = NULL;
    }
    if (manager->messageD != NULL) {
        ZeroHalfThenFree(manager->messageD);
        manager->messageD = NULL;
    }
    if (gStageManager->events != NULL) {
        NNSi_FndFreeFromDefaultHeap(gStageManager->events);
        gStageManager->events = NULL;
    }
    if (gStageManager->links != NULL) {
        NNSi_FndFreeFromDefaultHeap(gStageManager->links);
        gStageManager->links = NULL;
    }
    if (gStageManager->linkFlags != NULL) {
        NNSi_FndFreeFromDefaultHeap(gStageManager->linkFlags);
        gStageManager->linkFlags = NULL;
    }
    /* Each expanded heap must be finalized before its memory is freed. */
    for (i = 0; i < 2; i++) {
        if (manager->heapScope.blocks[i].activeRecord != NULL) {
            DestroyHeapRecord(manager->heapScope.blocks[i].activeRecord);
            manager->heapScope.blocks[i].activeRecord = NULL;
        }
        if (manager->heapScope.blocks[i].memory != NULL) {
            NNSi_FndFreeFromDefaultHeap(manager->heapScope.blocks[i].memory);
            manager->heapScope.blocks[i].memory = NULL;
        }
    }
    gStageManager = NULL;
}
