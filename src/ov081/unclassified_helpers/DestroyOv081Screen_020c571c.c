#include "nitro/types.h"

typedef struct Ov081State {
    void *bgBuffer;
    void *objBuffer;
    void *fileA;
    u8 pad_0C[8];
    void *fileB;
} Ov081State;

extern Ov081State *data_020c5d80;
extern void *func_ov039_020bc1bc(void);
extern void FreeEntryLists_020c523c(Ov081State *state);
extern void DestroyAllContainerElements_020b900c(void *container);
extern void ReleaseIfMarked_020b903c(void *owner);
extern void FreePointerIfSet_020ba294(void **ptr);
extern int ZeroHalfThenFree_0202cd78(void *ptr);
extern void func_ov039_020be6a0(void);
extern void NNS_GfdResetFrmTexVramState_0201391c(void);
extern void func_02013d74(void);
extern void SetStateFlagBits_020bc688(u8 clearMask, u8 setBits);

void DestroyOv081Screen_020c571c(Ov081State *state)
{
    void *container = func_ov039_020bc1bc();

    FreeEntryLists_020c523c(state);
    DestroyAllContainerElements_020b900c(container);
    ReleaseIfMarked_020b903c(container);
    FreePointerIfSet_020ba294(&state->fileA);
    FreePointerIfSet_020ba294(&state->fileB);
    ZeroHalfThenFree_0202cd78(state->bgBuffer);
    ZeroHalfThenFree_0202cd78(state->objBuffer);
    func_ov039_020be6a0();
    *(vu32 *)0x04000014 = 0;
    *(vu32 *)0x04000018 = 0;
    *(vu32 *)0x0400001c = 0;
    *(vu32 *)0x04000000 &= ~0xe000;
    NNS_GfdResetFrmTexVramState_0201391c();
    func_02013d74();
    SetStateFlagBits_020bc688(1, 1);
    data_020c5d80 = NULL;
}
