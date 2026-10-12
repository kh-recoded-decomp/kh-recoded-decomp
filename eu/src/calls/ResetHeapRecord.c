#include "src/HeapRecord.h"

/* Only the end of the NitroSystem heap header is needed to recover its extent. */
typedef struct HeapExtent {
    u8 reserved00[0x1c];
    u8 *end;
} HeapExtent;

extern void NNS_FndDestroyExpHeap(void *heap);
extern void *NNS_FndCreateExpHeapEx(void *memory, u32 size, u16 flags);
extern void NNS_FndInitAllocatorForExpHeap(void *allocator, void *heap, s32 alignment);

void ResetHeapRecord(HeapRecord *record)
{
    u8 *start = record->heap;
    s32 size = ((HeapExtent *)start)->end - start;
    NNS_FndDestroyExpHeap(start);
    void *heap = NNS_FndCreateExpHeapEx(start, size, 1);
    record->heap = heap;
    NNS_FndInitAllocatorForExpHeap(record->allocator, heap, 4);
}
