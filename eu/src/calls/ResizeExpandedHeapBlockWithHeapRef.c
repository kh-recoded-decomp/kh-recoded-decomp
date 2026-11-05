#include "src/HeapRecord.h"

u32 ResizeExpandedHeapBlockWithHeapRef(HeapRecord *record, void *memoryBlock,
                                      u32 requestedBytes)
{
    return ResizeExpandedHeapBlock((struct NnsFndHeapHead *)record->heap,
                                    memoryBlock, requestedBytes);
}
