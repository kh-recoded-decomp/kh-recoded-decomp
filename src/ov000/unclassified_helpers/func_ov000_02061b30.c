#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x50];
    s32 mode;
} Heap;

extern Heap *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void func_02025644(int mode, int param2);
extern void func_02027558(int flag);

void func_ov000_02061b30(void)
{
    Heap *heap = NNSi_FndGetCurrentRootHeap_0202a764();

    if (heap->mode == 2) {
        func_02025644(3, 0);
        return;
    }
    func_02027558(1);
    func_02025644(2, 0);
}
