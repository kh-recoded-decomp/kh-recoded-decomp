#ifndef KH_RECODED_HEAP_RECORD_H
#define KH_RECODED_HEAP_RECORD_H

#include "nitro/types.h"

/* An expanded heap handle followed by its default-allocation adapter. */
typedef struct HeapRecord {
    void *heap;
    u32 allocator[4];
} HeapRecord;

extern HeapRecord *CreateHeapRecord(HeapRecord *record, void *memory, u32 size);
extern void DestroyHeapRecord(HeapRecord *record);
extern void ResetHeapRecord(HeapRecord *record);

typedef char HeapRecordSizeCheck[sizeof(HeapRecord) == 0x14 ? 1 : -1];

#endif
