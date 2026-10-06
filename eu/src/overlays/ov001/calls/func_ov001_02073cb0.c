#include "nitro/types.h"

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MIi_CpuClearFast(u32 fillValue, void *dest, u32 size);
extern void MIi_CpuCopyFast(void *src, void *dest, u32 size);

void func_ov001_02073cb0(void **outBuffer, void *source, u32 size)
{
    void *buffer;

    buffer = NNSi_FndAllocFromDefaultHeap(size);
    *outBuffer = buffer;
    if (source == 0) {
        MIi_CpuClearFast(0, buffer, size);
        return;
    }
    MIi_CpuCopyFast(source, buffer, size);
}
