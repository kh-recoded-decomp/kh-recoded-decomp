#include "nitro/types.h"

extern void ReleaseResourceAndDetach(u8 *object);
extern void NNSi_FndFreeFromDefaultHeap(int allocationAddress);
extern s32 func_ov001_02063a38(void);
extern void UnlinkPendingNode(int object);

void func_ov018_020a2234(int object)
{
    if (*(int *)(object + 0x48) != 0) {
        ReleaseResourceAndDetach((u8 *)*(int *)(object + 0x48));
        NNSi_FndFreeFromDefaultHeap(*(int *)(object + 0x48));
        *(int *)(object + 0x48) = 0;
    }
    if (func_ov001_02063a38() == 7) {
        UnlinkPendingNode(object + 0xa8);
    }
}
