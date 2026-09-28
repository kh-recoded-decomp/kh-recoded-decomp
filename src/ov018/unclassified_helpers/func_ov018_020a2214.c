#include "nitro/types.h"

extern void ReleaseResourceAndDetach_0202eee8(u8 *object);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(int allocationAddress);
extern s32 func_ov001_02063a38(void);
extern void func_ov031_020bc618(int object);

void func_ov018_020a2214(int object)
{
    if (*(int *)(object + 0x48) != 0) {
        ReleaseResourceAndDetach_0202eee8((u8 *)*(int *)(object + 0x48));
        NNSi_FndFreeFromDefaultHeap_0202a1c4(*(int *)(object + 0x48));
        *(int *)(object + 0x48) = 0;
    }
    if (func_ov001_02063a38() == 7) {
        func_ov031_020bc618(object + 0xa8);
    }
}
