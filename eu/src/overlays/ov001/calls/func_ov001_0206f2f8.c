#include "nitro/types.h"

extern void DestroyFndObjectList(u32 context);
extern void NNSi_FndFreeFromDefaultHeap(u32 handle);
extern void FreePointerIfSet(u32 context);

void func_ov001_0206f2f8(u32 context)
{
    FreePointerIfSet(context + 0x50c);
    NNSi_FndFreeFromDefaultHeap(*(u32 *)(context + 0x5c0));
    *(u32 *)(context + 0x5c0) = 0;
    DestroyFndObjectList(context + 0x584);
}
