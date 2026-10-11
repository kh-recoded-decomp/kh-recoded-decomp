#include "nitro/types.h"

typedef struct NNSFndAllocator NNSFndAllocator;
typedef struct HeapAllocatorOps {
    void *(*allocate)(NNSFndAllocator *allocator, u32 size);
    void (*free)(NNSFndAllocator *allocator, void *memory);
} HeapAllocatorOps;

extern void *AllocatorAllocForUnitHeap(NNSFndAllocator *allocator, u32 size);
extern void AllocatorFreeForUnitHeap(NNSFndAllocator *allocator, void *memory);
extern void *AllocatorAllocForFrmHeap(NNSFndAllocator *allocator, u32 size);
extern void AllocatorFreeForFrmHeap(NNSFndAllocator *allocator, void *memory);

const HeapAllocatorOps sAllocatorFuncForUnitHeap = {
    AllocatorAllocForUnitHeap, AllocatorFreeForUnitHeap
};
/* Frame-heap blocks are released together; its individual free callback is a no-op. */
const HeapAllocatorOps sAllocatorFuncForFrmHeap = {
    AllocatorAllocForFrmHeap, AllocatorFreeForFrmHeap
};
