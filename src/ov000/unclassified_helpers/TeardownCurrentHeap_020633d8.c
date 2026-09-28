#include "nitro/types.h"

typedef struct {
    u32 slotA;
    u32 slotB;
    u8 pad_08[0x6000 + 0x68c - 8];
    u32 slotC;
} Heap;

extern Heap *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void ReleaseHeapExtensions_02061818(Heap *heap);
extern void ZeroHalfThenFree_0202cd78(u32 value);
extern u16 func_0202b788(void);
extern void func_02027360(int opcode, int channel, u16 value);
extern void func_02027258(void);

void TeardownCurrentHeap_020633d8(void)
{
    Heap *heap = NNSi_FndGetCurrentRootHeap_0202a764();
    u16 value;

    ReleaseHeapExtensions_02061818(heap);
    ZeroHalfThenFree_0202cd78(heap->slotA);
    ZeroHalfThenFree_0202cd78(heap->slotB);
    ZeroHalfThenFree_0202cd78(heap->slotC);
    value = func_0202b788();
    func_02027360(0x1a02, 3, value);
    func_02027258();
}
