#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void FreePointerIfSet(void *obj);

void func_ov001_0207ab68(s32 panel)
{
    NNSi_FndFreeFromDefaultHeap((void *)*(u32 *)(panel + 0x1c));
    FreePointerIfSet((void *)(panel + 0x20));
}
