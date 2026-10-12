#include "src/HeapRecord.h"

extern void *NNS_FndCreateExpHeapEx(void *memory, u32 size, u16 flags);
extern void NNS_FndInitAllocatorForExpHeap(void *allocator, void *heap, s32 alignment);

HeapRecord *CreateHeapRecord(HeapRecord *record, void *memory, u32 size)
{
    void *heap = NNS_FndCreateExpHeapEx(memory, size, 1);

    if (heap != NULL) {
        record->heap = heap;
        NNS_FndInitAllocatorForExpHeap(record->allocator, heap, 4);
        return record;
    }
    return NULL;
}
