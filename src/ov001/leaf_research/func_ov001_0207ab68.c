#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void func_ov027_020ba294(void *obj);

void func_ov001_0207ab68(s32 panel)
{
    NNSi_FndFreeFromDefaultHeap_0202a1c4((void *)*(u32 *)(panel + 0x1c));
    func_ov027_020ba294((void *)(panel + 0x20));
}
