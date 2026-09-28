#include "nitro/types.h"
#include "nitro/mi.h"
#include "nitro/os.h"
#include "nnsys/fnd.h"

extern void OS_FreeToHeap(OSArenaId id, OSHeapHandle heap, void * ptr);

void AllocatorFreeForSDKHeap_020136e0 (NNSFndAllocator * pAllocator, void * memBlock)
{
    OSHeapHandle const heap = (int)pAllocator->pHeap;
    OSArenaId const id = (OSArenaId)pAllocator->heapParam1;
    OS_FreeToHeap(id, heap, memBlock);
}
