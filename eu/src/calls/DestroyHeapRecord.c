#include "src/HeapRecord.h"

extern void NNS_FndDestroyExpHeap(void *heap);

void DestroyHeapRecord(HeapRecord *record)
{
    NNS_FndDestroyExpHeap(record->heap);
}
