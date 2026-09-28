#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x1a0];
    void *slotA;
    u8 pad_1a4[0x21c - 0x1a4];
    void *slotB;
    void *slotC;
} Heap;

extern void func_0202a1c4(void *slot);

void ReleaseHeapExtensions_02061818(Heap *heap)
{
    func_0202a1c4(heap->slotA);
    func_0202a1c4(heap->slotB);
    func_0202a1c4(heap->slotC);
}
