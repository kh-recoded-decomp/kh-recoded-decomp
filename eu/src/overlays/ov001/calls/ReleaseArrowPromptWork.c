#include "nitro/types.h"

extern u32 gArrowPromptWork;
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void ReleaseArrowPromptWork(void)
{
    u8 *context;

    context = (u8 *)gArrowPromptWork;
    NNSi_FndFreeFromDefaultHeap(*(void **)(gArrowPromptWork + 0x30));
    NNSi_FndFreeFromDefaultHeap(*(void **)(context + 0x34));
    NNSi_FndFreeFromDefaultHeap(*(void **)(context + 0x38));
    gArrowPromptWork = 0;
}
