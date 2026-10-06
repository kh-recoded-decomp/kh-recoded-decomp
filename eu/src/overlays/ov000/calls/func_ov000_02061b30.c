#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x50];
    s32 mode;
} Heap;

extern Heap *NNSi_FndGetCurrentRootHeap(void);
extern void SetPendingScene(int mode, int param2);
extern void InitDifficultyConfigBlock(int flag);

void func_ov000_02061b30(void)
{
    Heap *heap = NNSi_FndGetCurrentRootHeap();

    if (heap->mode == 2) {
        SetPendingScene(3, 0);
        return;
    }
    InitDifficultyConfigBlock(1);
    SetPendingScene(2, 0);
}
