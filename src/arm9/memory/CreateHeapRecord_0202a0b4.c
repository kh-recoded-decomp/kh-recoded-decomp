#include "nitro/types.h"

struct NNSiFndHeapHead;

typedef struct HeapRecord {
    struct NNSiFndHeapHead *heap;
    u32 info[4];
} HeapRecord;

extern struct NNSiFndHeapHead *CreateExpandedHeap_020130f0(void *startAddress, u32 size, u16 optionFlag);
extern void func_02013740(void *dest, struct NNSiFndHeapHead *heap, int count);

HeapRecord *CreateHeapRecord_0202a0b4(HeapRecord *record, void *startAddress, u32 size) {
    struct NNSiFndHeapHead *heap = CreateExpandedHeap_020130f0(startAddress, size, 1);

    if (heap != NULL) {
        record->heap = heap;
        func_02013740(record->info, heap, 4);
        return record;
    }
    return NULL;
}
