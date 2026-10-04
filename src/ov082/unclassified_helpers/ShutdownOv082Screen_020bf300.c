#include "nitro/types.h"

typedef struct Ov082State {
    u8 pad_0000[0x36d4];
    u8 objectList[0x38];
    void *bufferA;
    void *bufferB;
} Ov082State;

extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void *func_ov039_020bc1a4(void);
extern void SweepElements_020b831c(void *manager);
extern void *func_ov039_020bc1cc(void);
extern void DestroyAllContainerElements_020b900c(void *container);
extern void ReleaseIfMarked_020b903c(void *container);
extern void DestroyFndObjectList_020014f0(void *list);

void ShutdownOv082Screen_020bf300(Ov082State *state)
{
    NNSi_FndFreeFromDefaultHeap_0202a1c4(state->bufferA);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(state->bufferB);
    SweepElements_020b831c(func_ov039_020bc1a4());
    DestroyAllContainerElements_020b900c(func_ov039_020bc1cc());
    ReleaseIfMarked_020b903c(func_ov039_020bc1cc());
    DestroyFndObjectList_020014f0(state->objectList);
    *(vu32 *)0x04001014 = 0;
    *(vu32 *)0x04001018 = 0;
    *(vu32 *)0x0400101c = 0;
    *(vu32 *)0x04001000 &= ~0xe000;
}
